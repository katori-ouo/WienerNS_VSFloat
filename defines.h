/*
 *  Copyright (c) 2011 The InnoTALK project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef INNOTALK_MODULES_AUDIO_PROCESSING_NS_MAIN_SOURCE_DEFINES_H_
#define INNOTALK_MODULES_AUDIO_PROCESSING_NS_MAIN_SOURCE_DEFINES_H_
//#define PROCESS_FLOW_0    // Use the traditional method.
#define PROCESS_FLOW_1    // Use traditional with DD estimate of prior SNR.
//#define PROCESS_FLOW_2    // Use the new method of speech/noise classification.
#define BLOCKL_MAX			128 // 最大处理块长度
#define ANAL_BLOCKL_MAX		256 // 最大分析块长度
#define HALF_ANAL_BLOCKL	129 //块分析长度一半加一

#define END_STARTUP_LONG    200       //分位数计算循环次数
#define END_STARTUP_SHORT   50        //计算简化噪声模型次数

#define SMOOTH              (float)0.75 // 滤波初始化系数
// Length of fft work arrays.FFT工作空间长度
#define IP_LENGTH (ANAL_BLOCKL_MAX >> 1) // must be at least ceil(2 + sqrt(ANAL_BLOCKL_MAX/2))
#define W_LENGTH (ANAL_BLOCKL_MAX >> 1)

#define FSmooth				0 //滤波器在频域的平滑操作

#define B_LIM               (float)0.5    // 最终能量增益因子计算中的阈值
#define SMOOTH_APY          (float)0.7    // 平滑功率谱的平滑因子
#define SMOOTH_R            (float)0.998  // 更新平滑功率谱最小值的经验常数
#define SMOOTH_BETA         (float)0.96   // 更新平滑功率谱最小值的经验常数
#define AP                  (float)0.2    // 语音概率更新系数
#define G                   (float)0.1    // 语音概率变换系数
#define AF                  (float)0.98   // 更新先验信噪比的经验系数
#define FILTER_SMOOTH       (float)0.9   // 更新滤波器系数的经验常数

#if FSmooth
#define ZETA_THR			(float)0.4    // 去除音乐噪音的信噪比阈值
#define PSI					(float)20.0   // 去除音乐噪声的平滑程度
#endif

#endif // INNOTALK_MODULES_AUDIO_PROCESSING_NS_MAIN_SOURCE_DEFINES_H_
