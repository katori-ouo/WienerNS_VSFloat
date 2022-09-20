
#include "CEVA_typedef.h"

/*****************************************************************************\
*
* Copyright (C) Ceva Inc. All rights reserved.
*
\*****************************************************************************/


#ifndef WIN32
	__attribute__((section(".DSECT CEVA_DSP_LIB_DATA_ROM")))
#endif
const int32 CEVA_DSP_LIB_INIT_ROUND_TABLE[4] = { 0x40000000, 0, 0x40000000, 0 };

#ifndef WIN32
	__attribute__((section(".DSECT CEVA_DSP_LIB_DATA_ROM")))
#endif
const int32 CEVA_DSP_LIB_INIT_ZERO_TABLE[4] = { 0, 0, 0, 0 };

#ifndef WIN32
	__attribute__((section(".DSECT CEVA_DSP_LIB_DATA_ROM")))
#endif
const int16 CEVA_DSP_LIB_COSSIN_Q15_sincos_coeff_q12[32] = {
	0, 32767,   12540, 30274,   23170, 23170,   30274, 12540,   32767,0,   30274,-12540,   23170,-23170,   12540,-30274,
	0,-32768,  -12540,-30274,  -23170,-23170,  -30274,-12540,  -32768,0,  -30274, 12540,  -23170, 23170,  -12540, 30274 };

#ifndef WIN32
	__attribute__((section(".DSECT CEVA_DSP_LIB_DATA_ROM")))
#endif
const uint16 CEVA_DSP_LIB_COSSIN_Q15_sincos_coeff_q8[32] = {
	0,32767,    804,32758,   1608,32729,   2411,32679,   3212,32610,   4011,32522,   4808,32413,   5602,32286,
	6393,32138,   7180,31972,   7962,31786,   8740,31581,   9512,31357,  10279,31114,  11039,30853,  11793,30572 };

#ifndef WIN32
	__attribute__((section(".DSECT CEVA_DSP_LIB_DATA_ROM")))
#endif
const uint16 CEVA_DSP_LIB_COSSIN_Q15_sincos_coeff_q4[32] = {
	0,32767,     50,32767,    101,32767,    151,32767,    201,32767,    251,32767,    302,32767,    352,32766,
	402,32766,    452,32765,    503,32764,   553, 32763,    603,32762,    653,32761,    704,32760,    754,32759 };

#ifndef WIN32
	__attribute__((section(".DSECT CEVA_DSP_LIB_DATA_ROM")))
#endif
const uint16 CEVA_DSP_LIB_COSSIN_Q15_sincos_coeff_q0[32] = {
	0,32767,   3,32767,   6,32767,   9,32767,  13,32767,  16,32767,  19,32767,  22,32767,
	25,32767,  28,32767,  31,32767,  35,32767,  38,32767,  41,32767,  44,32767,  47,32767 };


/*
	sigmoid_pol_table[i] = sigmoid(0.125*i) * (1LL<<31); // sigmoid with step 0.125 in Q31
*/
#ifndef WIN32
	__attribute__((section(".DSECT CEVA_DSP_LIB_DATA_ROM")))
#endif
const unsigned long CEVA_DSP_LIB_sigmoid_pol_table[129] = {
	0x40000000,
	0x43feab33,
	0x47f5664b,
	0x4bdc7fc8,
	0x4facbf53,
	0x535f98a1,
	0x56ef53df,
	0x5a5729ee,
	0x5d9353d7,
	0x60a10de6,
	0x637e8fd5,
	0x662afbfd,
	0x68a647cb,
	0x6af11fe2,
	0x6d0cca17,
	0x6efb071c,
	0x70bdf56a,
	0x7257f66e,
	0x73cb96b7,
	0x751b7978,
	0x764a4777,
	0x775aa149,
	0x784f14a5,
	0x792a1467,
	0x79edf2f1,
	0x7a9cde8d,
	0x7b38df60,
	0x7bc3d6b2,
	0x7c3f7f30,
	0x7cad6de8,
	0x7d0f13da,
	0x7d65bfdc,
	0x7db2a0bc,
	0x7df6c784,
	0x7e3329bf,
	0x7e68a3c1,
	0x7e97fad8,
	0x7ec1df66,
	0x7ee6eed6,
	0x7f07b57e,
	0x7f24b04c,
	0x7f3e4e5c,
	0x7f54f269,
	0x7f68f41b,
	0x7f7aa136,
	0x7f8a3ead,
	0x7f98099b,
	0x7fa4381f,
	0x7faefa22,
	0x7fb87a0c,
	0x7fc0dd61,
	0x7fc8454e,
	0x7fcecf2c,
	0x7fd494e8,
	0x7fd9ad70,
	0x7fde2d05,
	0x7fe2258c,
	0x7fe5a6d7,
	0x7fe8beda,
	0x7feb79ee,
	0x7fede2f5,
	0x7ff0038f,
	0x7ff1e43a,
	0x7ff38c75,
	0x7ff502e1,
	0x7ff64d55,
	0x7ff770fa,
	0x7ff8725f,
	0x7ff95588,
	0x7ffa1e03,
	0x7ffacef1,
	0x7ffb6b16,
	0x7ffbf4e4,
	0x7ffc6e82,
	0x7ffcd9d6,
	0x7ffd388e,
	0x7ffd8c25,
	0x7ffdd5ea,
	0x7ffe1704,
	0x7ffe5079,
	0x7ffe832d,
	0x7ffeafec,
	0x7ffed769,
	0x7ffefa42,
	0x7fff1904,
	0x7fff3428,
	0x7fff4c1b,
	0x7fff613f,
	0x7fff73e6,
	0x7fff845c,
	0x7fff92e3,
	0x7fff9fb6,
	0x7fffab06,
	0x7fffb502,
	0x7fffbdd2,
	0x7fffc599,
	0x7fffcc75,
	0x7fffd284,
	0x7fffd7dc,
	0x7fffdc94,
	0x7fffe0bd,
	0x7fffe469,
	0x7fffe7a7,
	0x7fffea84,
	0x7fffed0a,
	0x7fffef44,
	0x7ffff13c,
	0x7ffff2f8,
	0x7ffff480,
	0x7ffff5da,
	0x7ffff70b,
	0x7ffff819,
	0x7ffff906,
	0x7ffff9d8,
	0x7ffffa91,
	0x7ffffb35,
	0x7ffffbc5,
	0x7ffffc44,
	0x7ffffcb4,
	0x7ffffd18,
	0x7ffffd6f,
	0x7ffffdbc,
	0x7ffffe00,
	0x7ffffe3d,
	0x7ffffe72,
	0x7ffffea0,
	0x7ffffeca,
	0x7ffffeee,
	0x7fffffff};

#ifndef WIN32
	__attribute__((section(".DSECT CEVA_DSP_LIB_DATA_ROM")))
#endif
const unsigned long CEVA_DSP_LIB_sigmoid_error_table[128] = {
		0x831b*2,
		0x17c66*2,
		0x26bce*2,
		0x348f0*2,
		0x40dde*2,
		0x4b639*2,
		0x53f42*2,
		0x5a7d2*2,
		0x5f03f*2,
		0x61a1f*2,
		0x62805*2,
		0x61d34*2,
		0x5fd57*2,
		0x5cc3c*2,
		0x58da3*2,
		0x5450e*2,
		0x4f5ab*2,
		0x4a23f*2,
		0x44d24*2,
		0x3f846*2,
		0x3a52b*2,
		0x354f9*2,
		0x3088a*2,
		0x2c06e*2,
		0x27cff*2,
		0x23e66*2,
		0x204aa*2,
		0x1cfb6*2,
		0x19f5f*2,
		0x1736d*2,
		0x14b9f*2,
		0x127af*2,
		0x10753*2,
		0xea41*2,
		0xd034*2,
		0xb8e5*2,
		0xa413*2,
		0x9181*2,
		0x80f6*2,
		0x723e*2,
		0x6528*2,
		0x598a*2,
		0x4f39*2,
		0x4614*2,
		0x3df8*2,
		0x36c9*2,
		0x306d*2,
		0x2acc*2,
		0x25d0*2,
		0x2168*2,
		0x1d83*2,
		0x1a11*2,
		0x1705*2,
		0x1454*2,
		0x11f3*2,
		0xfd9*2,
		0xdfe*2,
		0xc5b*2,
		0xae8*2,
		0x9a1*2,
		0x880*2,
		0x780*2,
		0x69f*2,
		0x5d8*2,
		0x529*2,
		0x48e*2,
		0x405*2,
		0x38c*2,
		0x321*2,
		0x2c3*2,
		0x270*2,
		0x227*2,
		0x1e6*2,
		0x1ad*2,
		0x17b*2,
		0x14e*2,
		0x127*2,
		0x104*2,
		0xe6*2,
		0xcb*2,
		0xb3*2,
		0x9e*2,
		0x8b*2,
		0x7b*2,
		0x6d*2,
		0x60*2,
		0x55*2,
		0x4b*2,
		0x42*2,
		0x3a*2,
		0x33*2,
		0x2d*2,
		0x28*2,
		0x23*2,
		0x1f*2,
		0x1b*2,
		0x18*2,
		0x15*2,
		0x13*2,
		0x11*2,
		0xf*2,
		0xd*2,
		0xb*2,
		0xa*2,
		0x9*2,
		0x8*2,
		0x7*2,
		0x6*2,
		0x5*2,
		0x5*2,
		0x4*2,
		0x4*2,
		0x3*2,
		0x3*2,
		0x3*2,
		0x2*2,
		0x2*2,
		0x2*2,
		0x2*2,
		0x1*2,
		0x1*2,
		0x1*2,
		0x1*2,
		0x1*2,
		0x1*2,
		0x1*2,
		0x1*2,
		0x1*2};

const uint16 approxRecip_1k0s[16] = {
	0xFFC4, 0xF0BE, 0xE363, 0xD76F, 0xCCAD, 0xC2F0, 0xBA16, 0xB201,
	0xAA97, 0xA3C6, 0x9D7A, 0x97A6, 0x923C, 0x8D32, 0x887E, 0x8417
};
const uint16 approxRecip_1k1s[16] = {
	0xF0F1, 0xD62C, 0xBFA1, 0xAC77, 0x9C0A, 0x8DDB, 0x8185, 0x76BA,
	0x6D3B, 0x64D4, 0x5D5C, 0x56B1, 0x50B6, 0x4B55, 0x4679, 0x4211
};

const uint16 approxRecipSqrt_1k0s[16] = {
	0xB4C9, 0xFFAB, 0xAA7D, 0xF11C, 0xA1C5, 0xE4C7, 0x9A43, 0xDA29,
	0x93B5, 0xD0E5, 0x8DED, 0xC8B7, 0x88C6, 0xC16D, 0x8424, 0xBAE1
};
const uint16 approxRecipSqrt_1k1s[16] = {
	0xA5A5, 0xEA42, 0x8C21, 0xC62D, 0x788F, 0xAA7F, 0x6928, 0x94B6,
	0x5CC7, 0x8335, 0x52A6, 0x74E2, 0x4A3E, 0x68FE, 0x432B, 0x5EFD
};



