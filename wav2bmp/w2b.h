#ifndef _DATA_TYPE
#define _DATA_TYPE
typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef unsigned char BYTE;
typedef long LONG;
#endif

#define BMP_TYPE 0x4D42
#define RATIO 1 //变换比例

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BMP.h"
#include "WAVE.h"
#include "err.h"

int chkID(const char id[4]) //检查CHUNKID
{
	int i = 0;
	int j = 0;
	int outID = -1;

	char okID[5][4] =
		{
			{'R', 'I', 'F', 'F'},
			{'W', 'A', 'V', 'E'},
			{'f', 'm', 't', ' '},
			{'f', 'a', 'c', 't'},
			{'d', 'a', 't', 'a'}};
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (okID[i][j] == id[j])
			{
				outID = i;
			}
			else
			{
				outID = -1;
				break;
			}
		}
		if (outID != -1)
			return outID;
	}
	return -1;
}

WAV_CACHE *cacheWaveFile(char *path)
{
	FILE *fp = NULL;
	BYTE *cache = NULL;
	WAVE_RIFF *pHEAD = NULL;
	WAVE_FMT *pFMT = NULL;
	WAVE_FACT *pFACT = NULL;
	WAVE_DATA *pDATA = NULL;
	WAV_CACHE *pOUT = NULL;

	fp = fopen(path, "rb");
	if (NULL == fp)
	{
		err(FileErr);
		return NULL;
	}

	cache = (BYTE *)calloc(sizeof(WAVE_RIFF), sizeof(BYTE));
	if (NULL == cache)
	{
		err(MemErr);
		fclose(fp);
		return NULL;
	}

	fread(cache, sizeof(BYTE), sizeof(WAVE_RIFF), fp);
	pHEAD = (WAVE_RIFF *)cache;
	if ((chkID(pHEAD->strRiffID) != 0) || (chkID(pHEAD->strRiffType) != 1))
	{
		err(TypeErr);
		free(cache);
		fclose(fp);
		pHEAD = NULL;
		cache = NULL;
		return NULL;
	}

	cache = (BYTE *)calloc((pHEAD->dwRiffSize) - 8, sizeof(BYTE));
	if (NULL == cache)
	{
		err(MemErr);
		free(pHEAD);
		fclose(fp);
		pHEAD = NULL;
		return NULL;
	}

	fread(cache, sizeof(BYTE), (pHEAD->dwRiffSize) - 8, fp);
	pFMT = (WAVE_FMT *)cache;
	if (chkID(pFMT->strFmtID) != 2)
	{
		err(TypeErr);
		free(cache);
		free(pHEAD);
		fclose(fp);
		pFMT = NULL;
		pHEAD = NULL;
		cache = NULL;
		return NULL;
	}

	pFACT = (WAVE_FACT *)((BYTE *)pFMT + 8 + (pFMT->dwFmtSize));
	if (chkID(pFACT->strFactID) != 3) //FACT检查
	{
		if (4 == chkID(pFACT->strFactID)) //Not have FACT
		{
			pDATA = (WAVE_DATA *)pFACT;
			pFACT = NULL;
		}
		else
		{
			err(TypeErr);
			free(cache);
			free(pHEAD);
			fclose(fp);
			pFACT = NULL;
			pFMT = NULL;
			pHEAD = NULL;
			cache = NULL;
			return NULL;
		}
	}
	else
	{
		pDATA = (WAVE_DATA *)((BYTE *)pFACT + 8 + (pFACT->dwFactSize));
		if (4 != chkID(pDATA->strDataID))
		{
			err(TypeErr);
			free(cache);
			free(pHEAD);
			fclose(fp);
			pDATA = NULL;
			pFACT = NULL;
			pFMT = NULL;
			pHEAD = NULL;
			cache = NULL;
			return NULL;
		}
	}
	pDATA->pWaveData = (BYTE *)pDATA + 8;

	pOUT = (WAV_CACHE *)calloc(sizeof(WAV_CACHE), sizeof(BYTE));
	if (NULL == pOUT)
	{
		err(MemErr);
		free(cache);
		free(pHEAD);
		fclose(fp);
		pFACT = NULL;
		pFMT = NULL;
		pHEAD = NULL;
		cache = NULL;
		return NULL;
	}
	memcpy(pOUT, (BYTE *)pFMT + 8, sizeof(WAVE_FORMAT));
	pOUT->DataSize = pDATA->dwDataSize;
	pOUT->DataCache = calloc(pOUT->DataSize, sizeof(BYTE));
	if (NULL == pOUT->DataCache)
	{
		err(MemErr);
		free(cache);
		free(pHEAD);
		free(pOUT);
		fclose(fp);
		pFACT = NULL;
		pFMT = NULL;
		pHEAD = NULL;
		cache = NULL;
		pOUT = NULL;
		return NULL;
	}
	memcpy(pOUT->DataCache, pDATA->pWaveData, pOUT->DataSize);
	free(cache);
	free(pHEAD);
	fclose(fp);
	pFACT = NULL;
	pFMT = NULL;
	pHEAD = NULL;
	cache = NULL;
	return pOUT;
}

void delCacheWaveFile(WAV_CACHE *cache)
{
	if (NULL != cache)
	{
		free(cache->DataCache);
		cache->DataCache = NULL;
		free(cache);
	}
}

DWORD listWavData(WAV_CACHE *cache)
{
	DWORD n = 0;
	DWORD n_samp = 0;
	PCM_8B1C_SAMP *p81 = (PCM_8B1C_SAMP *)cache->DataCache;
	PCM_8B2C_SAMP *p82 = (PCM_8B2C_SAMP *)cache->DataCache;
	PCM_16B1C_SAMP *p161 = (PCM_16B1C_SAMP *)cache->DataCache;
	PCM_16B2C_SAMP *p162 = (PCM_16B2C_SAMP *)cache->DataCache;
	short l,r;

	if (8 == cache->Format.wBitsPerSample)
	{
		if (1 == cache->Format.wChannels)
		{
			n_samp = cache->DataSize / sizeof(PCM_8B1C_SAMP);
			for (n = 0; n < n_samp; n++)
			{
				printf("%ld\t%d\t%d\t\n", n, p81->CH0Data, p81->CH0Data);
				p81++;
			}
			p81 = NULL;
			return n;
		}

		if (2 == cache->Format.wChannels)
		{
			n_samp = cache->DataSize / sizeof(PCM_8B2C_SAMP);
			for (n = 0; n < n_samp; n++)
			{
				printf("%ld\t%d\t%d\t\n", n, p82->CH0Data, p82->CH1Data);
				p82++;
			}
			p82 = NULL;
			return n;
		}
	}

	if (16 == cache->Format.wBitsPerSample)
	{
		if (1 == cache->Format.wChannels)
		{
			n_samp = cache->DataSize / sizeof(PCM_16B1C_SAMP);
			for (n = 0; n < n_samp; n++)
			{
				l=r=p161->CH0Data;
				printf("%ld\t%d\t%d\t\n", n, l, r);
				p161++;
			}
			p161 = NULL;
			return n;
		}

		if (2 == cache->Format.wChannels)
		{
			n_samp = cache->DataSize / sizeof(PCM_16B2C_SAMP);
			for (n = 0; n < n_samp; n++)
			{
				l=p162->CH0Data;
				r=p162->CH1Data;
				printf("%ld\t%d\t%d\t\n", n, l, r);
				p162++;
			}
			p162 = NULL;
			return n;
		}
	}

	err(DecodeErr);
	p81 = NULL;
	p82 = NULL;
	p161 = NULL;
	p162 = NULL;
	return n;
}

