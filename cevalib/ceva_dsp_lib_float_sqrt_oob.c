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


#include  <math.h>
#include <ceva_typedef.h>

/***
auto-doc:

.. c:function::  uint16 CEVA_DSP_LIB_SQRT_INT32_OOB(uint32 x, uint32 rnd_flag)

    :param uint32 x: [i] value whose square root is calculated.  Data interpreted as a unsigned 32 bit integer
    :param uint32 rnd_flag: [i] flag to indicate if rounding is to be used.
    :return: calculated square root
    :rtype: uint16 (interpreted as unsigned 16 bit integer)

*Restrictions*

=========================== =======================================  ========================================
Arguments                   Restriction                              Size in Bytes
=========================== =======================================  ========================================
x                           >0
=========================== =======================================  ========================================
***/

#if 0
float CEVA_DSP_LIB_FLOAT_ISQRT_OOB(float arg_in);

float CEVA_DSP_LIB_FLOAT_SQRT_OOB(float arg_in)
{
	float y;

	y = CEVA_DSP_LIB_FLOAT_ISQRT_OOB(arg_in);
	y = y * arg_in;

	return y;

}
#else


#define multiply_scale(x, y, s) (((int64)(x)*(y))>>(s))

extern const uint16 approxRecipSqrt_1k0s[16];
extern const uint16 approxRecipSqrt_1k1s[16];

uint32 approxRecipSqrt32_1(unsigned int oddExpA, uint32 a)
{
	int index;
	uint16 eps, r0;
	uint32 ESqrR0;
	uint32 sigma0;
	uint32 r;
	uint32 sqrSigma0;

	index = (a >> 19 & 0xE) + oddExpA;
	eps = (uint16)(a >> 4);
	// initial approximation
	r0 = approxRecipSqrt_1k0s[index] - ((approxRecipSqrt_1k1s[index] * (uint32)eps) >> 20);
	ESqrR0 = (uint32)r0 * r0;
	if (!oddExpA)
		ESqrR0 <<= 1;

	// NR iteration
	sigma0 = ~(uint32)(multiply_scale(ESqrR0, a, 15));
	r = ((uint32)r0 << 16) + (multiply_scale(r0, sigma0, 25));
	sqrSigma0 = multiply_scale(sigma0, sigma0, 32);
	r += ((uint32)((r >> 1) + (r >> 3) - ((uint32)r0 << 14)) * (long long)sqrSigma0) >> 48;
	return r;

}

float_32 CEVA_DSP_LIB_FLOAT_SQRT_OOB(float_32 a)
{
	uint32 a32, res32, mantA, mantZ;
	int expA, expZ;
	float_32 res;

	a32 = *((uint32*)(&a));  // treat float as long

	if (a32 == 0)
		return 0;

	expA = (a32 >> 23) & 0xff;
	mantA = a32 & 0x007FFFFF;

	expZ = (expA + 0x7D) >> 1;
	expA &= 1;
	mantA = (mantA | 0x00800000) ;
	mantZ = multiply_scale(mantA, approxRecipSqrt32_1(expA, mantA), 31);
	if (expA)
		mantZ >>= 1;

	// convert back to float
	res32 = (expZ << 23) + mantZ; //sign is 0
	res = *((float_32*)(&res32)); // treat long as float
	return res;
}

#endif
