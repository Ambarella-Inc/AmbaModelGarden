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

#ifndef AMBA_CNN_EXT_PRIM_C_TYPES_H
#define AMBA_CNN_EXT_PRIM_C_TYPES_H

////////////////////////////////////////////////////////////////////////////////
// This is a generated file. Please do not modify this file directly.         //
////////////////////////////////////////////////////////////////////////////////


#include "api/data-format-c.h"

#include "api/amba-cnn-c-vcoord-t.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct amba_cnn_ext_c_imm_s {
  amba_cnn_c_vcoord_t dim;
  const float* data;
} amba_cnn_ext_c_imm_t;

typedef struct amba_cnn_ext_c_abs_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_abs_attr_t;

typedef struct amba_cnn_ext_c_absdiff_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_absdiff_attr_t;

typedef struct amba_cnn_ext_c_absdiffi_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_absdiffi_attr_t;

typedef struct amba_cnn_ext_c_acos_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_acos_attr_t;

typedef struct amba_cnn_ext_c_acosh_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_acosh_attr_t;

typedef struct amba_cnn_ext_c_add_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_add_attr_t;

typedef struct amba_cnn_ext_c_addi_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_addi_attr_t;

typedef struct amba_cnn_ext_c_asin_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_asin_attr_t;

typedef struct amba_cnn_ext_c_asinh_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_asinh_attr_t;

typedef struct amba_cnn_ext_c_atan_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_atan_attr_t;

typedef struct amba_cnn_ext_c_atan2_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_atan2_attr_t;

typedef struct amba_cnn_ext_c_atanh_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_atanh_attr_t;

typedef struct amba_cnn_ext_c_bitcntwnd_attr_s {
  unsigned int window_w;
  unsigned int window_h;
  int start_w;
  int start_h;
  unsigned int stride_w;
  unsigned int stride_h;
  unsigned int out_w;
  unsigned int out_h;
} amba_cnn_ext_c_bitcntwnd_attr_t;

typedef struct amba_cnn_ext_c_cclbl_attr_s {
  unsigned int connectivity;
  unsigned int max_components;
  unsigned int max_segments_per_row;
  unsigned int min_pos_count;
  unsigned int min_pos_rows;
  unsigned int min_pos_cols;
  unsigned int min_neg_count;
  unsigned int min_neg_rows;
  unsigned int min_neg_cols;
  int comp_id_enable;
  int point_count_enable;
  int lite_mode;
} amba_cnn_ext_c_cclbl_attr_t;

typedef struct amba_cnn_ext_c_ceil_attr_s {
  int round_to_zero;
  int disable_reserved;
} amba_cnn_ext_c_ceil_attr_t;

typedef struct amba_cnn_ext_c_clampneg_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_clampneg_attr_t;

typedef struct amba_cnn_ext_c_clip_attr_s {
  float min;
  float max;
} amba_cnn_ext_c_clip_attr_t;

typedef struct amba_cnn_ext_c_conv2_attr_s {
  int start_w;
  int start_h;
  unsigned int stride_w;
  unsigned int stride_h;
  unsigned int out_w;
  unsigned int out_h;
  int zr0;
  int zr1;
  unsigned int padding_constant0;
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_conv2_attr_t;

typedef struct amba_cnn_ext_c_conv2i_attr_s {
  unsigned int dilation_w;
  unsigned int dilation_h;
  int start_w;
  int start_h;
  unsigned int stride_w;
  unsigned int stride_h;
  int transposed;
  int orig_conv_transposed_kernel;
  unsigned int out_w;
  unsigned int out_h;
  int zr;
  unsigned int padding_constant;
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_conv2i_attr_t;

typedef struct amba_cnn_ext_c_conv2ibeps_attr_s {
  int start_w;
  int start_h;
  unsigned int stride_w;
  unsigned int stride_h;
  unsigned int out_w;
  unsigned int out_h;
  unsigned int pool_mode;
  unsigned int pool_w;
  unsigned int pool_h;
  int zr;
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_conv2ibeps_attr_t;

typedef struct amba_cnn_ext_c_conv2ibepsbc_attr_s {
  unsigned int dilation_w;
  unsigned int dilation_h;
  int start_w;
  int start_h;
  unsigned int stride_w;
  unsigned int stride_h;
  int transposed;
  unsigned int out_w;
  unsigned int out_h;
  unsigned int pool_mode;
  unsigned int pool_w;
  unsigned int pool_h;
  int in_shift;
  int out_clamp_en;
  float out_clamp_min;
  float out_clamp_max;
  int zr;
  unsigned int padding_constant;
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_conv2ibepsbc_attr_t;

typedef struct amba_cnn_ext_c_conv2iepbs_attr_s {
  int start_w;
  int start_h;
  unsigned int stride_w;
  unsigned int stride_h;
  unsigned int out_w;
  unsigned int out_h;
  unsigned int pool_mode;
  unsigned int pool_w;
  unsigned int pool_h;
  int zr;
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_conv2iepbs_attr_t;

typedef struct amba_cnn_ext_c_conv2ipbs_attr_s {
  int start_w;
  int start_h;
  unsigned int stride_w;
  unsigned int stride_h;
  unsigned int out_w;
  unsigned int out_h;
  unsigned int pool_mode;
  unsigned int pool_w;
  unsigned int pool_h;
  int zr;
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_conv2ipbs_attr_t;

typedef struct amba_cnn_ext_c_conv3i_attr_s {
  unsigned int dilation_w;
  unsigned int dilation_h;
  unsigned int dilation_d;
  int start_w;
  int start_h;
  int start_d;
  unsigned int stride_w;
  unsigned int stride_h;
  unsigned int stride_d;
  int transposed;
  int orig_conv_transposed_kernel;
  unsigned int out_w;
  unsigned int out_h;
  unsigned int out_d;
  int zr;
  unsigned int padding_constant;
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_conv3i_attr_t;

typedef struct amba_cnn_ext_c_conv3ibepsbc_attr_s {
  unsigned int dilation_w;
  unsigned int dilation_h;
  unsigned int dilation_d;
  int start_w;
  int start_h;
  int start_d;
  unsigned int stride_w;
  unsigned int stride_h;
  unsigned int stride_d;
  int transposed;
  unsigned int out_w;
  unsigned int out_h;
  unsigned int out_d;
  unsigned int pool_mode;
  unsigned int pool_w;
  unsigned int pool_h;
  unsigned int pool_d;
  int in_shift;
  int out_clamp_en;
  float out_clamp_min;
  float out_clamp_max;
  int zr;
  unsigned int padding_constant;
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_conv3ibepsbc_attr_t;

typedef struct amba_cnn_ext_c_corr2_attr_s {
  int start_w;
  int start_h;
  unsigned int stride_w;
  unsigned int stride_h;
  unsigned int displ_stride_w;
  unsigned int displ_stride_h;
  unsigned int out_patch_w;
  unsigned int out_patch_h;
  unsigned int out_w;
  unsigned int out_h;
  int zr0;
  unsigned int padding_constant0;
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_corr2_attr_t;

typedef struct amba_cnn_ext_c_cos_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_cos_attr_t;

typedef struct amba_cnn_ext_c_cosh_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_cosh_attr_t;

typedef struct amba_cnn_ext_c_cotan_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_cotan_attr_t;

typedef struct amba_cnn_ext_c_crop_attr_s {
  unsigned int w;
  unsigned int h;
  unsigned int d;
  unsigned int p;
  int start_w;
  int start_h;
  int start_d;
  int start_p;
  int zr;
  unsigned int padding_constant;
} amba_cnn_ext_c_crop_attr_t;

typedef struct amba_cnn_ext_c_datamask_attr_s {
  unsigned int region_format;
} amba_cnn_ext_c_datamask_attr_t;

typedef struct amba_cnn_ext_c_depth2tile_attr_s {
  unsigned int tile_w;
  unsigned int tile_h;
  unsigned int order;
} amba_cnn_ext_c_depth2tile_attr_t;

typedef struct amba_cnn_ext_c_dfconv2i_attr_s {
  unsigned int deformable_mode;
  int warp_field_clip_enable;
  float x_min;
  float x_max;
  float y_min;
  float y_max;
  int start_w;
  int start_h;
  unsigned int stride_w;
  unsigned int stride_h;
  unsigned int out_w;
  unsigned int out_h;
  int zr0;
  unsigned int padding_constant0;
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_dfconv2i_attr_t;

typedef struct amba_cnn_ext_c_dfcorr2_attr_s {
  int warp_field_clip_enable;
  float x_min;
  float x_max;
  float y_min;
  float y_max;
  int start_w;
  int start_h;
  unsigned int stride_w;
  unsigned int stride_h;
  unsigned int displ_stride_w;
  unsigned int displ_stride_h;
  unsigned int out_patch_w;
  unsigned int out_patch_h;
  unsigned int out_w;
  unsigned int out_h;
  int zr0;
  unsigned int padding_constant0;
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_dfcorr2_attr_t;

typedef struct amba_cnn_ext_c_dot_attr_s {
  int strong_zero;
  int disable_reserved;
  unsigned int dot_dim;
} amba_cnn_ext_c_dot_attr_t;

typedef struct amba_cnn_ext_c_dotib_attr_s {
  int strong_zero;
  int disable_reserved;
  unsigned int dot_dim;
} amba_cnn_ext_c_dotib_attr_t;

typedef struct amba_cnn_ext_c_dotibe_attr_s {
  int strong_zero;
  int disable_reserved;
  unsigned int dot_dim;
} amba_cnn_ext_c_dotibe_attr_t;

typedef struct amba_cnn_ext_c_dwconv2_attr_s {
  int start_w;
  int start_h;
  unsigned int stride_w;
  unsigned int stride_h;
  unsigned int out_w;
  unsigned int out_h;
  int cm_inside;
  int zr0;
  unsigned int padding_constant0;
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_dwconv2_attr_t;

typedef struct amba_cnn_ext_c_dwconv2i_attr_s {
  unsigned int dilation_w;
  unsigned int dilation_h;
  int start_w;
  int start_h;
  unsigned int stride_w;
  unsigned int stride_h;
  int transposed;
  int orig_conv_transposed_kernel;
  unsigned int out_w;
  unsigned int out_h;
  int cm_inside;
  int zr;
  unsigned int padding_constant;
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_dwconv2i_attr_t;

typedef struct amba_cnn_ext_c_dwconv2ibeps_attr_s {
  int start_w;
  int start_h;
  unsigned int stride_w;
  unsigned int stride_h;
  unsigned int out_w;
  unsigned int out_h;
  unsigned int pool_mode;
  unsigned int pool_w;
  unsigned int pool_h;
  int cm_inside;
  int zr;
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_dwconv2ibeps_attr_t;

typedef struct amba_cnn_ext_c_dwconv2ibepsbc_attr_s {
  unsigned int dilation_w;
  unsigned int dilation_h;
  int start_w;
  int start_h;
  unsigned int stride_w;
  unsigned int stride_h;
  int transposed;
  unsigned int out_w;
  unsigned int out_h;
  unsigned int pool_mode;
  unsigned int pool_w;
  unsigned int pool_h;
  int cm_inside;
  int in_shift;
  int out_clamp_en;
  float out_clamp_min;
  float out_clamp_max;
  int zr;
  unsigned int padding_constant;
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_dwconv2ibepsbc_attr_t;

typedef struct amba_cnn_ext_c_dwconv2iepbs_attr_s {
  int start_w;
  int start_h;
  unsigned int stride_w;
  unsigned int stride_h;
  unsigned int out_w;
  unsigned int out_h;
  unsigned int pool_mode;
  unsigned int pool_w;
  unsigned int pool_h;
  int cm_inside;
  int zr;
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_dwconv2iepbs_attr_t;

typedef struct amba_cnn_ext_c_dwconv2ipbs_attr_s {
  int start_w;
  int start_h;
  unsigned int stride_w;
  unsigned int stride_h;
  unsigned int out_w;
  unsigned int out_h;
  unsigned int pool_mode;
  unsigned int pool_w;
  unsigned int pool_h;
  int cm_inside;
  int zr;
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_dwconv2ipbs_attr_t;

typedef struct amba_cnn_ext_c_dwconv3i_attr_s {
  unsigned int dilation_w;
  unsigned int dilation_h;
  unsigned int dilation_d;
  int start_w;
  int start_h;
  int start_d;
  unsigned int stride_w;
  unsigned int stride_h;
  unsigned int stride_d;
  int transposed;
  int orig_conv_transposed_kernel;
  unsigned int out_w;
  unsigned int out_h;
  unsigned int out_d;
  int cm_inside;
  int zr;
  unsigned int padding_constant;
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_dwconv3i_attr_t;

typedef struct amba_cnn_ext_c_dwconv3ibepsbc_attr_s {
  unsigned int dilation_w;
  unsigned int dilation_h;
  unsigned int dilation_d;
  int start_w;
  int start_h;
  int start_d;
  unsigned int stride_w;
  unsigned int stride_h;
  unsigned int stride_d;
  int transposed;
  unsigned int out_w;
  unsigned int out_h;
  unsigned int out_d;
  unsigned int pool_mode;
  unsigned int pool_w;
  unsigned int pool_h;
  unsigned int pool_d;
  int cm_inside;
  int in_shift;
  int out_clamp_en;
  float out_clamp_min;
  float out_clamp_max;
  int zr;
  unsigned int padding_constant;
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_dwconv3ibepsbc_attr_t;

typedef struct amba_cnn_ext_c_erf_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_erf_attr_t;

typedef struct amba_cnn_ext_c_exp_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_exp_attr_t;

typedef struct amba_cnn_ext_c_exp2_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_exp2_attr_t;

typedef struct amba_cnn_ext_c_feature2block_attr_s {
  unsigned int block_w;
  unsigned int block_h;
  unsigned int block_d;
} amba_cnn_ext_c_feature2block_attr_t;

typedef struct amba_cnn_ext_c_flip_attr_s {
  int hvrotate;
  int hflip;
  int vflip;
  int dflip;
  int pflip;
} amba_cnn_ext_c_flip_attr_t;

typedef struct amba_cnn_ext_c_floor_attr_s {
  int disable_reserved;
} amba_cnn_ext_c_floor_attr_t;

typedef struct amba_cnn_ext_c_frac_attr_s {
  int round_to_zero;
  int disable_reserved;
} amba_cnn_ext_c_frac_attr_t;

typedef struct amba_cnn_ext_c_gather_attr_s {
  unsigned int block_w;
  unsigned int block_h;
  unsigned int block_d;
  int start_w;
  int start_h;
  int start_d;
  int start_p;
  int zr;
  unsigned int padding_constant;
} amba_cnn_ext_c_gather_attr_t;

typedef struct amba_cnn_ext_c_gatheri_attr_s {
  unsigned int block_w;
  unsigned int block_h;
  unsigned int block_d;
  int start_w;
  int start_h;
  int start_d;
  int start_p;
  int zr;
  unsigned int padding_constant;
} amba_cnn_ext_c_gatheri_attr_t;

typedef struct amba_cnn_ext_c_grpaccumulatei_attr_s {
  int zr;
  unsigned int padding_constant;
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_grpaccumulatei_attr_t;

typedef struct amba_cnn_ext_c_grpduplicatei_attr_s {
  int zr;
  unsigned int padding_constant;
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_grpduplicatei_attr_t;

typedef struct amba_cnn_ext_c_histo_attr_s {
  unsigned int max_category;
} amba_cnn_ext_c_histo_attr_t;

typedef struct amba_cnn_ext_c_index_attr_s {
  unsigned int w;
  unsigned int h;
  unsigned int d;
  unsigned int p;
  unsigned int offset;
  unsigned int dim_coordinate;
  int flip;
  unsigned int inc;
} amba_cnn_ext_c_index_attr_t;

typedef struct amba_cnn_ext_c_inszero1_attr_s {
  unsigned int ins_dim;
  unsigned int num_ins;
} amba_cnn_ext_c_inszero1_attr_t;

typedef struct amba_cnn_ext_c_inszero2_attr_s {
  unsigned int num_ins_w;
  unsigned int num_ins_h;
} amba_cnn_ext_c_inszero2_attr_t;

typedef struct amba_cnn_ext_c_interleave_attr_s {
  unsigned int ins_dim;
} amba_cnn_ext_c_interleave_attr_t;

typedef struct amba_cnn_ext_c_linearcombine_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_linearcombine_attr_t;

typedef struct amba_cnn_ext_c_ln_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_ln_attr_t;

typedef struct amba_cnn_ext_c_lnxp1_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_lnxp1_attr_t;

typedef struct amba_cnn_ext_c_log2_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_log2_attr_t;

typedef struct amba_cnn_ext_c_lsh_attr_s {
  int arithmetic;
} amba_cnn_ext_c_lsh_attr_t;

typedef struct amba_cnn_ext_c_lshi_attr_s {
  int arithmetic;
} amba_cnn_ext_c_lshi_attr_t;

typedef struct amba_cnn_ext_c_maddi_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_maddi_attr_t;

typedef struct amba_cnn_ext_c_matmul_attr_s {
  int transpose_b;
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_matmul_attr_t;

typedef struct amba_cnn_ext_c_matmulib_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_matmulib_attr_t;

typedef struct amba_cnn_ext_c_maxroipool_attr_s {
  int out_w;
  int out_h;
  float spatial_scale;
} amba_cnn_ext_c_maxroipool_attr_t;

typedef struct amba_cnn_ext_c_mish_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_mish_attr_t;

typedef struct amba_cnn_ext_c_mmcw_attr_s {
  unsigned int op;
} amba_cnn_ext_c_mmcw_attr_t;

typedef struct amba_cnn_ext_c_mme_attr_s {
  unsigned int op;
} amba_cnn_ext_c_mme_attr_t;

typedef struct amba_cnn_ext_c_mmrd_attr_s {
  unsigned int op;
} amba_cnn_ext_c_mmrd_attr_t;

typedef struct amba_cnn_ext_c_mmrw_attr_s {
  unsigned int op;
} amba_cnn_ext_c_mmrw_attr_t;

typedef struct amba_cnn_ext_c_mmrwh_attr_s {
  unsigned int op;
} amba_cnn_ext_c_mmrwh_attr_t;

typedef struct amba_cnn_ext_c_mmrwhd_attr_s {
  unsigned int op;
} amba_cnn_ext_c_mmrwhd_attr_t;

typedef struct amba_cnn_ext_c_mmwnd_attr_s {
  unsigned int op;
  unsigned int window_w;
  unsigned int window_h;
  int start_w;
  int start_h;
  unsigned int stride_w;
  unsigned int stride_h;
  unsigned int out_w;
  unsigned int out_h;
  int zr;
  unsigned int padding_constant;
  int disable_reserved;
} amba_cnn_ext_c_mmwnd_attr_t;

typedef struct amba_cnn_ext_c_mmwnd3_attr_s {
  unsigned int op;
  unsigned int window_w;
  unsigned int window_h;
  unsigned int window_d;
  int start_w;
  int start_h;
  int start_d;
  unsigned int stride_w;
  unsigned int stride_h;
  unsigned int stride_d;
  unsigned int out_w;
  unsigned int out_h;
  unsigned int out_d;
  int zr;
  unsigned int padding_constant;
  int disable_reserved;
} amba_cnn_ext_c_mmwnd3_attr_t;

typedef struct amba_cnn_ext_c_mmwndnms_attr_s {
  unsigned int op;
  unsigned int window_w;
  unsigned int window_h;
  int start_w;
  int start_h;
  unsigned int stride_w;
  unsigned int stride_h;
  unsigned int out_w;
  unsigned int out_h;
  int zr;
  unsigned int padding_constant;
  int disable_reserved;
  unsigned int handle_ties;
} amba_cnn_ext_c_mmwndnms_attr_t;

typedef struct amba_cnn_ext_c_mul_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_mul_attr_t;

typedef struct amba_cnn_ext_c_muli_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_muli_attr_t;

typedef struct amba_cnn_ext_c_nms_attr_s {
  int center_point_box;
  int max_output_size;
  float overlap_threshold;
  float score_threshold;
} amba_cnn_ext_c_nms_attr_t;

typedef struct amba_cnn_ext_c_pow_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_pow_attr_t;

typedef struct amba_cnn_ext_c_pwli_attr_s {
  int indexing_mode;
  int reflection_mode;
  int index_below_mode;
  int index_above_mode;
  float out_value_range_below;
  float out_value_range_above;
  int disable_reserved;
} amba_cnn_ext_c_pwli_attr_t;

typedef struct amba_cnn_ext_c_random_attr_s {
  unsigned int w;
  unsigned int h;
  unsigned int d;
  unsigned int p;
  unsigned int initial_seed;
} amba_cnn_ext_c_random_attr_t;

typedef struct amba_cnn_ext_c_recip_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_recip_attr_t;

typedef struct amba_cnn_ext_c_repelmt_attr_s {
  unsigned int rep_dim;
  unsigned int num_rep;
} amba_cnn_ext_c_repelmt_attr_t;

typedef struct amba_cnn_ext_c_resamp_attr_s {
  int replicate_w;
  int replicate_h;
  unsigned int resamp_mode;
  int initial_phase_w;
  int initial_phase_h;
  unsigned int phase_inc_w;
  unsigned int phase_inc_h;
  unsigned int out_w;
  unsigned int out_h;
  int zr;
  unsigned int padding_constant;
} amba_cnn_ext_c_resamp_attr_t;

typedef struct amba_cnn_ext_c_reshape_attr_s {
  unsigned int w;
  unsigned int h;
  unsigned int d;
  unsigned int p;
} amba_cnn_ext_c_reshape_attr_t;

typedef struct amba_cnn_ext_c_roialign_attr_s {
  int pool_mode;
  int out_w;
  int out_h;
  float spatial_scale;
  int sampling_ratio;
} amba_cnn_ext_c_roialign_attr_t;

typedef struct amba_cnn_ext_c_round_attr_s {
  int round_mode;
  int disable_reserved;
} amba_cnn_ext_c_round_attr_t;

typedef struct amba_cnn_ext_c_rsh_attr_s {
  int arithmetic;
} amba_cnn_ext_c_rsh_attr_t;

typedef struct amba_cnn_ext_c_rshi_attr_s {
  int arithmetic;
} amba_cnn_ext_c_rshi_attr_t;

typedef struct amba_cnn_ext_c_rsqrt_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_rsqrt_attr_t;

typedef struct amba_cnn_ext_c_scatter_attr_s {
  unsigned int block_w;
  unsigned int block_h;
  unsigned int block_d;
} amba_cnn_ext_c_scatter_attr_t;

typedef struct amba_cnn_ext_c_scatteri_attr_s {
  unsigned int block_w;
  unsigned int block_h;
  unsigned int block_d;
} amba_cnn_ext_c_scatteri_attr_t;

typedef struct amba_cnn_ext_c_seginterp_attr_s {
  float low_l;
  float high_l;
  float low_r;
  float high_r;
  float val_l;
  float val_m;
  float val_r;
} amba_cnn_ext_c_seginterp_attr_t;

typedef struct amba_cnn_ext_c_selectb_attr_s {
  unsigned int block_sel;
} amba_cnn_ext_c_selectb_attr_t;

typedef struct amba_cnn_ext_c_sigmoid_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_sigmoid_attr_t;

typedef struct amba_cnn_ext_c_sin_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_sin_attr_t;

typedef struct amba_cnn_ext_c_sinh_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_sinh_attr_t;

typedef struct amba_cnn_ext_c_sqrt_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_sqrt_attr_t;

typedef struct amba_cnn_ext_c_sqrtdn_attr_s {
  unsigned int n;
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_sqrtdn_attr_t;

typedef struct amba_cnn_ext_c_stats_attr_s {
  int min;
  int max;
  int count;
  int average;
  int sigma;
  unsigned int out_h;
  unsigned int out_d;
  unsigned int out_p;
  int disable_reserved;
} amba_cnn_ext_c_stats_attr_t;

typedef struct amba_cnn_ext_c_stride_attr_s {
  unsigned int stride_w;
  unsigned int stride_higher_dim;
  unsigned int higher_dim;
} amba_cnn_ext_c_stride_attr_t;

typedef struct amba_cnn_ext_c_sub_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_sub_attr_t;

typedef struct amba_cnn_ext_c_subfrmi_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_subfrmi_attr_t;

typedef struct amba_cnn_ext_c_sumrd_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_sumrd_attr_t;

typedef struct amba_cnn_ext_c_sumrw_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_sumrw_attr_t;

typedef struct amba_cnn_ext_c_sumrwh_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_sumrwh_attr_t;

typedef struct amba_cnn_ext_c_sumrwhd_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_sumrwhd_attr_t;

typedef struct amba_cnn_ext_c_swish_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_swish_attr_t;

typedef struct amba_cnn_ext_c_tan_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_tan_attr_t;

typedef struct amba_cnn_ext_c_tanh_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_tanh_attr_t;

typedef struct amba_cnn_ext_c_tblinterp1_attr_s {
  unsigned int max_exp;
  unsigned int n_intervals_w_exp;
  int is_signed;
  int disable_reserved;
} amba_cnn_ext_c_tblinterp1_attr_t;

typedef struct amba_cnn_ext_c_tblinterp1i_attr_s {
  unsigned int max_exp;
  unsigned int n_intervals_w_exp;
  int is_signed;
  int disable_reserved;
} amba_cnn_ext_c_tblinterp1i_attr_t;

typedef struct amba_cnn_ext_c_tblinterp2_attr_s {
  unsigned int max_exp;
  unsigned int n_intervals_w_exp;
  unsigned int n_intervals_h_exp;
  int is_signed;
  int disable_reserved;
} amba_cnn_ext_c_tblinterp2_attr_t;

typedef struct amba_cnn_ext_c_tblinterp2i_attr_s {
  unsigned int max_exp;
  unsigned int n_intervals_w_exp;
  unsigned int n_intervals_h_exp;
  int is_signed;
  int disable_reserved;
} amba_cnn_ext_c_tblinterp2i_attr_t;

typedef struct amba_cnn_ext_c_tblinterp3_attr_s {
  unsigned int max_exp;
  unsigned int n_intervals_w_exp;
  unsigned int n_intervals_h_exp;
  unsigned int n_intervals_d_exp;
  int is_signed;
  int disable_reserved;
} amba_cnn_ext_c_tblinterp3_attr_t;

typedef struct amba_cnn_ext_c_tblinterp3i_attr_s {
  unsigned int max_exp;
  unsigned int n_intervals_w_exp;
  unsigned int n_intervals_h_exp;
  unsigned int n_intervals_d_exp;
  int is_signed;
  int disable_reserved;
} amba_cnn_ext_c_tblinterp3i_attr_t;

typedef struct amba_cnn_ext_c_tile2depth_attr_s {
  unsigned int tile_w;
  unsigned int tile_h;
  int start_w;
  int start_h;
  unsigned int stride_w;
  unsigned int stride_h;
  unsigned int out_w;
  unsigned int out_h;
  int zr;
  unsigned int padding_constant;
} amba_cnn_ext_c_tile2depth_attr_t;

typedef struct amba_cnn_ext_c_topk_attr_s {
  int k;
  int largest;
  int sorted;
} amba_cnn_ext_c_topk_attr_t;

typedef struct amba_cnn_ext_c_transpose_attr_s {
  unsigned int to_w;
  unsigned int to_h;
  unsigned int to_d;
  unsigned int to_p;
} amba_cnn_ext_c_transpose_attr_t;

typedef struct amba_cnn_ext_c_trunc_attr_s {
  int round_to_zero;
  int disable_reserved;
} amba_cnn_ext_c_trunc_attr_t;

typedef struct amba_cnn_ext_c_typeconv_attr_s {
  int strong_zero;
  int disable_reserved;
} amba_cnn_ext_c_typeconv_attr_t;

typedef struct amba_cnn_ext_c_variableresamp_attr_s {
  int replicate_w;
  int replicate_h;
  unsigned int resamp_mode;
  unsigned int out_w;
  unsigned int out_h;
  int zr;
  unsigned int padding_constant;
} amba_cnn_ext_c_variableresamp_attr_t;

typedef struct amba_cnn_ext_c_warp_attr_s {
  unsigned int out_w;
  unsigned int out_h;
  int warp_field_clip_enable;
  float x_min;
  float x_max;
  float y_min;
  float y_max;
  unsigned int horizontal_grid_spacing_log2;
  unsigned int vertical_grid_spacing_log2;
  int zr;
  unsigned int padding_constant;
} amba_cnn_ext_c_warp_attr_t;

typedef struct amba_cnn_ext_c_warpi_attr_s {
  unsigned int out_w;
  unsigned int out_h;
  unsigned int horizontal_grid_spacing_log2;
  unsigned int vertical_grid_spacing_log2;
  int zr;
  unsigned int padding_constant;
} amba_cnn_ext_c_warpi_attr_t;


typedef void (*amba_cnn_ext_c_abs_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_abs_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_absdiff_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_ext_c_absdiff_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_absdiffi_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_absdiffi_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_acos_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_acos_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_acosh_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_acosh_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_add_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_ext_c_add_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_addi_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_addi_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_asin_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_asin_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_asinh_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_asinh_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_atan_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_atan_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_atan2_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_ext_c_atan2_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_atanh_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_atanh_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_bitcntrw_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_bitcntrwh_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_bitcntrwhd_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_bitcntrwhdp_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_bitcntwnd_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_bitcntwnd_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_bwand_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_bwandi_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_bwandn0_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_bwandn1_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_bwnand_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_bwnandi_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_bwnor_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_bwnori_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_bwnot_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_bwor_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_bwori_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_bworn0_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_bworn1_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_bwxnor_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_bwxnori_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_bwxor_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_bwxori_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_cclbl_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_cclbl_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_cdf_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_ceil_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_ceil_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_clampneg_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_clampneg_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_clip_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_clip_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_conv2_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_ext_c_conv2_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_conv2i_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_conv2i_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_conv2ibeps_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_imm_t* imm1,
     const amba_cnn_ext_c_imm_t* imm2,
     const amba_cnn_ext_c_imm_t* imm3,
     const amba_cnn_ext_c_imm_t* imm4,
     const amba_cnn_ext_c_imm_t* imm5,
     const amba_cnn_ext_c_imm_t* imm6,
     const amba_cnn_ext_c_conv2ibeps_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_conv2ibepsbc_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_imm_t* imm1,
     const amba_cnn_ext_c_imm_t* imm2,
     const amba_cnn_ext_c_imm_t* imm3,
     const amba_cnn_ext_c_imm_t* imm4,
     const amba_cnn_ext_c_imm_t* imm5,
     const amba_cnn_ext_c_imm_t* imm6,
     const amba_cnn_ext_c_imm_t* imm7,
     const amba_cnn_ext_c_imm_t* imm8,
     const amba_cnn_ext_c_conv2ibepsbc_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_conv2iepbs_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_imm_t* imm1,
     const amba_cnn_ext_c_imm_t* imm2,
     const amba_cnn_ext_c_imm_t* imm3,
     const amba_cnn_ext_c_conv2iepbs_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_conv2ipbs_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_imm_t* imm1,
     const amba_cnn_ext_c_imm_t* imm2,
     const amba_cnn_ext_c_conv2ipbs_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_conv3i_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_conv3i_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_conv3ibepsbc_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_imm_t* imm1,
     const amba_cnn_ext_c_imm_t* imm2,
     const amba_cnn_ext_c_imm_t* imm3,
     const amba_cnn_ext_c_imm_t* imm4,
     const amba_cnn_ext_c_imm_t* imm5,
     const amba_cnn_ext_c_imm_t* imm6,
     const amba_cnn_ext_c_imm_t* imm7,
     const amba_cnn_ext_c_imm_t* imm8,
     const amba_cnn_ext_c_conv3ibepsbc_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_corr2_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_ext_c_corr2_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_cos_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_cos_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_cosh_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_cosh_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_cotan_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_cotan_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_crop_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_crop_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_datamask_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_ext_c_datamask_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_depth2tile_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_depth2tile_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_dfconv2i_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_dfconv2i_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_dfcorr2_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1, const char* src2, int port2,
     const amba_cnn_ext_c_dfcorr2_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_dot_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_ext_c_dot_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_dotib_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_imm_t* imm1,
     const amba_cnn_ext_c_dotib_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_dotibe_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_imm_t* imm1,
     const amba_cnn_ext_c_imm_t* imm2,
     const amba_cnn_ext_c_imm_t* imm3,
     const amba_cnn_ext_c_dotibe_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_dwconv2_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_ext_c_dwconv2_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_dwconv2i_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_dwconv2i_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_dwconv2ibeps_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_imm_t* imm1,
     const amba_cnn_ext_c_imm_t* imm2,
     const amba_cnn_ext_c_imm_t* imm3,
     const amba_cnn_ext_c_imm_t* imm4,
     const amba_cnn_ext_c_imm_t* imm5,
     const amba_cnn_ext_c_imm_t* imm6,
     const amba_cnn_ext_c_dwconv2ibeps_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_dwconv2ibepsbc_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_imm_t* imm1,
     const amba_cnn_ext_c_imm_t* imm2,
     const amba_cnn_ext_c_imm_t* imm3,
     const amba_cnn_ext_c_imm_t* imm4,
     const amba_cnn_ext_c_imm_t* imm5,
     const amba_cnn_ext_c_imm_t* imm6,
     const amba_cnn_ext_c_imm_t* imm7,
     const amba_cnn_ext_c_imm_t* imm8,
     const amba_cnn_ext_c_dwconv2ibepsbc_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_dwconv2iepbs_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_imm_t* imm1,
     const amba_cnn_ext_c_imm_t* imm2,
     const amba_cnn_ext_c_imm_t* imm3,
     const amba_cnn_ext_c_dwconv2iepbs_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_dwconv2ipbs_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_imm_t* imm1,
     const amba_cnn_ext_c_imm_t* imm2,
     const amba_cnn_ext_c_dwconv2ipbs_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_dwconv3i_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_dwconv3i_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_dwconv3ibepsbc_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_imm_t* imm1,
     const amba_cnn_ext_c_imm_t* imm2,
     const amba_cnn_ext_c_imm_t* imm3,
     const amba_cnn_ext_c_imm_t* imm4,
     const amba_cnn_ext_c_imm_t* imm5,
     const amba_cnn_ext_c_imm_t* imm6,
     const amba_cnn_ext_c_imm_t* imm7,
     const amba_cnn_ext_c_imm_t* imm8,
     const amba_cnn_ext_c_dwconv3ibepsbc_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_eqb_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_eqib_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_erf_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_erf_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_exp_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_exp_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_exp2_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_exp2_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_feature2block_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_feature2block_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_findfirstone_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_findfirstzero_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_flip_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_flip_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_floor_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_floor_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_frac_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_frac_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_gather_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_ext_c_gather_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_gatheri_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_gatheri_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_grpaccumulatei_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_imm_t* imm1,
     const amba_cnn_ext_c_imm_t* imm2,
     const amba_cnn_ext_c_grpaccumulatei_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_grpduplicatei_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_imm_t* imm1,
     const amba_cnn_ext_c_imm_t* imm2,
     const amba_cnn_ext_c_grpduplicatei_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_gtb_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_gteb_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_gteib_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_gtib_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_hflip_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_histo_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_histo_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_hvrotate_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_index_factory_t)
    (const char* id,
     const amba_cnn_ext_c_index_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_inszero1_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_inszero1_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_inszero2_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_inszero2_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_interleave_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_ext_c_interleave_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_intimg_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_linearcombine_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1, const char* src2, int port2,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_imm_t* imm1,
     const amba_cnn_ext_c_imm_t* imm2,
     const amba_cnn_ext_c_imm_t* imm3,
     const amba_cnn_ext_c_linearcombine_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_ln_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_ln_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_lnxp1_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_lnxp1_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_log2_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_log2_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_lsh_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_ext_c_lsh_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_lshi_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_lshi_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_ltb_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_lteb_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_lteib_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_ltib_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_maddi_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_imm_t* imm1,
     const amba_cnn_ext_c_maddi_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_matmul_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_ext_c_matmul_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_matmulib_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_imm_t* imm1,
     const amba_cnn_ext_c_matmulib_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_maxroipool_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_ext_c_maxroipool_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_merged_factory_t)
    (const char* id, int num_srcs, const char** srcs, const int* ports,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_mergeh_factory_t)
    (const char* id, int num_srcs, const char** srcs, const int* ports,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_mergep_factory_t)
    (const char* id, int num_srcs, const char** srcs, const int* ports,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_mergew_factory_t)
    (const char* id, int num_srcs, const char** srcs, const int* ports,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_mish_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_mish_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_mmcw_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_mmcw_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_mme_factory_t)
    (const char* id, int num_srcs, const char** srcs, const int* ports,
     const amba_cnn_ext_c_mme_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_mmrd_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_mmrd_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_mmrw_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_mmrw_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_mmrwh_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_mmrwh_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_mmrwhd_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_mmrwhd_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_mmwnd_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_mmwnd_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_mmwnd3_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_mmwnd3_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_mmwndnms_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_mmwndnms_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_mul_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_ext_c_mul_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_muli_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_muli_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_muxb_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1, const char* src2, int port2,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_neb_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_neib_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_nms_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_ext_c_nms_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_passthrough_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_pow_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_pow_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_pwli_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_imm_t* imm1,
     const amba_cnn_ext_c_imm_t* imm2,
     const amba_cnn_ext_c_pwli_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_random_factory_t)
    (const char* id,
     const amba_cnn_ext_c_random_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_recip_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_recip_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_repelmt_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_repelmt_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_resamp_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_resamp_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_reshape_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_reshape_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_rlsh_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_rlshi_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_roialign_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_ext_c_roialign_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_round_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_round_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_roundint_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_rowlsh_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_rowlshi_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_rowrsh_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_rowrshi_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_rrsh_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_rrshi_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_rsh_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_ext_c_rsh_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_rshi_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_rshi_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_rsqrt_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_rsqrt_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_scatter_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1, const char* src2, int port2,
     const amba_cnn_ext_c_scatter_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_scatteri_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_scatteri_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_seginterp_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_seginterp_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_selectb_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_ext_c_selectb_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_sigmoid_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_sigmoid_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_sin_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_sin_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_sinh_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_sinh_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_sqrt_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_sqrt_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_sqrtdn_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_sqrtdn_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_stats_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_ext_c_stats_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_stride_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_stride_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_sub_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_ext_c_sub_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_subfrmi_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_subfrmi_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_sumrd_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_sumrd_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_sumrw_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_sumrw_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_sumrwh_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_sumrwh_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_sumrwhd_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_sumrwhd_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_swish_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_swish_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_tan_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_tan_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_tanh_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_tanh_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_tblinterp1_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_ext_c_tblinterp1_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_tblinterp1i_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_tblinterp1i_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_tblinterp2_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_ext_c_tblinterp2_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_tblinterp2i_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_tblinterp2i_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_tblinterp3_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_ext_c_tblinterp3_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_tblinterp3i_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_tblinterp3i_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_tile2depth_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_tile2depth_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_topk_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_topk_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_transpose_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_transpose_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_transposewd_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_transposewh_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_trunc_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_trunc_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_typecast_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_typeconv_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_typeconv_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_variableresamp_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_ext_c_variableresamp_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_vflip_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_warp_factory_t)
    (const char* id, const char* src0, int port0, const char* src1, int port1,
     const amba_cnn_ext_c_warp_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_warpi_factory_t)
    (const char* id, const char* src0, int port0,
     const amba_cnn_ext_c_imm_t* imm0,
     const amba_cnn_ext_c_warpi_attr_t* attr,
     const amba_cnn_c_data_format_t* dfs,
     const int* reserved);

typedef void (*amba_cnn_ext_c_constant_factory_t)
    (const char* id, const amba_cnn_ext_c_imm_t* imm0);

typedef void (*amba_cnn_ext_c_select_output_t)
    (int node_oport, const char* prim_id, int prim_oport);

typedef void (*amba_cnn_ext_c_constant_input_t)
    (const float** data, const amba_cnn_c_vcoord_t** size, int node_iport);

typedef void (*amba_cnn_ext_c_imm_data_format_t)
    (const char* prim_id, int imm_id, const amba_cnn_c_data_format_t* df);


typedef struct amba_cnn_ext_c_prim_factories_s {
  amba_cnn_ext_c_abs_factory_t            abs_factory;
  amba_cnn_ext_c_absdiff_factory_t        absdiff_factory;
  amba_cnn_ext_c_absdiffi_factory_t       absdiffi_factory;
  amba_cnn_ext_c_acos_factory_t           acos_factory;
  amba_cnn_ext_c_acosh_factory_t          acosh_factory;
  amba_cnn_ext_c_add_factory_t            add_factory;
  amba_cnn_ext_c_addi_factory_t           addi_factory;
  amba_cnn_ext_c_asin_factory_t           asin_factory;
  amba_cnn_ext_c_asinh_factory_t          asinh_factory;
  amba_cnn_ext_c_atan_factory_t           atan_factory;
  amba_cnn_ext_c_atan2_factory_t          atan2_factory;
  amba_cnn_ext_c_atanh_factory_t          atanh_factory;
  amba_cnn_ext_c_bitcntrw_factory_t       bitcntrw_factory;
  amba_cnn_ext_c_bitcntrwh_factory_t      bitcntrwh_factory;
  amba_cnn_ext_c_bitcntrwhd_factory_t     bitcntrwhd_factory;
  amba_cnn_ext_c_bitcntrwhdp_factory_t    bitcntrwhdp_factory;
  amba_cnn_ext_c_bitcntwnd_factory_t      bitcntwnd_factory;
  amba_cnn_ext_c_bwand_factory_t          bwand_factory;
  amba_cnn_ext_c_bwandi_factory_t         bwandi_factory;
  amba_cnn_ext_c_bwandn0_factory_t        bwandn0_factory;
  amba_cnn_ext_c_bwandn1_factory_t        bwandn1_factory;
  amba_cnn_ext_c_bwnand_factory_t         bwnand_factory;
  amba_cnn_ext_c_bwnandi_factory_t        bwnandi_factory;
  amba_cnn_ext_c_bwnor_factory_t          bwnor_factory;
  amba_cnn_ext_c_bwnori_factory_t         bwnori_factory;
  amba_cnn_ext_c_bwnot_factory_t          bwnot_factory;
  amba_cnn_ext_c_bwor_factory_t           bwor_factory;
  amba_cnn_ext_c_bwori_factory_t          bwori_factory;
  amba_cnn_ext_c_bworn0_factory_t         bworn0_factory;
  amba_cnn_ext_c_bworn1_factory_t         bworn1_factory;
  amba_cnn_ext_c_bwxnor_factory_t         bwxnor_factory;
  amba_cnn_ext_c_bwxnori_factory_t        bwxnori_factory;
  amba_cnn_ext_c_bwxor_factory_t          bwxor_factory;
  amba_cnn_ext_c_bwxori_factory_t         bwxori_factory;
  amba_cnn_ext_c_cclbl_factory_t          cclbl_factory;
  amba_cnn_ext_c_cdf_factory_t            cdf_factory;
  amba_cnn_ext_c_ceil_factory_t           ceil_factory;
  amba_cnn_ext_c_clampneg_factory_t       clampneg_factory;
  amba_cnn_ext_c_clip_factory_t           clip_factory;
  amba_cnn_ext_c_conv2_factory_t          conv2_factory;
  amba_cnn_ext_c_conv2i_factory_t         conv2i_factory;
  amba_cnn_ext_c_conv2ibeps_factory_t     conv2ibeps_factory;
  amba_cnn_ext_c_conv2ibepsbc_factory_t   conv2ibepsbc_factory;
  amba_cnn_ext_c_conv2iepbs_factory_t     conv2iepbs_factory;
  amba_cnn_ext_c_conv2ipbs_factory_t      conv2ipbs_factory;
  amba_cnn_ext_c_conv3i_factory_t         conv3i_factory;
  amba_cnn_ext_c_conv3ibepsbc_factory_t   conv3ibepsbc_factory;
  amba_cnn_ext_c_corr2_factory_t          corr2_factory;
  amba_cnn_ext_c_cos_factory_t            cos_factory;
  amba_cnn_ext_c_cosh_factory_t           cosh_factory;
  amba_cnn_ext_c_cotan_factory_t          cotan_factory;
  amba_cnn_ext_c_crop_factory_t           crop_factory;
  amba_cnn_ext_c_datamask_factory_t       datamask_factory;
  amba_cnn_ext_c_depth2tile_factory_t     depth2tile_factory;
  amba_cnn_ext_c_dfconv2i_factory_t       dfconv2i_factory;
  amba_cnn_ext_c_dfcorr2_factory_t        dfcorr2_factory;
  amba_cnn_ext_c_dot_factory_t            dot_factory;
  amba_cnn_ext_c_dotib_factory_t          dotib_factory;
  amba_cnn_ext_c_dotibe_factory_t         dotibe_factory;
  amba_cnn_ext_c_dwconv2_factory_t        dwconv2_factory;
  amba_cnn_ext_c_dwconv2i_factory_t       dwconv2i_factory;
  amba_cnn_ext_c_dwconv2ibeps_factory_t   dwconv2ibeps_factory;
  amba_cnn_ext_c_dwconv2ibepsbc_factory_t dwconv2ibepsbc_factory;
  amba_cnn_ext_c_dwconv2iepbs_factory_t   dwconv2iepbs_factory;
  amba_cnn_ext_c_dwconv2ipbs_factory_t    dwconv2ipbs_factory;
  amba_cnn_ext_c_dwconv3i_factory_t       dwconv3i_factory;
  amba_cnn_ext_c_dwconv3ibepsbc_factory_t dwconv3ibepsbc_factory;
  amba_cnn_ext_c_eqb_factory_t            eqb_factory;
  amba_cnn_ext_c_eqib_factory_t           eqib_factory;
  amba_cnn_ext_c_erf_factory_t            erf_factory;
  amba_cnn_ext_c_exp_factory_t            exp_factory;
  amba_cnn_ext_c_exp2_factory_t           exp2_factory;
  amba_cnn_ext_c_feature2block_factory_t  feature2block_factory;
  amba_cnn_ext_c_findfirstone_factory_t   findfirstone_factory;
  amba_cnn_ext_c_findfirstzero_factory_t  findfirstzero_factory;
  amba_cnn_ext_c_flip_factory_t           flip_factory;
  amba_cnn_ext_c_floor_factory_t          floor_factory;
  amba_cnn_ext_c_frac_factory_t           frac_factory;
  amba_cnn_ext_c_gather_factory_t         gather_factory;
  amba_cnn_ext_c_gatheri_factory_t        gatheri_factory;
  amba_cnn_ext_c_grpaccumulatei_factory_t grpaccumulatei_factory;
  amba_cnn_ext_c_grpduplicatei_factory_t  grpduplicatei_factory;
  amba_cnn_ext_c_gtb_factory_t            gtb_factory;
  amba_cnn_ext_c_gteb_factory_t           gteb_factory;
  amba_cnn_ext_c_gteib_factory_t          gteib_factory;
  amba_cnn_ext_c_gtib_factory_t           gtib_factory;
  amba_cnn_ext_c_hflip_factory_t          hflip_factory;
  amba_cnn_ext_c_histo_factory_t          histo_factory;
  amba_cnn_ext_c_hvrotate_factory_t       hvrotate_factory;
  amba_cnn_ext_c_index_factory_t          index_factory;
  amba_cnn_ext_c_inszero1_factory_t       inszero1_factory;
  amba_cnn_ext_c_inszero2_factory_t       inszero2_factory;
  amba_cnn_ext_c_interleave_factory_t     interleave_factory;
  amba_cnn_ext_c_intimg_factory_t         intimg_factory;
  amba_cnn_ext_c_linearcombine_factory_t  linearcombine_factory;
  amba_cnn_ext_c_ln_factory_t             ln_factory;
  amba_cnn_ext_c_lnxp1_factory_t          lnxp1_factory;
  amba_cnn_ext_c_log2_factory_t           log2_factory;
  amba_cnn_ext_c_lsh_factory_t            lsh_factory;
  amba_cnn_ext_c_lshi_factory_t           lshi_factory;
  amba_cnn_ext_c_ltb_factory_t            ltb_factory;
  amba_cnn_ext_c_lteb_factory_t           lteb_factory;
  amba_cnn_ext_c_lteib_factory_t          lteib_factory;
  amba_cnn_ext_c_ltib_factory_t           ltib_factory;
  amba_cnn_ext_c_maddi_factory_t          maddi_factory;
  amba_cnn_ext_c_matmul_factory_t         matmul_factory;
  amba_cnn_ext_c_matmulib_factory_t       matmulib_factory;
  amba_cnn_ext_c_maxroipool_factory_t     maxroipool_factory;
  amba_cnn_ext_c_merged_factory_t         merged_factory;
  amba_cnn_ext_c_mergeh_factory_t         mergeh_factory;
  amba_cnn_ext_c_mergep_factory_t         mergep_factory;
  amba_cnn_ext_c_mergew_factory_t         mergew_factory;
  amba_cnn_ext_c_mish_factory_t           mish_factory;
  amba_cnn_ext_c_mmcw_factory_t           mmcw_factory;
  amba_cnn_ext_c_mme_factory_t            mme_factory;
  amba_cnn_ext_c_mmrd_factory_t           mmrd_factory;
  amba_cnn_ext_c_mmrw_factory_t           mmrw_factory;
  amba_cnn_ext_c_mmrwh_factory_t          mmrwh_factory;
  amba_cnn_ext_c_mmrwhd_factory_t         mmrwhd_factory;
  amba_cnn_ext_c_mmwnd_factory_t          mmwnd_factory;
  amba_cnn_ext_c_mmwnd3_factory_t         mmwnd3_factory;
  amba_cnn_ext_c_mmwndnms_factory_t       mmwndnms_factory;
  amba_cnn_ext_c_mul_factory_t            mul_factory;
  amba_cnn_ext_c_muli_factory_t           muli_factory;
  amba_cnn_ext_c_muxb_factory_t           muxb_factory;
  amba_cnn_ext_c_neb_factory_t            neb_factory;
  amba_cnn_ext_c_neib_factory_t           neib_factory;
  amba_cnn_ext_c_nms_factory_t            nms_factory;
  amba_cnn_ext_c_passthrough_factory_t    passthrough_factory;
  amba_cnn_ext_c_pow_factory_t            pow_factory;
  amba_cnn_ext_c_pwli_factory_t           pwli_factory;
  amba_cnn_ext_c_random_factory_t         random_factory;
  amba_cnn_ext_c_recip_factory_t          recip_factory;
  amba_cnn_ext_c_repelmt_factory_t        repelmt_factory;
  amba_cnn_ext_c_resamp_factory_t         resamp_factory;
  amba_cnn_ext_c_reshape_factory_t        reshape_factory;
  amba_cnn_ext_c_rlsh_factory_t           rlsh_factory;
  amba_cnn_ext_c_rlshi_factory_t          rlshi_factory;
  amba_cnn_ext_c_roialign_factory_t       roialign_factory;
  amba_cnn_ext_c_round_factory_t          round_factory;
  amba_cnn_ext_c_roundint_factory_t       roundint_factory;
  amba_cnn_ext_c_rowlsh_factory_t         rowlsh_factory;
  amba_cnn_ext_c_rowlshi_factory_t        rowlshi_factory;
  amba_cnn_ext_c_rowrsh_factory_t         rowrsh_factory;
  amba_cnn_ext_c_rowrshi_factory_t        rowrshi_factory;
  amba_cnn_ext_c_rrsh_factory_t           rrsh_factory;
  amba_cnn_ext_c_rrshi_factory_t          rrshi_factory;
  amba_cnn_ext_c_rsh_factory_t            rsh_factory;
  amba_cnn_ext_c_rshi_factory_t           rshi_factory;
  amba_cnn_ext_c_rsqrt_factory_t          rsqrt_factory;
  amba_cnn_ext_c_scatter_factory_t        scatter_factory;
  amba_cnn_ext_c_scatteri_factory_t       scatteri_factory;
  amba_cnn_ext_c_seginterp_factory_t      seginterp_factory;
  amba_cnn_ext_c_selectb_factory_t        selectb_factory;
  amba_cnn_ext_c_sigmoid_factory_t        sigmoid_factory;
  amba_cnn_ext_c_sin_factory_t            sin_factory;
  amba_cnn_ext_c_sinh_factory_t           sinh_factory;
  amba_cnn_ext_c_sqrt_factory_t           sqrt_factory;
  amba_cnn_ext_c_sqrtdn_factory_t         sqrtdn_factory;
  amba_cnn_ext_c_stats_factory_t          stats_factory;
  amba_cnn_ext_c_stride_factory_t         stride_factory;
  amba_cnn_ext_c_sub_factory_t            sub_factory;
  amba_cnn_ext_c_subfrmi_factory_t        subfrmi_factory;
  amba_cnn_ext_c_sumrd_factory_t          sumrd_factory;
  amba_cnn_ext_c_sumrw_factory_t          sumrw_factory;
  amba_cnn_ext_c_sumrwh_factory_t         sumrwh_factory;
  amba_cnn_ext_c_sumrwhd_factory_t        sumrwhd_factory;
  amba_cnn_ext_c_swish_factory_t          swish_factory;
  amba_cnn_ext_c_tan_factory_t            tan_factory;
  amba_cnn_ext_c_tanh_factory_t           tanh_factory;
  amba_cnn_ext_c_tblinterp1_factory_t     tblinterp1_factory;
  amba_cnn_ext_c_tblinterp1i_factory_t    tblinterp1i_factory;
  amba_cnn_ext_c_tblinterp2_factory_t     tblinterp2_factory;
  amba_cnn_ext_c_tblinterp2i_factory_t    tblinterp2i_factory;
  amba_cnn_ext_c_tblinterp3_factory_t     tblinterp3_factory;
  amba_cnn_ext_c_tblinterp3i_factory_t    tblinterp3i_factory;
  amba_cnn_ext_c_tile2depth_factory_t     tile2depth_factory;
  amba_cnn_ext_c_topk_factory_t           topk_factory;
  amba_cnn_ext_c_transpose_factory_t      transpose_factory;
  amba_cnn_ext_c_transposewd_factory_t    transposewd_factory;
  amba_cnn_ext_c_transposewh_factory_t    transposewh_factory;
  amba_cnn_ext_c_trunc_factory_t          trunc_factory;
  amba_cnn_ext_c_typecast_factory_t       typecast_factory;
  amba_cnn_ext_c_typeconv_factory_t       typeconv_factory;
  amba_cnn_ext_c_variableresamp_factory_t variableresamp_factory;
  amba_cnn_ext_c_vflip_factory_t          vflip_factory;
  amba_cnn_ext_c_warp_factory_t           warp_factory;
  amba_cnn_ext_c_warpi_factory_t          warpi_factory;
  amba_cnn_ext_c_constant_factory_t       constant_factory;
  amba_cnn_ext_c_select_output_t          select_output;
  amba_cnn_ext_c_constant_input_t         constant_input;
  amba_cnn_ext_c_imm_data_format_t        imm_data_format;
} amba_cnn_ext_c_prim_factories_t;

#ifdef __cplusplus
}
#endif

#endif
