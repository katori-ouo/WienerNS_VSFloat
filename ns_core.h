#ifndef INNOTALK_MODULES_AUDIO_PROCESSING_NS_MAIN_SOURCE_NS_CORE_H_
#define INNOTALK_MODULES_AUDIO_PROCESSING_NS_MAIN_SOURCE_NS_CORE_H_

#include "audio_config.h"
#include "ceva_typedef.h"
#include "ceva_fft_lib.h"
#include "wdrc.h"

#define FSmooth				      0 //滤波器在频域的平滑操作
#define SMOOTH              0 // 滤波初始化系数
#define B_LIM               (float)0.5    // 最终能量增益因子计算中的阈值
#define SMOOTH_APY          (float)0.7    // 平滑功率谱的平滑因子
#define SMOOTH_R            (float)0.998  // 更新平滑功率谱最小值的经验常数
#define SMOOTH_BETA         (float)0.96   // 更新平滑功率谱最小值的经验常数
#define AP                  (float)0.2    // 语音概率更新系数
#define G                   (float)0.1    // 语音概率变换系数
#define AF                  (float)0.98   // 更新先验信噪比的经验系数
#define FILTER_SMOOTH       (float)0.9    // 更新滤波器系数的经验常数
#if FSmooth
#define ZETA_THR			(float)0.4    // 去除音乐噪音的信噪比阈值
#define PSI					(float)20.0   // 去除音乐噪声的平滑程度
#endif

typedef struct NSinst_t_ {

  uint32_t        fs;
  int             blockLen;			//块长度
  int             anaLen;//分析窗长度
  int             magnLen;//每个幅值
  float           dataBuf[ANAL_BLOCKL_MAX];//数据缓存
  float           syntBuf[ANAL_BLOCKL_MAX];//同步缓存

  // 维纳滤波有关
  float           smooth[HALF_ANAL_BLOCKL];//滤波系数
  float           overdrive;//滤波快慢程度
  float           denoiseBound;//降噪界限值
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
int InnoTalkNs_ProcessCore(NSinst_t* inst, short* inFrameLow, short* outFrameLow);
#ifdef __cplusplus
}
#endif
#endif  // INNOTALK_MODULES_AUDIO_PROCESSING_NS_MAIN_SOURCE_NS_CORE_H_
