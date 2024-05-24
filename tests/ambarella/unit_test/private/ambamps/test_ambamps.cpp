/*******************************************************************************
 * test_ambamps.cpp
 *
 * History:
 *    2022/9/19 - [Monica Yang] created
 *
 * Copyright [2022] Ambarella International LP.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
******************************************************************************/


#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <unistd.h>
#include <getopt.h>

#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/objdetect.hpp"

#include "cavalry_mem.h"
#include "nnctrl.h"

#include "ambamps_priv.hpp"

using namespace cv;

#define AMBAMPS_DEBUG		(0)

#define NO_ARG		0
#define HAS_ARG		1

#define AMBAMPS_COLOR_NUM	13
static const Scalar AMBAMPS_COLORS[] = {
	CV_RGB(255, 255, 255),
	CV_RGB(0, 0, 255),
	CV_RGB(0, 255, 0),
	CV_RGB(255, 0, 0),
	CV_RGB(255, 255, 0),
	CV_RGB(255, 0, 255),
	CV_RGB(0, 255, 255),
	CV_RGB(255, 128, 128),
	CV_RGB(128, 255, 128),
	CV_RGB(128, 128, 255),
	CV_RGB(128, 255, 255),
	CV_RGB(255, 128, 255),
	CV_RGB(255, 255, 128),
};

static int store_file(const char *file_name, uint8_t *virt_addr, uint32_t size)
{
	FILE *out = NULL;
	int rval = 0;

	do {
		if ((out = fopen(file_name, "w+b")) == NULL) {
			perror(file_name);
			rval = -1;
			break;
		}
		if (fwrite(virt_addr, 1, size, out) != size) {
			perror(file_name);
			rval = -1;
			break;
		}
	} while (0);

	if (out) {
		fclose(out);
		out = NULL;
	}

	return rval;
}

static int load_file(const char *file_name, uint8_t *virt_addr, uint32_t size)
{
	FILE *in = NULL;
	int rval = 0;

	do {
		if ((in = fopen(file_name, "rb")) == NULL) {
			perror(file_name);
			rval = -1;
			break;
		}
		if (fread(virt_addr, 1, size, in) != size) {
			perror("fread input file");
			rval = -1;
			break;
		}
	} while (0);

	if (in) {
		fclose(in);
		in = NULL;
	}

	return rval;
}

static int ambamps_graph_io_cfg(graph_ctx_t *pctx)
{
	int rval = 0;
	const char *grf_io_name = nullptr, *nd_io_name = nullptr;
	node_match_t *node = nullptr;

	for (uint32_t i = 0; i < pctx->in_num; ++i) {
		grf_io_name = pctx->in_pair[i].port_name;
		for (int j = 0; j < pctx->node_num; ++j) {
			node = &pctx->node_list[j];
			for (uint32_t k = 0; k < node->in_num; ++k) {
				nd_io_name = node->in_pair[k].port_name;
				if (is_cstring_match(grf_io_name, nd_io_name)) {
					pctx->in_pair[i].virt_addr = node->in_pair[k].virt_addr;
					pctx->in_pair[i].dram_addr = node->in_pair[k].dram_addr;
					pctx->in_pair[i].size = node->in_pair[k].size;
					pctx->in_pair[i].dim = node->in_pair[k].dim;
					pctx->in_pair[i].data_fmt = node->in_pair[k].data_fmt;
				}
			}
		}
	}

	for (uint32_t i = 0; i < pctx->out_num; ++i) {
		grf_io_name = pctx->out_pair[i].port_name;
		for (int j = 0; j < pctx->node_num; ++j) {
			node = &pctx->node_list[j];
			for (uint32_t k = 0; k < node->out_num; ++k) {
				nd_io_name = node->out_pair[k].port_name;
				if (is_cstring_match(grf_io_name, nd_io_name)) {
					pctx->out_pair[i].virt_addr = node->out_pair[k].virt_addr;
					pctx->out_pair[i].dram_addr = node->out_pair[k].dram_addr;
					pctx->out_pair[i].size = node->out_pair[k].size;
					pctx->out_pair[i].dim = node->out_pair[k].dim;
					pctx->out_pair[i].data_fmt = node->out_pair[k].data_fmt;
				}
			}
		}
	}

	/*for (uint32_t i = 0; i < pctx->in_num; ++i) {
		ambamps_log("graph input: %u [%s] dim: (%u, %u, %u, %u), pitch: %u, "
			"data_fmt: (%d, %d, %d, %d), "
			"size: %u, virt_addr 0x%p\n",
			i, pctx->in_pair[i].port_name,
			pctx->in_pair[i].dim.plane, pctx->in_pair[i].dim.depth,
			pctx->in_pair[i].dim.height, pctx->in_pair[i].dim.width,
			pctx->in_pair[i].dim.pitch,
			pctx->in_pair[i].data_fmt.sign, pctx->in_pair[i].data_fmt.size,
			pctx->in_pair[i].data_fmt.expoffset, pctx->in_pair[i].data_fmt.expbits,
			pctx->in_pair[i].size, pctx->in_pair[i].virt_addr);
	}
	for (uint32_t i = 0; i < pctx->out_num; ++i) {
		ambamps_log("graph output: %u [%s] dim: (%u, %u, %u, %u), pitch: %u, "
			"data_fmt: (%d, %d, %d, %d), "
			"size: %u, virt_addr 0x%p\n",
			i, pctx->out_pair[i].port_name,
			pctx->out_pair[i].dim.plane, pctx->out_pair[i].dim.depth,
			pctx->out_pair[i].dim.height, pctx->out_pair[i].dim.width,
			pctx->out_pair[i].dim.pitch,
			pctx->out_pair[i].data_fmt.sign, pctx->out_pair[i].data_fmt.size,
			pctx->out_pair[i].data_fmt.expoffset, pctx->out_pair[i].data_fmt.expbits,
			pctx->out_pair[i].size, pctx->out_pair[i].virt_addr);
	}*/

	return rval;
}

static int ambamps_chain_next_nodes(graph_ctx_t *pctx, node_match_t *pnet)
{
	int rval = 0;
	node_match_t *node_list = pctx->node_list;
	int jnt_num = pctx->node_jnt_num;
	ambamps_graph_node_joint_t *jnt_list = pctx->node_joint;
	node_match_t *to_nd = nullptr;
	int to_nd_id = -1;
	int *exec_idx = pctx->exec_index;
	uint32_t cur_nd_id = pnet->id;
	const char *from_port_nm = nullptr, *to_port_nm = nullptr;
	int i = 0, j = 0;
	int from_port_idx = -1, to_port_idx = -1;
	int from_port_size = -1, to_port_size = -1;
	struct io_dim *from_dim = nullptr, *to_dim = nullptr;

	for (i = 0; i < jnt_num; ++i) {
		if (jnt_list[i].from_node_id != cur_nd_id) continue;
		to_nd_id = jnt_list[i].to_node_id;
		to_nd = &node_list[exec_idx[to_nd_id]];
		from_port_nm = jnt_list[i].from_port_name;
		to_port_nm = jnt_list[i].to_port_name;
		for (j = 0; j < (int)pnet->out_num; ++j) {
			if (is_cstring_match(from_port_nm, pnet->out_pair[j].port_name)) {
				from_port_idx = j;
			}
		}
		if (from_port_idx == -1) {
			ambamps_error("there is no output port name %s for node %s\n", \
				from_port_nm, pnet->name);
			rval = -1;
			break;
		}
		for (j = 0; j < (int)to_nd->in_num; ++j) {
			if (is_cstring_match(to_port_nm, to_nd->in_pair[j].port_name)) {
				to_port_idx = j;
			}
		}
		if (to_port_idx == -1) {
			ambamps_error("there is no input port name %s for node %s\n", \
				to_port_nm, to_nd->name);
			rval = -1;
			break;
		}
		if (pnet->out_pair[from_port_idx].data_fmt.sign != to_nd->in_pair[to_port_idx].data_fmt.sign ||
			pnet->out_pair[from_port_idx].data_fmt.size != to_nd->in_pair[to_port_idx].data_fmt.size ||
			pnet->out_pair[from_port_idx].data_fmt.expoffset != to_nd->in_pair[to_port_idx].data_fmt.expoffset ||
			pnet->out_pair[from_port_idx].data_fmt.expbits != to_nd->in_pair[to_port_idx].data_fmt.expbits) {
			ambamps_error("node %s and node %s have different data format. io %s data format: %d,%d,%d,%d "
				" io %s data format: %d,%d,%d,%d\n", pnet->name, to_nd->name,
				pnet->out_pair[from_port_idx].port_name,
				pnet->out_pair[from_port_idx].data_fmt.sign, pnet->out_pair[from_port_idx].data_fmt.size,
				pnet->out_pair[from_port_idx].data_fmt.expoffset, pnet->out_pair[from_port_idx].data_fmt.expbits,
				to_nd->in_pair[to_port_idx].port_name,
				to_nd->in_pair[to_port_idx].data_fmt.sign, to_nd->in_pair[to_port_idx].data_fmt.size,
				to_nd->in_pair[to_port_idx].data_fmt.expoffset, to_nd->in_pair[to_port_idx].data_fmt.expbits);

			rval = -1;
			break;
		}

		from_dim = &pnet->out_pair[from_port_idx].dim;
		to_dim = &to_nd->in_pair[to_port_idx].dim;
		from_port_size = from_dim->plane * from_dim->depth * from_dim->height * from_dim->width;
		to_port_size = to_dim->plane * to_dim->depth * to_dim->height * to_dim->width;
		if (from_port_size!= to_port_size) {
			ambamps_error("node %s and node %s has different io size. io %s dim %u,%u,%u,%u "
				"io %s dim dim %u,%u,%u,%u\n",pnet->name, to_nd->name,
				pnet->out_pair[from_port_idx].port_name,
				pnet->out_pair[from_port_idx].dim.plane, pnet->out_pair[from_port_idx].dim.depth,
				pnet->out_pair[from_port_idx].dim.height, pnet->out_pair[from_port_idx].dim.width,
				to_nd->in_pair[to_port_idx].port_name,
				to_nd->in_pair[to_port_idx].dim.plane, to_nd->in_pair[to_port_idx].dim.depth,
				to_nd->in_pair[to_port_idx].dim.height,to_nd->in_pair[to_port_idx].dim.width);

			rval = -1;
			break;
		}
		to_nd->in_pair[to_port_idx].virt_addr = pnet->out_pair[from_port_idx].virt_addr;
		to_nd->in_pair[to_port_idx].dram_addr = pnet->out_pair[from_port_idx].dram_addr;
		to_nd->in_pair[to_port_idx].size = pnet->out_pair[from_port_idx].size;
	}

	return rval;
}

static int ambamps_net_io_cfg(node_match_t *pnet, struct net_input_cfg *net_in,
	struct net_output_cfg *net_out)
{
	uint32_t i = 0;
	int rval = 0;

	pnet->in_num = net_in->in_num;
	for (i = 0; i < net_in->in_num; i++) {
		strncpy(pnet->in_pair[i].port_name, net_in->in_desc[i].name, AMBAMPS_IO_NAME_MAX - 1);
		pnet->in_pair[i].virt_addr = net_in->in_desc[i].virt;
		pnet->in_pair[i].dram_addr = net_in->in_desc[i].addr;
		pnet->in_pair[i].size = net_in->in_desc[i].size;
		if ((net_in->in_desc[i].addr == 0) || (net_in->in_desc[i].size == 0)) {
			ambamps_error("Input [%u] [%s] get invalid addr: 0x%x, size: 0x%x\n",
				i, net_in->in_desc[i].name,
				net_in->in_desc[i].addr, net_in->in_desc[i].size);
			rval = -1;
			break;
		}
		pnet->in_pair[i].dim = net_in->in_desc[i].dim;
		pnet->in_pair[i].data_fmt = net_in->in_desc[i].data_fmt;

#if AMBAMPS_DEBUG
		ambamps_log("node [ %s ] input: %u [%s] dim: (%u, %u, %u, %u), pitch: %u, "
			"data_fmt: (%d, %d, %d, %d), "
			"size: %u, virt_addr 0x%p\n",
			pnet->name,
			i, net_in->in_desc[i].name,
			net_in->in_desc[i].dim.plane, net_in->in_desc[i].dim.depth,
			net_in->in_desc[i].dim.height, net_in->in_desc[i].dim.width,
			net_in->in_desc[i].dim.pitch,
			net_in->in_desc[i].data_fmt.sign, net_in->in_desc[i].data_fmt.size,
			net_in->in_desc[i].data_fmt.expoffset, net_in->in_desc[i].data_fmt.expbits,
			net_in->in_desc[i].size, net_in->in_desc[i].virt);
#endif
	}

	pnet->out_num = net_out->out_num;
	for (i = 0; i < net_out->out_num; i++) {
		strncpy(pnet->out_pair[i].port_name, net_out->out_desc[i].name, AMBAMPS_IO_NAME_MAX - 1);
		pnet->out_pair[i].virt_addr = net_out->out_desc[i].virt;
		pnet->out_pair[i].dram_addr = net_out->out_desc[i].addr;
		pnet->out_pair[i].size = net_out->out_desc[i].size;
		if ((net_out->out_desc[i].addr == 0) || (net_out->out_desc[i].size == 0)) {
			ambamps_error("Output [%u] [%s] get invalid addr: 0x%x, size: 0x%x\n",
				i, net_out->out_desc[i].name,
				net_out->out_desc[i].addr, net_out->out_desc[i].size);
			rval = -1;
			break;
		}
		pnet->out_pair[i].dim = net_out->out_desc[i].dim;
		pnet->out_pair[i].data_fmt = net_out->out_desc[i].data_fmt;

#if AMBAMPS_DEBUG
		ambamps_log("node [ %s ] output: %u [%s] dim: (%u, %u, %u, %u), pitch: %u, "
			"data_fmt: (%d, %d, %d, %d), "
			"size: %u, virt_addr 0x%p\n",
			pnet->name,
			i, net_out->out_desc[i].name,
			net_out->out_desc[i].dim.plane, net_out->out_desc[i].dim.depth,
			net_out->out_desc[i].dim.height, net_out->out_desc[i].dim.width,
			net_out->out_desc[i].dim.pitch,
			net_out->out_desc[i].data_fmt.sign, net_out->out_desc[i].data_fmt.size,
			net_out->out_desc[i].data_fmt.expoffset, net_out->out_desc[i].data_fmt.expbits,
			net_out->out_desc[i].size, net_out->out_desc[i].virt);
#endif
	}

	return rval;
}

static int ambamps_init_one_vp_node(node_match_t *pnet, graph_ctx_t *pctx)
{
	struct net_cfg net_cf;
	struct net_input_cfg net_in;
	struct net_output_cfg net_out;
	vp_nd_t *vp_nd = &pnet->node.vp_node;
	int net_id = 0;
	int rval = 0;

	memset((void *)&net_cf, 0, sizeof(struct net_cfg));
	memset((void *)&net_in, 0, sizeof(struct net_input_cfg));
	memset((void *)&net_out, 0, sizeof(struct net_output_cfg));

	net_cf.verbose = 0;
	net_cf.reuse_mem = 1;
	vp_nd->cache_en = 1;

	do {
		net_cf.net_file = vp_nd->net_fn;
		net_id = nnctrl_init_net(&net_cf, nullptr, nullptr);
		if (net_id < 0) {
			ambamps_error("nnctrl_init_net\n");
			rval = -1;
			break;
		}
		if (net_cf.net_mem_total == 0) {
			ambamps_error("nnctrl_init_net get total size is zero\n");
			rval = -1;
			break;
		}
		vp_nd->net_id = net_id;
		vp_nd->net_m.mem_size = net_cf.net_mem_total;

		unsigned long mem_size_cv2x = vp_nd->net_m.mem_size;
		unsigned long phy_addr_cv2x = vp_nd->net_m.phy_addr;

		rval = cavalry_mem_alloc(&mem_size_cv2x, &phy_addr_cv2x,
			(void**)&vp_nd->net_m.virt_addr, vp_nd->cache_en);

		vp_nd->net_m.mem_size = (uint32_t)mem_size_cv2x;
		vp_nd->net_m.phy_addr = (uint32_t)phy_addr_cv2x;

		if (rval < 0) {
			ambamps_error("failed to alloc mem for node %s\n", pnet->name);
			rval = -1;
			break;
		}
		if (vp_nd->net_m.virt_addr == nullptr) {
			ambamps_error("alloc cv mem is nullptr\n");
			rval = -1;
			break;
		}
		if (nnctrl_get_net_io_cfg(net_id, &net_in, &net_out)) {
			ambamps_error("nnctrl_get_net_io_cfg\n");
			rval = -1;
			break;
		}
		if (nnctrl_load_net(net_id, &vp_nd->net_m, &net_in, &net_out) < 0) {
			ambamps_error("nnctrl_load_net\n");
			rval = -1;
			break;
		}
		if (vp_nd->cache_en) {
			if (cavalry_mem_sync_cache(vp_nd->net_m.mem_size,
				vp_nd->net_m.phy_addr, 1, 0) < 0) {
				ambamps_error("cavalry_mem_sync_cache\n");
				rval = -1;
				break;
			}
		}
		if (ambamps_net_io_cfg(pnet, &net_in, &net_out) < 0) {
			ambamps_error("ambamps_net_io_cfg\n");
			rval = -1;
			break;
		}
		/* chain arm node i/o with those of vp node */
		if (ambamps_chain_next_nodes(pctx, pnet) < 0) {
			ambamps_error("failed to chain node %s to its next nodes\n", pnet->name);
			rval = -1;
			break;
		}
	} while (0);

	return rval;
}

static int ambamps_run_one_vp_node(node_match_t *pnet)
{
	struct net_result net_ret;
	int rval = 0, result = 0;
	int i = 0;
	int out_num = 0;
	vp_nd_t *vp_nd = &pnet->node.vp_node;

	do {
		result = nnctrl_run_net(vp_nd->net_id, &net_ret, nullptr, nullptr, nullptr);
		if (result == -EAGAIN) {
			do {
				result = nnctrl_resume_net(vp_nd->net_id, &net_ret);
				if (result == -EINTR) {
					ambamps_error("interrupt by signal in resume\n");
					break;
				}
			} while (result == -EAGAIN);
		} else if (result == -EINTR) {
			ambamps_error("interrupt by signal in run\n");
			break;
		} else if (result < 0){
			ambamps_error("nnctrl_run_net failed ret: %d\n", result);
			rval = -1;
			break;
		}
		ambamps_log("vp node (%s) execution time: %.1fus\n", pnet->name, net_ret.vp_time_us);

		// assume that all output data goes to arm side
		if (vp_nd->cache_en) {
			out_num = pnet->out_num;
			for (i = 0; i < out_num; ++i) {
				if (cavalry_mem_sync_cache(pnet->out_pair[i].size,
					pnet->out_pair[i].dram_addr, 0, 1) < 0) {
					ambamps_error("cavalry_mem_sync_cache\n");
					rval = -1;
					break;
				}
			}
			if (rval) break;
		}
	} while (0);

	return rval;
}

static int ambamps_init_one_arm_node(node_match_t *pnet, graph_ctx_t *pctx)
{
	int rval = 0;
	amba_cnn_ext_c_extern_node_type_t *type = nullptr;
	arm_nd_t *arm_nd = &pnet->node.arm_node;

	do {
		if ((arm_nd->lib_handle = dlopen(arm_nd->lib_fn, RTLD_LAZY | RTLD_GLOBAL)) == nullptr) {
			ambamps_error("dlopen failed with error: %s for %s\n", dlerror(), pnet->name);
			rval = -1;
			break;
		}
		if ((arm_nd->ptr_query = (amba_cnn_ext_c_dll_query_t)dlsym(arm_nd->lib_handle,
			"query_extern_node_types")) == nullptr) {
			ambamps_error("dlsym query_extern_node_types err %s\n", dlerror());
			rval = -1;
			break;
		}
		rval = (*arm_nd->ptr_query)(&arm_nd->num_types,
			(const amba_cnn_ext_c_node_type_t **)&arm_nd->types);
		if (rval < 0) {
			ambamps_error("query_extern_node_types func run err\n");
			break;
		}

#if AMBAMPS_DEBUG
		for (uint32_t i = 0; i < pnet->in_num; ++i) {
			ambamps_log("node [ %s ] input: %u [%s] dim: (%u, %u, %u, %u), pitch: %u, "
				"data_fmt: (%d, %d, %d, %d), "
				"size: %u, virt_addr 0x%p\n", pnet->name,
				i, pnet->in_pair[i].port_name,
				pnet->in_pair[i].dim.plane, pnet->in_pair[i].dim.depth,
				pnet->in_pair[i].dim.height, pnet->in_pair[i].dim.width,
				pnet->in_pair[i].dim.pitch,
				pnet->in_pair[i].data_fmt.sign, pnet->in_pair[i].data_fmt.size,
				pnet->in_pair[i].data_fmt.expoffset, pnet->in_pair[i].data_fmt.expbits,
				pnet->in_pair[i].size, pnet->in_pair[i].virt_addr);
		}
#endif

		arm_nd->lib_exec.num_src = pnet->in_num;
		for (uint32_t i = 0; i < pnet->in_num; ++i) {
			arm_nd->lib_exec.isz[i].p = pnet->in_pair[i].dim.plane;
			arm_nd->lib_exec.isz[i].d = pnet->in_pair[i].dim.depth;
			arm_nd->lib_exec.isz[i].h = pnet->in_pair[i].dim.height;
			arm_nd->lib_exec.isz[i].w = pnet->in_pair[i].dim.width;
		}

		arm_nd->lib_exec.attr = arm_nd->lib_attr; // "20 25200 0.001 0.6 300";
		type = arm_nd->types[0];		// only one entry;

		rval = (*type->init) (&arm_nd->lib_exec.cid, arm_nd->lib_exec.osz,
			arm_nd->lib_exec.idf, arm_nd->lib_exec.odf,
			&arm_nd->lib_exec.data_mode, arm_nd->lib_exec.num_src,
			arm_nd->lib_exec.isz, arm_nd->lib_exec.attr, NULL);
		if (rval) {
			ambamps_error("extern_node_init err\n");
			break;
		}

		for (uint32_t i = 0; i < pnet->out_num; ++i) {
			uint32_t p = pnet->out_pair[i].dim.plane;
			uint32_t d = pnet->out_pair[i].dim.depth;
			uint32_t h = pnet->out_pair[i].dim.height;
			uint32_t w = pnet->out_pair[i].dim.width;
			uint32_t datasize = pnet->out_pair[i].data_fmt.size;
			uint32_t pitch = w << datasize;
			pnet->out_pair[i].dim.pitch = pitch;
			pnet->out_pair[i].size = p * d * h * pitch;

			pnet->out_pair[i].virt_addr = (uint8_t*)malloc(pnet->out_pair[i].size);
			if (pnet->out_pair[i].virt_addr == nullptr) {
				ambamps_error("failed to alloc mem for arm node %s\n", pnet->name);
				rval = -1;
				break;
			}
			memset(pnet->out_pair[i].virt_addr, 0, pnet->out_pair[i].size);
			pnet->out_pair[i].dram_addr = 0;
		}

#if AMBAMPS_DEBUG
		for (uint32_t i = 0; i < pnet->out_num; ++i) {
			ambamps_log("node [ %s ] output: %u [%s] dim: (%u, %u, %u, %u), pitch: %u, "
				"data_fmt: (%d, %d, %d, %d), "
				"size: %u, virt_addr 0x%p\n", pnet->name,
				i, pnet->out_pair[i].port_name,
				pnet->out_pair[i].dim.plane, pnet->out_pair[i].dim.depth,
				pnet->out_pair[i].dim.height, pnet->out_pair[i].dim.width,
				pnet->out_pair[i].dim.pitch,
				pnet->out_pair[i].data_fmt.sign, pnet->out_pair[i].data_fmt.size,
				pnet->out_pair[i].data_fmt.expoffset, pnet->out_pair[i].data_fmt.expbits,
				pnet->out_pair[i].size, pnet->out_pair[i].virt_addr);
		}
#endif
	} while(0);

	return rval;
}

static int ambamps_run_one_arm_node(node_match_t *pnet)
{
	int rval = 0;
	amba_cnn_ext_c_extern_node_type_t *type = nullptr;
	arm_nd_t *arm_nd = &pnet->node.arm_node;
	int in_batch_size = 1, out_batch_size = 1;
	uint32_t i = 0;

	do {
		type = arm_nd->types[0];		// only one entry;
		rval = (*type->iter_init) (arm_nd->lib_exec.cid, arm_nd->lib_exec.osz,
			arm_nd->lib_exec.isz, out_batch_size, &in_batch_size);
		if (rval) {
			ambamps_error("extern_node_iter_init err\n");
			break;
		}
		for (i = 0; i < pnet->in_num; ++i) {
			arm_nd->lib_exec.src_array[i] = pnet->in_pair[i].virt_addr;
		}
		for (i = 0; i < pnet->out_num; ++i) {
			arm_nd->lib_exec.dst_array[i] = pnet->out_pair[i].virt_addr;
		}
		rval = (*type->forward)(arm_nd->lib_exec.cid,
			(void **)arm_nd->lib_exec.dst_array, (void **)arm_nd->lib_exec.src_array);
		if (rval) {
			ambamps_error("extern_node_forward err\n");
			break;
		}
	} while(0);

	return rval;
}

static int ambamps_release_one_arm_node(node_match_t *pnet)
{
	int rval = 0;
	amba_cnn_ext_c_extern_node_type_t *type = nullptr;
	arm_nd_t *arm_nd = &pnet->node.arm_node;

	do {
		type = arm_nd->types[0];		// only one entry;
		if (type && type->release) {
			rval = (type->release)(arm_nd->lib_exec.cid);
			if (rval) {
				ambamps_error("extern_node release cid: %u error\n", arm_nd->lib_exec.cid);
			}
		}
		if (arm_nd->lib_handle) {
			dlclose(arm_nd->lib_handle);
			arm_nd->lib_handle = nullptr;
		}
	} while(0);

	return rval;
}

template <typename T>
void convert_hwc_chw(T *pdst, T *psrc, uint32_t c, uint32_t h, uint32_t w)
{
	for (uint32_t kc = 0; kc < c; ++kc) {
		for (uint32_t kh = 0; kh < h;  ++kh) {
			for (uint32_t kw = 0; kw < w; ++kw) {
				*(pdst + kc * h *w + kh * w + kw) = *(psrc + kh * w * c + kw * c + kc);
			}
		}
	}
}

static int ambamps_set_input(graph_ctx_t *pctx, init_cfg_t *pcfg)
{
	int rval = 0;
	const char *input_name_y = "images_y";
	const char *input_name_uv = "images_uv";
	uint32_t in_num = pctx->node_list[0].in_num;
	cv::Mat img;

	if (pcfg->mode == USE_JPG) {
		img = cv::imread(pcfg->input_file_y);
		if (img.empty()) {
			ambamps_error("failed to read file %s\n", pcfg->input_file_y.c_str());
			return -1;
		}
	}

	for (uint32_t i = 0; i < pctx->in_num; ++i) {
		if (is_cstring_match(input_name_y, pctx->in_pair[i].port_name)) {
			uint32_t p = pctx->in_pair[i].dim.plane;
			uint32_t d = pctx->in_pair[i].dim.depth;
			uint32_t h = pctx->in_pair[i].dim.height;
			uint32_t w = pctx->in_pair[i].dim.width;
			uint32_t pitch = (1 << pctx->in_pair[i].data_fmt.size) * w;
			uint32_t size = p * d * h * pitch;
			struct io_data_fmt *dt_fmt = &pctx->in_pair[i].data_fmt;

			if (USE_JPG == pcfg->mode) {
				cv::resize(img, img, Size(w, h), INTER_AREA);
				// HWC -> CHW
				if (dt_fmt->size == 0) {		/* u8*/
					uint8_t *psrc = (uint8_t*)img.data;
					uint8_t *pdst = (uint8_t*)pctx->in_pair[i].virt_addr;
					convert_hwc_chw(pdst, psrc, d, h, w);
				}  else if (dt_fmt->sign == 1 && dt_fmt->size == 2 &&
					dt_fmt->expoffset == 0 && dt_fmt->expbits == 7) {	/* fp32 */
					cv::Mat img32f;
					img.convertTo(img32f, CV_32F);
					float *psrc = (float*)img32f.data;
					float *pdst = (float*)pctx->in_pair[i].virt_addr;
					convert_hwc_chw(pdst, psrc, d, h, w);
				} else {
					ambamps_error("network input data format (%d,%d,%d,%d) is not supported\n",\
						dt_fmt->sign, dt_fmt->size, dt_fmt->expoffset, dt_fmt->expbits);
				}
			} else if (USE_BIN == pcfg->mode) {
				if (load_file(pcfg->input_file_y.c_str(), pctx->in_pair[i].virt_addr, size) < 0) {
					ambamps_error("failed to set input for input y %s\n", input_name_y);
					rval = -1;
					break;
				}
			}

			if (cavalry_mem_sync_cache(pctx->in_pair[i].size,
				pctx->in_pair[i].dram_addr, 1, 0) < 0) {
				ambamps_error("cavalry_mem_sync_cache\n");
				rval = -1;
				break;
			}
		}

		if (in_num > 1 && is_cstring_match(input_name_uv, pctx->in_pair[i].port_name)) {
			uint32_t p = pctx->in_pair[i].dim.plane;
			uint32_t d = pctx->in_pair[i].dim.depth;
			uint32_t h = pctx->in_pair[i].dim.height;
			uint32_t w = pctx->in_pair[i].dim.width;
			uint32_t pitch = (1 << pctx->in_pair[i].data_fmt.size) * w;
			uint32_t size = p * d * h * pitch;

			if (load_file(pcfg->input_file_uv.c_str(), pctx->in_pair[i].virt_addr, size) < 0) {
				ambamps_error("failed to set input for input uv %s\n", input_name_uv);
				rval = -1;
				break;
			}
			if (cavalry_mem_sync_cache(pctx->in_pair[i].size,
				pctx->in_pair[i].dram_addr, 1, 0) < 0) {
				ambamps_error("cavalry_mem_sync_cache\n");
				rval = -1;
				break;
			}
		}
	}

	return rval;
}

// hardcode to "output" for yolov5s, (x1, y1, x2, y2, score, class ID)
static int ambamps_process_output(graph_ctx_t *pctx, init_cfg_t *pcfg)
{
	int rval = 0;
	float *out_buf = nullptr, *buf_line = nullptr;
	uint32_t bbox_num = 0, pitch = 0;
	const float conf_th = pcfg->conf_th;
	float conf = 0.0f;
	const char *input_name_y = "images_y";
	const char *output_name = "output";
	std::string fn;
	char text[128] = "";

	int net_w = 0;
	int net_h = 0;
	cv::Mat img;

	for (uint32_t i = 0; i < pctx->in_num; ++i) {
		if (is_cstring_match(pctx->in_pair[i].port_name, input_name_y)) {
			net_w = pctx->in_pair[i].dim.width;
			net_h = pctx->in_pair[i].dim.height;
		}
	}

	if (USE_JPG == pcfg->mode) {
		img = cv::imread(pcfg->input_file_y);
		if (img.empty()) {
			ambamps_error("failed to read file %s\n", pcfg->input_file_y.c_str());
			return -1;
		}
	}

	for (uint32_t i = 0; i < pctx->out_num; ++i) {
		if (is_cstring_match(output_name, pctx->out_pair[i].port_name)) {
			bbox_num = pctx->out_pair[i].dim.height;
			out_buf =(float*) pctx->out_pair[i].virt_addr;
			pitch = pctx->out_pair[i].dim.pitch;

			if (USE_JPG == pcfg->mode) {
				for (uint32_t j = 0; j < bbox_num; ++j) {
					buf_line = (float*)((uint8_t*)out_buf + j * pitch);

					conf = buf_line[4];
					if (conf < 1e-5) {
						break;
					} else if (conf < conf_th) {
						continue;
					}

					int x1 = (int)(buf_line[0] * img.cols / net_w);
					int y1 = (int)(buf_line[1] * img.rows / net_h);
					int x2 = (int)(buf_line[2] * img.cols / net_w);
					int y2 = (int)(buf_line[3] * img.rows / net_h);

					x1 = MIN(MAX(0, x1), img.cols);
					y1 = MIN(MAX(0, y1), img.rows);
					x2 = MIN(MAX(0, x2), img.cols);
					y2 = MIN(MAX(0, y2), img.rows);

					int cls_id = (int)buf_line[5];
					cv::rectangle(img, cv::Point(x1, y1), cv::Point(x2,y2),
						AMBAMPS_COLORS[cls_id % AMBAMPS_COLOR_NUM], 2);
					sprintf(text, "%s %.2f", pctx->intr_param.label_map[cls_id], buf_line[4]);
					cv::putText(img, text,
						cv::Point(x1, (y1 > 25? y1 - 2 : y1 + 25)),
						cv::FONT_HERSHEY_COMPLEX,
						1, AMBAMPS_COLORS[cls_id % AMBAMPS_COLOR_NUM], 2, 8, false);
				}
				fn = pcfg->output_nm + "_" + std::string(pctx->out_pair[i].port_name) + ".jpg";
				cv::imwrite(fn.c_str(), img);
			}

			fn = pcfg->output_nm + "_" + std::string(pctx->out_pair[i].port_name) + ".bin";
			if (store_file(fn.c_str(), pctx->out_pair[i].virt_addr, pctx->out_pair[i].size ) < 0) {
				ambamps_error("failed to store binary for output %s\n", "output");
				rval = -1;
				break;
			}
		}
	}

	return rval;
}

static struct option long_options[] = {
	{"in-folder", HAS_ARG, 0, 'b'},
	{"in-y", HAS_ARG, 0, 'y'},
	{"in-uv", HAS_ARG, 0, 'u'},
	{"out", HAS_ARG, 0, 'o'},
	{"conf-th", HAS_ARG, 0, 't'},
	{"mode", HAS_ARG, 0, 'm'},
	{0, 0, 0, 0}
};

static const char *short_options = "b:y:u:o:t:m:";

struct hint_s {
	const char *arg;
	const char *str;
};

static const struct hint_s hint[] = {
	{"", "\t\tartifact folder which contains cavalry manifest json file"},
	{"", "\t\tinput y channel bin or image (.jpg/.png ...)"},
	{"", "\t\tinput uv channel bin"},
	{"", "\t\tprefix of output files"},
	{"", "\t\toutput confidence threshold"},
	{"", "\t\tinput file mode, 0: jpg, 1: bin"},
};

void usage(void)
{
	uint32_t i;

	printf("test_ambamps usage:\n");
	for (i = 0; i < sizeof(long_options) / sizeof(long_options[0]) - 1; i++) {
		if (isalpha(long_options[i].val))
			printf("-%c ", long_options[i].val);
		else
			printf("   ");
		printf("--%s", long_options[i].name);
		if (hint[i].arg[0] != 0)
			printf(" [%s]", hint[i].arg);
		printf("\t%s\n", hint[i].str);
	}
	printf("Example: test_ambamps -b dir -y input_y.bin -u input_uv.bin -o result -m 1 -t 0.25\n");
}

static int init_param(int argc, char **argv, init_cfg_t *pcfg)
{
	int ch;
	int option_index = 0;
	opterr = 0;
	float ftmp = 0.0;
	uint32_t utmp = 0;

	pcfg->output_nm = "result";
	pcfg->conf_th = 0.25;
	pcfg->mode = 0;
	while ((ch = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
	switch (ch) {
		case 'b':
			pcfg->model_dir = std::string(optarg);
			break;
		case 'y':
			pcfg->input_file_y = std::string(optarg);
			break;
		case 'u':
			pcfg->input_file_uv = std::string(optarg);
			break;
		case 'o':
			pcfg->output_nm = std::string(optarg);
			break;
		case 't':
			ftmp = atof(optarg);
			if (ftmp < 0.0 || ftmp > 1.0) {
				ambamps_error("confidence threshold should be in range [0.0, 1.0]\n");
				return -1;
			}
			pcfg->conf_th = ftmp;
			break;
		case 'm':
			utmp = atoi(optarg);
			if (utmp > USE_BIN) {
				ambamps_error("input file mode should be 0: jpg or 1: bin\n");
				return -1;
			}
			pcfg->mode = utmp;
			break;
		default:
			ambamps_error("unknown option found: %c\n", ch);
			return -1;
		}
	}

	return 0;
}

static std::string get_ambamps_version()
{
	return std::to_string(AMBAMPS_VER_MAJOR) + "." +
		std::to_string(AMBAMPS_VER_MINOR) + "." +
		std::to_string(AMBAMPS_VER_PATCH);
}

int main(int argc, char *argv[])
{
	int rval = 0;
	int fd_cav = -1;
	graph_ctx_t graph_ctx;
	init_cfg_t init_cfg;
	node_match_t *node=nullptr;
	struct net_mem *p_cv_mem = nullptr;
	int i = 0, j = 0;

	memset(&graph_ctx, 0, sizeof(graph_ctx_t));
	do {
		if (argc < 2) {
			usage();
			rval = 1;
			break;
		}
		if (init_param(argc, argv, &init_cfg) < 0) {
			usage();
			rval = -1;
			break;
		}
		ambamps_log("version: %s\n", get_ambamps_version().c_str());
		if (construct_graph(&graph_ctx, init_cfg.model_dir.c_str()) < 0) {
			ambamps_error("failed to construct graph from compiled artifact folder %s\n", \
				init_cfg.model_dir.c_str());
			rval = -1;
			break;
		}

		/* first graph node must be vp */
		if (graph_ctx.node_list[0].node_type != AMBAMPS_COPROC_VP) {
			ambamps_error("the first graph node should be VP node\n");
			rval = -1;
			break;
		}
		if ((fd_cav = open(CAVALRY_DEV_NODE, O_RDWR, 0)) < 0) {
			perror(CAVALRY_DEV_NODE);
			rval = -1;
			break;
		}
		if (nnctrl_init(fd_cav, 0) < 0) {
			ambamps_error("nnctrl_init err\n");
			rval = -1;
			break;
		}
		if (cavalry_mem_init(fd_cav, 0) < 0) {
			ambamps_error("cavalry_mem_init err\n");
			rval = -1;
			break;
		}
		for (i = 0; i < graph_ctx.node_num; ++i) {
			node = &graph_ctx.node_list[i];
			if (node->node_type == AMBAMPS_COPROC_VP) {
				if (ambamps_init_one_vp_node(node, &graph_ctx) < 0) {
					ambamps_error("failed to init vp node %s\n", node->name);
					rval = -1;
					break;
				}
			} else if (node->node_type == AMBAMPS_COPROC_ARM) {
				if (ambamps_init_one_arm_node(node, &graph_ctx) < 0) {
					ambamps_error("failed to init one arm node %s\n", node->name);
					rval = -1;
					break;
				}
			}
		}
		if (rval) break;

		if (ambamps_graph_io_cfg(&graph_ctx) < 0) {
			ambamps_error("failed to config graph io\n");
			rval = -1;
			break;
		}
		if (ambamps_set_input(&graph_ctx, &init_cfg) < 0) {
			ambamps_error("failed to set input\n");
			rval = -1;
			break;
		}
		for (i = 0; i < graph_ctx.node_num; ++i) {
			node = &graph_ctx.node_list[i];
			if (node->node_type == AMBAMPS_COPROC_VP) {
				if (ambamps_run_one_vp_node(node) < 0) {
					ambamps_error("failed to run vp node %s\n", node->name);
					rval = -1;
					break;
				}
			} else if (node->node_type == AMBAMPS_COPROC_ARM) {
				if (ambamps_run_one_arm_node(node) < 0) {
					ambamps_error("failed to run arm node %s\n", node->name);
					rval = -1;
					break;
				}
			}
		}
		if (rval) break;

		if (ambamps_process_output(&graph_ctx, &init_cfg) < 0) {
			ambamps_error("failed to process output\n");
			rval = -1;
			break;
		}
	} while(0);

	for (i = 0; i < graph_ctx.node_num; ++i) {
		node = &graph_ctx.node_list[i];
		if (node->node_type == AMBAMPS_COPROC_VP) {
			nnctrl_exit_net(node->node.vp_node.net_id);
			p_cv_mem = &node->node.vp_node.net_m;
			if (p_cv_mem->virt_addr && p_cv_mem->mem_size) {
				cavalry_mem_free(p_cv_mem->mem_size,
						p_cv_mem->phy_addr, p_cv_mem->virt_addr);
			}
		} else if (node->node_type == AMBAMPS_COPROC_ARM) {
			ambamps_release_one_arm_node(node);
			for (j = 0; j < (int)node->out_num; ++j) {
				if (node->out_pair[j].virt_addr) {
					free(node->out_pair[j].virt_addr);
				}
			}
		}
	}
	if (fd_cav) {
		close(fd_cav);
		fd_cav = -1;
	}

	return rval;
}

