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

#ifndef AMBA_CNN_EXT_C_TYPES_H
#define AMBA_CNN_EXT_C_TYPES_H

#include "api/amba-cnn-ext-prim-c-types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*amba_cnn_ext_c_node_init_t)
  (int* cid, amba_cnn_c_vcoord_t* osz,
   int num_src, const amba_cnn_c_vcoord_t* isz, const char* attr,
   const amba_cnn_c_data_format_t* df);

typedef int (*amba_cnn_ext_c_node_expand_t)
  (int cid, const amba_cnn_ext_c_prim_factories_t* funcs);

typedef int (*amba_cnn_ext_c_node_release_t)(int cid);

typedef struct amba_cnn_ext_c_node_type_s {
  const char*                   type_name;
  bool                          var_src;
  int                           num_out;
  amba_cnn_ext_c_node_init_t    init;
  amba_cnn_ext_c_node_expand_t  expand;
  amba_cnn_ext_c_node_release_t release;
} amba_cnn_ext_c_node_type_t;

typedef int (*amba_cnn_ext_c_dll_query_t)
  (int* num_types, const amba_cnn_ext_c_node_type_t** types);

typedef int (*amba_cnn_ext_c_extern_node_init_t)
  (int* cid, amba_cnn_c_vcoord_t* osz,
   amba_cnn_c_data_format_t* idf, amba_cnn_c_data_format_t* odf,
   int* data_mode,
   int num_src, const amba_cnn_c_vcoord_t* isz, const char* attr,
   const void* reserved);

typedef int (*amba_cnn_ext_c_extern_node_iter_init_t)
  (int cid, amba_cnn_c_vcoord_t* osz, const amba_cnn_c_vcoord_t* isz,
   int o_batch_size, const int* i_batch_size);

typedef int (*amba_cnn_ext_c_extern_node_fwd_t)
  (int cid, void* const* dest_data, const void* const* src_data);

typedef int (*amba_cnn_ext_c_extern_node_bwd_t)
  (int cid, void* const* dloss_dsrc, const void* const* dloss_ddest);

typedef int (*amba_cnn_ext_c_extern_node_release_t)(int cid);

typedef struct amba_cnn_ext_c_extern_node_type_s {
  const char*                            type_name;
  const char*                            device;
  int                                    num_out;
  amba_cnn_ext_c_extern_node_init_t      init;
  amba_cnn_ext_c_extern_node_iter_init_t iter_init;
  amba_cnn_ext_c_extern_node_fwd_t       forward;
  amba_cnn_ext_c_extern_node_fwd_t       quantized_forward;
  amba_cnn_ext_c_extern_node_bwd_t       backward;
  amba_cnn_ext_c_extern_node_release_t   release;
} amba_cnn_ext_c_extern_node_type_t;

typedef int (*amba_cnn_ext_c_dll_extern_node_query_t)
  (int* num_types, const amba_cnn_ext_c_extern_node_type_t** types);

#ifdef __cplusplus
}
#endif


#endif
