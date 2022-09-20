// InnoTalkAudioTest.cpp : Defines the entry point for the console application.
//
//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "ns_core.h"

void InnoTalkNS16KSample(char *szFileIn, char *szFileOut, uint32_t nSample)
{

	NSinst_t *pNS_inst = NULL;
	short shInL[FRAME_LEN];
	short shOutL[FRAME_LEN] = { 0 };
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
			if (FRAME_LEN == fread(shInL, sizeof(short), FRAME_LEN, fpIn))
			{
				InnoTalkNs_ProcessCore(pNS_inst, shInL, shOutL);
				fwrite(shOutL, sizeof(short), FRAME_LEN, fpOut);
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
	InnoTalkNS16KSample("TelinkTest.pcm", "TelinkTest_0920.pcm", (uint32_t)16000);
	printf("end!\n");

	getchar();
	return 0;
}
