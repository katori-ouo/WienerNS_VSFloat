#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "wdrc.h"

/**
 * @brief 计算声压级修正
 * 
 * @param inst WDRC结构体指针
 * @return int 计算成功返回0
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
 * @brief 根据听力图中特征点的频率和听阈, 计算各通道的听阈
 * 
 * @param inst WDRC结构体指针
 * @return int 计算成功则返回0
 */
int InnoTalkWdrc_GetHt(WDRCinst_t* inst)
{
    int i, j;
    float k, b;
    int audiogram_k[FeatureNum];
    float fstep = (float)inst->fs / (float)ANAL_BLOCKL_MAX; // FFT频点间隔
    // 1. 把听力图的频率值转换为FFT的频点索引
    for (i = 0; i < FeatureNum; i++)
    {
        audiogram_k[i] = (int)(inst->audiogram_f[i] / fstep);
    }
    // 2. 线性插值, 计算每个通道的听阈
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
 * @brief 根据FIG6计算每个通道的k和b
 * 
 * @param inst WDRC结构体指针
 * @return int 计算成功返回0
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
 * @brief 为wdrc结构体分配内存空间
 * 
 * @param WDRC_inst &(WDRCinst_t *)
 * @return int 分配失败返回-1, 否则返回0
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
 * @brief 初始化ns结构体
 * 
 * @param inst 指向ns结构体的指针
 * @param fs 采样频率
 * @return int  初始化失败返回-1, 否则返回0
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
 * @brief 根据输入的幅度谱计算增益
 * 
 * @param inst WDRC结构体
 * @param magn 输入幅度谱的平方
 * @return float* 计算的增益
 */
int InnoTalkWdrc_ProcessCore(WDRCinst_t* inst, float* magn, float* gain)
{
    int i;
    float spl_in, spl_out, ig;
    for (i = 0; i < ChannelNum; i++)
    {
        // 1. 计算输入声压级
        spl_in = 20.0f * log10f(sqrtf(magn[i + 1])) + inst->SPL_offset[i];
        // 2. 平滑输入声压级
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
        // 3. 根据曲线计算输出声压级
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
        // 4. 计算增益
        ig = spl_out - spl_in;
        gain[i] = powf(10.0f, ig/20.0f);
    }
    return gain;
}
