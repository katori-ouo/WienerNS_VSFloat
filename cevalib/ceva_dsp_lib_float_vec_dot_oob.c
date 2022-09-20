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
#include <ceva_dsp_lib.h>


/***
auto-doc:

.. c:function::  float_32 CEVA_DSP_LIB_FLOAT_VEC_DOT_OOB(float_32 *a, float_32 *b, uint32 N)

:param float_32 \*a: [i] ptr to array holding *N* elements.  The elements in this array are interpreted  as Q31 data.
:param float_32 \*b: [i] ptr to array holding *N* elements.  The elements in this array are interpreted  as Q31 data.
:param uint32 N: [i] the number of elements in the input array
:return: dot product, interpreted as Q31 value
:rtype: int32

*Restrictions*

=========================== =======================================  ========================================
Arguments                   Restriction                              Size in Bytes
=========================== =======================================  ========================================
a                           None                                     N*sizeof(float_32)
b                           None                                     N*sizeof(float_32)
N                           >= 1
=========================== =======================================  ========================================

***/

#if 1
float_32 CEVA_DSP_LIB_FLOAT_VEC_DOT_OOB(float_32 *a, float_32 *b, uint32 N)
{

	float_32 res1;
	float_32 res2;
	float_32 res3;
	float_32 res4;
	float_32 res5;

	res1 = 0.0;
	res2 = 0.0;
	res3 = 0.0;
	res4 = 0.0;
	res5 = 0.0;
	while (N >= 5)
	{

		res1 += ((*a++) * (*b++));
		res2 += ((*a++) * (*b++));
		res3 += ((*a++) * (*b++));
		res4 += ((*a++) * (*b++));
		res5 += ((*a++) * (*b++));
		N -= 5;
	}
	if (N >= 1)
	{
		res1 += ((*a++) * (*b++));
	}
	if (N >= 2)
	{
		res2 += ((*a++) * (*b++));
	}
	if (N >= 3)
	{
		res3 += ((*a++) * (*b++));
	}
	if (N >= 4)
	{
		res4 += ((*a++) * (*b++));
	}
	res1 = res1 + res5;
	res2 = res2 + res3;
	res1 = res1 + res4;
	res1 = res1 + res2;


	return res1;

}

#else
float_32 CEVA_DSP_LIB_FLOAT_VEC_DOT_OOB(float_32 *a, float_32 *b, uint32 N)
{
	uint32 i;
	float_32 res;

	res = 0.0;
	for (i = 0; i<N; i++)
	{

		res +=  ((*a++) * (*b++));

	}
	return res;

}
#endif

