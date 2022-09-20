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


.. c:function::  void CEVA_DSP_LIB_FLOAT_VEC_MUL_OOB(float_32 *a, float_32 *b, uint32 N, float_32 *c)

:param float_32 \*a: [i] ptr to input array 1, contains *N* elements. Element interpreted as Q31 fractional data
:param float_32 \*b: [i] ptr to input array 2, contains *N* elements. Element interpreted as Q31 fractional data
:param uint32 N: [i] the number of elements in the vectors
:param float_32 \*c:  [o] ptr to output array, contains *N* elements. Element interpreted as Q31 fractional data


*Restrictions*

=========================== =======================================  ========================================
Arguments                   Restriction                              Size in Bytes
=========================== =======================================  ========================================
a                           None                                     N*sizeof(float_32)
b                           None                                     N*sizeof(float_32)
c                           None                                     N*sizeof(float_32)
N                           >= 1
=========================== =======================================  ========================================

***/

void CEVA_DSP_LIB_FLOAT_VEC_MUL_OOB(float_32 *a, float_32 *b, uint32 N, float_32 *c)
{

	int32 i;
	float_32 res;

	for (i = 0; i<N; i++)
	{
		res = (*a++) * (*b++);
		*c++ = res;
	}

}
