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



/***
auto-doc:

.. c:function::  float_32 CEVA_DSP_LIB_FLOAT_LOGN_OOB(float_32 inp)

:param float_32 arg: [i] value whose logn is calculated.
:return: calculated logn value
:rtype: float_32

*Restrictions*

=========================== =======================================  ========================================
Arguments                   Restriction                              Size in Bytes
=========================== =======================================  ========================================

=========================== =======================================  ========================================

***/

#include"math.h"
#include <ceva_typedef.h>

// =============================================================================================
// =                          logarithm approximation [-inf...inf]							   =
// =============================================================================================
float_32 CEVA_DSP_LIB_FLOAT_LOGN_OOB(float_32 inp)
{
	float_32 rez, arg;
	float_32 a0_0, a0, a1, a2, a3, a4, a5, a6, a7, a8;
#if 0
	float_32 arg_exp;
	unsigned int *p_ret_val;
	int gain_scale_l = 0;
	int gain_scale_r = 0;
	arg = inp;
	if (arg != 0)
	{
		if (arg > 0)
		{
			if (arg > 2.0) {
				while (arg > 2.0) {
					gain_scale_r = gain_scale_r + 1;
					arg = arg / 2;
				}
			}
			else {
				while (arg < 1.0) {
					gain_scale_l = gain_scale_l - 1;
					arg = arg * 2;
				}
			}
		}
		else
		{
			if (arg < -2.0) {
				while (arg < -2.0) {
					gain_scale_r = gain_scale_r + 1;
					arg = arg / 2;
				}
			}
			else {
				while (arg > -1.0) {
					gain_scale_l = gain_scale_l - 1;
					arg = arg * 2;
				}
			}
		}
	}
	else gain_scale_l = 24;

	arg_exp = gain_scale_l + gain_scale_r;
#else


	unsigned int tmp_inp, tmp1;
	int tmp2, arg_exp;
	unsigned int *p_ret_val, *p_tmp;

	p_ret_val = (unsigned int *)&arg;
	p_tmp = (unsigned int*)&inp;
	tmp_inp = *p_tmp;

	tmp1 = tmp_inp & 0x807fffff;
	tmp1 = tmp1 | 0x3f800000;

	*p_ret_val = tmp1;

	tmp2 = tmp_inp >> 23;
	tmp2 = tmp2 & 0xff;

	arg_exp = tmp2 - 0x7f;
#endif

	a0_0 = 0.6931471805;
	a0 = 1.4426950409;
	a1 = 0.9999964239;
	a2 = -0.4998741238;
	a3 = 0.3317990258;
	a4 = -0.2407338084;
	a5 = 0.1676540711;
	a6 = -0.0953293897;
	a7 = 0.0360884937;
	a8 = -0.0064535442;

#if 0
	arg = arg - 1;

	rez = arg * a8;

	rez += a7;
	rez = rez * arg;

	rez += a6;
	rez = rez * arg;

	rez += a5;
	rez = rez * arg;

	rez += a4;
	rez = rez * arg;

	rez += a3;
	rez = rez * arg;

	rez += a2;
	rez = rez * arg;

	rez += a1;
	rez = rez * arg;

	rez = rez * a0;

	rez = rez + arg_exp;

	rez = rez * a0_0;

#else
	arg = arg - 1;
	float_32 a1_0 = a0*a1;
	float_32 a2_0 = a0*a2;
	float_32 a3_0 = a0*a3;
	float_32 a4_0 = a0*a4;
	float_32 a5_0 = a0*a5;
	float_32 a6_0 = a0*a6;
	float_32 a7_0 = a0*a7;
	float_32 a8_0 = a0*a8;

	float_32 rez1 = a1_0 * arg;
	float_32 rez2 = arg * arg;
	float_32 rez3 = rez2 * arg;
	float_32 rez4 = rez2 * rez2;
	float_32 rez5 = rez3 * rez2;
	float_32 rez6 = rez4 * rez2;
	float_32 rez7 = rez4 * rez3;
	float_32 rez8 = rez4 * rez4;
	rez1 = rez1 + (float)arg_exp;
	rez2 = a2_0 * rez2;
	rez3 = a3_0 * rez3;
	rez4 = a4_0 * rez4;
	rez5 = a5_0 * rez5;
	rez6 = a6_0 * rez6;
	rez7 = a7_0 * rez7;
	rez8 = a8_0 * rez8;
	rez1 = rez1 + rez2;
	rez3 = rez3 + rez4;
	rez5 = rez5 + rez6;
	rez7 = rez7 + rez8;
	rez = rez1 + rez3;
	rez5 = rez5 + rez7;
	rez = rez + rez5;
	rez = rez * a0_0;
#endif
	if (inp < 0.0)
	{
		p_ret_val = (unsigned int *)&rez;
		*p_ret_val = 0xffc00000;
	}
	if (inp == 0.0)
	{
		p_ret_val = (unsigned int *)&rez;
		*p_ret_val = 0xff800000;
	}
	return rez;
}

