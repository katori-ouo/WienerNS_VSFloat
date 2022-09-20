#ifndef INNOTALK_MODULES_AUDIO_PROCESSING_NS_MAIN_SOURCE_NS_CORE_H_
#define INNOTALK_MODULES_AUDIO_PROCESSING_NS_MAIN_SOURCE_NS_CORE_H_

#include "defines.h"
#define INNOTALK_SPL_WORD16_MAX       32767
#define INNOTALK_SPL_WORD16_MIN       -32768
#define CEVAOPT 1
#include "typedefs.h"
typedef struct NSinst_t_ {

  uint32_t        fs;
  int             blockLen;			//�鳤��
  int             anaLen;//����������
  int             magnLen;//129��ÿ����ֵ
  float           dataBuf[ANAL_BLOCKL_MAX];//���ݻ���
  float           syntBuf[ANAL_BLOCKL_MAX];//ͬ������

  // ά���˲��й�
  float           smooth[HALF_ANAL_BLOCKL];//�˲�ϵ��
  float           overdrive;//�˲������̶�
  float           denoiseBound;//�������ֵ
#if 1-CEVAOPT
  // fft work arrays.
  int             ip[IP_LENGTH];
  float           wfft[W_LENGTH];
#endif
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

int InnoTalkNs_ProcessCore(NSinst_t* inst,
                         short* inFrameLow,
                         short* outFrameLow);


#ifdef __cplusplus
}
#endif
#endif  // INNOTALK_MODULES_AUDIO_PROCESSING_NS_MAIN_SOURCE_NS_CORE_H_
