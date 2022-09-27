#ifndef INNOTALK_AUDIO_CONFIG_H_
#define INNOTALK_AUDIO_CONFIG_H_

// Define C99 equivalent types, since MSVC doesn't provide stdint.h.
typedef signed char         int8_t;
typedef signed short        int16_t;
typedef signed int          int32_t;
typedef __int64             int64_t;
typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned __int64    uint64_;

#define INNOTALK_SPL_WORD16_MAX       32767
#define INNOTALK_SPL_WORD16_MIN       -32768

#define FRAME128            1

#if FRAME128
#define FRAME_LEN			128 // 帧长
#define ANAL_BLOCKL_MAX		256 // 最大分析块长度
#define HALF_ANAL_BLOCKL	129 // 块分析长度一半加一
#else
#define FRAME_LEN			64 // 帧长
#define ANAL_BLOCKL_MAX		128 // 最大分析块长度
#define HALF_ANAL_BLOCKL	65 // 块分析长度一半加一
#endif

#endif /* INNOTALK_AUDIO_CONFIG_H_ */
