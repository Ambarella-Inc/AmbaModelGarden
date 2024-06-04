 /*******************************************************************************
 * ambamps_graph_ctrl.cpp
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
#include <unistd.h>
#include <dirent.h>
#include <algorithm>

#include "ambamps_priv.hpp"

int check_string_len_limit(std::string str, int len_limit, std::string item)
{
	int rval = 0;
	if (str.length() >= std::size_t(len_limit)) {
		ambamps_error("please increase length limit of MACRO [%s]  for string \"%s\"  "
			"with length [%ld].\n", item.c_str(), str.c_str(), str.length());
		rval = -1;
	}
	return rval;
}

std::string get_file_postfix(std::string filename, const int mode = 0)
{
	std::size_t pos = filename.rfind(".");
	std::string ret_str("");

	if (pos != std::string::npos && (pos + 1) < filename.length()) {
		std::string post_str = filename.substr(pos + 1);
		if (mode == 0) {
			std::transform(post_str.begin(), post_str.end(), post_str.begin(), ::tolower);
		}
		ret_str = post_str;
	}

	return ret_str;
}

bool is_cstring_match(const char* src, const char *match)
{
	return (strcmp(src, match) == 0)? true : false;
}

int get_file_index(std::string filename, int &index)
{
	std::string postfix = get_file_postfix(filename, 1);
	std::size_t pfx_fnd = filename.rfind("."+postfix);
	int rval = 0;

	do {
		if (pfx_fnd == std::string::npos) {
			ambamps_error("can't match file type .%s for file %s.\n", postfix.c_str(), filename.c_str());
			rval = -1;
			break;
		}
		std::string file_key_str("_split_");
		std::size_t file_key_fnd = filename.rfind(file_key_str);

		/* vproc vas_output */
		if (file_key_fnd == std::string::npos) {
			index = 0;
			rval = 0;
			break;
		}
		/* NN vas_output */
		std::size_t digit_start = file_key_fnd + file_key_str.length();
		std::size_t digit_end = pfx_fnd - 1;
		if (!isdigit(filename[pfx_fnd - 1])) {
			ambamps_error("filename format is incorrect, can't find file index for file %s."
				" Filename format should be *_split_#.dvi and *_split_#.h "
				"(# is Dag split number index).\n", filename.c_str());
			rval = -1; break;
		}
		for (int i = pfx_fnd - 1; i >= 0; --i) {
			if (isdigit(filename[i])) {
				digit_end = i;
				break;
			}
		}
		for (std::size_t i = digit_end; i >= file_key_fnd + file_key_str.length(); --i) {
			if (!isdigit(filename[i])) {
				digit_start = i + 1;
				break;
			}
		}
		index = atoi(filename.substr(digit_start, digit_end - digit_start + 1).c_str());
	}while(0);

	return rval;
}

bool sort_by_name_cnt(std::pair<std::string, int> item_1, std::pair<std::string, int> item_2)
{
	return (item_1.second < item_2.second);
}

int match_file_types_in_dir(const char *dir_path, const char *match, name_cnt_vec *file_list)
{
	DIR* dir = nullptr;
	struct dirent* ptr = nullptr;
	std::string filename, postfix;
	int idx = 0, max_idx = -1, file_cnt = 0;

	do {
		if ((dir = opendir(dir_path)) == nullptr) {
			ambamps_error("cannot open folder %s.\n", dir_path);
			file_cnt = -1;
			break;
		}
		while((ptr = readdir(dir)) != nullptr) {
			filename = ptr->d_name;
			postfix = get_file_postfix(filename);
			if (is_cstring_match(postfix.c_str(), match)) {
				if (get_file_index(filename, idx)) {
					continue;
				}
				file_list->push_back(std::make_pair(std::string(dir_path) + "/" + filename, idx));
				if (idx) max_idx = MAX(max_idx, idx);
			}
		}
		closedir(dir);

		if (max_idx > 0 && (max_idx + 1) != (int)file_list->size()) {
			ambamps_error("%s files in folder %s are disordered.\n", match, dir_path);
			file_cnt = -1;
			break;
		}

		if (file_list->size()) {
			std::sort(file_list->begin(), file_list->end(), sort_by_name_cnt);
			file_cnt = (file_list->size());
		}
	}while(0);

	return file_cnt;
}

std::string get_file_dirname(const char *file_path)
{
	std::string file(file_path), dir_path(".");
	size_t pos = file.rfind("/");

	if (pos != std::string::npos) {
		dir_path = file.substr(0, pos);
	}
	return dir_path;
}

std::string get_file_filename(const char *file_path)
{
	std::string file(file_path), basename(file_path);
	std::size_t pos = file.rfind("/");

	if (pos != std::string::npos) {
		basename = file.substr(pos + 1);
	}
	return basename;
}

int amend_relative_path(std::string dir_path, std::string &path)
{
	int rval = 0;
	struct stat statbuff;

	do {
		if (path.length() == 0) {
			break;
		}
		std::string try_abs_dir = dir_path + "/" + path;
		if (stat(try_abs_dir.c_str(), &statbuff) == 0) {
			path = try_abs_dir;
		} else if (stat(path.c_str(), &statbuff)) {
			ambamps_error("path %s is invalid\n", path.c_str());
			rval = -1;
		}
	} while(0);

	return rval;
}

int amend_directory_path(priv_body_t *p_body, priv_node_vec *p_node_list,
	const char *json_file)
{
	int rval = 0;
	std::string dir_name("");

	do {
		/* file path is relative in json file */
		if (strlen(json_file) == 0) {
			break;
		}
		dir_name = get_file_dirname(json_file);
		for (auto &nit: *p_node_list) {
			priv_node_t *node = &nit.second;
			if (amend_relative_path(dir_name, node->compiled_bin)) {
				ambamps_error("failed to amend relative path for %s\n", \
					node->compiled_bin.c_str());
				rval = -1;
				break;
			}
			if (amend_relative_path(dir_name, node->ext_lib.lib_file)) {
				ambamps_error("failed to amend relative path for %s\n", \
					node->ext_lib.lib_file.c_str());
				rval = -1;
				break;
			}
			if (amend_relative_path(dir_name, node->ext_lib.lib_prim_file)) {
				ambamps_error("failed to amend relative path for %s\n", \
					node->ext_lib.lib_prim_file.c_str());
				rval = -1;
				break;
			}
		}
		if (rval) break;

		p_body->intr_file = "intrinsics/intrinsics.json";
		if (amend_relative_path(dir_name, p_body->intr_file)) {
			ambamps_error("failed to amend relative path for %s\n", \
				p_body->intr_file.c_str());
			rval = -1;
			break;
		}
	} while(0);

	return rval;
}

int get_node_by_id(priv_node_t **p_node, priv_node_vec *p_node_list, uint32_t id)
{
	int found = 0;

	for (auto &nd_it: *p_node_list) {
		if (nd_it.second.id == id) {
			*p_node = &nd_it.second;
			found = 1;
			break;
		}
	}
	if (!found) {
		ambamps_error("cannot find node id %d\n", id);
	}

	return (found? 0 : -1);
}

int get_node_by_name(priv_node_t **p_node, priv_node_vec *p_node_list, std::string name)
{
	int found = 0;

	for (auto &nd_it: *p_node_list) {
		if (nd_it.first.compare(name) == 0) {
			*p_node = &nd_it.second;
			found = 1;
			break;
		}
	}
	if (!found) {
		ambamps_error("cannot find node name %s\n", name.c_str());
	}

	return (found? 0 : -1);
}

int sort_out_body_nodes(priv_body_t *p_body, priv_node_vec *p_node_list, const char *json_file)
{
	int rval = 0;

	do {
		if (amend_directory_path(p_body, p_node_list, json_file)) {
			ambamps_error("failed to amend directory path\n");
			rval = -1;
			break;
		}

		/* body->nodes */
		for (const auto &nd_nm: p_body->nodes) {
			priv_node_t *node = nullptr;
			if (get_node_by_name(&node, p_node_list, nd_nm)) {
				ambamps_error("get_node_by_name %s.\n", nd_nm.c_str());
				rval = -1;
				break;
			}
			p_body->nodes_map.push_back(std::make_pair(nd_nm, *node));
		}
		if (rval) break;

		/* node->next_nodes */
		for (auto &nd_it: *p_node_list) {
			for (const auto &next_nd_nm: nd_it.second.next_nodes) {
				priv_node_t *node;
				if (get_node_by_name(&node, p_node_list, next_nd_nm)) {
					ambamps_error("get_node_by_name %s.\n", next_nd_nm.c_str());
					rval = -1;
					break;
				}
				nd_it.second.nodes_map.push_back(std::make_pair(next_nd_nm, *node));
			}
			if (rval) break;
		}
		if (rval) break;
	} while(0);

	return rval;
}

void node_vec_to_map(priv_node_map *p_map, priv_node_vec *p_vec)
{
	for (const auto &vit: *p_vec) {
		p_map->emplace(vit.first, vit.second);
	}
}

int fill_node_joint(ambamps_graph_node_joint_t &node_jnt,
		priv_node_t *from_node, priv_node_t *to_node, const uint32_vec *jnt_index)
{
	int rval = 0;
	std::string from_name, to_name;
	uint32_t from_idx = -1, to_idx = -1;

	do {
		memset(&node_jnt, 0, sizeof(node_jnt));
		node_jnt.from_node_id = from_node->id;
		node_jnt.to_node_id = to_node->id;
		from_idx = jnt_index->front();
		to_idx = jnt_index->back();
		if ((from_idx + 1) > from_node->outputs.size()) {
			ambamps_error("cannot find index %d for outputs of node %s\n", from_idx,
				from_node->name.c_str());
			rval = -1;
			break;
		}
		if ((to_idx + 1)> to_node->inputs.size()) {
			ambamps_error("cannot find index %d for inputs of node %s\n", to_idx,
				to_node->name.c_str());
			rval = -1;
			break;
		}
		from_name = from_node->outputs[from_idx].first;
		to_name = to_node->inputs[to_idx].first;

		rval = check_string_len_limit(from_name, STR_LEN_MAX(IO_NAME), STR(IO_NAME));
		if (rval) break;
		strncpy(node_jnt.from_port_name, from_name.c_str(), CAVALRY_IO_NAME_MAX - 1);

		rval = check_string_len_limit(to_name, STR_LEN_MAX(IO_NAME), STR(IO_NAME));
		if (rval) break;
		strncpy(node_jnt.to_port_name, to_name.c_str(), CAVALRY_IO_NAME_MAX - 1);
	} while(0);
	if (rval) {
		ambamps_error("node joint from node %s io id %d, to node %s io id %d\n",\
			from_node->name.c_str(), jnt_index->front(),
			to_node->name.c_str(), jnt_index->back());
	}

	return rval;
}

int get_node_joint_description(node_jnt_vec *p_jnt, priv_node_vec *p_node_list)
{
	int rval = 0;
	ambamps_graph_node_joint_t node_jnt;

	for (const auto& nit: *p_node_list) {
		priv_node_t cur_node = nit.second;
		priv_node_map nodes_map;
		node_vec_to_map(&nodes_map, &cur_node.nodes_map);

		/* normal nodes joint */
		for (const auto &joint_nit: cur_node.next_nodes_joint) {
			priv_node_t next_node = nodes_map[joint_nit.first];
			if (fill_node_joint(node_jnt, &cur_node, &next_node, &joint_nit.second)) {
				ambamps_error("failed to fill node joint info between node %s and node %s\n", \
					cur_node.name.c_str(), next_node.name.c_str());
				rval = -1;
				break;
			}
			p_jnt->push_back(node_jnt);
		}
		if (rval) break;
	}

	return rval;
}

uint32_vec::iterator find_vec_pos(uint32_vec *p_order, uint32_t val)
{
	uint32_vec::iterator pos = p_order->end();
	for (uint32_vec::iterator it = p_order->begin(); it != p_order->end(); ++it) {
		if (val == *it) {
			pos = it;
			break;
		}
	}

	return pos;
}

int get_node_exec_order(uint32_vec *p_order, node_jnt_vec *p_jnt)
{
	int rval = 0;

	uint32_t cur_nd_id = 0xffff, to_nd_id = 0xffff;
	uint32_vec::iterator dit = p_order->begin();

	for (uint32_t i = 0; i < p_order->size(); ++i) {
		cur_nd_id = *(dit + i);
		for (const auto &jit: *p_jnt) {
			if (jit.from_node_id == cur_nd_id) {
				to_nd_id = jit.to_node_id;
				auto pos = find_vec_pos(p_order, to_nd_id);
				if (pos != p_order->end()) {
					p_order->erase(pos);
				}
				p_order->push_back(to_nd_id);
			}
		}
	}

	return rval;
}

#if defined(AMBAMPS_CAVALRY_V2)
int construct_graph(graph_ctx_t *pctx, const char* model_dir)
{
	int rval = 0;
	struct json_object *root_obj = nullptr;
	name_cnt_vec json_list;
	std::string json_file;
	priv_body_t graph_body;
	priv_node_vec graph_node_list;
	node_jnt_vec node_jnt_list;
	uint32_vec node_order;
	int node_num = -1, node_id = -1, jnt_num = -1;
	priv_node_t *node = nullptr;
	node_match_t *pnet = nullptr;
	ambamps_graph_node_joint_t *pjnt = nullptr;

	memset(pctx, 0, sizeof(graph_ctx_t));
	node_order.push_back(0);

	do {
		if (match_file_types_in_dir(model_dir, "json", &json_list) <= 0) {
			ambamps_error("cannot find json file in folder %s\n", model_dir);
			rval = -1;
			break;
		}
		json_file = json_list.front().first;
		if (!(root_obj = json_object_from_file(json_file.c_str()))) {
			ambamps_error("failed to get json object from file %s.\n", json_file.c_str());
			rval = -1;
			break;
		}
		if (parse_graph_body(&graph_body, &graph_node_list, root_obj) < 0) {
			ambamps_error("failed to parse graph body from json file %s\n", json_file.c_str());
			rval = -1;
			break;
		}
		if (graph_node_list.size() == 0) {
			ambamps_error("node num is 0!\n");
			rval = -1;
			break;
		}
		if(sort_out_body_nodes(&graph_body, &graph_node_list, json_file.c_str()) < 0) {
			ambamps_error("failed to sort body and nodes.\n");
			rval = -1;
			break;
		}
		if (graph_node_list.size() > AMBAMPS_NODE_NUM_MAX) {
			ambamps_error("node num is more than expected (%ld > %d)\n", \
				graph_node_list.size(), AMBAMPS_NODE_NUM_MAX);
			rval = -1;
			break;
		}
		if (graph_node_list.size() > 1) {
			if (get_node_joint_description(&node_jnt_list, &graph_node_list) < 0) {
				ambamps_error("failed to get node joint list\n");
				rval = -1;
				break;
			}
			if (node_jnt_list.size() > AMBAMPS_NODE_JOINT_NUM_MAX) {
				ambamps_error("node joint num is more than expected (%ld > %d)\n", \
					node_jnt_list.size(), AMBAMPS_NODE_JOINT_NUM_MAX);
				rval = -1;
				break;
			}
			if (get_node_exec_order(&node_order, &node_jnt_list) < 0) {
				ambamps_error("failed to get node execution order\n");
				rval = -1;
				break;
			}
		}
		/* fill in node list for execution */
		node_num = graph_node_list.size();
		pnet = pctx->node_list;
		pctx->node_num = node_num;
		for (int i = 0; i < node_num; ++i) {
			node_id = node_order[i];
			pctx->exec_index[node_id] = i;
			if (get_node_by_id(&node, &graph_node_list, node_id) < 0) {
				ambamps_error("failed to get node with id %d\n", node_id);
				rval = -1;
				break;
			}
			pnet[i].id = node->id;
			strncpy(pnet[i].name, node->name.c_str(), AMBAMPS_NODE_NAME_MAX - 1);
			pnet[i].node_type = node->coproc_type;
			if (node->coproc_type == AMBAMPS_COPROC_VP) {
				strncpy(pnet[i].node.vp_node.net_fn, node->compiled_bin.c_str(),
					AMBAMPS_FILE_PATH_MAX - 1);
			} else if (node->coproc_type == AMBAMPS_COPROC_ARM) {
				std::string ext_attr;
				strncpy(pnet[i].node.arm_node.lib_fn, node->ext_lib.lib_file.c_str(),
					AMBAMPS_FILE_PATH_MAX - 1);
				cvb_io_vec::iterator ioit = node->inputs.begin();
				pnet[i].in_num = node->inputs.size();
				for (uint32_t j = 0; j < pnet[i].in_num; ++j) {
					pnet[i].in_pair[j].dim.plane = (ioit + j)->second.dim.data()[0];
					pnet[i].in_pair[j].dim.depth = (ioit + j)->second.dim.data()[1];
					pnet[i].in_pair[j].dim.height = (ioit + j)->second.dim.data()[2];
					pnet[i].in_pair[j].dim.width = (ioit + j)->second.dim.data()[3];
					pnet[i].in_pair[j].data_fmt.sign = (ioit + j)->second.data_format.data()[0];
					pnet[i].in_pair[j].data_fmt.size = (ioit + j)->second.data_format.data()[1];
					pnet[i].in_pair[j].data_fmt.expoffset = (ioit + j)->second.data_format.data()[2];
					pnet[i].in_pair[j].data_fmt.expbits = (ioit + j)->second.data_format.data()[3];
					strncpy(pnet[i].in_pair[j].port_name, (ioit + j)->first.c_str(),
						AMBAMPS_IO_NAME_MAX - 1);
				}
				ioit = node->outputs.begin();
				pnet[i].out_num = node->outputs.size();
				for (uint32_t j = 0; j < pnet[i].out_num; ++j) {
					pnet[i].out_pair[j].dim.plane = (ioit + j)->second.dim.data()[0];
					pnet[i].out_pair[j].dim.depth = (ioit + j)->second.dim.data()[1];
					pnet[i].out_pair[j].dim.height = (ioit + j)->second.dim.data()[2];
					pnet[i].out_pair[j].dim.width = (ioit + j)->second.dim.data()[3];
					pnet[i].out_pair[j].data_fmt.sign = (ioit + j)->second.data_format.data()[0];
					pnet[i].out_pair[j].data_fmt.size = (ioit + j)->second.data_format.data()[1];
					pnet[i].out_pair[j].data_fmt.expoffset = (ioit + j)->second.data_format.data()[2];
					pnet[i].out_pair[j].data_fmt.expbits = (ioit + j)->second.data_format.data()[3];
					strncpy(pnet[i].out_pair[j].port_name, (ioit + j)->first.c_str(),
						AMBAMPS_IO_NAME_MAX - 1);
				}
				if (parse_extern_primitive(ext_attr, node->ext_lib.lib_prim_file.c_str()) < 0) {
					ambamps_error("failed to parse extern primive attr from file %s\n", \
						node->ext_lib.lib_prim_file.c_str());
					rval = -1;
					break;
				}
				strncpy(pnet[i].node.arm_node.lib_attr, ext_attr.c_str(), AMBAMPS_FILE_PATH_MAX - 1);
			}
		}
		if (rval) break;

		/* file in primary io */
		priv_node_map nodes_map;
		node_vec_to_map(&nodes_map, &graph_body.nodes_map);

		pctx->in_num = graph_body.inputs.size();
		cvb_io_vec::iterator ioit = graph_body.inputs.begin();
		for (uint32_t i = 0; i < pctx->in_num; ++i) {
			strncpy(pctx->in_pair[i].port_name, (ioit + i)->first.c_str(), AMBAMPS_IO_NAME_MAX - 1);
		}

		pctx->out_num = graph_body.outputs.size();
		ioit = graph_body.outputs.begin();
		for (uint32_t i = 0; i < pctx->out_num; ++i) {
			strncpy(pctx->out_pair[i].port_name, (ioit + i)->first.c_str(), AMBAMPS_IO_NAME_MAX - 1);
		}

		/* fill in node joint info */
		jnt_num = node_jnt_list.size();
		node_jnt_vec::iterator jit = node_jnt_list.begin();
		pjnt = pctx->node_joint;
		pctx->node_jnt_num = jnt_num;
		for (int i = 0; i < jnt_num; ++i) {
			pjnt[i] = *(jit + i);
		}

		/* model intrinsic param */
		if (parse_model_intrinsic_param(&pctx->intr_param,
			graph_body.intr_file.c_str())) {
			ambamps_error("failed to parse intrinsics params from file %s\n", graph_body.intr_file.c_str());
			rval = -1;
			break;
		}
	} while(0);

	return rval;
}
#elif defined(AMBAMPS_CAVALRY_V3)
int construct_graph(graph_ctx_t *pctx, const char* model_dir)
{
	int rval = 0;
	name_cnt_vec ambapb_list;
	std::string filename(""), model_name(""), cavalry_bin_name(""), intr_file("");
	std::size_t pos = std::string::npos;
	node_match_t *pnet = &pctx->node_list[0];

	pctx->node_num = 1;
	pctx->exec_index[0] = 0;
	pctx->node_jnt_num = 0;

	pnet->id = 0;
	pnet->node_type = AMBAMPS_COPROC_VP;

	do {
		if(match_file_types_in_dir(model_dir, "onnx", &ambapb_list) <= 0) {
			ambamps_error("cannot find ambapb file in folder %s\n", model_dir);
			rval = -1;
			break;
		}
		filename = get_file_filename(ambapb_list.front().first.c_str());
		pos = filename.find(".");
		model_name = filename.substr(0,pos);
		cavalry_bin_name = std::string(model_dir) + "/" + model_name + ".bin";

		strncpy(pnet->name, model_name.c_str(), AMBAMPS_NODE_NAME_MAX - 1);
		strncpy(pnet->node.vp_node.net_fn, cavalry_bin_name.c_str(), AMBAMPS_FILE_PATH_MAX - 1);

		/* fill in_pair/out_pair in ambamps_graph_io_cfg_CV3x */

		/* model intrinsic param */
		intr_file = std::string(model_dir) + "/intrinsics/intrinsics.json";
		if (parse_model_intrinsic_param(&pctx->intr_param, intr_file.c_str())) {
			ambamps_error("failed to parse intrinsics params from file %s\n", intr_file.c_str());
			rval = -1;
			break;
		}
	} while(0);

	return rval;
}
#endif


