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


.. c:function::  int32 CEVA_DSP_LIB_POW_INT32_OOB(int32 arg_in_X, int16 arg_exp_in_X, int32 arg_in_Y, int16 arg_exp_in_Y, int16 *arg_exp_out)

    :param int32 arg_in_X: [i] the soperand_X mantissa. A Q31 number in range 0, 0.5..1.
    :param int16 arg_exp_in_X: [i] the soperand_X exponent, integer in range -127..127
    :param int32 arg_in_Y: [i] the soperand_Y mantissa. A Q31 number in range 0, 0.5..1.
    :param int16 arg_exp_in_Y: [i] the soperand_Y exponent, integer in range -127..127
    :param int32 \*arg_exp_out: [o] the exponent of the result, integer in range -127..127
    :return: the mantissa of the result, A Q31 number in range 0, 0.5..1.
    :rtype: int32


*Restrictions*

=========================== =======================================  ========================================
Arguments                   Restriction                              Size in Bytes
=========================== =======================================  ========================================
arg_in_X                    Q31 number in range 0, 0.5..1
arg_exp_in_X                integer in range -127..127
arg_in_Y                    Q31 number in range 0, 0.5..1
arg_exp_in_Y                integer in range -127..127
=========================== =======================================  ========================================

***/

float_32 CEVA_DSP_LIB_FLOAT_POW2_OOB(float_32 arg);
float_32 CEVA_DSP_LIB_FLOAT_LOG2_OOB(float_32 arg);


// =============================================================================================
// =                    arg_out = arg_X ^ arg_Y = 2 ^ (arg_Y * log2(arg_X))
// = 
// =					Restriction
// =					arg_X = (0   ...inf]
// =					arg_Y = [-inf...inf]
// =============================================================================================
float_32 CEVA_DSP_LIB_FLOAT_POW_OOB(float_32 arg_X, float_32 arg_Y)
{
	float_32 pow_out;


	pow_out = CEVA_DSP_LIB_FLOAT_LOG2_OOB(arg_X);
	pow_out = pow_out * arg_Y;
	pow_out = CEVA_DSP_LIB_FLOAT_POW2_OOB(pow_out);
	return (pow_out);
}

