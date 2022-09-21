/*
 *  Copyright (c) 2012 The InnoTALK project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "ns_core.h"
const float delta[65] = {
  1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3,
  1.4088, 1.5176, 1.6264, 1.7352, 1.8440, 1.9528,2.0616, 2.1704, 2.2792, 2.3880, 2.4968,
  2.6056,2.7144, 2.8232, 2.9320, 3.0408, 3.1496, 3.2584,3.3672, 3.4760, 3.5848, 3.6936,
  3.8024, 3.9112,4.0200, 4.1288, 4.2376, 4.3464, 4.4552, 4.5640,4.6728, 4.7816, 4.8904,
  5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0};
static const float WinTable[128] = {
	0.0000, 0.0245, 0.0491, 0.0736, 0.0980, 0.1224,
	0.1467, 0.1710, 0.1951, 0.2191, 0.2430, 0.2667,
	0.2903, 0.3137, 0.3369, 0.3599, 0.3827, 0.4052,
	0.4276, 0.4496, 0.4714, 0.4929, 0.5141, 0.5350,
	0.5556, 0.5758, 0.5957, 0.6152, 0.6344, 0.6532,
	0.6716, 0.6895, 0.7071, 0.7242, 0.7410, 0.7572,
	0.7730, 0.7883, 0.8032, 0.8176, 0.8315, 0.8449,
	0.8577, 0.8701, 0.8819, 0.8932, 0.9040, 0.9142,
	0.9239, 0.9330, 0.9415, 0.9495, 0.9569, 0.9638,
	0.9700, 0.9757, 0.9808, 0.9853, 0.9892, 0.9925,
	0.9952, 0.9973, 0.9988, 0.9997, 1.0000, 0.9997,
	0.9988, 0.9973, 0.9952, 0.9925, 0.9892, 0.9853,
	0.9808, 0.9757, 0.9700, 0.9638, 0.9569, 0.9495,
	0.9415, 0.9330, 0.9239, 0.9142, 0.9040, 0.8932,
	0.8819, 0.8701, 0.8577, 0.8449, 0.8315, 0.8176,
	0.8032, 0.7883, 0.7730, 0.7572, 0.7410, 0.7242,
	0.7071, 0.6895, 0.6716, 0.6532, 0.6344, 0.6152,
	0.5957, 0.5758, 0.5556, 0.5350, 0.5141, 0.4929,
	0.4714, 0.4496, 0.4276, 0.4052, 0.3827, 0.3599,
	0.3369, 0.3137, 0.2903, 0.2667, 0.2430, 0.2191,
	0.1951, 0.1710, 0.1467, 0.1224, 0.0980, 0.0736,
	0.0491, 0.0245};

#if FSmooth
/**
 * @brief ����һ������ƽ���˲�������ʼ��
 * 
 * @param size �������ڳ���
 * @return MovingAverage* ����ƽ���˲���obj
 */
MovingAverage* movingAverageCreate(int size) {
    MovingAverage* obj = (MovingAverage*)malloc(sizeof(MovingAverage));
    obj->size = size;
    obj->sum = 0.0;
    obj->queue = (float*)malloc(sizeof(float) * (size + 1));
    obj->front = 0;
    obj->rear = 0;
    return obj;
}

/**
 * @brief �������ֵ������ƽ��
 * 
 * @param obj ����ƽ���˲���
 * @param val �������һ��ֵ
 * @return uint32_t ����ƽ�����ֵ
 */
float movingAverageNext(MovingAverage* obj, float val) {
    int size = (obj->rear - obj->front + obj->size + 1) % (obj->size + 1);
    if (size == obj->size) {
        obj->sum -= obj->queue[obj->front];
        obj->front = (obj->front + 1) % (obj->size + 1);
        size--;
    }
    obj->queue[obj->rear] = val;
    obj->rear = (obj->rear + 1) % (obj->size + 1);
    obj->sum += val;
    size++;
    return (float)(obj->sum / size);
}

/**
 * @brief �ͷŻ���ƽ���˲������ڴ�ռ�
 * 
 * @param obj ����ƽ���˲���
 */
void movingAverageFree(MovingAverage* obj) {
    free(obj->queue);
    free(obj);
}
#endif

/**
 * @brief Ϊns�ṹ������ڴ�ռ�
 * 
 * @param NS_inst &(NSinst_t *)
 * @return int ����ʧ�ܷ���-1, ���򷵻�0
 */
int InnoTalkNs_CreateN(NSinst_t** NS_inst) {
	*NS_inst = (NSinst_t*)malloc(sizeof(NSinst_t));
	if (*NS_inst != NULL) {
		return 0;
	}
	else {
		return -1;
	}

}

/**
 * @brief ��ʼ��ns�ṹ��
 * 
 * @param inst ָ��ns�ṹ���ָ��
 * @param fs ����Ƶ��
 * @return int  ��ʼ��ʧ�ܷ���-1, ���򷵻�0
 */
int InnoTalkNs_InitCore(NSinst_t* inst, uint32_t fs) {
  if (inst == NULL) {
    return -1;
  }
  // Initialization of struct
  inst->fs = fs;

  // We only support 10ms frames
  inst->blockLen = FRAME_LEN;
  inst->anaLen = ANAL_BLOCKL_MAX;
  inst->magnLen = inst->anaLen / 2 + 1; // Number of frequency bins
  memset(inst->dataBuf, 0, sizeof(float) * ANAL_BLOCKL_MAX);
  memset(inst->syntBuf, 0, sizeof(float) * ANAL_BLOCKL_MAX);

  memset(inst->smooth, SMOOTH, sizeof(float) * HALF_ANAL_BLOCKL);
  memset(inst->pmagnPrev, 0, sizeof(float) * HALF_ANAL_BLOCKL);
  memset(inst->magnPrev, 0, sizeof(float) * HALF_ANAL_BLOCKL);
  memset(inst->noisePrev, 0, sizeof(float) * HALF_ANAL_BLOCKL);
  memset(inst->probPrev, 0, sizeof(float) * HALF_ANAL_BLOCKL);
  memset(inst->signalPrev, 0, sizeof(float) * HALF_ANAL_BLOCKL);
  memset(inst->minMagn, 0, sizeof(float) * HALF_ANAL_BLOCKL);

	inst->overdrive = (float)1.3;
	inst->denoiseBound = (float)0.07;

	inst->blockInd = -1; //֡����

  return 0;
}

/**
 * @brief �����㷨�ĺ��ĺ���
 * 
 * @param inst ns�ṹ��
 * @param speechFrame �����short��һ֡�ź�
 * @param outFrame  �����short��һ֡������ź�
 * @return int ����ʧ�ܷ���-1, ���򷵻�0
 */
int InnoTalkNs_ProcessCore(NSinst_t* inst, short* speechFrame, short* outFrame){

  int     i;
  float   energy1, energy2, gain, factor;
  float   fTmp, dTmp;
  float   fin[FRAME_LEN], fout[FRAME_LEN];
  float   winData[ANAL_BLOCKL_MAX];
  float   CFFT_Outns[2 * ANAL_BLOCKL_MAX];//FFT�������Ҫ��ʵ�����鲿ȡ���������������
  float   CFFT_InvOutns[2 * ANAL_BLOCKL_MAX];		//CEVAֻ��Ҫһ��Ŀռ�
  float   magn[HALF_ANAL_BLOCKL], noise[HALF_ANAL_BLOCKL], pmagn[HALF_ANAL_BLOCKL];//lry20180929
  float   ii[HALF_ANAL_BLOCKL], pr[HALF_ANAL_BLOCKL], afa[HALF_ANAL_BLOCKL];
  float   theFilter[HALF_ANAL_BLOCKL];
  float   snrLocPost[HALF_ANAL_BLOCKL] = { 0 }, snrLocPrior[HALF_ANAL_BLOCKL] = { 0 };
  float   probSpeechFinal[HALF_ANAL_BLOCKL] = { 0 };
  float   real[ANAL_BLOCKL_MAX], imag[HALF_ANAL_BLOCKL];
#if FSmooth
  float   zeta,fenergy1,fenergy2;
  int     winLen;
  MovingAverage* average;
#endif

  // convert to float
  for (i = 0; i < inst->blockLen; i++) {
    fin[i] = (float)speechFrame[i];
  }
	// �������ݴ��뻺����
  memcpy(inst->dataBuf, inst->dataBuf + inst->blockLen,
         sizeof(float) * (inst->anaLen - inst->blockLen));
  memcpy(inst->dataBuf + inst->anaLen - inst->blockLen, fin,
         sizeof(float) * inst->blockLen);
	// ����Ƿ�����ns������
	// �Ӵ�������
  energy1 = 0.0;
  for ( i = 0; i < inst->anaLen; i++)
  {
    winData[i] = WinTable[i] * inst->dataBuf[i];
    energy1 += winData[i] * winData[i];
  }
#if 1
  // ĿǰΪ0�������
  // �����Ѵ���õ������ź�
  if (energy1 == 0.0)
  {
    // read out fully processed segment
    for (i = 0; i < inst->blockLen; i++) {
      fout[i] = inst->syntBuf[i];
    }
    // ��syntBuf��0
    memcpy(inst->syntBuf, inst->syntBuf + inst->blockLen,
             sizeof(float) * (inst->anaLen - inst->blockLen));
    memset(inst->syntBuf + inst->anaLen - inst->blockLen, 0,
             sizeof(float) * inst->blockLen);
    // �źŶ������ȴ�Сȷ�������껹����С��
    for (i = 0; i < inst->blockLen; i++) {
        dTmp = fout[i];
        if (dTmp < INNOTALK_SPL_WORD16_MIN) {
          dTmp = INNOTALK_SPL_WORD16_MIN;
        } else if (dTmp > INNOTALK_SPL_WORD16_MAX) {
          dTmp = INNOTALK_SPL_WORD16_MAX;
        }
        outFrame[i] = (short)dTmp;
      }

      return 0;
  }
#endif
  inst->blockInd++; // Update the block index only when we process a block.

  float CFFT_Inns[2 * ANAL_BLOCKL_MAX];//FFT���룬ʵ���ǼӴ�֮������룬�鲿Ϊ0
	float tmp[2 * ANAL_BLOCKL_MAX] = {0};
  for (i=0;i<inst->anaLen;i++)
  {
    CFFT_Inns[2 * i] = winData[i];	// ʵ��
    CFFT_Inns[2 * i + 1] = 0;     		// �鲿Ϊ 0
  }
	CEVA_DSP_LIB_FLOAT_FFT_CX_OOB(7, CFFT_Inns, CFFT_Outns, CEVA_DSP_LIB_FLOAT_cos_sin, (int16*)bitrev_32_1024, tmp, 1);
  // ���㵱ǰ֡�Ĺ����׺���λ��

  imag[0] = 0;
  real[0] = CFFT_Outns[0];
  imag[inst->magnLen - 1] = 0;
  real[inst->magnLen - 1] = CFFT_Outns[inst->anaLen];
  magn[0] = (float)(real[0] * real[0]);
  magn[inst->magnLen - 1] = (float)(real[inst->magnLen - 1] * real[inst->magnLen - 1]);
  for (i = 1; i < inst->magnLen - 1; i++)
  {
    real[i] = CFFT_Outns[2 * i];
    imag[i] = -1*CFFT_Outns[2 * i + 1];
    // magnitude spectrum
    fTmp = real[i] * real[i];
    fTmp += imag[i] * imag[i];
    magn[i] = (float)fTmp;
  }

  // ����ǵ�һ֡
  if (inst->blockInd == 0)
  {
    memcpy(inst->minMagn, magn, sizeof(float) * inst->magnLen);
    memcpy(pmagn, magn, sizeof(float) * inst->magnLen);
    memcpy(noise, magn, sizeof(float) * inst->magnLen);
    memset(probSpeechFinal, 0, sizeof(float) * inst->magnLen);
  }
  else
  // ����֡
  {
    for ( i = 0; i < inst->magnLen; i++)
    {
      // 1.ƽ�������� ��Ӧԭ������Сֵͳ�ƹ���ĵ�(1)������ʽ(1)
		  pmagn[i] = SMOOTH_APY * inst->pmagnPrev[i] + (1 - SMOOTH_APY) * magn[i];

      // 2.����Ƶ����Сֵ ��Ӧԭ������Сֵͳ�ƹ���ĵ�(2)��
      if (inst->minMagn[i] < pmagn[i])
      {
        inst->minMagn[i] = SMOOTH_R * inst->minMagn[i] + (1 - SMOOTH_R) / (1 - SMOOTH_BETA) * (pmagn[i] - SMOOTH_BETA * inst->pmagnPrev[i]);
      }
      else
      {
        inst->minMagn[i] = pmagn[i];
      }
      // 3.�ж��Ƿ�������� ��Ӧԭ������Сֵͳ�ƹ���ĵ�(3)��
      if (inst->minMagn[i] == 0)
      {
        pr[i] = delta[i] + (float)1.0;
      }
      else
      {
        pr[i] = pmagn[i] / inst->minMagn[i];
      }
      if (pr[i] > delta[i])
      {
        ii[i] = (float)1.0;
      }
      else
      {
        ii[i] = (float)0.0;
      }

      // 4.�����������ֵĸ��� ��Ӧԭ������Сֵͳ�ƹ���ĵ�(4)��
      probSpeechFinal[i] = AP * inst->probPrev[i] + ((float)1.0 - AP) * ii[i];
    }

    for ( i = 0; i < inst->magnLen; i++)
    {
      // 5.�����׹���,��Ӧԭ������Сֵͳ�ƹ���ĵ�(5)��:
      if (inst->blockInd < 7)
      {
        noise[i] = pmagn[i];
      }
      else
      {
        afa[i] = G * probSpeechFinal[i] + ((float)1.0 - G);
        noise[i] = afa[i] * inst->noisePrev[i] + ((float)1.0 - afa[i]) * magn[i];
      }
    }
  }

  // ����ǰ֡��ֵ����ǰһ֡
  memcpy(inst->pmagnPrev, pmagn, sizeof(float) * inst->magnLen);
  memcpy(inst->probPrev, probSpeechFinal, sizeof(float) * inst->magnLen);
  memcpy(inst->noisePrev, noise, sizeof(float) * inst->magnLen);
  // 6. ��������/��������Ⱥ�ά���˲���
  for ( i = 0; i < inst->magnLen; i++)
  {
    if (inst->blockInd == 0)
    {
      snrLocPrior[i] = 0.96f;
      theFilter[i] = snrLocPrior[i] / (inst->overdrive + snrLocPrior[i]);
    }
    else
    {
      if (noise[i] == 0)
      {
        snrLocPrior[i] = AF * 0.96f;
        theFilter[i] = snrLocPrior[i] / (inst->overdrive + snrLocPrior[i]);
      }
      else
      {
        snrLocPost[i] = magn[i];
        snrLocPrior[i] = AF * inst->signalPrev[i] + (1.0f - AF) * max((snrLocPost[i] - noise[i]),0);
        theFilter[i] = snrLocPrior[i] / (inst->overdrive * noise[i] + snrLocPrior[i]);
      }
    }

    if (theFilter[i] > 1.0)
    {
      theFilter[i] = (float)1.0;
    }
    if (theFilter[i] < inst->denoiseBound)
    {
      theFilter[i] = inst->denoiseBound;
    }
    inst->signalPrev[i] = magn[i] * theFilter[i] * theFilter[i];
  }

  // 7. ����ˮ��
  for (size_t i = 0; i < inst->magnLen; i++)
  {
    inst->smooth[i] = FILTER_SMOOTH * inst->smooth[i] + (1 - FILTER_SMOOTH) * theFilter[i];
  }
#if FSmooth
   fenergy1 = 0.0;
   fenergy2 = 0.0;
   for ( i = 0; i < inst->magnLen; i++)
   {
       fenergy1 += real[i] * real[i] + imag[i] * imag[i];
       fenergy2 += real[i] * real[i] * theFilter[i] * theFilter[i];
       fenergy2 += imag[i] * imag[i] * theFilter[i] * theFilter[i];
   }
   zeta = (float)fenergy2 / fenergy1;
   if (zeta > ZETA_THR)
   {
       zeta = (float)1.0;
   }
   if (zeta == 1.0f)
   {
       winLen = 1;
   }
   else
   {
       winLen = 2 * (int)((1.0f - zeta / ZETA_THR) * PSI + 0.5f) + 1;
       average = movingAverageCreate(winLen);
       for ( i = 0; i < HALF_ANAL_BLOCKL; i++)
       {
         theFilter[i] = movingAverageNext(average, theFilter[i]);
       }
       movingAverageFree(average);
   }
   memcpy(inst->smooth, theFilter, HALF_ANAL_BLOCKL * sizeof(float));
#endif
  for (i = 0; i < inst->magnLen; i++)
  {
      // 8. ��ǿ����������
      real[i] *= inst->smooth[i];
      imag[i] *= inst->smooth[i];
  }

  //�����Ľ����Խ�һ���Ż�
  CFFT_Outns[0] = real[0];
  CFFT_Outns[1] = 0;
  CFFT_Outns[inst->anaLen] = real[inst->magnLen - 1];
  CFFT_Outns[inst->anaLen + 1] = 0;
	for(i = 1;i < inst->magnLen-1; i++)
  {
    CFFT_Outns[2 * i] = real[i];
    CFFT_Outns[2 * i + 1] = imag[i];
  }
	CEVA_DSP_LIB_FLOAT_FFT_REAL_INV_OOB(7, CFFT_Outns, CFFT_InvOutns, CEVA_DSP_LIB_FLOAT_cos_sin, twi_table_float_rfft_128, bitrev_32_1024, tmp, 1);
	real[0] = CFFT_InvOutns[0] / ANAL_BLOCKL_MAX;
    for (i = 1; i < ANAL_BLOCKL_MAX; i++)
    {
        real[i] = CFFT_InvOutns[ANAL_BLOCKL_MAX - i] / ANAL_BLOCKL_MAX;
    }

  factor = (float)1.0;
  //if (inst->blockInd > END_STARTUP_LONG) {
  if (inst->blockInd > 0) {
	  energy2 = 0.0;
	  for (i = 0; i < inst->anaLen; i++) {
		  energy2 += (float)real[i] * (float)real[i];
	  }
	  gain = (float)sqrt(energy2 / (energy1 + (float)1.0));

	  if (gain > B_LIM) {
		  factor = (float)1.0 + (float)1.3 * (gain - B_LIM);
	  }
	  else {
		  factor = (float)1.0 + (float)2.0 * (gain - B_LIM);
	  }
	  if (gain * factor > (float)1.0) {
		  factor = (float)1.0 / gain;
	  }
	}

  for (i = 0; i < inst->anaLen; i++) {
    inst->syntBuf[i] += factor * WinTable[i] * (float)real[i];
  }
  for (i = 0; i < inst->blockLen; i++) {
    fout[i] = inst->syntBuf[i];
  }


  // update synthesis buffer
  memcpy(inst->syntBuf, inst->syntBuf + inst->blockLen,
          sizeof(float) * (inst->anaLen - inst->blockLen));
  memset(inst->syntBuf + inst->anaLen - inst->blockLen, 0,
          sizeof(float) * inst->blockLen);

  // convert to short
  for (i = 0; i < inst->blockLen; i++) {
    dTmp = fout[i];
    if (dTmp < INNOTALK_SPL_WORD16_MIN) {
      dTmp = INNOTALK_SPL_WORD16_MIN;
    } else if (dTmp > INNOTALK_SPL_WORD16_MAX) {
      dTmp = INNOTALK_SPL_WORD16_MAX;
    }
    outFrame[i] = (short)dTmp;
  }
  return 0;
}
