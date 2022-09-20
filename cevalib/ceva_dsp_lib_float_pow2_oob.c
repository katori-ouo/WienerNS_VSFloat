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

.. c:function::  float_32 CEVA_DSP_LIB_FLOAT_POW2_OOB(float_32 arg)

:param float_32 arg: [i] value whose pow2 is calculated.
:return: calculated pow2 value
:rtype: float_32

*Restrictions*

=========================== =======================================  ========================================
Arguments                   Restriction                              Size in Bytes
=========================== =======================================  ========================================

=========================== =======================================  ========================================

***/


// =============================================================================================
// =                          arg_out = 2^arg approximation [-inf...inf]						=
// =============================================================================================
float_32 CEVA_DSP_LIB_FLOAT_POW2_OOB(float_32 arg)
{
	float_32 rez;
	float_32 a1, a2, a3, a4, a5, a6, a7;
	double e;
	float_32 m = (float_32)modf(arg, &e);
	float_32 rez1, rez2,rez3,rez4,rez5,rez6,rez7;
	a1 = 0.693147180559945;
	a2 = 0.240226506959101;
	a3 = 0.0555041086648216;
	a4 = 0.00961706318229939;
	a5 = 0.00133331399721798;
	a6 = 0.000156474208648932;
	a7 = 1.53953958715684e-005;

#if 0
	rez = m * a7;

	rez += a6;
	rez = rez * m;

	rez += a5;
	rez = rez * m;

	rez += a4;
	rez = rez * m;

	rez += a3;
	rez = rez * m;

	rez += a2;
	rez = rez * m;

	rez += a1;
	rez = rez * m;

	rez = rez + 1;

#else
	rez1 = a1*m;
	rez1 = rez1 + 1.0f;
	rez2 = m*m;
	rez3 = rez2*m;
	rez4 = rez2*rez2;
	rez5 = rez4*m;
	rez6 = rez4*rez2;
	rez7 = rez4*rez3;

	rez2 = rez2 * a2;
	rez3 = rez3*a3;
	rez4 = rez4*a4;
	rez5 = rez5 * a5;
	rez6 = rez6 * a6;

	rez7 = rez7*a7;
	rez1 = rez1 + rez2;
	rez3 = rez3 + rez4;
	rez5 = rez5 + rez6;
	rez5 = rez5 + rez7;
	rez = rez1 + rez3;
	rez = rez + rez5;

#endif
#ifdef WIN32
	//rez = (float_32)ldexp(rez, e);
	rez = ldexpf(rez, e);
#else
	{
		int exp_new = (int)e;
		int tmp;
		int *rez_p = (int*)&rez5;
		exp_new += 127;
		if (exp_new > 0)
		{
			if (exp_new > 0x0ff)
				exp_new = 0x0ff;

			exp_new = exp_new << 23;
			*rez_p = exp_new;

		}
		else
		{
			tmp = 0x0400000;
			exp_new = -exp_new;
			if (exp_new > 30)
				tmp = 0;
			else
				tmp = tmp >> exp_new;

			*rez_p = tmp;
		}
		rez = rez * rez5;


	}

#endif
	return rez;

}
