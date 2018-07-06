#include "w2b.h"

int main ()
{
    FILE *pFile;
    char strPath[128];
    WAV_CACHE *data = NULL;
    DWORD n = 0;

    puts("Please input the .wav file name\n");
	scanf("%s", strPath);
	pFile = fopen(strPath, "rb");
	if (pFile != NULL)
	{
		puts("File open success\n");
	}
	else
	{
		return err(FileErr);
	}

    data = cacheWaveFile(strPath);
    n = listWavData(data);
    if(n)
    {
        printf("\nData size :%ld\n",n);
    }

    delCacheWaveFile(data);
    data = NULL;
    return 0;
}