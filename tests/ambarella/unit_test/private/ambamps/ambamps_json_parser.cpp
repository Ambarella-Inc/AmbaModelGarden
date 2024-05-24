/*******************************************************************************
 * ambamps_json_parser.cpp
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

#include "ambamps_priv.hpp"

int get_json_entry_list(struct json_object *obj, lh_entry_vec *p_list)
{
	int rval = 0;
	struct lh_entry *entry = NULL;

	do {
		if (!obj) {
			ambamps_error("null json object, err: %s.\n", json_util_get_last_err());
			rval = -1;
			break;
		}
		if (json_object_get_type(obj) != json_type_object) {
			ambamps_warn("Warning: no entry list.\n");
			break;
		}

		entry = json_object_get_object(obj)->head;
		while (entry) {
			p_list->push_back(entry);
			entry = entry->next;
		}
	} while(0);

	return rval;
}

int parse_model_intrinsic_param(intr_param_t *intr_param, const char* json_file)
{
	int rval = 0;
	struct json_object *root_obj = nullptr, *lbl_obj = nullptr;
	lh_entry_vec intr_items, label_items;
	const char *entry_key = nullptr;
	int id = 0;

	do {
		if (!(root_obj = json_object_from_file(json_file))) {
			ambamps_error("failed to get json object from file %s.\n", json_file);
			rval = -1;
			break;
		}
		if (get_json_entry_list(root_obj, &intr_items) < 0) {
			ambamps_error("failed to get entry list.\n");
			rval = -1;
			break;
		}
		for (const auto &it: intr_items) {
			entry_key = (char*)lh_entry_k(it);
			if (is_cstring_match(entry_key, "label_map")) {
				lbl_obj = (struct json_object*)lh_entry_v(it);
			}
		}
		if (lbl_obj == nullptr) {
			ambamps_error("cannot find label map info in file %s.\n", json_file);
			rval = -1;
			break;
		}
		if (get_json_entry_list(lbl_obj, &label_items) < 0) {
			ambamps_error("failed to get entry list.\n");
			rval = -1;
			break;
		}
		for (const auto &it: label_items) {
			id = atoi((const char*)lh_entry_k(it));
			if (id >= AMBAMPS_LABEL_NUM_MAX) {
				ambamps_error("label id %d exceeds valid num %d\n", id,
					AMBAMPS_LABEL_NUM_MAX);
				rval = -1;
				break;
			}
			strncpy(intr_param->label_map[id],
				json_object_get_string((struct json_object *)lh_entry_v(it)),
				AMBAMPS_LABEL_NAME_LEN);
		}
		if (rval) break;
	} while(0);

	return rval;
}

int parse_extern_primitive(std::string &attr, const char *json_file)
{
	int rval = 0;
	struct json_object *root_obj = nullptr, *prim_obj = nullptr, *iter_obj = nullptr;
	struct json_object *type_obj = nullptr, *extern_obj = nullptr, *attr_obj = nullptr;
	int prim_num = 0;

	do {
		if (!(root_obj = json_object_from_file(json_file))) {
			ambamps_error("failed to get json object from file %s.\n", json_file);
			rval = -1;
			break;
		}
		if (!json_object_object_get_ex(root_obj, "primitives", &prim_obj)) {
			ambamps_error("null primitives object. error code: %s\n", json_util_get_last_err());
			rval = -1;
			break;
		}
		if ((prim_num = json_object_array_length(prim_obj)) == 0) {
			ambamps_error("zero primitives.\n");
			rval = -1;
			break;
		}
		for (int i = 0; i < prim_num; ++i) {
			lh_entry_vec prim_items;
			iter_obj = json_object_array_get_idx(prim_obj, i);
			if (get_json_entry_list(iter_obj, &prim_items) < 0) {
				ambamps_error("failed to get entry list\n");
				rval = -1;
				break;
			}
			for (const auto &it: prim_items) {
				const char *entry_key = (char*)lh_entry_k(it);
				if (is_cstring_match(entry_key, "type")) {
					type_obj = (struct json_object*)lh_entry_v(it);
				} else if (is_cstring_match(entry_key, "extern")) {
					extern_obj = (struct json_object*)lh_entry_v(it);
				}
			}
			if (!type_obj) {
				ambamps_error("failed to find type keyword in primitive file %s\n", json_file);
				rval = -1;
				break;
			}
			if (!is_cstring_match("extern", json_object_get_string(type_obj))) {
				continue;
			}
			if (!extern_obj) {
				ambamps_error("failed to find extern keyword in primitive file %s\n", json_file);
				rval = -1;
				break;
			}
			if (!json_object_object_get_ex(extern_obj, "attr", &attr_obj)) {
				ambamps_error("null attr object. error code: %s\n", json_util_get_last_err());
				rval = -1;
				break;
			}
			attr = std::string(json_object_get_string(attr_obj));
		}
	} while(0);

	return rval;
}

int parse_body_io(cvb_io_vec *p_io_list, struct json_object *body_obj, io_type_t io_type)
{
	int rval = 0;
	struct json_object *io_obj = nullptr, *id_obj = nullptr, *dim_obj = nullptr, *iter_obj = nullptr;
	struct json_object *df_obj = nullptr, *sign_obj = nullptr, *datasize_obj = nullptr;
	struct json_object *expoff_obj = nullptr, *expbits_obj = nullptr;
	int io_num = 0, dim_cnt = 0;
	cvb_io_desc_t io_desc;
	std::string io_str;

	if (io_type == IO_INPUT) {
		io_str = "inputs";
	} else if (io_type == IO_OUTPUT) {
		io_str = "outputs";
	} else if (io_type == IO_INTERMEDIATE) {
		io_str = "intermediates";
	}

	do {
		if (!json_object_object_get_ex(body_obj, io_str.c_str(), &io_obj)) {
			ambamps_error("null %s object. error code: %s\n", io_str.c_str(), json_util_get_last_err());
			rval = -1;
			break;
		}
		if ((io_num = json_object_array_length(io_obj)) == 0) {
			break;
		}
		for (int i = 0; i < io_num; ++ i) {
			lh_entry_vec df_items_list;
			io_desc.dim.clear();
			io_desc.data_format.clear();
			iter_obj = json_object_array_get_idx(io_obj, i);
			if (!iter_obj) {
				ambamps_error("null %s object. error code: %s\n", io_str.c_str(), json_util_get_last_err());
				rval = -1;
				break;
			}
			if (!json_object_object_get_ex(iter_obj, "id", &id_obj)) {
				ambamps_error("null id object. error code: %s\n", json_util_get_last_err());
				rval = -1;
				break;
			}
			if (!json_object_object_get_ex(iter_obj, "dimension", &dim_obj)) {
				ambamps_error("null dimension object. error code: %s\n", json_util_get_last_err());
				rval = -1;
				break;
			}
			if (!json_object_object_get_ex(iter_obj, "data-format", &df_obj)) {
				ambamps_error("null data-format object. error code: %s\n", json_util_get_last_err());
				rval = -1;
				break;
			}
			if (get_json_entry_list(df_obj, &df_items_list) < 0) {
				ambamps_error("failed to get json entry list of data-format.\n");
				rval = -1;
				break;
			}
			for (const auto &dfit: df_items_list) {
				const char *entry_key = (char*)lh_entry_k(dfit);
				if (is_cstring_match(entry_key, "sign")) {
					sign_obj = (struct json_object*)lh_entry_v(dfit);
				} else if (is_cstring_match(entry_key, "datasize")) {
					datasize_obj = (struct json_object*)lh_entry_v(dfit);
				} else if (is_cstring_match(entry_key, "expoff")) {
					expoff_obj = (struct json_object*)lh_entry_v(dfit);
				} else if (is_cstring_match(entry_key, "expbits")) {
					expbits_obj = (struct json_object*)lh_entry_v(dfit);
				}
			}
			io_desc.data_format.push_back(json_object_get_int(sign_obj));
			io_desc.data_format.push_back(json_object_get_int(datasize_obj));
			io_desc.data_format.push_back(json_object_get_int(expoff_obj));
			io_desc.data_format.push_back(json_object_get_int(expbits_obj));
			if ((dim_cnt = json_object_array_length(dim_obj)) == 0) {
				ambamps_error("zero dimension item.\n");
				rval = -1;
				break;
			}
			for (int j = 0; j < dim_cnt; ++j) {
				io_desc.dim.push_back(json_object_get_int(json_object_array_get_idx(dim_obj, j)));
			}
			p_io_list->push_back(std::make_pair(std::string(json_object_get_string(id_obj)), io_desc));
		}
		if (rval) break;
	}while(0);

	return rval;
}

int parse_body_nodes(str_vec *p_nodes, struct json_object *body_obj)
{
	int rval = 0;
	struct json_object *nodes_obj = nullptr, *id_obj = nullptr, *type_obj = nullptr, *iter_obj = nullptr;
	int node_num = 0;

	do {
		if (!json_object_object_get_ex(body_obj, "nodes", &nodes_obj)) {
			ambamps_error("null nodes object. error code: %s\n", json_util_get_last_err());
			rval = -1;
			break;
		}
		if ((node_num = json_object_array_length(nodes_obj)) == 0) {
			ambamps_error("body zero nodes.\n");
			rval = -1;
			break;
		}
		for (int i = 0; i < node_num; ++i) {
			iter_obj = json_object_array_get_idx(nodes_obj, i);
			if (!iter_obj) {
				ambamps_error("null nodes object. error code: %s\n", json_util_get_last_err());
				rval = -1;
				break;
			}
			if (!json_object_object_get_ex(iter_obj, "id", &id_obj)) {
				ambamps_error("null id object. error code: %s\n", json_util_get_last_err());
				rval = -1;
				break;
			}
			if (!json_object_object_get_ex(iter_obj, "type", &type_obj)) {
				ambamps_error("null type object. error code: %s\n", json_util_get_last_err());
				rval = -1;
				break;
			}
			p_nodes->push_back(std::string(json_object_get_string(id_obj)));
		}
		if (rval) break;
	} while(0);

	return rval;
}

int get_body_io_by_name(cvb_io_desc_pair &io_pair, cvb_io_vec *p_io_list, std::string io_name)
{
	int found = 0;

	for (const auto &it: *p_io_list) {
		if (it.first.compare(io_name) == 0) {
			io_pair = it;
			found = 1;
			break;
		}
	}

	return (found? 0 : -1);
}

int get_next_nodes(priv_node_t *p_node, struct json_object *body_obj, std::string name)
{
	int rval = 0;
	struct json_object *nodes_obj = nullptr, *iter_obj = nullptr;
	struct json_object *id_obj = nullptr, *type_obj = nullptr, *src_ids_obj = nullptr, *out_ids_obj = nullptr;
	int node_num = 0, io_num = 0;
	node_io_map nodes_io_map;

	do {
		if (!json_object_object_get_ex(body_obj, "nodes", &nodes_obj)) {
			ambamps_error("null nodes object. error code: %s\n", json_util_get_last_err());
			rval = -1;
			break;
		}
		if ((node_num = json_object_array_length(nodes_obj)) == 0) {
			ambamps_error("body zero nodes.\n");
			rval = -1;
			break;
		}

		/* generate nodes io map */
		for (int i = 0; i < node_num; ++i) {
			node_io_t node_io;
			std::string node_name, io_name;
			iter_obj = json_object_array_get_idx(nodes_obj, i);
			if (!iter_obj) {
				ambamps_error("null nodes object. error code: %s\n", json_util_get_last_err());
				rval = -1;
				break;
			}
			/* node->id */
			if (!json_object_object_get_ex(iter_obj, "id", &id_obj)) {
				ambamps_error("null id object. error code: %s\n", json_util_get_last_err());
				rval = -1;
				break;
			}
			/* node->type */
			if (!json_object_object_get_ex(iter_obj, "type", &type_obj)) {
				ambamps_error("null type object. error code: %s\n", json_util_get_last_err());
				rval = -1;
				break;
			}
			node_name = std::string(json_object_get_string(id_obj));

			/* node->src-ids */
			if (!json_object_object_get_ex(iter_obj, "src-ids", &src_ids_obj)) {
				ambamps_error("null src ids object. error code: %s\n", json_util_get_last_err());
				rval = -1;
				break;
			}
			if ((io_num = json_object_array_length(src_ids_obj)) == 0) {
				ambamps_error("zero src ids item.\n");
				rval = -1;
				break;
			}
			for (int j = 0; j < io_num; ++j) {
				io_name = std::string(json_object_get_string(json_object_array_get_idx(src_ids_obj, j)));
				node_io.inputs.push_back(io_name);
			}

			/* node->out-ids */
			if (!json_object_object_get_ex(iter_obj, "out-ids", &out_ids_obj)) {
				ambamps_error("null out ids object. error code: %s\n", json_util_get_last_err());
				rval = -1;
				break;
			}
			if ((io_num = json_object_array_length(out_ids_obj)) == 0) {
				ambamps_error("zero out ids item.\n");
				rval = -1;
				break;
			}
			for (int j = 0; j < io_num; ++j) {
				io_name = std::string(json_object_get_string(json_object_array_get_idx(out_ids_obj, j)));
				node_io.outputs.push_back(io_name);
			}
			nodes_io_map.emplace(node_name, node_io);
		}
		if (rval) break;

		/* search for next nodes */
		node_io_map::iterator node_it = nodes_io_map.find(name);
		if (node_it == nodes_io_map.end()) {
			ambamps_error("cannot find node %s in body.\n", name.c_str());
			rval = -1;
			break;
		}
		for (const auto &nit: nodes_io_map) {
			if (nit.first.compare(name) == 0) continue;

			str_vec cur_nd_outs = node_it->second.outputs;
			str_vec::iterator cur_out_it = cur_nd_outs.begin();
			str_vec next_nd_ins = nit.second.inputs;
			str_vec::iterator next_in_it = next_nd_ins.begin();

			int match = 0;
			for (uint32_t i = 0; i < cur_nd_outs.size(); ++i) {
				for (uint32_t j = 0; j < next_nd_ins.size(); ++j) {
					if ((cur_out_it + i)->compare(*(next_in_it + j)) == 0) {
						uint32_vec index;
						index.push_back(i);
						index.push_back(j);
						p_node->next_nodes_joint.push_back(std::make_pair(nit.first, index));
						match = 1;
						break;
					}
				}
			}
			if (match) {
				p_node->next_nodes.push_back(nit.first);
			}
		}
	} while(0);

	return rval;
}

int parse_node_io(priv_node_t *p_node, priv_body_t *p_body,
			struct json_object *node_obj, io_type_t io_type)
{
	int rval = 0;
	int io_num = 0;
	struct json_object *io_obj = nullptr;
	std::string io_str, io_name;
	cvb_io_vec *p_io_list = nullptr, *p_body_io_list = nullptr;

	if (io_type == IO_INPUT) {
		io_str = "src-ids";
		p_io_list = &p_node->inputs;
	} else if (io_type == IO_OUTPUT) {
		io_str = "out-ids";
		p_io_list = &p_node->outputs;
	}

	do {
		if (io_type == IO_INPUT) {
			p_body_io_list = &p_body->inputs;
		} else if (io_type == IO_OUTPUT) {
			p_body_io_list = &p_body->outputs;
		}
		if (!json_object_object_get_ex(node_obj, io_str.c_str(), &io_obj)) {
			ambamps_error("null %s object. error code: %s\n", io_str.c_str(), json_util_get_last_err());
			rval = -1;
			break;
		}
		if ((io_num = json_object_array_length(io_obj)) == 0) {
			ambamps_error("zero %s item.\n", io_str.c_str());
			rval = -1;
			break;
		}
		for (int j = 0; j < io_num; ++j) {
			io_name = std::string(json_object_get_string(json_object_array_get_idx(io_obj, j)));
			if (io_name.length() == 0) continue;
			cvb_io_desc_pair io_pair;
			if (get_body_io_by_name(io_pair, &p_body->intermediates, io_name) &&
				get_body_io_by_name(io_pair, p_body_io_list, io_name)) {
			}
			p_io_list->push_back(std::make_pair(io_name, io_pair.second));
		}
	} while(0);

	return rval;
}

int node_coproc_type_string2num(ambamps_coproc_type_t &coproc_type,
	const char *node_coprocessor)
{
	int rval = 0;

	if (is_cstring_match(node_coprocessor, "vp")) {
		coproc_type = AMBAMPS_COPROC_VP;
	} else if (is_cstring_match(node_coprocessor, "arm")) {
		coproc_type = AMBAMPS_COPROC_ARM;
	} else {
		ambamps_error("unknown coprocessor type %s.\n", node_coprocessor);
		rval = -1;
	}

	return rval;
}

int parse_graph_nodes(priv_body_t *p_body, priv_node_vec *p_node_list, struct json_object *body_obj)
{
	int rval = 0;
	struct json_object *iter_obj = nullptr, *nodes_obj = nullptr, *id_obj = nullptr, *type_obj = nullptr;
	struct json_object *attr_obj = nullptr;
	int node_num = 0, io_num = 0;
	std::string io_name;

	do {
		if (!json_object_object_get_ex(body_obj, "nodes", &nodes_obj)) {
			ambamps_error("null nodes object. error code: %s\n", json_util_get_last_err());
			rval = -1;
			break;
		}
		if ((node_num = json_object_array_length(nodes_obj)) == 0) {
			ambamps_error("body zero nodes.\n");
			rval = -1;
			break;
		}
		for (int i = 0; i < node_num; ++i) {
			priv_node_t node;

			node.id = p_node_list->size();
			iter_obj = json_object_array_get_idx(nodes_obj, i);
			if (!iter_obj) {
				ambamps_error("null nodes object. error code: %s\n", json_util_get_last_err());
				rval = -1;
				break;
			}

			/* node->type */
			if (!json_object_object_get_ex(iter_obj, "type", &type_obj)) {
				ambamps_error("null type object. error code: %s\n", json_util_get_last_err());
				rval = -1;
				break;
			}
			/* node->id */
			if (!json_object_object_get_ex(iter_obj, "id", &id_obj)) {
				ambamps_error("null id object. error code: %s\n", json_util_get_last_err());
				rval = -1;
				break;
			}
			node.name = std::string(json_object_get_string(id_obj));

			/* next nodes */
			if (get_next_nodes(&node, body_obj, node.name)) {
				ambamps_error("failed to get next nodes for node %s.\n", node.name.c_str());
				rval = -1;
				break;
			}

			/* node->src-ids */
			if (parse_node_io(&node, p_body, iter_obj, IO_INPUT)) {
				ambamps_error("failed to parse src ids of node %s\n", node.name.c_str());
				rval = -1;
				break;
			}
			/* node->out-ids */
			if (parse_node_io(&node, p_body, iter_obj, IO_OUTPUT)) {
				ambamps_error("failed to parse out ids of node %s\n", node.name.c_str());
				rval = -1;
				break;
			}

			/* node->attributes */
			if (!json_object_object_get_ex(iter_obj, "attributes", &attr_obj)) {
				ambamps_error("null attributes object. error code: %s\n", json_util_get_last_err());
				rval = -1;
				break;
			}

			struct json_object *coproc_obj = nullptr, *vas_obj = nullptr;
			struct json_object *exts_obj = nullptr, *lib_obj = nullptr, *arms_obj = nullptr;
			struct json_object *iter_ext_obj = nullptr, *iter_arm_obj = nullptr;
			struct json_object *iport_ids_obj = nullptr, *oport_ids_obj = nullptr;
			struct json_object *prim_ext = nullptr;
			int ext_num = 0, arm_num = 0;

			/* attributes->iport-ids */
			if (!json_object_object_get_ex(attr_obj, "iport-ids", &iport_ids_obj)) {
				ambamps_error("null iport ids object. error code: %s\n", json_util_get_last_err());
				rval = -1;
				break;
			}
			if ((io_num = json_object_array_length(iport_ids_obj)) == 0) {
				ambamps_error("zero iport ids item.\n");
				rval = -1;
				break;
			}
			for (int j = 0; j < io_num; ++j) {
				io_name = std::string(json_object_get_string(json_object_array_get_idx(iport_ids_obj, j)));
				node.iports.push_back(io_name);
			}
			if (rval) break;

			/* attributes->oport-ids */
			if (!json_object_object_get_ex(attr_obj, "oport-ids", &oport_ids_obj)) {
				ambamps_error("null oport ids object. error code: %s\n", json_util_get_last_err());
				rval = -1;
				break;
			}
			if ((io_num = json_object_array_length(oport_ids_obj)) == 0) {
				ambamps_error("zero oport ids item.\n");
				rval = -1;
				break;
			}
			for (int j = 0; j < io_num; ++j) {
				io_name = std::string(json_object_get_string(json_object_array_get_idx(oport_ids_obj, j)));
				node.oports.push_back(io_name);
			}
			if (rval) break;

			/* attributes->coprocessor */
			if (!json_object_object_get_ex(attr_obj, "coprocessor", &coproc_obj)) {
				ambamps_error("null coprocessor object. error code: %s\n", json_util_get_last_err());
				rval = -1;
				break;
			}
			if (node_coproc_type_string2num(node.coproc_type, json_object_get_string(coproc_obj))) {
				ambamps_error("failed to translate coproc type from string to number\n");
				rval = -1;
				break;
			}
			if (node.coproc_type == AMBAMPS_COPROC_VP) {
				/* attributes->vas_output */
				if (!json_object_object_get_ex(attr_obj, "vas_output", &vas_obj)) {
					ambamps_error("null vas output object. error code: %s\n", json_util_get_last_err());
					rval = -1;
					break;
				}
				std::string vas_output_dir = std::string(json_object_get_string(vas_obj));
				std::string node_dir = vas_output_dir.substr(0, vas_output_dir.rfind("vas_output"));
				node.compiled_bin = node.name + ".bin";
			} else if (node.coproc_type == AMBAMPS_COPROC_ARM) {
				/* attributes->primitive-graph */
				if (!json_object_object_get_ex(attr_obj, "primitive-graph", &prim_ext)) {
					ambamps_error("null primitive graph object. error code: %s\n", json_util_get_last_err());
					rval = -1;
					break;
				}
				/* attributes->extern */
				if (!json_object_object_get_ex(attr_obj, "extern", &exts_obj)) {
					ambamps_error("null extern object. error code: %s\n", json_util_get_last_err());
					rval = -1;
					break;
				}
				if ((ext_num = json_object_array_length(exts_obj)) == 0) {
					ambamps_error("node zero extern nodes.\n");
					rval = -1;
					break;
				}
				if (ext_num != 1) {
					ambamps_error("only one extern library is supported.\n");
					rval = -1;
					break;
				}
				for (int j = 0; j < ext_num; ++j) {
					iter_ext_obj = json_object_array_get_idx(exts_obj, j);
					if (!json_object_object_get_ex(iter_ext_obj, "library", &lib_obj)) {
						ambamps_error("null library object. error code: %s\n", json_util_get_last_err());
						rval = -1;
						break;
					}
					if (!json_object_object_get_ex(lib_obj, "arm", &arms_obj)) {
						ambamps_error("null arm object. error code: %s\n", json_util_get_last_err());
						rval = -1;
						break;
					}
					if ((arm_num = json_object_array_length(arms_obj)) == 0) {
						ambamps_error("zero arm libs.\n");
						rval = -1;
						break;
					}
					if (arm_num != 1) {
						ambamps_error("only one arm library is supported.\n");
						rval = -1;
						break;
					}
					for (int k = 0; k < arm_num; ++k) {
						priv_ext_lib_t ext_lib;
						iter_arm_obj = json_object_array_get_idx(arms_obj, k);
						ext_lib.lib_file = std::string(json_object_get_string(iter_arm_obj));
						ext_lib.lib_name = get_file_filename(ext_lib.lib_file.c_str());
						ext_lib.lib_prim_file = std::string(json_object_get_string(prim_ext));
						node.ext_lib = ext_lib;
					}
				}
			}
			p_node_list->push_back(std::make_pair(node.name, node));
		}
	} while(0);

	return rval;
}

int parse_graph_body(priv_body_t *p_body, priv_node_vec *p_node_list, struct json_object *body_obj)
{
	int rval = 0;
	priv_body_t body;

	do {
		/* body->inputs */
		if (parse_body_io(&body.inputs, body_obj, IO_INPUT)) {
			ambamps_error("failed to parse body inputs.\n");
			rval = -1;
			break;
		}
		/* body->outputs */
		if (parse_body_io(&body.outputs, body_obj, IO_OUTPUT)) {
			ambamps_error("failed to parse body outputs\n");
			rval = -1;
			break;
		}
		/* body->intermediates */
		if (parse_body_io(&body.intermediates, body_obj, IO_INTERMEDIATE)) {
			ambamps_error("failed to parse body intermediates\n");
			rval = -1;
			break;
		}
		/* body->nodes */
		if (parse_body_nodes(&body.nodes, body_obj)) {
			ambamps_error("failed to parse body nodes\n");
			rval = -1;
			break;
		}
		*p_body = body;

		if (parse_graph_nodes(p_body, p_node_list, body_obj)) {
			ambamps_error("failed to parse nodes.\n");
			rval = -1;
			break;
		}
	} while(0);

	return rval;
}


