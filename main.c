// InnoTalkAudioTest.cpp : Defines the entry point for the console application.
//
//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#include "ns_core.h"
#define LEN128_PACKET (128)
#define LEN256_PACKET (256)

void InnoTalkNS16KSample(char *szFileIn, char *szFileOut, int nSample, int nMode)
{

	NSinst_t *pNS_inst = NULL;
	short shInL[LEN128_PACKET];
	short shOutL[LEN128_PACKET] = { 0 };
	int i = 0;
	FILE *fpIn = NULL;
	FILE *fpOut = NULL;

	do
	{
		InnoTalkNs_CreateN(&pNS_inst);
		InnoTalkNs_InitCore(pNS_inst, nSample);

		fpIn = fopen(szFileIn, "rb");
		fpOut = fopen(szFileOut, "wb");
		if (NULL == fpIn || NULL == fpOut)
		{
			printf("open file err \n");
			break;
		}

		while (1)
		{
			if (LEN128_PACKET == fread(shInL, sizeof(short), LEN128_PACKET, fpIn))
			{
				InnoTalkNs_ProcessCore(pNS_inst, shInL, shOutL);
				fwrite(shOutL, sizeof(short), LEN128_PACKET, fpOut);
			}
			else
			{
				break;
			}
		}
	} while (0);

	//InnoTalkNs_Free(pNS_inst);
	fclose(fpIn);
	fclose(fpOut);
}

int main()
{
	printf("processing...\n");
	InnoTalkNS16KSample("TelinkTest.pcm", "TelinkTest_0920.pcm", 16000, 3);
	printf("end!\n");

	getchar();
	return 0;
}
