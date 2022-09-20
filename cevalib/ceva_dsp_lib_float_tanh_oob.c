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

.. c:function::  int32 CEVA_DSP_LIB_TAN_INT32_OOB(int32 arg)

    :param int32 arg: [i] value whose tan is calculated.  Data interpreted as Q2.29 type
    :return: calculated tan value
    :rtype: int32 (interpreted as Q2.29 type)

*Restrictions*

=========================== =======================================  ========================================
Arguments                   Restriction                              Size in Bytes
=========================== =======================================  ========================================
arg                         in range -1..1
=========================== =======================================  ========================================


***/

#define COEFF_2X_POW2		 2.885390081777927f		// 2*log2(e)

float_32 CEVA_DSP_LIB_FLOAT_POW2_OOB(float_32 arg);
float_32 CEVA_DSP_LIB_FLOAT_DIV_OOB(float_32 numerator, float_32 denominator);

// =============================================================================================
// =                         Hyperbolic Tangent  [-inf...inf] (full band)                                 =
// =============================================================================================
float_32 CEVA_DSP_LIB_FLOAT_TANH_OOB(float_32 arg)
{
	float_32 tanh_res;
	float_32 exp_2x_coeff;

	exp_2x_coeff = CEVA_DSP_LIB_FLOAT_POW2_OOB(arg*COEFF_2X_POW2);

	tanh_res = CEVA_DSP_LIB_FLOAT_DIV_OOB((exp_2x_coeff - 1.0), (exp_2x_coeff + 1.0));

	return(tanh_res);
}
