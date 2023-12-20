// vim: set filetype=cpp:
/*
 * Copyright (c) 2023 Ambarella International LP
 *
 * This file and its contents ("Software") are protected by intellectual
 * property rights including, without limitation, U.S. and/or foreign
 * copyrights.  This Software is also the confidential and proprietary
 * information of Ambarella International LP and its licensors.  You may not
 * use, reproduce, disclose, distribute, modify, or otherwise prepare derivative
 * works of this Software or any portion thereof except pursuant to a signed
 * license agreement or nondisclosure agreement with Ambarella International LP
 * or its authorized affiliates.  In the absence of such an agreement, you
 * agree to promptly notify and return this Software to Ambarella International
 * LP.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF NON-INFRINGEMENT,
 * MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL AMBARELLA INTERNATIONAL LP OR ITS AFFILIATES BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; COMPUTER FAILURE OR MALFUNCTION; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef AMBA_CNN_C_H
#define AMBA_CNN_C_H

////////////////////////////////////////////////////////////////////////////////
// This is a generated file. Please do not modify this file directly.         //
////////////////////////////////////////////////////////////////////////////////

#include "api/amba-cnn-c-types.h"
#include "api/data-format-c.h"

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif


#define AMBA_CNN_API_DUMP_IDENTIFIER  0x004e4341

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////
// session control
////////////////////////////////////////////////////////////////////////////////

extern EXPORT int
amba_cnn_c_open_session(int* session, const char* name, int gpu_id, const char* mode);

extern EXPORT int
amba_cnn_c_open_record_session(int* session, const char* name,
                               const char* path, int gpu_id, const char* mode);

extern EXPORT int
amba_cnn_c_open_session_ex(int* session, const char* name, const char* config);

extern EXPORT int
amba_cnn_c_open_record_session_ex(int* session, const char* name,
                                  const char* config, const char* path);

extern EXPORT int
amba_cnn_c_session_debug_level(int session, int level);

extern EXPORT int
amba_cnn_c_session_interactive_display(int session, int enable);

extern EXPORT int
amba_cnn_c_close_session(int session);

extern EXPORT const char*
amba_cnn_c_lib_version();

////////////////////////////////////////////////////////////////////////////////
// replay
////////////////////////////////////////////////////////////////////////////////

extern EXPORT int
amba_cnn_c_replay_all(int session);

extern EXPORT int
amba_cnn_c_replay_next(int session);

extern EXPORT int
amba_cnn_c_replay_available(int* avail, int session);

////////////////////////////////////////////////////////////////////////////////
// core precessing
////////////////////////////////////////////////////////////////////////////////

extern EXPORT int
amba_cnn_c_node_output_dimension(amba_cnn_c_vcoord_t* sz,
                                 int session, const char* nid);

////////////////////////////////////////////////////////////////////////////////
// exception retrieval
////////////////////////////////////////////////////////////////////////////////

extern EXPORT const char*
amba_cnn_c_exception_msg(int session);

extern EXPORT int
amba_cnn_c_exception_num_trackers(int session);

extern EXPORT int
amba_cnn_c_exception_tracker(int session, int i);

////////////////////////////////////////////////////////////////////////////////
// tracker handling
////////////////////////////////////////////////////////////////////////////////

#define AID_NEW_TRACKER  1

extern EXPORT int
amba_cnn_c_new_tracker(
    int session,
    int id,
    const char* info
  );

////////////////////////////////////////////////////////////////////////////////
// task handling
////////////////////////////////////////////////////////////////////////////////

#define AID_CONFIG_DEFAULT_NODE_TASK  2

extern EXPORT int
amba_cnn_c_config_default_node_task(
    int session,
    const char* op,
    const char* cfg
  );

#define AID_CONFIG_DEFAULT_PRIM_TASK  3

extern EXPORT int
amba_cnn_c_config_default_prim_task(
    int session,
    const char* op,
    const char* cfg
  );

#define AID_CONFIG_DEFAULT_FRAG_TASK  4

extern EXPORT int
amba_cnn_c_config_default_frag_task(
    int session,
    const char* op,
    const char* cfg
  );

#define AID_CONFIG_NODE_EXPAND_OP  5

extern EXPORT int
amba_cnn_c_config_node_expand_op(
    int session,
    const char* cfg
  );

#define AID_CONFIG_FRAG_CONSTRUCT_OP  6

extern EXPORT int
amba_cnn_c_config_frag_construct_op(
    int session,
    const char* cfg
  );

#define AID_REGISTER_NODE_TASK  7

extern EXPORT int
amba_cnn_c_register_node_task(
    int session,
    const char* id,
    const char* script
  );

#define AID_REGISTER_PRIM_TASK  8

extern EXPORT int
amba_cnn_c_register_prim_task(
    int session,
    const char* id,
    const char* script
  );

#define AID_REGISTER_FRAG_TASK  9

extern EXPORT int
amba_cnn_c_register_frag_task(
    int session,
    const char* id,
    const char* script
  );

#define AID_ASSIGN_NODE_TASK_VARIABLE_AS_POINTER  10

extern EXPORT int
amba_cnn_c_assign_node_task_variable_as_pointer(
    int session,
    const char* id,
    const void* ptr
  );

#define AID_ASSIGN_PRIM_TASK_VARIABLE_AS_POINTER  11

extern EXPORT int
amba_cnn_c_assign_prim_task_variable_as_pointer(
    int session,
    const char* id,
    const void* ptr
  );

#define AID_ASSIGN_NODE_TASK_VARIABLE_AS_INTEGER  12

extern EXPORT int
amba_cnn_c_assign_node_task_variable_as_integer(
    int session,
    const char* id,
    long long value
  );

#define AID_ASSIGN_PRIM_TASK_VARIABLE_AS_INTEGER  13

extern EXPORT int
amba_cnn_c_assign_prim_task_variable_as_integer(
    int session,
    const char* id,
    long long value
  );

#define AID_ASSIGN_NODE_TASK_VARIABLE_AS_STRING  14

extern EXPORT int
amba_cnn_c_assign_node_task_variable_as_string(
    int session,
    const char* id,
    const char* string
  );

#define AID_ASSIGN_PRIM_TASK_VARIABLE_AS_STRING  15

extern EXPORT int
amba_cnn_c_assign_prim_task_variable_as_string(
    int session,
    const char* id,
    const char* string
  );

#define AID_RETRIEVE_NODE_TASK_VARIABLE_AS_POINTER  16

extern EXPORT int
amba_cnn_c_retrieve_node_task_variable_as_pointer(
    const void** ptr,
    int session,
    const char* id
  );

#define AID_RETRIEVE_PRIM_TASK_VARIABLE_AS_POINTER  17

extern EXPORT int
amba_cnn_c_retrieve_prim_task_variable_as_pointer(
    const void** ptr,
    int session,
    const char* id
  );

#define AID_RETRIEVE_NODE_TASK_VARIABLE_AS_INTEGER  18

extern EXPORT int
amba_cnn_c_retrieve_node_task_variable_as_integer(
    long long* pvalue,
    int session,
    const char* id
  );

#define AID_RETRIEVE_PRIM_TASK_VARIABLE_AS_INTEGER  19

extern EXPORT int
amba_cnn_c_retrieve_prim_task_variable_as_integer(
    long long* pvalue,
    int session,
    const char* id
  );

#define AID_RETRIEVE_NODE_TASK_VARIABLE_AS_STRING  20

extern EXPORT int
amba_cnn_c_retrieve_node_task_variable_as_string(
    char* str, int max_len,
    int session,
    const char* id
  );

#define AID_RETRIEVE_PRIM_TASK_VARIABLE_AS_STRING  21

extern EXPORT int
amba_cnn_c_retrieve_prim_task_variable_as_string(
    char* str, int max_len,
    int session,
    const char* id
  );

#define AID_RUN_DEFAULT_NODE_TASK  22

extern EXPORT int
amba_cnn_c_run_default_node_task(
    int session
  );

#define AID_RUN_DEFAULT_PRIM_TASK  23

extern EXPORT int
amba_cnn_c_run_default_prim_task(
    int session
  );

#define AID_RUN_DEFAULT_FRAG_TASK  24

extern EXPORT int
amba_cnn_c_run_default_frag_task(
    int session
  );

#define AID_RUN_NODE_EXPAND_OP  25

extern EXPORT int
amba_cnn_c_run_node_expand_op(
    int session
  );

#define AID_RUN_FRAG_CONSTRUCT_OP  26

extern EXPORT int
amba_cnn_c_run_frag_construct_op(
    int session
  );

#define AID_RUN_NODE_TASK  27

extern EXPORT int
amba_cnn_c_run_node_task(
    int session,
    const char* id
  );

#define AID_RUN_PRIM_TASK  28

extern EXPORT int
amba_cnn_c_run_prim_task(
    int session,
    const char* id
  );

#define AID_RUN_FRAG_TASK  29

extern EXPORT int
amba_cnn_c_run_frag_task(
    int session,
    const char* id
  );

#define AID_RUN_DEFAULT_TASKS  30

extern EXPORT int
amba_cnn_c_run_default_tasks(
    int session
  );

#define AID_CONFIG_FROM_JSON  31

extern EXPORT int
amba_cnn_c_config_from_json(
    int session,
    const char* json_file
  );

#define AID_CONFIG_FROM_PARSER  32

extern EXPORT int
amba_cnn_c_config_from_parser(
    int session,
    const char* arg
  );

////////////////////////////////////////////////////////////////////////////////
// node expand operator handling
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// network initialization
////////////////////////////////////////////////////////////////////////////////

#define AID_LOAD_PRIM_GRAPH_FROM_JSON  33

extern EXPORT int
amba_cnn_c_load_prim_graph_from_json(
    int session,
    const char* json_file
  );

////////////////////////////////////////////////////////////////////////////////
// create nodes
////////////////////////////////////////////////////////////////////////////////

// input ///////////////////////////////////////////////////////////////////////

#define AID_NEW_INPUT_NODE  34

extern EXPORT int
amba_cnn_c_new_input_node(
    int session,
    const char* id,
    const amba_cnn_c_input_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_INPUT_NODE_FROM_FILE  35

extern EXPORT int
amba_cnn_c_new_input_node_from_file(
    int session,
    const char* id,
    const amba_cnn_c_input_attr_t* attr,
    const char* file_path,
    bool quantized,
    int file_dram_bit_packing_mode,
    int file_dram_format,
    int file_offset,
    int file_dram_pitch,
    int file_tile_width_lg2,
    int file_tile_height_lg2,
    bool sequence,
    const amba_cnn_c_data_format_t* file_data_format,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_TENSOR_DATA_FEEDER_FROM_FILE  36

extern EXPORT int
amba_cnn_c_new_tensor_data_feeder_from_file(
    int session,
    const char* id,
    int w,
    int h,
    int d,
    int p,
    const char* file_path,
    bool quantized,
    int file_dram_bit_packing_mode,
    int file_dram_format,
    int file_offset,
    int file_dram_pitch,
    int file_tile_width_lg2,
    int file_tile_height_lg2,
    bool sequence,
    const amba_cnn_c_data_format_t* file_data_format
  );

#define AID_NEW_CONSTANT_NODE_FROM_FILE  37

extern EXPORT int
amba_cnn_c_new_constant_node_from_file(
    int session,
    const char* id,
    const amba_cnn_c_constant_attr_t* attr,
    const char* file_path,
    bool quantized,
    const amba_cnn_c_data_format_t* file_data_format,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_INPUT_NODE_FROM_ARRAY  38

extern EXPORT int
amba_cnn_c_new_input_node_from_array(
    int session,
    const char* id,
    const amba_cnn_c_input_attr_t* attr,
    const float* data,
    unsigned int data_count,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_TENSOR_DATA_FEEDER_FROM_MEMORY  39

extern EXPORT int
amba_cnn_c_new_tensor_data_feeder_from_memory(
    int session,
    const char* id,
    int w,
    int h,
    int d,
    int p,
    int available_frames,
    const float* data,
    bool keep_local_copy
  );

#define AID_NEW_CONSTANT_NODE_FROM_ARRAY  40

extern EXPORT int
amba_cnn_c_new_constant_node_from_array(
    int session,
    const char* id,
    const amba_cnn_c_constant_attr_t* attr,
    const float* data,
    unsigned int data_count,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_LINK_TENSOR_DATA_FEEDER_TO_INPUT  41

extern EXPORT int
amba_cnn_c_link_tensor_data_feeder_to_input(
    int session,
    const char* feeder_id,
    const char* input_id
  );

// output //////////////////////////////////////////////////////////////////////

#define AID_NEW_OUTPUT_NODE  42

extern EXPORT int
amba_cnn_c_new_output_node(
    int session,
    const char* id,
    const amba_cnn_c_output_attr_t* attr,
    const char* src0,
    int tracker
  );

#define AID_NEW_OUTPUT_PORT_SELECTOR  43

extern EXPORT int
amba_cnn_c_new_output_port_selector(
    int session,
    const char* id,
    const char* src0,
    int port0,
    int tracker
  );

#define AID_NEW_OUTPUT_VOLATILE  44

extern EXPORT int
amba_cnn_c_new_output_volatile(
    int session,
    const char* id,
    const char* src0,
    int port0,
    int tracker
  );

// custom //////////////////////////////////////////////////////////////////////

#define AID_LOAD_CUSTOM_NODE_DLL  45

extern EXPORT int
amba_cnn_c_load_custom_node_dll(
    int session,
    const char* dll_file,
    int reserved
  );

#define AID_LOAD_EXTERN_NODE_DLL  46

extern EXPORT int
amba_cnn_c_load_extern_node_dll(
    int session,
    const char* dll_file,
    int reserved
  );

#define AID_LOAD_EXTENSION_DLL  47

extern EXPORT int
amba_cnn_c_load_extension_dll(
    int session,
    const char* dll_file,
    int reserved
  );

#define AID_NEW_CUSTOM_NODE  48

extern EXPORT int
amba_cnn_c_new_custom_node(
    int session,
    const char* id,
    int num_src,
    const char** src,
    const char* custom_type,
    const char* attr_string,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_EXTERN_NODE  49

extern EXPORT int
amba_cnn_c_new_extern_node(
    int session,
    const char* id,
    int num_src,
    const char** src,
    const char* extern_type,
    const char* attr_string,
    int tracker
  );

#define AID_NEW_JSON_NODE  50

extern EXPORT int
amba_cnn_c_new_json_node(
    int session,
    const char* json_file,
    const char* id,
    int num_src,
    const char** src,
    int num_in,
    const char** in,
    int num_out,
    const char** out,
    int tracker
  );

#define AID_BEGIN_NAMED_GRAPH  51

extern EXPORT int
amba_cnn_c_begin_named_graph(
    int session,
    const char* id
  );

#define AID_END_NAMED_GRAPH  52

extern EXPORT int
amba_cnn_c_end_named_graph(
    int session
  );

#define AID_SET_PORT_DATA_FORMAT_EX  53

extern EXPORT int
amba_cnn_c_set_port_data_format_ex(
    int session,
    const char* id,
    int port,
    const amba_cnn_c_data_format_ex_t* data_format_ex
  );


// regional operations /////////////////////////////////////////////////////////

#define AID_NEW_AVERAGE_POOL_NODE  54

extern EXPORT int
amba_cnn_c_new_average_pool_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_average_pool_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_AVERAGE_POOL_3D_NODE  55

extern EXPORT int
amba_cnn_c_new_average_pool_3d_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_average_pool_3d_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_CONV_NODE  56

extern EXPORT int
amba_cnn_c_new_conv_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    const char* src2,
    const amba_cnn_c_conv_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_CONV_3D_NODE  57

extern EXPORT int
amba_cnn_c_new_conv_3d_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    const char* src2,
    const amba_cnn_c_conv_3d_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_CONV_3D_TRANSPOSE_NODE  58

extern EXPORT int
amba_cnn_c_new_conv_3d_transpose_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    const char* src2,
    const amba_cnn_c_conv_3d_transpose_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_CONV_DEPTHWISE_NODE  59

extern EXPORT int
amba_cnn_c_new_conv_depthwise_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    const char* src2,
    const amba_cnn_c_conv_depthwise_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_CONV_TRANSPOSE_NODE  60

extern EXPORT int
amba_cnn_c_new_conv_transpose_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    const char* src2,
    const amba_cnn_c_conv_transpose_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_CONV_TRANSPOSE_DEPTHWISE_NODE  61

extern EXPORT int
amba_cnn_c_new_conv_transpose_depthwise_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    const char* src2,
    const amba_cnn_c_conv_transpose_depthwise_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_CORRELATION_NODE  62

extern EXPORT int
amba_cnn_c_new_correlation_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    const amba_cnn_c_correlation_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_CUM_SUM_NODE  63

extern EXPORT int
amba_cnn_c_new_cum_sum_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_cum_sum_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_DEFORMABLE_CONV_NODE  64

extern EXPORT int
amba_cnn_c_new_deformable_conv_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    const char* src2,
    const char* src3,
    const amba_cnn_c_deformable_conv_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_DOT_NODE  65

extern EXPORT int
amba_cnn_c_new_dot_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    const char* src2,
    const amba_cnn_c_dot_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_GEMM_NODE  66

extern EXPORT int
amba_cnn_c_new_gemm_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    const char* src2,
    const amba_cnn_c_gemm_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_GLOBAL_AVERAGE_POOL_NODE  67

extern EXPORT int
amba_cnn_c_new_global_average_pool_node(
    int session,
    const char* id,
    const char* src0,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_GLOBAL_MAX_POOL_NODE  68

extern EXPORT int
amba_cnn_c_new_global_max_pool_node(
    int session,
    const char* id,
    const char* src0,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_HW_CONV_A_NODE  69

extern EXPORT int
amba_cnn_c_new_hw_conv_a_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    const char* src2,
    const char* src3,
    const char* src4,
    const amba_cnn_c_hw_conv_a_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_HW_DWCONV_A_NODE  70

extern EXPORT int
amba_cnn_c_new_hw_dwconv_a_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    const char* src2,
    const char* src3,
    const char* src4,
    const amba_cnn_c_hw_dwconv_a_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_INSTANCE_NORMALIZATION_NODE  71

extern EXPORT int
amba_cnn_c_new_instance_normalization_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    const char* src2,
    const amba_cnn_c_instance_normalization_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_LOG_SOFTMAX_NODE  72

extern EXPORT int
amba_cnn_c_new_log_softmax_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_log_softmax_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_LP_NORMALIZATION_NODE  73

extern EXPORT int
amba_cnn_c_new_lp_normalization_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_lp_normalization_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_LRN_NODE  74

extern EXPORT int
amba_cnn_c_new_lrn_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_lrn_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_MAT_MUL_NODE  75

extern EXPORT int
amba_cnn_c_new_mat_mul_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    const amba_cnn_c_mat_mul_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_MAX_POOL_NODE  76

extern EXPORT int
amba_cnn_c_new_max_pool_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_max_pool_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_MAX_POOL_3D_NODE  77

extern EXPORT int
amba_cnn_c_new_max_pool_3d_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_max_pool_3d_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_MAX_ROI_POOL_NODE  78

extern EXPORT int
amba_cnn_c_new_max_roi_pool_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    const amba_cnn_c_max_roi_pool_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_MAX_UNPOOL_NODE  79

extern EXPORT int
amba_cnn_c_new_max_unpool_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    const amba_cnn_c_max_unpool_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_RESIZE_NODE  80

extern EXPORT int
amba_cnn_c_new_resize_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_resize_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_RGB_TO_YUV_NODE  81

extern EXPORT int
amba_cnn_c_new_rgb_to_yuv_node(
    int session,
    const char* id,
    const char* src0,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_ROI_ALIGN_NODE  82

extern EXPORT int
amba_cnn_c_new_roi_align_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    const amba_cnn_c_roi_align_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_SOFTMAX_NODE  83

extern EXPORT int
amba_cnn_c_new_softmax_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_softmax_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_YUV_TO_RGB_NODE  84

extern EXPORT int
amba_cnn_c_new_yuv_to_rgb_node(
    int session,
    const char* id,
    const char* src0,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );


// reduction operations ////////////////////////////////////////////////////////

#define AID_NEW_ARG_MAX_NODE  85

extern EXPORT int
amba_cnn_c_new_arg_max_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_arg_max_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_ARG_MIN_NODE  86

extern EXPORT int
amba_cnn_c_new_arg_min_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_arg_min_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_REDUCE_LOG_SUM_EXP_NODE  87

extern EXPORT int
amba_cnn_c_new_reduce_log_sum_exp_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_reduce_log_sum_exp_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_REDUCE_MAX_NODE  88

extern EXPORT int
amba_cnn_c_new_reduce_max_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_reduce_max_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_REDUCE_MEAN_NODE  89

extern EXPORT int
amba_cnn_c_new_reduce_mean_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_reduce_mean_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_REDUCE_MIN_NODE  90

extern EXPORT int
amba_cnn_c_new_reduce_min_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_reduce_min_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_REDUCE_PROD_NODE  91

extern EXPORT int
amba_cnn_c_new_reduce_prod_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_reduce_prod_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_REDUCE_SUM_NODE  92

extern EXPORT int
amba_cnn_c_new_reduce_sum_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_reduce_sum_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );


// pointwise operations ////////////////////////////////////////////////////////

#define AID_NEW_ABS_NODE  93

extern EXPORT int
amba_cnn_c_new_abs_node(
    int session,
    const char* id,
    const char* src0,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_ADD_NODE  94

extern EXPORT int
amba_cnn_c_new_add_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_BATCH_NORMALIZATION_NODE  95

extern EXPORT int
amba_cnn_c_new_batch_normalization_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    const char* src2,
    const char* src3,
    const char* src4,
    const amba_cnn_c_batch_normalization_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_BATCH_NORMALIZATION_3D_NODE  96

extern EXPORT int
amba_cnn_c_new_batch_normalization_3d_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    const char* src2,
    const char* src3,
    const char* src4,
    const amba_cnn_c_batch_normalization_3d_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_BIAS_NODE  97

extern EXPORT int
amba_cnn_c_new_bias_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_BIT_SHIFT_NODE  98

extern EXPORT int
amba_cnn_c_new_bit_shift_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    const amba_cnn_c_bit_shift_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_BW_AND_NODE  99

extern EXPORT int
amba_cnn_c_new_bw_and_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_BW_NOT_NODE  100

extern EXPORT int
amba_cnn_c_new_bw_not_node(
    int session,
    const char* id,
    const char* src0,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_BW_OR_NODE  101

extern EXPORT int
amba_cnn_c_new_bw_or_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_BW_XOR_NODE  102

extern EXPORT int
amba_cnn_c_new_bw_xor_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_CEIL_NODE  103

extern EXPORT int
amba_cnn_c_new_ceil_node(
    int session,
    const char* id,
    const char* src0,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_CLIP_NODE  104

extern EXPORT int
amba_cnn_c_new_clip_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_clip_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_DIV_NODE  105

extern EXPORT int
amba_cnn_c_new_div_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_ELU_NODE  106

extern EXPORT int
amba_cnn_c_new_elu_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_elu_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_EQUAL_NODE  107

extern EXPORT int
amba_cnn_c_new_equal_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_ERF_NODE  108

extern EXPORT int
amba_cnn_c_new_erf_node(
    int session,
    const char* id,
    const char* src0,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_EXP_NODE  109

extern EXPORT int
amba_cnn_c_new_exp_node(
    int session,
    const char* id,
    const char* src0,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_FLOOR_NODE  110

extern EXPORT int
amba_cnn_c_new_floor_node(
    int session,
    const char* id,
    const char* src0,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_GREATER_NODE  111

extern EXPORT int
amba_cnn_c_new_greater_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_GREATER_OR_EQUAL_NODE  112

extern EXPORT int
amba_cnn_c_new_greater_or_equal_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_LEAKY_RELU_NODE  113

extern EXPORT int
amba_cnn_c_new_leaky_relu_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_leaky_relu_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_LESS_NODE  114

extern EXPORT int
amba_cnn_c_new_less_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_LESS_OR_EQUAL_NODE  115

extern EXPORT int
amba_cnn_c_new_less_or_equal_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_LOG_NODE  116

extern EXPORT int
amba_cnn_c_new_log_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_log_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_MISH_NODE  117

extern EXPORT int
amba_cnn_c_new_mish_node(
    int session,
    const char* id,
    const char* src0,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_MUL_NODE  118

extern EXPORT int
amba_cnn_c_new_mul_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_NEG_NODE  119

extern EXPORT int
amba_cnn_c_new_neg_node(
    int session,
    const char* id,
    const char* src0,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_NOT_EQUAL_NODE  120

extern EXPORT int
amba_cnn_c_new_not_equal_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_POW_NODE  121

extern EXPORT int
amba_cnn_c_new_pow_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_PRELU_NODE  122

extern EXPORT int
amba_cnn_c_new_prelu_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_RECIPROCAL_NODE  123

extern EXPORT int
amba_cnn_c_new_reciprocal_node(
    int session,
    const char* id,
    const char* src0,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_RELU_NODE  124

extern EXPORT int
amba_cnn_c_new_relu_node(
    int session,
    const char* id,
    const char* src0,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_ROUND_NODE  125

extern EXPORT int
amba_cnn_c_new_round_node(
    int session,
    const char* id,
    const char* src0,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_SEG_INTERP_NODE  126

extern EXPORT int
amba_cnn_c_new_seg_interp_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_seg_interp_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_SELU_NODE  127

extern EXPORT int
amba_cnn_c_new_selu_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_selu_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_SIGMOID_NODE  128

extern EXPORT int
amba_cnn_c_new_sigmoid_node(
    int session,
    const char* id,
    const char* src0,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_SQRT_NODE  129

extern EXPORT int
amba_cnn_c_new_sqrt_node(
    int session,
    const char* id,
    const char* src0,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_SUB_NODE  130

extern EXPORT int
amba_cnn_c_new_sub_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_SWISH_NODE  131

extern EXPORT int
amba_cnn_c_new_swish_node(
    int session,
    const char* id,
    const char* src0,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_TANH_NODE  132

extern EXPORT int
amba_cnn_c_new_tanh_node(
    int session,
    const char* id,
    const char* src0,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_TYPE_CAST_NODE  133

extern EXPORT int
amba_cnn_c_new_type_cast_node(
    int session,
    const char* id,
    const char* src0,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_TYPE_CONV_NODE  134

extern EXPORT int
amba_cnn_c_new_type_conv_node(
    int session,
    const char* id,
    const char* src0,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_WHERE_NODE  135

extern EXPORT int
amba_cnn_c_new_where_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    const char* src2,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );


// multi-reduction operations //////////////////////////////////////////////////

#define AID_NEW_MAX_NODE  136

extern EXPORT int
amba_cnn_c_new_max_node(
    int session,
    const char* id,
    int num_src,
    const char** src,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_MIN_NODE  137

extern EXPORT int
amba_cnn_c_new_min_node(
    int session,
    const char* id,
    int num_src,
    const char** src,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_SUM_NODE  138

extern EXPORT int
amba_cnn_c_new_sum_node(
    int session,
    const char* id,
    int num_src,
    const char** src,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );


// generation operations ///////////////////////////////////////////////////////

#define AID_NEW_RANDOM_UNIFORM_NODE  139

extern EXPORT int
amba_cnn_c_new_random_uniform_node(
    int session,
    const char* id,
    const amba_cnn_c_random_uniform_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );


// manipulation operations /////////////////////////////////////////////////////

#define AID_NEW_CONCAT_NODE  140

extern EXPORT int
amba_cnn_c_new_concat_node(
    int session,
    const char* id,
    int num_src,
    const char** src,
    const amba_cnn_c_concat_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_DATA_MASK_NODE  141

extern EXPORT int
amba_cnn_c_new_data_mask_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    const amba_cnn_c_data_mask_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_DEPTH_TO_SPACE_NODE  142

extern EXPORT int
amba_cnn_c_new_depth_to_space_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_depth_to_space_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_FLATTEN_NODE  143

extern EXPORT int
amba_cnn_c_new_flatten_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_flatten_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_FLIP_NODE  144

extern EXPORT int
amba_cnn_c_new_flip_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_flip_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_GATHER_NODE  145

extern EXPORT int
amba_cnn_c_new_gather_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    const amba_cnn_c_gather_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_NMS_NODE  146

extern EXPORT int
amba_cnn_c_new_nms_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    const amba_cnn_c_nms_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_ONE_HOT_NODE  147

extern EXPORT int
amba_cnn_c_new_one_hot_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_one_hot_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_RESHAPE_NODE  148

extern EXPORT int
amba_cnn_c_new_reshape_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_reshape_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_RESAMP_NODE  149

extern EXPORT int
amba_cnn_c_new_resamp_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_resamp_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_SCATTER_NODE  150

extern EXPORT int
amba_cnn_c_new_scatter_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    const char* src2,
    const amba_cnn_c_scatter_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_SLICE_NODE  151

extern EXPORT int
amba_cnn_c_new_slice_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_slice_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_SPACE_TO_DEPTH_NODE  152

extern EXPORT int
amba_cnn_c_new_space_to_depth_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_space_to_depth_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_SQUEEZE_NODE  153

extern EXPORT int
amba_cnn_c_new_squeeze_node(
    int session,
    const char* id,
    const char* src0,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_STRIDED_SLICE_NODE  154

extern EXPORT int
amba_cnn_c_new_strided_slice_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_strided_slice_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_TILE_NODE  155

extern EXPORT int
amba_cnn_c_new_tile_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_TOP_K_NODE  156

extern EXPORT int
amba_cnn_c_new_top_k_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_top_k_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_TRANSPOSE_NODE  157

extern EXPORT int
amba_cnn_c_new_transpose_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_transpose_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_UNSQUEEZE_NODE  158

extern EXPORT int
amba_cnn_c_new_unsqueeze_node(
    int session,
    const char* id,
    const char* src0,
    const amba_cnn_c_unsqueeze_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_VARIABLE_RESAMP_NODE  159

extern EXPORT int
amba_cnn_c_new_variable_resamp_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    const amba_cnn_c_variable_resamp_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );

#define AID_NEW_WARP_NODE  160

extern EXPORT int
amba_cnn_c_new_warp_node(
    int session,
    const char* id,
    const char* src0,
    const char* src1,
    const amba_cnn_c_warp_attr_t* attr,
    int tracker,
    const amba_cnn_c_data_format_t* data_format
  );


#ifdef __cplusplus
}
#endif

#endif
