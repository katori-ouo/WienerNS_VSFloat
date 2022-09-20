#ifndef INNOTALK_MODULES_AUDIO_PROCESSING_NS_MAIN_SOURCE_NS_CORE_H_
#define INNOTALK_MODULES_AUDIO_PROCESSING_NS_MAIN_SOURCE_NS_CORE_H_

#include "defines.h"
#define INNOTALK_SPL_WORD16_MAX       32767
#define INNOTALK_SPL_WORD16_MIN       -32768
#define CEVAOPT 1
#include "typedefs.h"
typedef struct NSinst_t_ {

  uint32_t        fs;
  int             blockLen;			//块长度
  int             anaLen;//分析窗长度
  int             magnLen;//129，每个幅值
  float           dataBuf[ANAL_BLOCKL_MAX];//数据缓存
  float           syntBuf[ANAL_BLOCKL_MAX];//同步缓存

  // 维纳滤波有关
  float           smooth[HALF_ANAL_BLOCKL];//滤波系数
  float           overdrive;//滤波快慢程度
  float           denoiseBound;//降噪界限值
#if 1-CEVAOPT
  // fft work arrays.
  int             ip[IP_LENGTH];
  float           wfft[W_LENGTH];
#endif
  int32_t         blockInd;                           //帧索引计数器
  float           noisePrev[HALF_ANAL_BLOCKL];        //前一帧的噪声功率谱
  float           magnPrev[HALF_ANAL_BLOCKL];         //前一帧的幅度谱
  float           pmagnPrev[HALF_ANAL_BLOCKL];         //前一帧的平滑功率谱
  float           probPrev[HALF_ANAL_BLOCKL];         //前一帧的语音概率
  float           signalPrev[HALF_ANAL_BLOCKL];       //前一帧干净语音的幅度谱估计值
  float           minMagn[HALF_ANAL_BLOCKL];          //平滑功率谱的最小值

} NSinst_t;

#if FSmooth
typedef struct {
  int size;
  float sum;
  float* queue;
  uint32_t front;
  uint32_t rear;
} MovingAverage;
#endif


#ifdef __cplusplus
extern "C" {
#endif
	int InnoTalkNs_CreateN(NSinst_t** NS_inst);
int InnoTalkNs_InitCore(NSinst_t* inst, uint32_t fs);

int InnoTalkNs_ProcessCore(NSinst_t* inst,
                         short* inFrameLow,
                         short* outFrameLow);


#ifdef __cplusplus
}
#endif
#endif  // INNOTALK_MODULES_AUDIO_PROCESSING_NS_MAIN_SOURCE_NS_CORE_H_
