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

#include <string.h>
#include "ceva_typedef.h"
#include "ceva_fft_lib.h"

//void CEVA_DSP_LIB_FLOAT_FFT_CX_BITREV_OOB(
//	float_32 *buf2,					//out_buf
//	float_32 *buf1,					//in_buf
//	int32 log2_buf_len,
//	int16 const *bitrev_tbl
//);

//void CEVA_DSP_LIB_FLOAT_FFT_STAGE0_OOB(
//	int32 fftn,
//    float_32 *in_buf,
//	float_32 *in_buf_2,
//	float_32 *out_buf)
//{
//    int i;
//	float_32 ar, ai, br, bi;
//
//    //tw is (1,0)
//
//    for (i = 0; i<fftn / 2; i++)
//    {
//
//        ar = in_buf[2 * i + 0];
//        ai = in_buf[2 * i + 1];
//        br = in_buf_2[2 * i + 0];
//        bi = in_buf_2[2 * i + 1];
//
//        out_buf[4 * i + 0] = ar + br;
//        out_buf[4 * i + 1] = ai + bi;
//        out_buf[4 * i + 2] = ar - br;
//        out_buf[4 * i + 3] = ai - bi;
//    }
//
//
//}

void CEVA_DSP_LIB_FLOAT_FFT_CX_INV_STAGEN_OOB(int32 fft_size,
	float_32 *in_buf,                // block0
	float_32* in_buf_2,
	float_32 *out_buf,               // block2
    int32 modu_fac,
	float_32 const *twi_table)       // block0
{
    int i;
    int j;
	float_32 ar, ai, br, bi, cr, ci;

    j = 0;

    for (i = 0; i<fft_size / 2; i++)
    {
		float_32 rtemp, itemp;

        cr = twi_table[2 * j+0];
        ci = twi_table[2 * j+1];
        ar = in_buf[2 * i+0];
        ai = in_buf[2 * i+1];
        br = in_buf_2[2 * i+0];
        bi = in_buf_2[2 * i+1];

        rtemp = (br * cr) + (bi * ci);
        itemp = (bi * cr) - (br * ci);

        out_buf[4 * i + 0] = ar + rtemp;
        out_buf[4 * i + 1] = ai + itemp;
        out_buf[4 * i + 2] = ar - rtemp;
        out_buf[4 * i + 3] = ai - itemp;


        //use the tw from prev
        //real(2) = imag(1)
        //imag(2) = -real(1)

        i++;

        ar = in_buf[2 * i + 0];
        ai = in_buf[2 * i + 1];
        br = in_buf_2[2 * i + 0];
        bi = in_buf_2[2 * i + 1];

        rtemp = (br * cr) + (bi * ci);
        itemp = (bi * cr) - (br * ci);

        out_buf[4 * i + 0] = ar - itemp; // r15 = r20 - r7*r24
        out_buf[4 * i + 1] = ai + rtemp; // r16 = r23 + r6*r24
        out_buf[4 * i + 2] = ar + itemp; // r14 = r20 + r7*r24
        out_buf[4 * i + 3] = ai - rtemp; // r17 = r23 - r6*r24


        j++;

		if (j == modu_fac)
		{
			j = 0;
		}

    }
}

/***
auto-doc:


.. c:function::  void CEVA_FFT_LIB_CX32_IFFT_OOB(int32 log2_buf_len, int32 *in_buf, int32 *out_buf, int32 const *twi_table, int16 *bitrev_tbl, int32 *temp_buf, int8 *ScaleShift, int32 br)

    :param int32 log2_buf_len: [i] The log2 value of the FFT size, the FFT size, *N*, is (1<<log2_buf_len)
    :param int32 \*in_buf: [i] ptr to input vector, contains *N* complex elements.  The elements in this vector are interpreted as Complex Q31 data.
    :param int32 \*out_buf: [o] ptr to output vector, contains *N* complex elements.  The elements in this vector are interpreted as Complex Q31 data.
    :param int32 const \*twi_table: [i] pointer to phase factor table, set the define array *CEVA_FFT_LIB_cos_sin_fft_32*.  Only the first (1<<log2_buf_len) locations of this table are used for FFT size (1<<log2_buf_len).
    :param int16 \*bitrev_tbl: [i] pointer to auxiliary buffer for resort (bit-reverse order).
    :param int32 \*temp_buf:  [o] ptr to temp buffer used by function
    :param int8 \*ScaleShift:  [i] ptr to Scale buffer used by function
    :param int32 \br:  [i] disable/enable bit-reverse for last stage

*Restrictions*

=========================== =======================================  ========================================
Arguments                   Restriction                              Size in Bytes
=========================== =======================================  ========================================
log2_buf_len                Limited to 4,5,6,7,8,9,10
in_buf                                                               (1<<log2_buf_len)*2*sizeof(int32)
out_buf                                                              (1<<log2_buf_len)*2*sizeof(int32)
twi_table                                                            (32*16+1)*sizeof(int32)
bitrev_tbl                                                           16*16*sizeof(int16)
temp_buf                                                             (1<<log2_buf_len)*2*sizeof(int32)
ScaleShift                                                           (log2_buf_len-2) bytes
br                                                                   4 bytes
=========================== =======================================  ========================================

***/
void CEVA_DSP_LIB_FLOAT_FFT_CX_INV_OOB(
	int32 log2_buf_len,
	float_32 *in_buf,                // block0
	float_32 *out_buf,               // block2
	float_32 const *twi_table,       // block0
    int16 const *bitrev_tbl,
	float_32 *temp_buf,
    int32 br
    )
{
    int32 i;
	float_32 *buf1, *buf2, *buf_t;
    int32 fft_size = 1 << log2_buf_len;
    int32 modu_fac = 1;
	float_32 *ptrTwiCycl = (float_32*)&twi_table[0];

    if (log2_buf_len & 1)
    {
        buf1 = temp_buf;
        buf2 = out_buf;
    }
    else
    {
        buf1 = out_buf;
        buf2 = temp_buf;
    }

    // first stage
	CEVA_DSP_LIB_FLOAT_FFT_STAGE0_OOB(fft_size, in_buf, in_buf + fft_size, buf1);

    for (i = 1; i<log2_buf_len; i++)
    {
		CEVA_DSP_LIB_FLOAT_FFT_CX_INV_STAGEN_OOB(fft_size, (float_32*)buf1, (float_32*)(buf1 + fft_size), (float_32*)buf2, modu_fac, ptrTwiCycl);
        modu_fac <<= 1;
        buf_t = buf1;
        buf1 = buf2;
        buf2 = buf_t;
    }

    //bitrev
    if (br)
    {
		CEVA_DSP_LIB_FLOAT_FFT_CX_BITREV_OOB(buf2, buf1, log2_buf_len, bitrev_tbl);
    }
    else
    {
        memcpy(buf2, buf1, 2*fft_size*sizeof(float_32));
    }
}



