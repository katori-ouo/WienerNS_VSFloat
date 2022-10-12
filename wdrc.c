#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "wdrc.h"

/**
 * @brief ������ѹ������
 * 
 * @param inst WDRC�ṹ��ָ��
 * @return int ����ɹ�����0
 */
int InnoTalkWdrc_GetOffset(WDRCinst_t* inst)
{
    int i;
    for (i = 0; i < ChannelNum; i++)
    {
        inst->SPL_offset[i] = AOP+ SPLC;
    }
    return 0;
}

/**
 * @brief ��������ͼ���������Ƶ�ʺ�����, �����ͨ��������
 * 
 * @param inst WDRC�ṹ��ָ��
 * @return int ����ɹ��򷵻�0
 */
int InnoTalkWdrc_GetHt(WDRCinst_t* inst)
{
    int i, j;
    float k, b;
    int audiogram_k[FeatureNum];
    float fstep = (float)inst->fs / (float)ANAL_BLOCKL_MAX; // FFTƵ����
    // 1. ������ͼ��Ƶ��ֵת��ΪFFT��Ƶ������
    for (i = 0; i < FeatureNum; i++)
    {
        audiogram_k[i] = (int)(inst->audiogram_f[i] / fstep);
    }
    // 2. ���Բ�ֵ, ����ÿ��ͨ��������
    for (i = 1; i <= ChannelNum; i++)
    {
        for (j = 0; j < FeatureNum; j++)
        {
            if (i == audiogram_k[j])
            {
                inst->channel_ht[i - 1] = inst->audiogram_ht[j];
                break;
            }
            if (i > audiogram_k[j] && i < audiogram_k[j + 1])
            {
                k = (inst->audiogram_ht[j + 1] - inst->audiogram_ht[j]) / (audiogram_k[j + 1] - audiogram_k[j]);
                b = inst->audiogram_ht[j] - k * (float)audiogram_k[j];
                inst->channel_ht[i - 1] = k * (float)i + b;
                break;
            }
        }
    }
    return 0;
}

/**
 * @brief ����FIG6����ÿ��ͨ����k��b
 * 
 * @param inst WDRC�ṹ��ָ��
 * @return int ����ɹ�����0
 */
int InnoTalkWdrc_GetKB(WDRCinst_t* inst)
{
    int i;
    float ig40, ig65, ig90;
    float splout40, splout65, splout90;
    float tklout, tkhout;
    for ( i = 0; i < ChannelNum; i++)
    {
        inst->k1[i] = 1.0f;
        if (inst->channel_ht[i] < 20)
        {
            inst->b1[i] = 0.0f;
            inst->k2[i] = 1.0f;
            inst->b2[i] = 0.0f;
            inst->k3[i] = 1.0f;
            inst->b3[i] = 0.0f;
        }
        else if (inst->channel_ht[i] < 40)
        {
            ig40 = inst->channel_ht[i] - 20.0f;
            splout40 = 40.0f + ig40;
            inst->b1[i] = splout40 - 40.0f;
            tklout = TKLOW + inst->b1[i];

            ig65 = 0.6f * (inst->channel_ht[i] - 20.0f);
            splout65 = 65.0f + ig65;
            inst->k2[i] = (splout65 - tklout) / (65.0f - TKLOW);
            inst->b2[i] = (tklout * 65.0f - splout65 * TKLOW) / (65.0f - TKLOW);
            tkhout = inst->k2[i] * TKHIGH + inst->b2[i];

            ig90 = 0.0f;
            splout90 = 90.0f + ig90;
            inst->k3[i] = (splout90 - tkhout) / (90.0f - TKHIGH);
            inst->b3[i] = (tkhout * 90.0f - splout90 * TKHIGH) / (90.0f - TKHIGH);
        }
        else if (inst->channel_ht[i] < 60)
        {
            ig40 = inst->channel_ht[i] - 20.0f;
            splout40 = 40.0f + ig40;
            inst->b1[i] = splout40 - 40.0f;
            tklout = TKLOW + inst->b1[i];

            ig65 = 0.6f * (inst->channel_ht[i] - 20.0f);
            splout65 = 65.0f + ig65;
            inst->k2[i] = (splout65 - tklout) / (65.0f - TKLOW);
            inst->b2[i] = (tklout * 65.0f - splout65 * TKLOW) / (65.0f -TKLOW);
            tkhout = inst->k2[i] * TKHIGH + inst->b2[i];

            ig90 = 0.1f * powf(inst->channel_ht[i] - 40.0f, 1.4f);
            splout90 = 90.0f + ig90;
            inst->k3[i] = (splout90 - tkhout) / (90.0f - TKHIGH);
            inst->b3[i] = (tkhout * 90.0f - splout90 * TKHIGH) / (90.0f - TKHIGH);
        }
        else
        {
            ig40 = inst->channel_ht[i] - 20.0f - 0.5f * (inst->channel_ht[i] - 60.0f);
            splout40 = 40.0f + ig40;
            inst->b1[i] = splout40 - 40.0f;
            tklout = TKLOW + inst->b1[i];

            ig65 = 0.8f * inst->channel_ht[i] - 23.0f;
            splout65 = 65.0f + ig65;
            inst->k2[i] = (splout65 - tklout) / (65.0f - TKLOW);
            inst->b2[i] = (tklout * 65.0f - splout65 * TKLOW) / (65.0f -TKLOW);
            tkhout = inst->k2[i] * TKHIGH + inst->b2[i];

            ig90 = 0.1f * powf(inst->channel_ht[i] - 40.0f, 1.4f);
            splout90 = 90.0f + ig90;
            inst->k3[i] = (splout90 - tkhout) / (90.0f - TKHIGH);
            inst->b3[i] = (tkhout * 90.0f - splout90 * TKHIGH) / (90.0f - TKHIGH);
        }
    }
    return 0;
}

/**
 * @brief Ϊwdrc�ṹ������ڴ�ռ�
 * 
 * @param WDRC_inst &(WDRCinst_t *)
 * @return int ����ʧ�ܷ���-1, ���򷵻�0
 */
int InnoTalkWdrc_CreateN(WDRCinst_t** WDRC_inst)
{
	*WDRC_inst = (WDRCinst_t*)malloc(sizeof(WDRCinst_t));
	if (*WDRC_inst != NULL)
    {
		return 0;
	}
	else
    {
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
int InnoTalkWdrc_InitCore(WDRCinst_t* inst, uint32_t fs, float* audiogram_f, float* audiogram_ht)
{
  if (inst == NULL)
  {
    return -1;
  }
  // Initialization of struct
  inst->fs = fs;
  memcpy(inst->audiogram_f, audiogram_f, sizeof(float) * FeatureNum);
  memcpy(inst->audiogram_ht, audiogram_ht, sizeof(float) * FeatureNum);
  memset(inst->SPL_buffer, 0.0f, sizeof(float) * ChannelNum);
  InnoTalkWdrc_GetHt(inst);
  InnoTalkWdrc_GetKB(inst);
  InnoTalkWdrc_GetOffset(inst);
  return 0;
}

/**
 * @brief ��������ķ����׼�������
 * 
 * @param inst WDRC�ṹ��
 * @param magn ��������׵�ƽ��
 * @return float* ���������
 */
int InnoTalkWdrc_ProcessCore(WDRCinst_t* inst, float* magn, float* gain)
{
    int i;
    float spl_in, spl_out, ig;
    for (i = 0; i < ChannelNum; i++)
    {
        // 1. ����������ѹ��
        spl_in = 20.0f * log10f(sqrtf(magn[i + 1])) + inst->SPL_offset[i];
        // 2. ƽ��������ѹ��
        if(spl_in > inst->SPL_buffer[i])
        {
            spl_in = (1.0f - UA) * spl_in + UA * inst->SPL_buffer[i];
        }
        else
        {
            spl_in = (1.0f - UR) * spl_in + UR * inst->SPL_buffer[i];
        }
        spl_in = spl_in > 0.0f ? spl_in : 0.0f;
        inst->SPL_buffer[i] = spl_in;
        // 3. �������߼��������ѹ��
        if (spl_in < TKLOW)
        {
            spl_out = inst->k1[i] * spl_in + inst->b1[i];
        }
        else if (spl_in < TKHIGH)
        {
            spl_out = inst->k2[i] * spl_in + inst->b2[i];
        }
        else
        {
            spl_out = inst->k3[i] * spl_in + inst->b3[i];
        }
        spl_out = spl_out < SPLMAX ? spl_out : SPLMAX;
        // 4. ��������
        ig = spl_out - spl_in;
        gain[i] = powf(10.0f, ig/20.0f);
    }
    return gain;
}
