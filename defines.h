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
#define BLOCKL_MAX			128 // �����鳤��
#define ANAL_BLOCKL_MAX		256 // �������鳤��
#define HALF_ANAL_BLOCKL	129 //���������һ���һ

#define END_STARTUP_LONG    200       //��λ������ѭ������
#define END_STARTUP_SHORT   50        //���������ģ�ʹ���

#define SMOOTH              (float)0.75 // �˲���ʼ��ϵ��
// Length of fft work arrays.FFT�����ռ䳤��
#define IP_LENGTH (ANAL_BLOCKL_MAX >> 1) // must be at least ceil(2 + sqrt(ANAL_BLOCKL_MAX/2))
#define W_LENGTH (ANAL_BLOCKL_MAX >> 1)

#define FSmooth				0 //�˲�����Ƶ���ƽ������

#define B_LIM               (float)0.5    // ���������������Ӽ����е���ֵ
#define SMOOTH_APY          (float)0.7    // ƽ�������׵�ƽ������
#define SMOOTH_R            (float)0.998  // ����ƽ����������Сֵ�ľ��鳣��
#define SMOOTH_BETA         (float)0.96   // ����ƽ����������Сֵ�ľ��鳣��
#define AP                  (float)0.2    // �������ʸ���ϵ��
#define G                   (float)0.1    // �������ʱ任ϵ��
#define AF                  (float)0.98   // ������������ȵľ���ϵ��
#define FILTER_SMOOTH       (float)0.9   // �����˲���ϵ���ľ��鳣��

#if FSmooth
#define ZETA_THR			(float)0.4    // ȥ�������������������ֵ
#define PSI					(float)20.0   // ȥ������������ƽ���̶�
#endif

#endif // INNOTALK_MODULES_AUDIO_PROCESSING_NS_MAIN_SOURCE_DEFINES_H_
