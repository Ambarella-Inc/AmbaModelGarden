/*******************************************************************************
 * ambamps_priv.hpp
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


#ifndef __CAVALRY_GEN_INTERNAL_HPP__
#define __CAVALRY_GEN_INTERNAL_HPP__

#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <iomanip>

#include "json-c/json.h"

#include "iav_ioctl.h"
#include "cavalry_gen.h"
#include "nnctrl.h"
#include "api/amba-cnn-ext-c-types.h"

#define AMBAMPS_VER_MAJOR 0
#define AMBAMPS_VER_MINOR 5
#define AMBAMPS_VER_PATCH 0
#define AMBAMPS_VERSION ((AMBAMPS_VER_MAJOR << 16) | \
			(AMBAMPS_VER_MINOR << 8)  | \
			AMBAMPS_VER_PATCH)

#define AMBAMPS_IO_NAME_MAX				(256)
#define AMBAMPS_NODE_NUM_MAX			(8)
#define AMBAMPS_NODE_JOINT_NUM_MAX		(16)
#define AMBAMPS_NODE_NAME_MAX			(64)
#define AMBAMPS_IO_NUM_MAX				(8)
#define AMBAMPS_TYPE_NUM_MAX			(8)
#define AMBAMPS_LABEL_NUM_MAX			(1024)
#define AMBAMPS_LABEL_NAME_LEN			(64)
#define AMBAMPS_FILE_PATH_MAX			(2048)
#define AMBAMPS_EXT_LIB_ATTR_LEN			(2048)

#ifndef MIN
#  define MIN(a,b)  ((a) > (b) ? (b) : (a))
#endif

#ifndef MAX
#  define MAX(a,b)  ((a) < (b) ? (b) : (a))
#endif

#define ambamps_error(str, arg...) { \
	fprintf(stderr, "[ AmbaMPS error ] "); \
	fprintf(stderr, str, ##arg); }
#define ambamps_warn(str, arg...) { \
	fprintf(stderr, "[ AmbaMPS warning ] "); \
	fprintf(stderr, str, ##arg); }
#define ambamps_log(str, arg...) { \
	fprintf(stdout, str, ##arg); }

#define STR_LEN_MAX(X) 		AMBAMPS_##X##_MAX
#define STR(X)	#X

typedef std::vector<std::string> str_vec;
typedef std::unordered_set<std::string> str_set;
typedef std::vector<uint32_t> uint32_vec;
typedef std::vector<std::pair<std::string, int> > name_cnt_vec;
typedef std::unordered_map<std::string, std::string> name_str_map;
typedef std::vector<std::pair<std::string, uint32_vec> > name_array_vec;

typedef enum {
	IO_INPUT = 0,
	IO_OUTPUT = 1,
	IO_INTERMEDIATE = 2,
} io_type_t;

typedef enum {
	AMBAMPS_COPROC_VP = 0,
	AMBAMPS_COPROC_ARM = 1,
} ambamps_coproc_type_t;


/* ----- json parser ----- */

typedef struct priv_ext_lib_s {
	std::string lib_name;
	std::string lib_file;
	std::string lib_prim_file;
} priv_ext_lib_t;

typedef struct ambamps_graph_node_joint_s {
	uint32_t from_node_id;
	char from_port_name[CAVALRY_IO_NAME_MAX];
	uint32_t to_node_id;
	char to_port_name[CAVALRY_IO_NAME_MAX];
} ambamps_graph_node_joint_t;

typedef std::vector<ambamps_graph_node_joint_t> node_jnt_vec;

typedef std::vector<struct lh_entry*> lh_entry_vec;

typedef struct cvb_io_desc_s {
	uint32_vec dim;
	uint32_vec data_format;
} cvb_io_desc_t;

typedef std::vector<std::pair<std::string, cvb_io_desc_t> > cvb_io_vec;
typedef std::pair<std::string, cvb_io_desc_t> cvb_io_desc_pair;
typedef struct priv_node_s priv_node_t;
typedef std::vector<std::pair<std::string, priv_node_t> > priv_node_vec;


typedef struct priv_body_s {
	cvb_io_vec inputs;						// "inputs" <name, <cvb_io_desc>>
	cvb_io_vec outputs;					// "outputs" <name, <cvb_io_desc>>
	cvb_io_vec intermediates;				// LSTM time step input
	str_vec nodes;						// list of nodes
	priv_node_vec nodes_map;

	std::string intr_file;
} priv_body_t;

struct priv_node_s {
	uint32_t id;
	std::string name;
	str_vec next_nodes;
	name_array_vec next_nodes_joint;		// <next_nd_name, (from_out_index, to_in_index)>
	cvb_io_vec inputs;						// "src-ids" <name, <cvb_io_desc>>
	cvb_io_vec outputs;					// "out-ids" <name, <cvb_io_desc>>
	str_vec iports;						// "iport-ids"
	str_vec oports;						// "oport-ids"
	priv_node_vec nodes_map;

	ambamps_coproc_type_t coproc_type;
	std::string compiled_bin;

	priv_ext_lib_t ext_lib;					// only one lib in one node
};

typedef std::unordered_map<std::string, priv_node_t> priv_node_map;

typedef struct node_io_s {
	str_vec inputs;
	str_vec outputs;
} node_io_t;

typedef std::unordered_map<std::string, node_io_t> node_io_map;

typedef struct intr_param_s {
	char label_map[AMBAMPS_LABEL_NUM_MAX][AMBAMPS_LABEL_NAME_LEN];
} intr_param_t;

typedef struct node_port_s {
	uint8_t *virt_addr;
	unsigned long dram_addr;
	unsigned long size;
	struct io_dim dim;
	struct io_data_fmt data_fmt;

	char port_name[AMBAMPS_IO_NAME_MAX];
} node_port_t;

typedef struct {
	uint32_t cache_en : 1;
	uint32_t reserved : 31;

	uint32_t net_id;
	char net_fn[AMBAMPS_FILE_PATH_MAX];

	struct net_mem net_m;
} vp_nd_t;

typedef struct {
	const char *attr;
	int cid;
	int num_src;
	int data_mode;
	int reserved;
	amba_cnn_c_vcoord_t isz[AMBAMPS_IO_NUM_MAX];
	amba_cnn_c_vcoord_t osz[AMBAMPS_IO_NUM_MAX];
	amba_cnn_c_data_format_t idf[AMBAMPS_IO_NUM_MAX];
	amba_cnn_c_data_format_t odf[AMBAMPS_IO_NUM_MAX];
	void *src_array[AMBAMPS_IO_NUM_MAX];
	void *dst_array[AMBAMPS_IO_NUM_MAX];
} arm_exec_t;

typedef struct {
	void *lib_handle;
	char lib_fn[AMBAMPS_FILE_PATH_MAX];

	arm_exec_t lib_exec;
	char lib_attr[AMBAMPS_EXT_LIB_ATTR_LEN];

	int num_types;
	amba_cnn_ext_c_dll_query_t ptr_query;
	amba_cnn_ext_c_extern_node_type_t *types[AMBAMPS_TYPE_NUM_MAX];
} arm_nd_t;

typedef struct node_match_s {
	uint32_t id;
	char name[AMBAMPS_NODE_NAME_MAX];
	ambamps_coproc_type_t node_type;
	union {
		vp_nd_t vp_node;
		arm_nd_t arm_node;
	} node;

	uint32_t in_num;
	uint32_t out_num;
	node_port_t in_pair[AMBAMPS_IO_NUM_MAX];
	node_port_t out_pair[AMBAMPS_IO_NUM_MAX];
} node_match_t;

typedef struct graph_ctx_s {
	int node_num;
	int node_jnt_num;
	node_match_t node_list[AMBAMPS_NODE_NUM_MAX];
	ambamps_graph_node_joint_t node_joint[AMBAMPS_NODE_JOINT_NUM_MAX];
	int exec_index[AMBAMPS_NODE_NUM_MAX];

	uint32_t in_num;
	uint32_t out_num;
	node_port_t in_pair[AMBAMPS_IO_NUM_MAX];
	node_port_t out_pair[AMBAMPS_IO_NUM_MAX];

	intr_param_t intr_param;
} graph_ctx_t;

typedef enum {
	USE_JPG = 0,
	USE_BIN = 1
} infile_mode_t;

typedef struct init_cfg_s {
	std::string model_dir;
	std::string input_file_y;
	std::string input_file_uv;
	std::string output_nm;
	float conf_th;
	uint32_t mode;
} init_cfg_t;

typedef enum {
	AMBAMPS_QUERY_BUF_CANVAS = 0,
	AMBAMPS_QUERY_BUF_PYRAMID,
	AMBAMPS_QUERY_BUF_TYPE_NUM,
} ambamps_query_type_t;

typedef struct ambamps_iav_s {
	int fd_iav;
	uint8_t *dsp_mem;
	uint32_t dsp_phy_addr;
	uint32_t dsp_size;

	struct iav_yuv_cap data_cap;

	uint32_t query_buf_type;
	uint32_t query_buf_id;
} ambamps_iav_t;

bool is_cstring_match(const char* src, const char *match);
std::string get_file_filename(const char *file_path);

int parse_extern_primitive(std::string &attr, const char *json_file);
int parse_graph_nodes(priv_body_t * p_body,priv_node_vec * p_node_list,struct json_object * body_obj);
int parse_graph_body(priv_body_t * p_body,priv_node_vec * p_node_list,struct json_object * body_obj);
int parse_model_intrinsic_param(intr_param_t *intr_param, const char* json_file);

int get_node_exec_order(uint32_vec *p_order, node_jnt_vec *p_jnt);
int construct_graph(graph_ctx_t * pctx,const char * model_dir);

#endif

