#ifndef INNOTALK_MODULES_AUDIO_PROCESSING_WDRC_MAIN_SOURCE_WDRC_CORE_H_
#define INNOTALK_MODULES_AUDIO_PROCESSING_WDRC_MAIN_SOURCE_WDRC_CORE_H_

#include "audio_config.h"

// WDRC��ͨ����(Ƶ��), ��FFT����Ϊ128(0-127), ��64��ͨ���ֱ��Ӧ1-64
#define ChannelNum          (ANAL_BLOCKL_MAX / 2)
#define FeatureNum          7              // ��������ͼ�����������
#define SPLC                (float)(-90)   // ��ѹ��У׼����, -20*log10(32768)
#define AOP                 (float)90      // ������˷������ѹ��
#define P0                  (float)0.00002 // ��׼��ѹ2��10^-5
#define UA                  (float)0.1     // ��������ʱ��Ĳ���
#define UR                  (float)0.95    // �����ͷ�ʱ��Ĳ���
#define TKLOW               (float)45      // IO���ߵĵ�һ���յ�
#define TKHIGH              (float)75      // IO���ߵĵڶ����յ�
#define SPLMAX              (float)120     // ��������ѹ��
#define HT1                 (float)20      // ���з�Χ0-HT1
#define HT2                 (float)40      // ���з�ΧHT1-HT2
#define HT3                 (float)60      // ���з�ΧHT2-HT3

typedef struct WDRCinst_t_ {

  uint32_t        fs;                       // ����Ƶ��
  float           audiogram_f[FeatureNum];  // ����ͼ�������Ƶ��
  float           audiogram_ht[FeatureNum]; // ����ͼ�����������
  float           channel_ht[ChannelNum];   // ÿ��ͨ��������
  float           SPL_offset[ChannelNum];   // ��ѹ������
  float           SPL_buffer[ChannelNum];   // ������ѹ���Ļ���
  // ÿ��������ѹ����Χ�ڵ�б�ʺͽؾ�
  float           k1[ChannelNum];
  float           k2[ChannelNum];
  float           k3[ChannelNum];
  float           b1[ChannelNum];
  float           b2[ChannelNum];
  float           b3[ChannelNum];

} WDRCinst_t;

#ifdef __cplusplus
extern "C" {
#endif
int InnoTalkWdrc_GetOffset(WDRCinst_t* inst);
int InnoTalkWdrc_GetHt(WDRCinst_t* inst);
int InnoTalkWdrc_GetKB(WDRCinst_t* inst);
int InnoTalkWdrc_CreateN(WDRCinst_t** WDRC_inst);
int InnoTalkWdrc_InitCore(WDRCinst_t* inst, uint32_t fs, float* audiogram_f, float* audiogram_ht);
int InnoTalkWdrc_ProcessCore(WDRCinst_t* inst, float* magn, float* gain);
#ifdef __cplusplus
}
#endif


#endif