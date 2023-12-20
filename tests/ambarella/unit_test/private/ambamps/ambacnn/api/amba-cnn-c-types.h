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

#ifndef AMBA_CNN_C_TYPES_H
#define AMBA_CNN_C_TYPES_H

////////////////////////////////////////////////////////////////////////////////
// This is a generated file. Please do not modify this file directly.         //
////////////////////////////////////////////////////////////////////////////////


#include "api/amba-cnn-c-vcoord-t.h"

#ifdef __cplusplus
extern "C" {
#endif

// i/o /////////////////////////////////////////////////////////////////////////

typedef struct amba_cnn_c_constant_attr_s {
  int w;
  int h;
  int d;
  int p;
} amba_cnn_c_constant_attr_t;

typedef struct amba_cnn_c_input_attr_s {
  int w;
  int h;
  int d;
  int p;
  int dram_bit_packing_mode;
  int dram_format;
  int tile_width_lg2;
  int tile_height_lg2;
  int dram_rotate;
  int runtime_configurable;
} amba_cnn_c_input_attr_t;

typedef struct amba_cnn_c_output_attr_s {
  int dram_format;
  int tile_width_lg2;
  int tile_height_lg2;
} amba_cnn_c_output_attr_t;


// regional operations /////////////////////////////////////////////////////////

typedef struct amba_cnn_c_average_pool_attr_s {
  int kernel_w;
  int kernel_h;
  int pad_w_begin;
  int pad_h_begin;
  int pad_w_end;
  int pad_h_end;
  int stride_w;
  int stride_h;
  int compatibility_mode;
  int ceil_mode;
} amba_cnn_c_average_pool_attr_t;

typedef struct amba_cnn_c_average_pool_3d_attr_s {
  int kernel_w;
  int kernel_h;
  int kernel_d;
  int pad_w_begin;
  int pad_h_begin;
  int pad_d_begin;
  int pad_w_end;
  int pad_h_end;
  int pad_d_end;
  int stride_w;
  int stride_h;
  int stride_d;
  int f_in;
  int packed_mode;
} amba_cnn_c_average_pool_3d_attr_t;

typedef struct amba_cnn_c_conv_attr_s {
  int dilation_w;
  int dilation_h;
  int kernel_w;
  int kernel_h;
  int pad_w_begin;
  int pad_h_begin;
  int pad_w_end;
  int pad_h_end;
  int stride_w;
  int stride_h;
  int group;
  float k_split_sparsity_th;
} amba_cnn_c_conv_attr_t;

typedef struct amba_cnn_c_conv_3d_attr_s {
  int dilation_w;
  int dilation_h;
  int dilation_d;
  int kernel_w;
  int kernel_h;
  int kernel_d;
  int pad_w_begin;
  int pad_h_begin;
  int pad_d_begin;
  int pad_w_end;
  int pad_h_end;
  int pad_d_end;
  int stride_w;
  int stride_h;
  int stride_d;
  int f_in;
  int f_out;
  int packed_mode;
} amba_cnn_c_conv_3d_attr_t;

typedef struct amba_cnn_c_conv_3d_transpose_attr_s {
  int dilation_w;
  int dilation_h;
  int dilation_d;
  int kernel_w;
  int kernel_h;
  int kernel_d;
  int pad_w_begin;
  int pad_h_begin;
  int pad_d_begin;
  int pad_w_end;
  int pad_h_end;
  int pad_d_end;
  int stride_w;
  int stride_h;
  int stride_d;
  int f_in;
  int f_out;
  int packed_mode;
} amba_cnn_c_conv_3d_transpose_attr_t;

typedef struct amba_cnn_c_conv_depthwise_attr_s {
  int dilation_w;
  int dilation_h;
  int kernel_w;
  int kernel_h;
  int pad_w_begin;
  int pad_h_begin;
  int pad_w_end;
  int pad_h_end;
  int stride_w;
  int stride_h;
  int channel_multiplier;
  int cm_inside;
  float k_split_sparsity_th;
} amba_cnn_c_conv_depthwise_attr_t;

typedef struct amba_cnn_c_conv_transpose_attr_s {
  int dilation_w;
  int dilation_h;
  int kernel_w;
  int kernel_h;
  int pad_w_begin;
  int pad_h_begin;
  int pad_w_end;
  int pad_h_end;
  int stride_w;
  int stride_h;
  int group;
  int allow_d2t;
  float k_split_sparsity_th;
} amba_cnn_c_conv_transpose_attr_t;

typedef struct amba_cnn_c_conv_transpose_depthwise_attr_s {
  int dilation_w;
  int dilation_h;
  int kernel_w;
  int kernel_h;
  int pad_w_begin;
  int pad_h_begin;
  int pad_w_end;
  int pad_h_end;
  int stride_w;
  int stride_h;
  int channel_multiplier;
  int cm_inside;
  int allow_d2t;
  float k_split_sparsity_th;
} amba_cnn_c_conv_transpose_depthwise_attr_t;

typedef struct amba_cnn_c_correlation_attr_s {
  int kernel_w;
  int kernel_h;
  int pad_w_begin;
  int pad_h_begin;
  int pad_w_end;
  int pad_h_end;
  int stride_w;
  int stride_h;
  int max_displ_w;
  int max_displ_h;
  int displ_stride_w;
  int displ_stride_h;
} amba_cnn_c_correlation_attr_t;

typedef struct amba_cnn_c_cum_sum_attr_s {
  int axis;
  int exclusive;
  int reverse;
} amba_cnn_c_cum_sum_attr_t;

typedef struct amba_cnn_c_deformable_conv_attr_s {
  int deformable_mode;
  int dilation_w;
  int dilation_h;
  int kernel_w;
  int kernel_h;
  int pad_w_begin;
  int pad_h_begin;
  int pad_w_end;
  int pad_h_end;
  int stride_w;
  int stride_h;
  int group;
} amba_cnn_c_deformable_conv_attr_t;

typedef struct amba_cnn_c_dot_attr_s {
  int dot_dim;
} amba_cnn_c_dot_attr_t;

typedef struct amba_cnn_c_gemm_attr_s {
  float alpha;
  float beta;
  int trans_a;
  int trans_b;
} amba_cnn_c_gemm_attr_t;

typedef struct amba_cnn_c_hw_conv_a_attr_s {
  int start_w;
  int start_h;
  int stride_w;
  int stride_h;
  int out_w;
  int out_h;
  int pool_mode;
  int pool_w;
  int pool_h;
  int zr;
  int strong_zero;
  int disable_reserved;
} amba_cnn_c_hw_conv_a_attr_t;

typedef struct amba_cnn_c_hw_dwconv_a_attr_s {
  int start_w;
  int start_h;
  int stride_w;
  int stride_h;
  int out_w;
  int out_h;
  int pool_mode;
  int pool_w;
  int pool_h;
  int cm_inside;
  int zr;
  int strong_zero;
  int disable_reserved;
} amba_cnn_c_hw_dwconv_a_attr_t;

typedef struct amba_cnn_c_instance_normalization_attr_s {
  float epsilon;
} amba_cnn_c_instance_normalization_attr_t;

typedef struct amba_cnn_c_log_softmax_attr_s {
  int axis;
  int group;
  int interleaved;
  int range_control;
} amba_cnn_c_log_softmax_attr_t;

typedef struct amba_cnn_c_lp_normalization_attr_s {
  int axes;
  int order;
  float epsilon;
} amba_cnn_c_lp_normalization_attr_t;

typedef struct amba_cnn_c_lrn_attr_s {
  float alpha;
  float beta;
  float bias;
  int size;
  int within_channel;
} amba_cnn_c_lrn_attr_t;

typedef struct amba_cnn_c_mat_mul_attr_s {
  int transpose_b;
} amba_cnn_c_mat_mul_attr_t;

typedef struct amba_cnn_c_max_pool_attr_s {
  int kernel_w;
  int kernel_h;
  int pad_w_begin;
  int pad_h_begin;
  int pad_w_end;
  int pad_h_end;
  int stride_w;
  int stride_h;
  int ceil_mode;
} amba_cnn_c_max_pool_attr_t;

typedef struct amba_cnn_c_max_pool_3d_attr_s {
  int kernel_w;
  int kernel_h;
  int kernel_d;
  int pad_w_begin;
  int pad_h_begin;
  int pad_d_begin;
  int pad_w_end;
  int pad_h_end;
  int pad_d_end;
  int stride_w;
  int stride_h;
  int stride_d;
  int f_in;
  int packed_mode;
} amba_cnn_c_max_pool_3d_attr_t;

typedef struct amba_cnn_c_max_roi_pool_attr_s {
  int out_w;
  int out_h;
  float spatial_scale;
} amba_cnn_c_max_roi_pool_attr_t;

typedef struct amba_cnn_c_max_unpool_attr_s {
  int kernel_w;
  int kernel_h;
  int pad_w_begin;
  int pad_h_begin;
  int pad_w_end;
  int pad_h_end;
  int stride_w;
  int stride_h;
} amba_cnn_c_max_unpool_attr_t;

typedef struct amba_cnn_c_resize_attr_s {
  int w;
  int h;
} amba_cnn_c_resize_attr_t;

typedef struct amba_cnn_c_roi_align_attr_s {
  int pool_mode;
  int out_w;
  int out_h;
  float spatial_scale;
  int sampling_ratio;
} amba_cnn_c_roi_align_attr_t;

typedef struct amba_cnn_c_softmax_attr_s {
  int axis;
  int group;
  int interleaved;
  int range_control;
} amba_cnn_c_softmax_attr_t;


// reduction operations ////////////////////////////////////////////////////////

typedef struct amba_cnn_c_arg_max_attr_s {
  int axis;
} amba_cnn_c_arg_max_attr_t;

typedef struct amba_cnn_c_arg_min_attr_s {
  int axis;
} amba_cnn_c_arg_min_attr_t;

typedef struct amba_cnn_c_reduce_log_sum_exp_attr_s {
  int axes;
} amba_cnn_c_reduce_log_sum_exp_attr_t;

typedef struct amba_cnn_c_reduce_max_attr_s {
  int axes;
} amba_cnn_c_reduce_max_attr_t;

typedef struct amba_cnn_c_reduce_mean_attr_s {
  int axes;
} amba_cnn_c_reduce_mean_attr_t;

typedef struct amba_cnn_c_reduce_min_attr_s {
  int axes;
} amba_cnn_c_reduce_min_attr_t;

typedef struct amba_cnn_c_reduce_prod_attr_s {
  int axes;
} amba_cnn_c_reduce_prod_attr_t;

typedef struct amba_cnn_c_reduce_sum_attr_s {
  int axes;
} amba_cnn_c_reduce_sum_attr_t;


// pointwise operations ////////////////////////////////////////////////////////

typedef struct amba_cnn_c_batch_normalization_attr_s {
  float epsilon;
} amba_cnn_c_batch_normalization_attr_t;

typedef struct amba_cnn_c_batch_normalization_3d_attr_s {
  float epsilon;
  int f_in;
  int packed_mode;
} amba_cnn_c_batch_normalization_3d_attr_t;

typedef struct amba_cnn_c_bit_shift_attr_s {
  int arithmetic;
  int left;
  int rotate;
} amba_cnn_c_bit_shift_attr_t;

typedef struct amba_cnn_c_clip_attr_s {
  float min;
  float max;
} amba_cnn_c_clip_attr_t;

typedef struct amba_cnn_c_elu_attr_s {
  float alpha;
} amba_cnn_c_elu_attr_t;

typedef struct amba_cnn_c_leaky_relu_attr_s {
  float alpha;
} amba_cnn_c_leaky_relu_attr_t;

typedef struct amba_cnn_c_log_attr_s {
  float base;
} amba_cnn_c_log_attr_t;

typedef struct amba_cnn_c_seg_interp_attr_s {
  float low_l;
  float high_l;
  float low_r;
  float high_r;
  float val_l;
  float val_m;
  float val_r;
} amba_cnn_c_seg_interp_attr_t;

typedef struct amba_cnn_c_selu_attr_s {
  float alpha;
  float gamma;
} amba_cnn_c_selu_attr_t;


// multi-reduction operations //////////////////////////////////////////////////


// generation operations ///////////////////////////////////////////////////////

typedef struct amba_cnn_c_random_uniform_attr_s {
  int w;
  int h;
  int d;
  int p;
  int initial_seed;
  float high;
  float low;
} amba_cnn_c_random_uniform_attr_t;


// manipulation operations /////////////////////////////////////////////////////

typedef struct amba_cnn_c_concat_attr_s {
  int axis;
} amba_cnn_c_concat_attr_t;

typedef struct amba_cnn_c_data_mask_attr_s {
  int region_format;
} amba_cnn_c_data_mask_attr_t;

typedef struct amba_cnn_c_depth_to_space_attr_s {
  int tile_w;
  int tile_h;
  int order;
} amba_cnn_c_depth_to_space_attr_t;

typedef struct amba_cnn_c_flatten_attr_s {
  int axis;
} amba_cnn_c_flatten_attr_t;

typedef struct amba_cnn_c_flip_attr_s {
  int hvrotate;
  int hflip;
  int vflip;
  int dflip;
  int pflip;
} amba_cnn_c_flip_attr_t;

typedef struct amba_cnn_c_gather_attr_s {
  int object_w;
  int object_h;
  int object_d;
} amba_cnn_c_gather_attr_t;

typedef struct amba_cnn_c_nms_attr_s {
  int center_point_box;
  int max_output_size;
  float overlap_threshold;
  float score_threshold;
} amba_cnn_c_nms_attr_t;

typedef struct amba_cnn_c_one_hot_attr_s {
  int depth;
  float on_value;
  float off_value;
} amba_cnn_c_one_hot_attr_t;

typedef struct amba_cnn_c_reshape_attr_s {
  int w;
  int h;
  int d;
  int p;
} amba_cnn_c_reshape_attr_t;

typedef struct amba_cnn_c_resamp_attr_s {
  int replicate_w;
  int replicate_h;
  int resamp_mode;
  int initial_phase_w;
  int initial_phase_h;
  int phase_inc_w;
  int phase_inc_h;
  int out_w;
  int out_h;
  int zr;
} amba_cnn_c_resamp_attr_t;

typedef struct amba_cnn_c_scatter_attr_s {
  int block_w;
  int block_h;
  int block_d;
} amba_cnn_c_scatter_attr_t;

typedef struct amba_cnn_c_slice_attr_s {
  int start_w;
  int start_h;
  int start_d;
  int start_p;
  int w;
  int h;
  int d;
  int p;
  int zr;
} amba_cnn_c_slice_attr_t;

typedef struct amba_cnn_c_space_to_depth_attr_s {
  int tile_w;
  int tile_h;
} amba_cnn_c_space_to_depth_attr_t;

typedef struct amba_cnn_c_strided_slice_attr_s {
  int start_w;
  int start_h;
  int start_d;
  int start_p;
  int w;
  int h;
  int d;
  int p;
  int stride_w;
  int stride_h;
  int stride_d;
  int stride_p;
  int zr;
} amba_cnn_c_strided_slice_attr_t;

typedef struct amba_cnn_c_top_k_attr_s {
  int k;
  int largest;
  int sorted;
} amba_cnn_c_top_k_attr_t;

typedef struct amba_cnn_c_transpose_attr_s {
  int to_w;
  int to_h;
  int to_d;
  int to_p;
} amba_cnn_c_transpose_attr_t;

typedef struct amba_cnn_c_unsqueeze_attr_s {
  int axes;
} amba_cnn_c_unsqueeze_attr_t;

typedef struct amba_cnn_c_variable_resamp_attr_s {
  int replicate_w;
  int replicate_h;
  int resamp_mode;
  int out_w;
  int out_h;
  int zr;
} amba_cnn_c_variable_resamp_attr_t;

typedef struct amba_cnn_c_warp_attr_s {
  int out_w;
  int out_h;
  int horizontal_grid_spacing_log2;
  int vertical_grid_spacing_log2;
  int zr;
} amba_cnn_c_warp_attr_t;


#ifdef __cplusplus
}
#endif

#endif
