/*******************************************************************************
 * test_ambamps_live.cpp
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
#include <sys/mman.h>
#include <sys/ioctl.h>
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
#include "core/eazyai_core.h"
#include <signal.h>

#include "ambamps_priv.hpp"

using namespace cv;

#define AMBAMPS_DEBUG		(0)

typedef struct {
	ea_osd_t *display;
	ea_img_resource_t *img_resource;
	const ea_osd_area_buffer_t *buf_info;
	uint32_t stream_id;
} ambamps_overlay_t;

typedef struct init_live_cfg_s {
	std::string model_dir;
	float conf_th;

	ambamps_iav_t iav;
	ambamps_overlay_t overlay;
} init_live_cfg_t;


#define NO_ARG		0
#define HAS_ARG		1

EA_LOG_DECLARE_LOCAL(EA_LOG_LEVEL_NOTICE);

enum lut_color {
	COLOR_RED = 0,
	COLOR_LIME = 1,
	COLOR_BLUE = 2,
	COLOR_MAGENTA = 3,
	COLOR_SPRING_GREEN = 4,
	COLOR_MEDIUM_SLATE_BLUE = 5,
	COLOR_YELLOW = 6,
	COLOR_DARK_ORANGE = 7,
	COLOR_CYAN = 8,
	COLOR_GREEN = 9,
	COLOR_BLUE_VIOLET = 10,
	COLOR_VIOLET = 11,
	COLOR_DEEP_PINK = 12,
	COLOR_NAVY = 13,
	COLOR_MAROON = 14,
	COLOR_PURPLE = 15,
	COLOR_SALMON = 16,
	COLOR_OLIVE = 17,
	COLOR_MOCCASIN = 18,
	COLOR_TEAL = 19,
	COLOR_GRAY = 20,
	COLOR_BLACK = 21,
	COLOR_WHITE = 22,
	COLOR_NUM,
};

const static ea_osd_color_rgba_t colors_table[COLOR_NUM] = {
	[COLOR_RED] = {.r = 255, .g = 0, .b = 0, .alpha = 0},
	[COLOR_LIME] = {.r = 0, .g = 255, .b = 0, .alpha = 255},
	[COLOR_BLUE] = {.r = 0, .g = 0, .b = 255, .alpha = 255},
	[COLOR_MAGENTA] = {.r = 255, .g = 0, .b = 255, .alpha = 255},
	[COLOR_SPRING_GREEN] = {.r = 0, .g = 255, .b = 127, .alpha = 255},
	[COLOR_MEDIUM_SLATE_BLUE] = {.r = 127, .g = 127, .b = 255, .alpha = 255},
	[COLOR_YELLOW] = {.r = 255, .g = 255, .b = 0, .alpha = 255},
	[COLOR_DARK_ORANGE] = {.r = 255, .g = 127, .b = 0, .alpha = 255},
	[COLOR_CYAN] = {.r = 0, .g = 255, .b = 255, .alpha = 255},
	[COLOR_GREEN] = {.r = 0, .g = 127, .b = 0, .alpha = 255},
	[COLOR_BLUE_VIOLET] = {.r = 127, .g = 0, .b = 255, .alpha = 255},
	[COLOR_VIOLET] = {.r = 255, .g = 127, .b = 255, .alpha = 255},
	[COLOR_DEEP_PINK] = {.r = 255, .g = 0, .b = 127, .alpha = 255},
	[COLOR_NAVY] = {.r = 0, .g = 0, .b = 127, .alpha = 255},
	[COLOR_MAROON] = {.r = 127, .g = 0, .b = 0, .alpha = 255},
	[COLOR_PURPLE] = {.r = 127, .g = 0, .b = 127, .alpha = 255},
	[COLOR_SALMON] = {.r = 255, .g = 127, .b = 127, .alpha = 255},
	[COLOR_OLIVE] = {.r = 127, .g = 127, .b = 0, .alpha = 255},
	[COLOR_MOCCASIN] = {.r = 255, .g = 255, .b = 180, .alpha = 255},
	[COLOR_TEAL] = {.r = 0, .g = 127, .b = 127, .alpha = 255},
	[COLOR_GRAY] = {.r = 127, .g = 127, .b = 127, .alpha = 255},
	[COLOR_BLACK] = {.r = 0, .g = 0, .b = 0, .alpha = 255},
	[COLOR_WHITE] = {.r = 255, .g = 255, .b = 255, .alpha = 255},
};

static int live_mode_flag = 1;

static int ambamps_alloc_cv_mem(uint32_t *psize, uint32_t *pphys, uint8_t **pvirt, uint8_t cache_en)
{
	void *virt = nullptr;
	unsigned long phys = 0, size = 0;
	int rval = 0;

	size = *psize;
	if (cavalry_mem_alloc(&size, &phys, &virt, cache_en) < 0) {
		ambamps_error("cavalry_mem_alloc\n");
		rval = -1;
	} else {
		*psize = size;
		*pphys = phys;
		*pvirt = (uint8_t *)virt;
		memset(virt, 0, size);
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
	graph_node_joint_t *jnt_list = pctx->node_joint;
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
		/* no need to assign addr since it might be no mem case */
		pnet->in_pair[i].size = net_in->in_desc[i].size;
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
	net_cf.net_all_input_no_mem = 1;
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
		if (ambamps_alloc_cv_mem(&vp_nd->net_m.mem_size, &vp_nd->net_m.phy_addr,
			&vp_nd->net_m.virt_addr, vp_nd->cache_en) < 0) {
			ambamps_error("ambamps_alloc_cv_mem\n");
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

		if (nnctrl_load_net(net_id, &vp_nd->net_m, NULL, &net_out) < 0) {
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
		/* fill vp pnet prot name */
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

static int ambamps_run_one_vp_node(node_match_t *pnet, net_input_cfg *net_input)
{
	struct net_result net_ret;
	int rval = 0, result = 0;
	int i = 0;
	int out_num = 0;
	vp_nd_t *vp_nd = &pnet->node.vp_node;

	do {
		result = nnctrl_run_net(vp_nd->net_id, &net_ret, nullptr, net_input, nullptr);
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

			if (ambamps_alloc_cv_mem(&pnet->out_pair[i].size, &pnet->out_pair[i].dram_addr,
				&pnet->out_pair[i].virt_addr, 0) < 0) {
				ambamps_error("failed to alloc mem for arm node %s\n", pnet->name);
				rval = -1;
				break;
			}
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

static void get_overlay_screen(init_live_cfg_t *pcfg, cv::Mat &img)
{
	ambamps_overlay_t *p_overlay = &pcfg->overlay;

	uint8_t *fb_buf = ea_osd_area_current_buffer(p_overlay->display, 0, nullptr)->buf;
	img = cv::Mat(p_overlay->buf_info->height, p_overlay->buf_info->width, CV_8UC1,
			fb_buf, p_overlay->buf_info->pitch);
	memset(img.data, 0, img.rows * img.step);
}

// hardcode to "output" for yolov5s, (x1, y1, x2, y2, score, class ID)
static int ambamps_process_output(graph_ctx_t *pctx, init_live_cfg_t *pcfg)
{
	int rval = 0;
	float *out_buf = nullptr, *buf_line = nullptr;
	uint32_t bbox_num = 0, pitch = 0;
	const float conf_th = pcfg->conf_th;
	float conf = 0.0f;
	const char *output_name = "output";

	int osd_color = 0;
	char text[128] = "";

	int net_w = pctx->in_pair[0].dim.width;
	int net_h = pctx->in_pair[0].dim.height;
	cv::Mat img;

	get_overlay_screen(pcfg, img);

	for (uint32_t i = 0; i < pctx->out_num; ++i) {
		if (is_cstring_match(output_name, pctx->out_pair[i].port_name)) {
			bbox_num = pctx->out_pair[i].dim.height;
			out_buf =(float*) pctx->out_pair[i].virt_addr;
			pitch = pctx->out_pair[i].dim.pitch;

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
				int cls_id = (int)buf_line[5];

				osd_color = cls_id % COLOR_NUM;
				osd_color = (osd_color == 0)? COLOR_VIOLET : osd_color;

				cv::rectangle(img, cv::Point(x1, y1), cv::Point(x2,y2), osd_color, 2);
				sprintf(text, "%s %.2f", pctx->intr_param.label_map[cls_id], buf_line[4]);
				cv::putText(img, text,
					cv::Point(x1, (y1 > 25? y1 - 5 : y1 + 25)),
					cv::FONT_HERSHEY_SIMPLEX,
					1, osd_color, 2, 8, false);
			}
		}
	}

	ea_osd_refresh(pcfg->overlay.display, NULL);

	return rval;
}

static struct option long_options[] = {
	{"in-folder", 	HAS_ARG, 0, 'b'},
	{"conf-th", 	HAS_ARG, 0, 'h'},
	{"buf-type", 	HAS_ARG, 0, 't'},
	{"buf-id", 	HAS_ARG, 0, 'i'},
	{"stream-id", 	HAS_ARG, 0, 's'},
	{0, 0, 0, 0}
};

static const char *short_options = "b:t:h:i:s:";

struct hint_s {
	const char *arg;
	const char *str;
};

static const struct hint_s hint[] = {
	{"", "\tartifact folder which contains cavalry manifest json file"},
	{"", "\toutput confidence threshold"},
	{"", "\tSet live input data source type = canvas_buffer/pyramid_buffer,"
		"\n\t\t\t0=canvas_buffer, 1=pyramid_buffer"},
	{"", "\tSet live input data canvas/pyramid id, \n\t\t\tcanvas_buffer "
		"0:Main/1:Second/2:Thrid/3:Fourth/4:Fifth, \n\t\t\tpyramid layer 0/1/2/3/4/5"},
	{"", "\tDisplay on encoding stream, set stream id, [0:1:2...]"},
};

void usage(void)
{
	uint32_t i;

	printf("test_ambamps_live usage:\n");
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
	printf("Example: test_ambamps_live --in-folder ./output/ -t 0 -i 1 -s 0 -h 0.25\n");
}

static int init_param(int argc, char **argv, init_live_cfg_t *pcfg)
{
	int ch;
	int option_index = 0;
	opterr = 0;

	pcfg->conf_th = 0.25;
	pcfg->iav.query_buf_type = AMBAMPS_QUERY_BUF_CANVAS;
	pcfg->iav.query_buf_id = 1;
	pcfg->overlay.stream_id = 1;
	while ((ch = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
	switch (ch) {
		case 'b':
			pcfg->model_dir = std::string(optarg);
			break;
		case 'h':
			pcfg->conf_th = atof(optarg);
			break;
		case 't':
			pcfg->iav.query_buf_type = atoi(optarg);
			ambamps_log("Input buffer type = %d\n", pcfg->iav.query_buf_type);

			if (pcfg->iav.query_buf_type < 0 || pcfg->iav.query_buf_type > 3) {
				ambamps_error("buffer type out of range, should be 0/1/2/3\n");
				return -1;
			}
			break;
		case 'i':
			pcfg->iav.query_buf_id = atoi(optarg);
			ambamps_log("Input buffer id = %d\n", pcfg->iav.query_buf_id);

			if (pcfg->iav.query_buf_id < 0 || pcfg->iav.query_buf_id > 5) {
				ambamps_error("buffer id out of range\n");
				return -1;
			}
			break;
		case 's':
			pcfg->overlay.stream_id = atoi(optarg);
			ambamps_log("Display on stream, id = %d\n", pcfg->overlay.stream_id);

			if (pcfg->overlay.stream_id < 0) {
				ambamps_error("stream id out of range, should >= 0\n");
				return -1;
			}
			break;
		default:
			ambamps_error("unknown option found: %c\n", ch);
			return -1;
		}
	}

	return 0;
}

static void ambamps_init_color_table(init_live_cfg_t *pcfg)
{
	ea_osd_area_set_color_table_rgba(pcfg->overlay.display, 0, colors_table, COLOR_NUM);
}

static int ambamps_init_overlay(init_live_cfg_t *pcfg)
{
	int rval = 0;
	int env_ret = -1;
	int features = 0;
	ambamps_overlay_t *p_overlay = &pcfg->overlay;

	do {
		features = EA_ENV_ENABLE_IAV | EA_ENV_ENABLE_OSD_STREAM;
		//features = EA_ENV_ENABLE_IAV | EA_ENV_ENABLE_OSD_VOUT;

		env_ret = ea_env_open(features);
		if (env_ret < 0) {
			ambamps_error("ea_env_open failed !\n");
			rval = -1;
			break;
		}
		if (pcfg->iav.query_buf_type == AMBAMPS_QUERY_BUF_CANVAS) {
			p_overlay->img_resource = ea_img_resource_new(EA_CANVAS, (void *)(unsigned long)pcfg->iav.query_buf_id);
		} else {
			p_overlay->img_resource = ea_img_resource_new(EA_PYRAMID, (void *)(unsigned long)0);
		}
		RVAL_ASSERT(p_overlay->img_resource != NULL);
		p_overlay->display = ea_osd_new(EA_OSD_STREAM, pcfg->overlay.stream_id, NULL);
		//p_overlay->display = ea_osd_new(EA_OSD_VOUT, pcfg->overlay.stream_id, NULL);
		RVAL_ASSERT(p_overlay->display != NULL);
		p_overlay->buf_info = ea_osd_area_current_buffer(p_overlay->display, 0, nullptr);
	} while(0);

	if (rval < 0) {
		if (p_overlay->display) {
			ea_osd_free(p_overlay->display);
			p_overlay->display = NULL;
		}

		if (p_overlay->img_resource) {
			ea_img_resource_free(p_overlay->img_resource);
			p_overlay->img_resource = NULL;
		}

		if (env_ret >= 0) {
			ea_env_close();
		}
	}

	return rval;
}

static void ambamps_deinit_overlay(ambamps_overlay_t *p_overlay)
{
	if (p_overlay->display) {
		ea_osd_free(p_overlay->display);
		p_overlay->display = NULL;
	}
	if (p_overlay->img_resource) {
		ea_img_resource_free(p_overlay->img_resource);
		p_overlay->img_resource = NULL;
	}
	ea_env_close();
}

static int ambamps_check_dsp_state(ambamps_iav_t *p_iav)
{
	int state;
	int rval = 0;
	do {
		if (ioctl(p_iav->fd_iav, IAV_IOC_GET_IAV_STATE, &state) < 0) {
			perror("IAV_IOC_GET_IAV_STATE");
			rval = -1;
			break;
		}
		if ((state != IAV_STATE_PREVIEW) && state != IAV_STATE_ENCODING) {
			printf("Error: IAV is not in preview / encoding state, cannot get yuv buf!\n");
			rval = -1;
			break;
		}
	} while (0);

	return rval;
}

static int ambamps_map_dsp_buffer(ambamps_iav_t *p_iav)
{
	struct iav_querymem query_mem;
	struct iav_mem_part_info *part_info;
	int rval = 0;

	do {
		memset(&query_mem, 0, sizeof(query_mem));
		query_mem.mid = IAV_MEM_PARTITION;
		part_info = &query_mem.arg.partition;
		part_info->pid = IAV_PART_DSP;
		if (ioctl(p_iav->fd_iav, IAV_IOC_QUERY_MEMBLOCK, &query_mem) < 0) {
			perror("IAV_IOC_QUERY_MEMBLOCK");
			rval = -1;
			break;
		}

		p_iav->dsp_size = part_info->mem.length;
		p_iav->dsp_mem = static_cast<uint8_t*>(mmap(NULL, p_iav->dsp_size,
			PROT_READ, MAP_SHARED, p_iav->fd_iav, part_info->mem.addr));
		if (p_iav->dsp_mem == MAP_FAILED) {
			perror("mmap (%d) failed: %s\n");
			rval = -1;
			break;
		}
		p_iav->dsp_phy_addr = part_info->mem.addr;
	} while (0);

	return rval;
}

static int ambamps_init_iav(ambamps_iav_t *p_iav)
{
	int rval = 0;

	do {
		if ((p_iav->fd_iav = open("/dev/iav", O_RDWR, 0)) < 0) {
			perror("/dev/iav");
			rval = -1;
			break;
		}

		if (ambamps_check_dsp_state(p_iav) < 0) {
			rval = -1;
			printf("Error: ambamps_check_dsp_state\n");
			break;
		}
		if (ambamps_map_dsp_buffer(p_iav) < 0) {
			rval = -1;
			printf("Error: ambamps_map_dsp_buffer\n");
			break;
		}
		printf("Init iav done.\n");
	} while (0);

	return rval;
}

static void ambamps_deinit_iav(ambamps_iav_t *p_iav)
{
	if (p_iav->dsp_mem) {
		if (munmap(p_iav->dsp_mem, p_iav->dsp_size) < 0 ) {
			perror("munmap ambamps dsp");
		}
		p_iav->dsp_mem = NULL;
	}

	if (p_iav->fd_iav >= 0) {
		close(p_iav->fd_iav);
		p_iav->fd_iav = -1;
	}
}

static int ambamps_get_dsp_input(ambamps_iav_t *p_iav)
{
	int rval = 0;
	struct iav_querydesc query_desc;
	struct iav_yuv_cap *data_cap = NULL;

	memset(&query_desc, 0, sizeof(query_desc));

	do {
		if (p_iav->query_buf_type == AMBAMPS_QUERY_BUF_CANVAS) {
			/* for canvas buffer, buffer id is canvas id  in 0 ~ 4*/
			query_desc.qid = IAV_DESC_CANVAS;
			query_desc.arg.canvas.canvas_id = p_iav->query_buf_id;
			query_desc.arg.canvas.non_block_flag &= ~IAV_BUFCAP_NONBLOCK;

			if (ioctl(p_iav->fd_iav, IAV_IOC_QUERY_DESC, &query_desc) < 0) {
				if (errno != EINTR) {
					perror("IAV_IOC_QUERY_DESC");
					rval = -1;
					break;
				}
			}
			data_cap = &query_desc.arg.canvas.yuv;
		} else if (p_iav->query_buf_type == AMBAMPS_QUERY_BUF_PYRAMID) {
			/* for pyramid buffer, buffer id is pyramid layer id in 0 ~ 5 */
			query_desc.qid = IAV_DESC_PYRAMID;
			query_desc.arg.pyramid.chan_id = 0;
			query_desc.arg.pyramid.non_block_flag &= ~IAV_BUFCAP_NONBLOCK;

			if (ioctl(p_iav->fd_iav, IAV_IOC_QUERY_DESC, &query_desc) < 0) {
				if (errno != EINTR) {
					perror("IAV_IOC_QUERY_DESC");
					rval = -1;
					break;
				}
			}
			data_cap = &query_desc.arg.pyramid.layers[p_iav->query_buf_id];
		} else {
			printf("Error: Unknown input type [%d]\n", p_iav->query_buf_type);
			rval = -1;
			break;
		}

		if ((data_cap->y_addr_offset == 0) || (data_cap->uv_addr_offset == 0)) {
			printf("Error: Data buffer [%d] address is NULL!\n", p_iav->query_buf_type);
			rval = -1;
			break;
		}
		memcpy(&p_iav->data_cap, data_cap, sizeof(p_iav->data_cap));
	} while(0);

	return rval;
}

int ambamps_execute_net(graph_ctx_t *pctx, init_live_cfg_t *pcfg)
{
	int rval = 0;
	int i = 0;
	struct net_input_cfg net_input;
	ambamps_iav_t *p_iav = &pcfg->iav;
	node_match_t *node=nullptr;
	int in_num = 0;

	memset((void *)&net_input, 0, sizeof(struct net_input_cfg));

	do {
		if (ambamps_get_dsp_input(&pcfg->iav) < 0) {
			ambamps_error("ambamps_get_dsp_input\n");
			rval = -1;
			break;
		}

		/* vp node */
		node = &pctx->node_list[0];
		in_num = node->in_num;
		net_input.in_num = in_num;

		for (i = 0; i < in_num; ++i) {
			net_input.in_desc[i].name = node->in_pair[i].port_name;
			net_input.in_desc[i].addr = (i == 0)? (p_iav->data_cap.y_addr_offset + p_iav->dsp_phy_addr) : \
				(p_iav->data_cap.uv_addr_offset + p_iav->dsp_phy_addr);
			net_input.in_desc[i].update_pitch = p_iav->data_cap.pitch;
#if AMBAMPS_DEBUG
			ambamps_log("node %s io %s phys addr: 0x%x width: %d height: %d pitch: %d\n", node->name,
				net_input.in_desc[i].name, net_input.in_desc[i].addr,
				p_iav->data_cap.width, p_iav->data_cap.height, net_input.in_desc[i].update_pitch);
#endif
		}

		for (i = 0; i < pctx->node_num; ++i) {
			node = &pctx->node_list[i];
			if (node->node_type == COPROC_VP) {
				if (ambamps_run_one_vp_node(node, &net_input) < 0) {
					ambamps_error("failed to run vp node %s\n", node->name);
					rval = -1;
					break;
				}
			} else if (node->node_type == COPROC_ARM) {
				if (ambamps_run_one_arm_node(node) < 0) {
					ambamps_error("failed to run arm node %s\n", node->name);
					rval = -1;
					break;
				}
			}
		}
		if (rval) break;

		if (ambamps_process_output(pctx, pcfg) < 0) {
			ambamps_error("failed to process output\n");
			rval = -1;
			break;
		}
	} while (live_mode_flag);

	return rval;
}

static void sigstop(int flag)
{
	live_mode_flag = 0;
	printf("Receive Stop Signal, exit live mode!\n");
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
	init_live_cfg_t init_cfg;
	node_match_t *node=nullptr;
	struct net_mem *p_cv_mem = nullptr;
	int i = 0, j = 0;

	memset(&graph_ctx, 0, sizeof(graph_ctx_t));

	signal(SIGINT, sigstop);
	signal(SIGQUIT, sigstop);
	signal(SIGTERM, sigstop);

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
		if (ambamps_init_iav(&init_cfg.iav) < 0) {
			printf("Error: ambamps_init_iav.\n");
			rval = -1;
			break;
		}
		if (ambamps_init_overlay(&init_cfg) < 0) {
			printf("Error: ambamps_init_overlay.\n");
			rval = -1;
			break;
		}
		ambamps_init_color_table(&init_cfg);

		if (construct_graph(&graph_ctx, init_cfg.model_dir.c_str()) < 0) {
			ambamps_error("failed to construct graph from compiled artifact folder %s\n", \
				init_cfg.model_dir.c_str());
			rval = -1;
			break;
		}

		/* first graph node must be vp */
		if (graph_ctx.node_list[0].node_type != COPROC_VP) {
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
			if (node->node_type == COPROC_VP) {
				if (ambamps_init_one_vp_node(node, &graph_ctx) < 0) {
					ambamps_error("failed to init vp node %s\n", node->name);
					rval = -1;
					break;
				}
			} else if (node->node_type == COPROC_ARM) {
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

		if (ambamps_execute_net(&graph_ctx, &init_cfg)) {
			ambamps_error("failed to run net\n");
			rval = -1;
			break;
		}
	} while(0);

	for (i = 0; i < graph_ctx.node_num; ++i) {
		node = &graph_ctx.node_list[i];
		if (node->node_type == COPROC_VP) {
			nnctrl_exit_net(node->node.vp_node.net_id);
			p_cv_mem = &node->node.vp_node.net_m;
			if (p_cv_mem->virt_addr && p_cv_mem->mem_size) {
				cavalry_mem_free(p_cv_mem->mem_size,
						p_cv_mem->phy_addr, p_cv_mem->virt_addr);
			}
		} else if (node->node_type == COPROC_ARM) {
			ambamps_release_one_arm_node(node);
			for (j = 0; j < (int)node->out_num; ++j) {
				if (node->out_pair[j].virt_addr && node->out_pair[j].size) {
					cavalry_mem_free(node->out_pair[j].size,
						node->out_pair[j].dram_addr, node->out_pair[j].virt_addr);
				}
			}
		}
	}
	if (fd_cav) {
		close(fd_cav);
		fd_cav = -1;
	}

	ambamps_deinit_overlay(&init_cfg.overlay);
	ambamps_deinit_iav(&init_cfg.iav);

	return rval;
}

