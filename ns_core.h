#ifndef INNOTALK_MODULES_AUDIO_PROCESSING_NS_MAIN_SOURCE_NS_CORE_H_
#define INNOTALK_MODULES_AUDIO_PROCESSING_NS_MAIN_SOURCE_NS_CORE_H_

#include "audio_config.h"
#include "ceva_typedef.h"
#include "ceva_fft_lib.h"
#include "wdrc.h"

#define FSmooth				      0 //�˲�����Ƶ���ƽ������
#define SMOOTH              0 // �˲���ʼ��ϵ��
#define B_LIM               (float)0.5    // ���������������Ӽ����е���ֵ
#define SMOOTH_APY          (float)0.7    // ƽ�������׵�ƽ������
#define SMOOTH_R            (float)0.998  // ����ƽ����������Сֵ�ľ��鳣��
#define SMOOTH_BETA         (float)0.96   // ����ƽ����������Сֵ�ľ��鳣��
#define AP                  (float)0.2    // �������ʸ���ϵ��
#define G                   (float)0.1    // �������ʱ任ϵ��
#define AF                  (float)0.98   // ������������ȵľ���ϵ��
#define FILTER_SMOOTH       (float)0.9    // �����˲���ϵ���ľ��鳣��
#if FSmooth
#define ZETA_THR			(float)0.4    // ȥ�������������������ֵ
#define PSI					(float)20.0   // ȥ������������ƽ���̶�
#endif

typedef struct NSinst_t_ {

  uint32_t        fs;
  int             blockLen;			//�鳤��
  int             anaLen;//����������
  int             magnLen;//ÿ����ֵ
  float           dataBuf[ANAL_BLOCKL_MAX];//���ݻ���
  float           syntBuf[ANAL_BLOCKL_MAX];//ͬ������

  // ά���˲��й�
  float           smooth[HALF_ANAL_BLOCKL];//�˲�ϵ��
  float           overdrive;//�˲������̶�
  float           denoiseBound;//�������ֵ
  int32_t         blockInd;                           //֡����������
  float           noisePrev[HALF_ANAL_BLOCKL];        //ǰһ֡������������
  float           magnPrev[HALF_ANAL_BLOCKL];         //ǰһ֡�ķ�����
  float           pmagnPrev[HALF_ANAL_BLOCKL];         //ǰһ֡��ƽ��������
  float           probPrev[HALF_ANAL_BLOCKL];         //ǰһ֡����������
  float           signalPrev[HALF_ANAL_BLOCKL];       //ǰһ֡�ɾ������ķ����׹���ֵ
  float           minMagn[HALF_ANAL_BLOCKL];          //ƽ�������׵���Сֵ

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
