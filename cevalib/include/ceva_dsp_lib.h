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

#ifndef _CEVA_DSP_LIB_H
#define _CEVA_DSP_LIB_H

#include "ceva_typedef.h"
//#include "prefix-compatibility.h"
#ifdef WIN32
#define __attribute__(x)
#endif

void CEVA_DSP_LIB_VEC_ADD16(int16 *a, int16 *b, uint32 N, int16 *c);
void CEVA_DSP_LIB_VEC_ADD32(int32 *a, int32 *b, uint32 N, int32 *c);

void CEVA_DSP_LIB_VEC_SUB16(int16 *a, int16 *b, uint32 N, int16 *c);
void CEVA_DSP_LIB_VEC_SUB32(int32 *a, int32 *b, uint32 N, int32 *c);

void CEVA_DSP_LIB_VEC_NEG16(int16 *a, uint32 N, int16 *c);
void CEVA_DSP_LIB_VEC_NEG32(int32 *a, uint32 N, int32 *c);

int16 CEVA_DSP_LIB_VEC_MAX_ABS16(int16 *a, uint32 N);
int32 CEVA_DSP_LIB_VEC_MAX_ABS32(int32 *a, uint32 N);

int16 CEVA_DSP_LIB_VEC_MAX_ABS16_WITH_INDEX(uint32 *ind, int16 *buf, uint32 size_buf, uint32 first_index);
int32 CEVA_DSP_LIB_VEC_MAX_ABS32_WITH_INDEX(uint32 *ind, int32 *buf, uint32 size_buf, uint32 first_index);


int16 CEVA_DSP_LIB_VEC_MAX16(int16 *buf, uint32 size_buf);
int16 CEVA_DSP_LIB_VEC_MAX16_WITH_INDEX(uint32 *ind, int16 *buf, uint32 size_buf, uint32 first_index);

int32 CEVA_DSP_LIB_VEC_MAX32(int32 *buf, uint32 size_buf);
int32 CEVA_DSP_LIB_VEC_MAX32_WITH_INDEX(uint32 *ind, int32 *buf, uint32 size_buf, uint32 first_index);

int16 CEVA_DSP_LIB_VEC_MIN16(int16 *buf, uint32 size_buf);
int16 CEVA_DSP_LIB_VEC_MIN16_WITH_INDEX(uint32 *ind, int16 *buf, uint32 size_buf, uint32 first_index);

int32 CEVA_DSP_LIB_VEC_MIN32(int32 *buf, uint32 size_buf);
int32 CEVA_DSP_LIB_VEC_MIN32_WITH_INDEX(uint32 *ind, int32 *buf, uint32 size_buf, uint32 first_index);

void CEVA_DSP_LIB_VEC_MUL_Q15(int16 *a, int16 *b, uint32 N, int16 *c);
void CEVA_DSP_LIB_VEC_MUL_Q31(int32 *a, int32 *b, uint32 N, int32 *c);

int32 CEVA_DSP_LIB_VEC_DOT_Q15(int16 *a, int16 *b, uint32 N);
int32 CEVA_DSP_LIB_VEC_DOT_Q31(int32 *a, int32 *b, uint32 N);
int32 CEVA_DSP_LIB_VEC_DOT_Q15X7(int16 *a, int8 *b, uint32 N);
int32 CEVA_DSP_LIB_VEC_DOT_Q31X15(int32 *a, int16 *b, uint32 N);
cint32 CEVA_DSP_LIB_VEC_CX_DOT_Q15(cint16 *a, cint16 *b, uint32 N);
cint32 CEVA_DSP_LIB_VEC_CX_DOT_Q31(cint32 *a, cint32 *b, uint32 N);

void CEVA_DSP_LIB_VEC_SHF16(int16 *inp, int32 shift_val, uint32 size_buf, int16 *out);
void CEVA_DSP_LIB_VEC_SHF16_NO_SAT(int16 *inp, int32 shift_val, uint32 size_buf, int16 *out);

void CEVA_DSP_LIB_VEC_SHF32(int32 *inp, int32 shift_val, uint32 size_buf, int32 *out);
void CEVA_DSP_LIB_VEC_SHF32_NO_SAT(int32 *inp, int32 shift_val, uint32 size_buf, int32 *out);

void CEVA_DSP_LIB_FIR_Q15(int16 *x, int16 *b,  int16 *state, int16 *y, uint32 N, uint32 Nc);
void CEVA_DSP_LIB_FIR_Q31(int32 *x, int32 *b,  int32 *state, int32 *y, uint32 N, uint32 Nc);

void CEVA_DSP_LIB_FIR_SCX_Q15(cint16 *x, int16 *b,  cint16 *state, cint16 *y, uint32 N, uint32 Nc);
void CEVA_DSP_LIB_FIR_SCX_Q31(cint32 *x, int32 *b,  cint32 *state, cint32 *y, uint32 N, uint32 Nc);

void CEVA_DSP_LIB_FIR_CX_Q15(cint16 *x, cint16 *b,  cint16 *state, cint16 *y, uint32 N, uint32 Nc);
void CEVA_DSP_LIB_FIR_CX_Q31(cint32 *X, cint32 *B,  cint32 *state, cint32 *Y, uint32 N, uint32 Nc);

void CEVA_DSP_LIB_FIR_DLMS32(int32 adaptRate, int16 T, int16 shift_val, int32 input, int32 *StateAddr, int32 *CoefAddr, int32 *output, int32 *error, int32 desired);
void CEVA_DSP_LIB_FIR_DLMS16(int16 adaptRate, int16 T, int16 input, int16 desired, int16 *StateAddr, int16 *CoefAddr, int16 *output, int16 *error);
void CEVA_DSP_LIB_FIR_BLMS16(int16 nInputs, int16 adaptRate, int16 T, int16 *input, int16 *desired, int16 *StateAddr, int16 *CoefAddr, int16 *output, int16 *error);
void CEVA_DSP_LIB_FIR_BLMS32(int16 nInputs, int32 adaptRate, int16 T, int16 shift_val, int32 *input, int32 *desired, int32 *StateAddr, int32 *CoefAddr, int32 *output, int32 *error);
void CEVA_DSP_LIB_FIR_BLMS16(int16 nInputs, int16 adaptRate, int16 T, int16 *input, int16 *desired, int16 *StateAddr, int16 *CoefAddr, int16 *output, int16 *error);
void CEVA_DSP_LIB_FIR_ACORR32(int32 *input, int32 *output, int32 input_length, int32 output_length, int16 shift_m);
void CEVA_DSP_LIB_FIR_ACORR16(int16 *input, int16 *output, int16 input_length, int16 output_length);

void CEVA_DSP_LIB_FIR_XCORR32(int32 *x, int32 *h, int32 *y, int32 size_buf, int32 size_buf_coef, int32 shift_val);
void CEVA_DSP_LIB_FIR_XCORR16(int32 size_buf_coef, int16 *h, int16 *y, int32 size_buf, int16 *x);

void CEVA_DSP_LIB_FIR_SR16(int32 size_table, int32 buf_len, int16 const *in_buf, int16 *out_buf, int16 const *coeff);
void CEVA_DSP_LIB_FIR_SR32(int32 size_table, int32 buf_len, int32 const *in_buf, int32 *out_buf, int32 const *coeff, int32 shift_val);
int16 CEVA_DSP_LIB_FIR_SS16(int32 size_table, int16 sample, int16 *state, int16 const *coeff);
int32 CEVA_DSP_LIB_FIR_SS32(int32 size_table, int32 sample, int32 *state, int32 const *coeff, int32 shift_val);
void CEVA_DSP_LIB_FIR_CONVOL16(int32 Vec_size, int32 N_Coeffs, int16 *State_buf, int16 *filter_coeffs_table, int16 *out_buffer, int16 *in_buffer);
void CEVA_DSP_LIB_FIR_CONVOL32(int32 *in_buffer, int32 *out_buffer, int32 *State_buf, int32 *filter_coeffs_table, int32 Vec_size, int32 N_Coeffs, int32 shift_val);


void CEVA_DSP_LIB_FIR_INTERP16(int16 D, int16 N, int16 T, int16 T_D_ratio, int16 *in_buffer, int16 *out_buffer, int16 *State_buf, int16 *filter_coeffs_table);
void CEVA_DSP_LIB_FIR_INTERP32(int16 D, int16 N, int16 T, int16 T_D_ratio, int16 shift_val, int32 *in_buffer, int32 *out_buffer, int32 *State_buf, int32 *filter_coeffs_table);


void CEVA_DSP_LIB_FIR_DEC32(int32 *in_buffer, int32 *out_buffer, int32 *State_buf, int32 *filter_coeffs_table, int32 dec_val, int32 Vec_size, int32 N_Coeffs, int32 shift_val);
void CEVA_DSP_LIB_FIR_DEC16(int16 *in_buffer, int16 *out_buffer, int16 *State_buf, int16 *filter_coeffs_table, int32	dec_val, int32 Vec_size, int32 N_Coeffs);
		
void CEVA_DSP_LIB_IIR_BQC32(int32 buf_len, int32 shift_val, int32 *x, int32 *y, int32 *a_b, int32 *x_scr, int32 *y_scr);
void CEVA_DSP_LIB_IIR_BQD32(int32 buf_len, int32 shift_val, int32 *x, int32 *y, int32 *a_b, int32 *x_scr, int32 *y_scr);
		
int16 CEVA_DSP_LIB_ATAN_INT16(int16 arg);
int32 CEVA_DSP_LIB_ATAN_INT32(int32 arg);

int16 CEVA_DSP_LIB_TAN_INT16(int16 arg);
int32 CEVA_DSP_LIB_TAN_INT32(int32 arg);

int16 CEVA_DSP_LIB_COS_INT16(int16 arg);
int32 CEVA_DSP_LIB_COS_INT32(int32 arg);

int16 CEVA_DSP_LIB_SIN_INT16(int16 arg);
int32 CEVA_DSP_LIB_SIN_INT32(int32 arg);

int16  CEVA_DSP_LIB_ATAN2_INT16(int16 Y, int16 X);
int32  CEVA_DSP_LIB_ATAN2_INT32(int32 Y, int32 X);

void  CEVA_DSP_LIB_COSSIN_Q15(int16* p_inp, int16* p_cossin, int N);

void CEVA_DSP_LIB_BLOCKCOPY(int8 *src, int8 *dst, int32 size);
void CEVA_DSP_LIB_BYTESWAP(int16 *src, int16 *dst, int32 size);
int32 CEVA_DSP_LIB_SIGMOID(int32 x);
int16 CEVA_DSP_LIB_DIV_INTEGER_INT16(int16 x, int16 y);
int32 CEVA_DSP_LIB_DIV_INTEGER_INT32(int32 x, int32 y);
int16 CEVA_DSP_LIB_DIV16_SS(int16 var1, int16 var2);
int32 CEVA_DSP_LIB_DIV32_SS(int32 var1, int32 var2);
int32 CEVA_DSP_LIB_DIV32_SHIFTED_INT32(int32 var1, int32 var2, int32 shift_val);

uint16 CEVA_DSP_LIB_SQRT_INT16 (uint16 operand_be1, uint32 rnd_flag);
uint16 CEVA_DSP_LIB_SQRT_INT32 (uint32 operand_be1, uint32 rnd_flag);

int16 CEVA_DSP_LIB_ISQRT16(int16 arg_in);
int32 CEVA_DSP_LIB_ISQRT32(int32 arg_in);

int32 CEVA_DSP_LIB_LOG10_INT32(int32 arg_in, int16 arg_exp_in, int16 *arg_exp_out);
int32 CEVA_DSP_LIB_LOG2_INT32(int32 arg_in, int16 arg_exp_in, int16 *arg_exp_out);
int32 CEVA_DSP_LIB_LOGN_INT32(int32 arg_in, int16 arg_exp_in, int16 *arg_exp_out);

int32 CEVA_DSP_LIB_POW2_INT32(int32 arg_in, int16 arg_exp_in, int16 *arg_exp_out);
int32 CEVA_DSP_LIB_POW10_INT32(int32 arg_in, int16 arg_exp_in, int16 *arg_exp_out);
int32 CEVA_DSP_LIB_POW_INT32(int32 arg_in_X, int16 arg_exp_in_X, int32 arg_in_Y, int16 arg_exp_in_Y, int16 *arg_exp_out);


void CEVA_DSP_LIB_VEC_ABS16(int16 *a, uint32 N, int16 *c);
void CEVA_DSP_LIB_VEC_ABS32(int32 *a, uint32 N, int32 *c);
// MARCO to generate linear matrix address for Row Major form
#define MAT_INDEX(R,C,Ncol)          ((C) + (R)*(Ncol))
#define HERMITIAN_UP_INDEX(R,C,Ncol) ((C)+((Ncol)-1)*(R) - ((R)*((R)-1)>>1))

void CEVA_DSP_LIB_MAT_CX_TRANS_Q15(cint16 *A, uint32 M, uint32 N, cint16 *C);
void CEVA_DSP_LIB_MAT_CX_TRANS_Q31(cint32 *A, uint32 M, uint32 N, cint32 *C);

void CEVA_DSP_LIB_MAT_CX_ADD16(cint16 *A, cint16 *B, uint32 Nrow, uint32 Ncol, cint16 *C);
void CEVA_DSP_LIB_MAT_CX_ADD32(cint32 *A, cint32 *B, uint32 Nrow, uint32 Ncol, cint32 *C);

void CEVA_DSP_LIB_MAT_CX_SUB16(cint16 *A, cint16 *B, uint32 Nrow, uint32 Ncol, cint16 *C);
void CEVA_DSP_LIB_MAT_CX_SUB32(cint32 *A, cint32 *B, uint32 Nrow, uint32 Ncol, cint32 *C);

void CEVA_DSP_LIB_MAT_CX_MUL_Q15(cint16 *A, cint16 *B, uint32 N, uint32 M, uint32 L, cint16 *C);
void CEVA_DSP_LIB_MAT_CX_MUL_Q31(cint32 *A, cint32 *B, uint32 N, uint32 M, uint32 L, cint32 *C);

void CEVA_DSP_LIB_MAT_CX_CONJ_MUL_Q15(cint16 *A, cint16 *B, uint32 N, uint32 M, uint32 L, cint16 *C);
void CEVA_DSP_LIB_MAT_CX_CONJ_MUL_Q31(cint32 *A, cint32 *B, uint32 N, uint32 M, uint32 L, cint32 *C);

void CEVA_DSP_LIB_MAT_CX_MUL_CONJ_Q15(cint16 *A, cint16 *B, uint32 N, uint32 M, uint32 L, cint16 *C);
void CEVA_DSP_LIB_MAT_CX_MUL_CONJ_Q31(cint32 *A, cint32 *B, uint32 N, uint32 M, uint32 L, cint32 *C);

void CEVA_DSP_LIB_MAT_CX_MUL_TRANS_Q15(cint16 *A, uint32 Nrow, uint32 Ncol, cint16 *C);
void CEVA_DSP_LIB_MAT_CX_MUL_TRANS_Q31(cint32 *A, uint32 Nrow, uint32 Ncol, cint32 *C);

void CEVA_DSP_LIB_MAT_CX_TRANS_MUL_Q15(cint16 *A, uint32 Nrow, uint32 Ncol, cint16 *C);
void CEVA_DSP_LIB_MAT_CX_TRANS_MUL_Q31(cint32 *A, uint32 Nrow, uint32 Ncol, cint32 *C);

void CEVA_DSP_LIB_INTPOL_Q15(int16 *X, int16 *Y, uint32 N, int16 a, int16 b, int16 *Z);
void CEVA_DSP_LIB_INTPOL_Q31(int32 *X, int32 *Y, uint32 N, int32 a, int32 b, int32 *Z);

void CEVA_DSP_LIB_INTPOL_SCX_Q15(cint16 *X, cint16 *Y, uint32 N, int16 a, int16 b, cint16 *Z);
void CEVA_DSP_LIB_INTPOL_SCX_Q31(cint32 *X, cint32 *Y, uint32 N, int32 a, int32 b, cint32 *Z);
float_32 CEVA_DSP_LIB_FLOAT_LOG10(float_32 inp);
float_32 CEVA_DSP_LIB_FLOAT_LOG2(float_32 inp);
float_32 CEVA_DSP_LIB_FLOAT_LOGN(float_32 inp);

float_32 CEVA_DSP_LIB_FLOAT_POW2(float_32 arg);
float_32 CEVA_DSP_LIB_FLOAT_POW10(float_32 arg);

float_32 CEVA_DSP_LIB_FLOAT_ATAN(float_32 arg);
float_32 CEVA_DSP_LIB_FLOAT_TAN(float_32 arg);

float_32 CEVA_DSP_LIB_FLOAT_COS(float_32 arg);
float_32 CEVA_DSP_LIB_FLOAT_SIN(float_32 arg);

void CEVA_DSP_LIB_FLOAT_FIR_ACORR(float_32 *input, float_32 *output, int32 input_length, int32 output_length);
void CEVA_DSP_LIB_FLOAT_FIR_XCORR_OOB(float_32 *x, float_32 *h, float_32 *y, int32 size_buf, int32 size_buf_coef);
void CEVA_DSP_LIB_FLOAT_FIR_CONVOL_OOB(float_32 *in_buffer, float_32 *out_buffer, float_32 *State_buf, float_32 *filter_coeffs_table, int32 Vec_size, int32 N_Coeffs);
float_32 CEVA_DSP_LIB_FLOAT_FIR_SS(int32 size_table, float_32 sample, float_32 *state, float_32 const *coeff);
void CEVA_DSP_LIB_FLOAT_FIR_INTERP(int16 D, int16 N, int16 T, float_32 *in_buffer, float_32 *out_buffer, float_32 *State_buf, float_32 *filter_coeffs_table);
void CEVA_DSP_LIB_FLOAT_FIR_CX(cfloat *X, cfloat *B, cfloat *S, cfloat *Y, uint32 N, uint32 Nc);


#endif // _CEVA_DSP_LIB_H
