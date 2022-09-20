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



#include "ceva_typedef.h"

//void CEVA_DSP_LIB_FLOAT_FFT_CX_BITREV_OOB(
//	float_32 *buf2,					// [o] out_buf
//	float_32 *buf1,					// [i] in_buf
//	int32 log2_buf_len,				// [i] The log2 value of the FFT size, the FFT size, *N*, is (1<<log2_buf_len)
//	int16 const *bitrev_tbl			// [i] pointer to auxiliary buffer for resort (bit-reverse order).
//)
//{
//	int32 i;
//	int32 jump_in_table = CEVA_FFT_LIB_MAX_FFT >> log2_buf_len;
//	int32 fft_size = 1 << log2_buf_len;
//	float_32 *buf1_mid = buf1 + fft_size;
//	for (i = 0; i<fft_size / (2 * 4); i++)
//	{
//		int32 j0 = bitrev_tbl[i*jump_in_table];
//
//		buf2[j0 / 4 + 0] = buf1[8 * i];
//		buf2[j0 / 4 + 1] = buf1[8 * i + 1];
//		buf2[j0 / 4 + 2] = buf1_mid[8 * i];
//		buf2[j0 / 4 + 3] = buf1_mid[8 * i + 1];
//
//		buf2[j0 / 4 + 0 + 2 * fft_size / 2] = buf1[8 * i + 2];
//		buf2[j0 / 4 + 1 + 2 * fft_size / 2] = buf1[8 * i + 3];
//		buf2[j0 / 4 + 2 + 2 * fft_size / 2] = buf1_mid[8 * i + 2];
//		buf2[j0 / 4 + 3 + 2 * fft_size / 2] = buf1_mid[8 * i + 3];
//
//		buf2[j0 / 4 + 0 + 1 * fft_size / 2] = buf1[8 * i + 4];
//		buf2[j0 / 4 + 1 + 1 * fft_size / 2] = buf1[8 * i + 5];
//		buf2[j0 / 4 + 2 + 1 * fft_size / 2] = buf1_mid[8 * i + 4];
//		buf2[j0 / 4 + 3 + 1 * fft_size / 2] = buf1_mid[8 * i + 5];
//
//		buf2[j0 / 4 + 0 + 3 * fft_size / 2] = buf1[8 * i + 6];
//		buf2[j0 / 4 + 1 + 3 * fft_size / 2] = buf1[8 * i + 7];
//		buf2[j0 / 4 + 2 + 3 * fft_size / 2] = buf1_mid[8 * i + 6];
//		buf2[j0 / 4 + 3 + 3 * fft_size / 2] = buf1_mid[8 * i + 7];
//	}
//
//}

void CEVA_FFT_LIB_BITREV_INT32(int32 data[], int32 data_out[], int32 nLog2np, int32 tmpbuf[])
{
    int32 np = (1<<nLog2np);
    int32 *px = data;
    int32 *pxk, *pxi;
    int32 *px_out = data_out;
    int32 *pxk_out, *pxi_out;
    int32 i, j, k;
        int32 n21, nn2;
        int32 tmp;

        nn2 = np / 2;
        n21 = np + 1;
        j = 0;
        for (i = 0; i < np; i += 4) {

            if (i <= j) {
                // swap 4 pairs of values (2 complex pairs with 2 others)
                pxi = &px[i];
                pxk = &px[j];
                pxi_out = &px_out[i];
                pxk_out = &px_out[j];

                tmp = *pxi++;
                *pxi_out++ = *pxk++;
                *pxk_out++ = tmp;



                tmp = *pxi;
                *pxi_out = *pxk;
                *pxk_out = tmp;

                pxi  += n21;
                pxk  += n21;
                pxi_out  += n21;
                pxk_out  += n21;

                tmp = *pxi++;
                *pxi_out++ = *pxk++;
                *pxk_out++ = tmp;

                tmp = *pxi;
                *pxi_out = *pxk;
                *pxk_out = tmp;
            }

            // swap 2 pairs of values (1 complex pair with another)
            pxi = &px[i+2];
            pxk = &px[j+np];
            pxi_out = &px_out[i+2];
            pxk_out = &px_out[j+np];

            tmp = *pxi++;
            *pxi_out++ = *pxk++;
            *pxk_out++ = tmp;

            tmp = *pxi;
            *pxi_out = *pxk;
            *pxk_out = tmp;

            k = nn2;
            while (k <= j) {
                j -= k;
                k = k / 2;
            }
            j += k;
        }
}
