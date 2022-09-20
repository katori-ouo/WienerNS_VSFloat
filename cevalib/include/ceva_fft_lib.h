/*************************************************************************************\
* Copyright (C) CEVA(R) Inc. All rights reserved                                      *
*                                                                                     *
* This information embodies materials and concepts, which are proprietary and         *
* confidential to CEVA Inc., and is made available solely pursuant to the terms       *
* of a written license agreement, or NDA, or another written agreement, as            *
* applicable ("CEVA Agreement"), with CEVA Inc. or any of its subsidiaries ("CEVA").  *
*                                                                                     *
* This information can be used only with the written permission from CEVA, in         *
* accordance with the terms and conditions stipulated in the CEVA Agreement, under    *
* which the information has been supplied and solely as expressly permitted for       *
* the purpose specified in the CEVA Agreement.                                        *
*                                                                                     *
* This information is made available exclusively to licensees or parties that have    *
* received express written authorization from CEVA to download or receive the         *
* information and have agreed to the terms and conditions of the CEVA Agreement.      *
*                                                                                     *
* IF YOU HAVE NOT RECEIVED SUCH EXPRESS AUTHORIZATION AND AGREED TO THE CEVA          *
* AGREEMENT, YOU MAY NOT DOWNLOAD, INSTALL OR USE THIS INFORMATION.                   *
*                                                                                     *
* The information contained in this document is subject to change without notice      *
* and does not represent a commitment on any part of CEVA. Unless specifically        *
* agreed otherwise in the CEVA Agreement, CEVA make no warranty of any kind with      *
* regard to this material, including, but not limited to implied warranties of        *
* merchantability and fitness for a particular purpose whether arising out of law,    *
* custom, conduct or otherwise.                                                       *
*                                                                                     *
* While the information contained herein is assumed to be accurate, CEVA assumes no   *
* responsibility for any errors or omissions contained herein, and assumes no         *
* liability for special, direct, indirect or consequential damage, losses, costs,     *
* charges, claims, demands, fees or expenses, of any nature or kind, which are        *
* incurred in connection with the furnishing, performance or use of this material.    *
*                                                                                     *
* This document contains proprietary information, which is protected by U.S. and      *
* international copyright laws. All rights reserved. No part of this document may     *
* be reproduced, photocopied, or translated into another language without the prior   *
* written consent of CEVA.                                                            *
\*************************************************************************************/

#ifndef _CEVA_FFT_LIB_H
#define _CEVA_FFT_LIB_H
#include "ceva_typedef.h"

//void CEVA_DSP_LIB_FLOAT_FFT_CX(
//	int32 log2_buf_len,
//	float_32 *in_buf,
//	float_32 *out_buf,
//	float_32 const *twi_table,
//	int16 const *bitrev_tbl,
//	float_32 *temp_buf,
//	int32 br);
//void CEVA_DSP_LIB_FLOAT_FFT_CX_INV(
//	int32 log2_buf_len,
//	float_32 *in_buf,
//	float_32 *out_buf,
//	float_32 const *twi_table,
//	int16 const *bitrev_tbl,
//	float_32 *temp_buf,
//	int32 br);
//
//void CEVA_DSP_LIB_FLOAT_FFT_REAL(
//	int32 log2_buf_len,
//	float_32 *in_buf,
//	float_32 *out_buf,
//	float_32 const *twi_table,
//	float_32 const *last_stage_twi_table,
//	int16 const *bitrev_tbl,
//	float_32 *temp_buf,
//	int32 br);
//void CEVA_DSP_LIB_FLOAT_FFT_REAL_INV(
//	int32 log2_buf_len,
//	float_32 *in_buf,
//	float_32 *out_buf,
//	float_32 const *twi_table,
//	float_32 const *last_stage_twi_table,
//	int16 const *bitrev_tbl,
//	float_32 *temp_buf,
//	int32 br);
//
//// ---------------------------
void CEVA_DSP_LIB_FLOAT_FFT_CX_OOB(
	int32 log2_buf_len,
	float_32 *in_buf,
	float_32 *out_buf,
	float_32 const *twi_table,
	int16 const *bitrev_tbl,
	float_32 *temp_buf,
	int32 br);

void CEVA_DSP_LIB_FLOAT_FFT_CX_INV_OOB(
	int32 log2_buf_len,
	float_32 *in_buf,
	float_32 *out_buf,
	float_32 const *twi_table,
	int16 const *bitrev_tbl,
	float_32 *temp_buf,
	int32 br);

void CEVA_DSP_LIB_FLOAT_FFT_REAL_OOB(
	int32 log2_buf_len,
	float_32 *in_buf,
	float_32 *out_buf,
	float_32 const *twi_table,
	float_32 const *last_stage_twi_table,
	int16 const *bitrev_tbl,
	float_32 *temp_buf,
	int32 br);

void CEVA_DSP_LIB_FLOAT_FFT_REAL_INV_OOB(
	int32 log2_buf_len,
	float_32 *in_buf,
	float_32 *out_buf,
	float_32 const *twi_table,
	float_32 const *last_stage_twi_table,
	int16 const *bitrev_tbl,
	float_32 *temp_buf,
	int32 br);

void CEVA_DSP_LIB_FLOAT_FFT_CX_BITREV_OOB(
	float_32 *buf2,					//out_buf
	float_32 *buf1,					//in_buf
	int32 log2_buf_len,
	int16 const *bitrev_tbl);

void CEVA_DSP_LIB_FLOAT_FFT_CX_BITREV_OOB(
	float_32 *buf2,					//out_buf
	float_32 *buf1,					//in_buf
	int32 log2_buf_len,
	int16 const *bitrev_tbl);

void CEVA_DSP_LIB_FLOAT_FFT_STAGE0_OOB(int32 fftn,
	float_32 *in_buf,
	float_32 *in_buf_2,
	float_32 *out_buf);

// ---------------------------
//void CEVA_FFT_LIB_CX32_FFT_OOB(int32 log2_buf_len,
//                           int32 *in_buf,
//                           int32 *out_buf,
//                           int32 const *twi_table,
//                           int16 const *bitrev_tbl,
//                           int32 *temp_buf,
//                           int32 br);
//void CEVA_FFT_LIB_CX32_FFT(int32 log2_buf_len,
//                           int32 *in_buf,
//                           int32 *out_buf,
//                           int32 const *twi_table,
//                           int16 const *bitrev_tbl,
//                           int32 *temp_buf,
//                           int32 br);
//
//// ---------------------------
//void CEVA_FFT_LIB_CX16_FFT_OOB(int32 log2_buf_len,
//                           int16 *in_buf16,
//                           int16 *out_buf,
//                           int16 const *twi_table,
//                           int16 const *bitrev_tbl,
//                           int16 *temp_buf,
//                           int8 *ScaleShift,
//                           int32 br);
//void CEVA_FFT_LIB_CX16_FFT(int32 log2_buf_len,
//                           int16 *in_buf16,
//                           int16 *out_buf,
//                           int16 const *twi_table,
//                           int16 const *bitrev_tbl,
//                           int16 *temp_buf,
//                           int8 *ScaleShift,
//                           int32 br);
//
//// ---------------------------
//void CEVA_FFT_LIB_CX16_IFFT_OOB(int32 log2_buf_len,
//                           int16 *in_buf16,
//                           int16 *out_buf,
//                           int16 const *twi_table,
//                           int16 const *bitrev_tbl,
//                           int16 *temp_buf,
//                           int8 *ScaleShift,
//                           int32 br);
//
//void CEVA_FFT_LIB_CX16_IFFT(int32 log2_buf_len,
//                           int16 *in_buf16,
//                           int16 *out_buf,
//                           int16 const *twi_table,
//                           int16 const *bitrev_tbl,
//                           int16 *temp_buf,
//                           int8 *ScaleShift,
//                           int32 br);
//
//void CEVA_FFT_LIB_CX32_IFFT_OOB(int32 log2_buf_len,
//                           int32 *in_buf,
//                           int32 *out_buf,
//                           int32 const *twi_table,
//                           int16 const *bitrev_tbl,
//                           int32 *temp_buf,
//                           int32 br);
//
//void CEVA_FFT_LIB_CX32_IFFT(int32 log2_buf_len,
//                           int32 *in_buf,
//                           int32 *out_buf,
//                           int32 const *twi_table,
//                           int16 const *bitrev_tbl,
//                           int32 *temp_buf,
//                           int32 br);
//
//
//
//void CEVA_FFT_LIB_INT32_FFT(int32 log2_buf_len,
//                              int32 *in_buf,
//                              int32 *out_buf,
//                              int32 const *twi_table,
//                              int32 const *last_stage_twi_table,
//                              int16 const *bitrev_tbl,
//                              int32 *temp_buf,
//                              int32 br);
//
//void CEVA_FFT_LIB_INT32_FFT_OOB(int32 log2_buf_len,
//                              int32 *in_buf,
//                              int32 *out_buf,
//                              int32 const *twi_table,
//                              int32 const *last_stage_twi_table,
//                              int16 const *bitrev_tbl,
//                              int32 *temp_buf,
//                              int32 br);
//
//// ---------------------------
//void CEVA_FFT_LIB_INT16_FFT_OOB(int32 log2_buf_len,
//                              int16 *in_buf16,
//                              int16 *out_buf,
//                              int16 const *twi_table,
//                              int16 const *last_stage_twi_table,
//                              int16 const *bitrev_tbl,
//                              int16 *temp_buf,
//                              int8 *ScaleShift,
//                              int32 br);
//
//void CEVA_FFT_LIB_INT16_FFT(int32 log2_buf_len,
//                              int16 *in_buf16,
//                              int16 *out_buf,
//                              int16 const *twi_table,
//                              int16 const *last_stage_twi_table,
//                              int16 const *bitrev_tbl,
//                              int16 *temp_buf,
//                              int8 *ScaleShift,
//                              int32 br);
//
//// ---------------------------
//void CEVA_FFT_LIB_INT16_IFFT_OOB(int32 log2_buf_len,
//                              int16 *in_buf16,
//                              int16 *out_buf,
//                              int16 const *twi_table,
//                              int16 const *last_stage_twi_table,
//                              int16 const *bitrev_tbl,
//                              int16 *temp_buf,
//                              int8 *ScaleShift,
//                              int32 bitrev);
//
//void CEVA_FFT_LIB_INT16_IFFT(int32 log2_buf_len,
//                              int16 *in_buf16,
//                              int16 *out_buf,
//                              int16 const *twi_table,
//                              int16 const *last_stage_twi_table,
//                              int16 const *bitrev_tbl,
//                              int16 *temp_buf,
//                              int8 *ScaleShift,
//                              int32 bitrev);
//
//void CEVA_FFT_LIB_INT32_IFFT(int32 log2_buf_len,
//                              int32 *in_buf,
//                              int32 *out_buf,
//                              int32 const *twi_table,
//                              int32 const *last_stage_twi_table,
//                              int16 const *bitrev_tbl,
//                              int32 *temp_buf,
//                              int32 bitrev);
//
//void CEVA_FFT_LIB_INT32_IFFT_OOB(int32 log2_buf_len,
//                              int32 *in_buf,
//                              int32 *out_buf,
//                              int32 const *twi_table,
//                              int32 const *last_stage_twi_table,
//                              int16 const *bitrev_tbl,
//                              int32 *temp_buf,
//                              int32 bitrev);
//void CEVA_FFT_LIB_BITREV_INT16(int16 data[], int16 data_out[], int32 nLog2np, int16 tmpbuf[]);

#ifdef MAX_FFT
#undef CEVA_FFT_LIB_MAX_FFT
#define CEVA_FFT_LIB_MAX_FFT MAX_FFT
#endif

#if !((CEVA_FFT_LIB_MAX_FFT==16) || (CEVA_FFT_LIB_MAX_FFT==32) || (CEVA_FFT_LIB_MAX_FFT==64) || (CEVA_FFT_LIB_MAX_FFT==128) || (CEVA_FFT_LIB_MAX_FFT==256) || (CEVA_FFT_LIB_MAX_FFT==512) || (CEVA_FFT_LIB_MAX_FFT==1024))
#error please add the definition of CEVA_FFT_LIB_MAX_FFT size in the project (supported values are: 16,32,64,128,256,512,1024)
#endif


extern const int16 CEVA_FFT_LIB_cos_sin_fft_16[];
extern const int32 CEVA_FFT_LIB_cos_sin_fft_32[];
extern const float CEVA_DSP_LIB_FLOAT_cos_sin[];

#if ((CEVA_FFT_LIB_MAX_FFT==32) || (CEVA_FFT_LIB_MAX_FFT==64) || (CEVA_FFT_LIB_MAX_FFT==128) || (CEVA_FFT_LIB_MAX_FFT==256) || (CEVA_FFT_LIB_MAX_FFT==512) || (CEVA_FFT_LIB_MAX_FFT==1024))
extern const int16 twi_table_16_rfft_32[];
#endif
#if ((CEVA_FFT_LIB_MAX_FFT==64) || (CEVA_FFT_LIB_MAX_FFT==128) || (CEVA_FFT_LIB_MAX_FFT==256) || (CEVA_FFT_LIB_MAX_FFT==512) || (CEVA_FFT_LIB_MAX_FFT==1024))
extern const int16 twi_table_16_rfft_64[];
#endif
#if ((CEVA_FFT_LIB_MAX_FFT==128) || (CEVA_FFT_LIB_MAX_FFT==256) || (CEVA_FFT_LIB_MAX_FFT==512) || (CEVA_FFT_LIB_MAX_FFT==1024))
extern const int16 twi_table_16_rfft_128[];
#endif
#if ((CEVA_FFT_LIB_MAX_FFT==256) || (CEVA_FFT_LIB_MAX_FFT==512) || (CEVA_FFT_LIB_MAX_FFT==1024))
extern const int16 twi_table_16_rfft_256[];
#endif
#if ((CEVA_FFT_LIB_MAX_FFT==512) || (CEVA_FFT_LIB_MAX_FFT==1024))
extern const int16 twi_table_16_rfft_512[];
#endif
#if ((CEVA_FFT_LIB_MAX_FFT==1024))
extern const int16 twi_table_16_rfft_1024[];
#endif


#if ((CEVA_FFT_LIB_MAX_FFT==32) || (CEVA_FFT_LIB_MAX_FFT==64) || (CEVA_FFT_LIB_MAX_FFT==128) || (CEVA_FFT_LIB_MAX_FFT==256) || (CEVA_FFT_LIB_MAX_FFT==512) || (CEVA_FFT_LIB_MAX_FFT==1024))
extern const float twi_table_float_rfft_32[];
#endif
#if ((CEVA_FFT_LIB_MAX_FFT==64) || (CEVA_FFT_LIB_MAX_FFT==128) || (CEVA_FFT_LIB_MAX_FFT==256) || (CEVA_FFT_LIB_MAX_FFT==512) || (CEVA_FFT_LIB_MAX_FFT==1024))
extern const float twi_table_float_rfft_64[];
#endif
#if ((CEVA_FFT_LIB_MAX_FFT==128) || (CEVA_FFT_LIB_MAX_FFT==256) || (CEVA_FFT_LIB_MAX_FFT==512) || (CEVA_FFT_LIB_MAX_FFT==1024))
extern const float twi_table_float_rfft_128[];
#endif
#if ((CEVA_FFT_LIB_MAX_FFT==256) || (CEVA_FFT_LIB_MAX_FFT==512) || (CEVA_FFT_LIB_MAX_FFT==1024))
extern const float twi_table_float_rfft_256[];
#endif
#if ((CEVA_FFT_LIB_MAX_FFT==512) || (CEVA_FFT_LIB_MAX_FFT==1024))
extern const float twi_table_float_rfft_512[];
#endif
#if ((CEVA_FFT_LIB_MAX_FFT==1024))
extern const float twi_table_float_rfft_1024[];
#endif

#if ((CEVA_FFT_LIB_MAX_FFT==32) || (CEVA_FFT_LIB_MAX_FFT==64) || (CEVA_FFT_LIB_MAX_FFT==128) || (CEVA_FFT_LIB_MAX_FFT==256) || (CEVA_FFT_LIB_MAX_FFT==512) || (CEVA_FFT_LIB_MAX_FFT==1024))
extern const int32 twi_table_32_rfft_32[];
#endif
#if ((CEVA_FFT_LIB_MAX_FFT==64) || (CEVA_FFT_LIB_MAX_FFT==128) || (CEVA_FFT_LIB_MAX_FFT==256) || (CEVA_FFT_LIB_MAX_FFT==512) || (CEVA_FFT_LIB_MAX_FFT==1024))
extern const int32 twi_table_32_rfft_64[];
#endif
#if ((CEVA_FFT_LIB_MAX_FFT==128) || (CEVA_FFT_LIB_MAX_FFT==256) || (CEVA_FFT_LIB_MAX_FFT==512) || (CEVA_FFT_LIB_MAX_FFT==1024))
extern const int32 twi_table_32_rfft_128[];
#endif
#if ((CEVA_FFT_LIB_MAX_FFT==256) || (CEVA_FFT_LIB_MAX_FFT==512) || (CEVA_FFT_LIB_MAX_FFT==1024))
extern const int32 twi_table_32_rfft_256[];
#endif
#if ((CEVA_FFT_LIB_MAX_FFT==512) || (CEVA_FFT_LIB_MAX_FFT==1024))
extern const int32 twi_table_32_rfft_512[];
#endif
#if ((CEVA_FFT_LIB_MAX_FFT==1024))
extern const int32 twi_table_32_rfft_1024[];
#endif

// bit reverse tables
extern const int16 bitrev_16_1024[];
extern const int16 bitrev_32_1024[];

extern const int16 bitrev1024[];

#endif // _CEVA_FFT_LIB_H
