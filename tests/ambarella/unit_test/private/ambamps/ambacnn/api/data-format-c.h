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

#ifndef DATA_FORMAT_C_H
#define DATA_FORMAT_C_H

#ifdef __cplusplus
extern "C" {
#endif

#define AMBA_CNN_DF_UNDEF_SIGN             (1U << 0)
#define AMBA_CNN_DF_UNDEF_DATASIZE         (1U << 1)
#define AMBA_CNN_DF_UNDEF_EXPOFF           (1U << 2)
#define AMBA_CNN_DF_UNDEF_EXPBITS          (1U << 3)
#define AMBA_CNN_DF_UNDEF_BITVECTOR        (1U << 4)
#define AMBA_CNN_DF_UNDEF_DISABLE_RESERVED (1U << 5)
#define AMBA_CNN_DF_UNDEF_IEEE_COMPATIBLE  (1U << 6)
#define AMBA_CNN_DF_UNDEF_ALL       (AMBA_CNN_DF_UNDEF_SIGN     | \
                                     AMBA_CNN_DF_UNDEF_DATASIZE | \
                                     AMBA_CNN_DF_UNDEF_EXPOFF   | \
                                     AMBA_CNN_DF_UNDEF_EXPBITS  | \
                                     AMBA_CNN_DF_UNDEF_BITVECTOR)

#define AMBA_CNN_DF_UNDEF_ALL_EX    (AMBA_CNN_DF_UNDEF_ALL | \
                                     AMBA_CNN_DF_UNDEF_DISABLE_RESERVED | \
                                     AMBA_CNN_DF_UNDEF_IEEE_COMPATIBLE)

typedef struct amba_cnn_c_data_format_s {
  int undef;
  int sign;
  int datasize;
  int expoff;
  int expbits;
  int bitvector;
} amba_cnn_c_data_format_t;

typedef struct amba_cnn_c_data_format_ex_s {
  int undef;
  int sign;
  int bits;
  int expoff;
  int expbits;
  int disable_reserved;
  int ieee_compatible;
} amba_cnn_c_data_format_ex_t;

#ifdef __cplusplus
}
#endif

#endif

