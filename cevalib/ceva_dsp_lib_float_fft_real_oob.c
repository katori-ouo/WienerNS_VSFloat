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
//#ifndef WIN32
//#include <vec-c.h>
//#include <asm-dsp.h>
//#endif
#include "ceva_typedef.h"
#include "ceva_fft_lib.h"

void CEVA_DSP_LIB_FLOAT_FFT_REAL_OOB_LAST_STAGE_PART1_OOB(int32 fftn,
	float_32 *ptr_in_0,
	float_32 *ptr_in_1,
	float_32 *ptr_out_0,
	float_32 *ptr_out_1)
{
    int i;
	float_32 ar, ai, br, bi,  re1, re2, im1, im2;

    for(i = 1; i < fftn / 4; i++)
    {
        ar = *ptr_in_0++;
        ai = *ptr_in_0++;
        bi = *ptr_in_1--;
        br = *ptr_in_1--;

        re1 = (ar + br)*0.5 ;
        im1 = (ai - bi)*0.5;

        re2 = bi + ai;
        im2 = br - ar;

        *ptr_out_0++ = im1;
        *ptr_out_0++ = re1;
        *ptr_out_1-- = im2;
        *ptr_out_1-- = re2;
    }
}

void CEVA_DSP_LIB_FLOAT_FFT_REAL_OOB_LAST_STAGE_PART2_OOB(int32 fftn,
	float_32 *ptr_in_0,
	float_32 *ptr_in_1,
	float_32 *ptr_out_0,
	float_32 *ptr_out_1,
                                 const float_32 *ptr_cos_sin)
{
    int i;
	float_32 ar, ai, br, bi,  cr, ci,  rtemp, itemp;

    for(i = 1; i < fftn / 4; i++)
    {
        ai = *ptr_in_0++;
        ar = *ptr_in_0++;
        bi = *ptr_in_1--;
        br = *ptr_in_1--;

        cr = *ptr_cos_sin++;
        ci = *ptr_cos_sin++;

        rtemp = (br * cr) + (bi * ci);
        itemp = (bi * cr) - (br * ci);

        *ptr_out_0++ =  ar + rtemp;
        *ptr_out_0++ =  ai + itemp;
		//*ptr_out_1-- = -(ai - itemp);
		*ptr_out_1-- = itemp  - ai;
		*ptr_out_1-- =  ar - rtemp;
    }
}



/***
auto-doc:

.. c:function::  void CEVA_FFT_LIB_INT32_FFT_OOB(int32 log2_buf_len, int32 *in_buf, int32 *out_buf, int32 const *twi_table, int32 const *last_stage_twi_table, int16 *bitrev_tbl, int32 *temp_buf, int32 br)

    :param int32 log2_buf_len: [i] The log2 value of the FFT size, the FFT size, *N*, is (1<<log2_buf_len)
    :param int32 \*in_buf: [i] ptr to input vector, contains *N* real elements.  The elements in this vector are interpreted as Q31 data.
    :param int32 \*out_buf: [o] ptr to output vector, contains *N/2* complex elements.  The elements in this vector are interpreted as Complex Q31 data.
    :param int32 const \*twi_table: [i] pointer to phase factor table, set the define array *CEVA_FFT_LIB_cos_sin_fft_32*.  Only the first (1<<log2_buf_len) locations of this table are used for FFT size (1<<log2_buf_len).
    :param int32 const \*last_stage_twi_table: [i] pointer to second twi phase factor table, set to one of the following defined arrays (depending on FFT size) : *twi_table_32_rfft_32*, *twi_table_32_rfft_64*, *twi_table_32_rfft_128*, *twi_table_32_rfft_256*, *twi_table_32_rfft_512*, *twi_table_32_rfft_1024*
    :param int16 \*bitrev_tbl: [i] pointer to auxiliary buffer for resort (bit-reverse order), Contains *N* element. It is set the define array: *bitrev1024*.
    :param int32 \*temp_buf:  [o] ptr to temp buffer used by function
    :param int32 br:  [i] disable/enable bit-reverse for last stage in cx fft. As far as cx fft is called before real part, this parameter has no sense an should be set to 1.

*Restrictions*

=========================== =======================================  ========================================
Arguments                   Restriction                              Size in Bytes
=========================== =======================================  ========================================
log2_buf_len                Limited to 5,6,7,8,9,10
in_buf                                                               (1<<log2_buf_len)*sizeof(int32)
out_buf                                                              (1<<log2_buf_len)*sizeof(int32)
twi_table                                                            (1<<log2_buf_len)*sizeof(int32)
last_stage_twi_table                                                 (1<<log2_buf_len)*sizeof(int32)/2
bitrev_tbl                                                           (1<<log2_buf_len)*sizeof(int16)
temp_buf                                                             (1<<log2_buf_len)*sizeof(int32)
br                          1
=========================== =======================================  ========================================

***/


void CEVA_DSP_LIB_FLOAT_FFT_REAL_OOB(int32 log2_buf_len,
	float_32 *in_buf,
	float_32 *out_buf,
	float_32 const *twi_table,
	float_32 const *last_stage_twi_table,
    int16 const *bitrev_tbl,
	float_32 *temp_buf,
    int32 br)
{
    int32 fftn = 1 << log2_buf_len;
	float_32 ar, ai;
	float_32 const *ptr_cos_sin;
	float_32 *ptr_in_0, *ptr_in_1, *ptr_out_0, *ptr_out_1;


    // Do (log2_buf_len - 1) complex fft without bitrev
	CEVA_DSP_LIB_FLOAT_FFT_CX_OOB(log2_buf_len - 1, in_buf, out_buf, twi_table, bitrev_tbl, temp_buf, br);

    // Do the first part of the last stage
    ptr_in_0 = out_buf + 2;
    ptr_in_1 = out_buf + fftn - 1;
    ptr_out_0 = temp_buf + 2;
    ptr_out_1 = temp_buf + fftn - 1;

	CEVA_DSP_LIB_FLOAT_FFT_REAL_OOB_LAST_STAGE_PART1_OOB(fftn, ptr_in_0,   ptr_in_1, ptr_out_0, ptr_out_1);

    // Do the second part of the last stage
    ptr_out_0 = out_buf;
    ptr_out_1 = out_buf + fftn + 1;
    ptr_in_0 = temp_buf + 2;
    ptr_in_1 = temp_buf + fftn - 1;
    ptr_cos_sin = last_stage_twi_table + 2;

    ar = ptr_out_0[0];
    ai = ptr_out_0[1];
    *ptr_out_0++ = ar + ai;
    *ptr_out_0++ = 0;
    *ptr_out_1-- = 0;
    *ptr_out_1-- = ar - ai;

	CEVA_DSP_LIB_FLOAT_FFT_REAL_OOB_LAST_STAGE_PART2_OOB(fftn, ptr_in_0,   ptr_in_1, ptr_out_0, ptr_out_1, ptr_cos_sin);
    ptr_out_0 += 2*(fftn/4 - 1);

	ptr_out_0[1] = -ptr_out_0[1];

}

