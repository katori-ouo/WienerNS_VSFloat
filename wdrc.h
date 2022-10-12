#ifndef INNOTALK_MODULES_AUDIO_PROCESSING_WDRC_MAIN_SOURCE_WDRC_CORE_H_
#define INNOTALK_MODULES_AUDIO_PROCESSING_WDRC_MAIN_SOURCE_WDRC_CORE_H_

#include "audio_config.h"

// WDRC的通道数(频点), 若FFT点数为128(0-127), 则64个通道分别对应1-64
#define ChannelNum          (ANAL_BLOCKL_MAX / 2)
#define FeatureNum          7              // 听力特征图的特征点个数
#define SPLC                (float)(-90)   // 声压级校准因子, -20*log10(32768)
#define AOP                 (float)90      // 数字麦克风最大声压级
#define P0                  (float)0.00002 // 基准声压2×10^-5
#define UA                  (float)0.1     // 调整攻击时间的参数
#define UR                  (float)0.95    // 调整释放时间的参数
#define TKLOW               (float)45      // IO曲线的第一个拐点
#define TKHIGH              (float)75      // IO曲线的第二个拐点
#define SPLMAX              (float)120     // 最大输出声压级
#define HT1                 (float)20      // 听阈范围0-HT1
#define HT2                 (float)40      // 听阈范围HT1-HT2
#define HT3                 (float)60      // 听阈范围HT2-HT3

typedef struct WDRCinst_t_ {

  uint32_t        fs;                       // 采样频率
  float           audiogram_f[FeatureNum];  // 听力图特征点的频率
  float           audiogram_ht[FeatureNum]; // 听力图特征点的听阈
  float           channel_ht[ChannelNum];   // 每个通道的听阈
  float           SPL_offset[ChannelNum];   // 声压级修正
  float           SPL_buffer[ChannelNum];   // 输入声压级的缓存
  // 每个输入声压级范围内的斜率和截距
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