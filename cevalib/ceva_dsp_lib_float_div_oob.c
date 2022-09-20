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

#ifndef WIN32
#include <basic_op.h>
#endif



/***
auto-doc:

.. c:function::  int32 CEVA_DSP_LIB_DIV32_SS_OOB(int32 var1, int32 var2)

    :param int32 var1: [i] value whose div is calculated.
    :param int32 var2: [i] value whose div is calculated.
    :return: calculated var1/var2 div value
    :rtype: int32

*Restrictions*

=========================== =======================================  ========================================
Arguments                   Restriction                              Size in Bytes
=========================== =======================================  ========================================

=========================== =======================================  ========================================


***/



// =============================================================================================
// =                         div approximation 	 = numerator / denominator                                              =
// =============================================================================================

#if 0
float_32 CEVA_DSP_LIB_FLOAT_ISQRT_OOB(float_32 arg_in);

float_32 CEVA_DSP_LIB_FLOAT_DIV_OOB(float_32 numerator, float_32 denominator)
{
	float_32 div_out;
	float_32 sign = 1.0f;

	if (denominator < 0)
	{
		denominator = -denominator;
		sign = -1.0f;
	}

	div_out = CEVA_DSP_LIB_FLOAT_ISQRT_OOB(denominator);
#if 1
	div_out = (sign * numerator) * (div_out * div_out);
#else
	div_out = sign * div_out * div_out * numerator;
#endif
    return (div_out);
}
#else



#ifndef WIN32
#define multiply_scale(x, y, s) (_mpyps((x),(y),(s)))
#else
#define multiply_scale(x, y, s) (((int64)(x)*(y))>>(s))
#endif

short norm_l1(long L_var1)
{
	short var_out;

	if (L_var1 == 0)
	{
		var_out = 0;
	}
	else
	{
		if (L_var1 == (long)0xffffffffL)
		{
			var_out = 31;
		}
		else
		{
			if (L_var1 < 0)
			{
				L_var1 = ~L_var1;
			}
			for (var_out = 0; L_var1 < (long)0x40000000L; var_out++)
			{
				L_var1 <<= 1;
			}
		}
	}

	return (var_out);
}

extern const uint16 approxRecip_1k0s[16];
extern const uint16 approxRecip_1k1s[16];


uint32 approximation(uint32 a)
{
	int index;
	uint16 r0;
	uint32 sigma0, eps;
	uint32 r;

	eps = a & 0x0007ffff; // 19 bits
	index = (a >> 19) & 0xF; // 4 bits

	// initial approximation 
	r0 = approxRecip_1k0s[index] - multiply_scale(approxRecip_1k1s[index], eps, 23);

	// NR iteration
	sigma0 = ~(uint32)((r0 * (uint64)a) );
	r = ((uint32)r0 << 16) + multiply_scale(r0, sigma0, 23);
	return r;
}



float_32 CEVA_DSP_LIB_FLOAT_DIV_OOB(float_32 a, float_32 b)
{
	uint32 a32, b32, res32;
	int signA, signB, sign;
	int expA, expB, exp, exp1;
	uint32 mantA, mantB, mant;
	float_32 res;

	if (b == 0)
		return 0;

	// extract sign, exp, mant
	a32 = *((uint32*)(&a));  // treat float as long
	signA = a32 >> 31;
	expA = (a32 >> 23) & 0xff;
	mantA = a32 & 0x007FFFFF;

	// extract sign, exp, mant
	b32 = *((uint32*)(&b));  // treat float as long
	signB = b32 >> 31;
	expB = (b32 >> 23) & 0xff;
	mantB = b32 & 0x007FFFFF;

	sign = signA ^ signB;

	if (!expB) 
	{
		exp1 = norm_l1(mantB) - 7;
		expB = 1 - exp1;
		mantB = mantB << exp1;
	}

	if (!expA) 
	{
		exp1 = norm_l1(mantA) - 7;
		expA = 1 - exp1;
		mantA = mantA << exp1;
	}

	exp = expA - expB + 0x7E;
	mantA |= 0x00800000;
	mantB |= 0x00800000;
	if (mantA < mantB) {
		--exp;
		mantA <<= 1;
	}

	mant = multiply_scale(mantA, approximation(mantB), 32);

	// combine back to float
	res32 = (sign << 31) + (exp << 23) + mant;
	res = *((float_32*)(&res32)); // treat long as float
	return res;
}
#endif
