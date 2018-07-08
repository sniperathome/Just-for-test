#include "w2b.h"
#define MAXPATH 128

int main(int argc, char *argv[])
{
    FILE *pFile;
    char strPath[MAXPATH];
    WAV_CACHE *data = NULL;
    DWORD n = 0;

    if (2 == argc && (strlen(argv[1]) + 1 <= MAXPATH))
    {
        sprintf(strPath, "%s", argv[1]);
    }
    else
    {
        fflush(stdin);
        puts("Please input the .wav file name\n");
        scanf("%[^\n]", strPath);
        fflush(stdin);
        strPath[MAXPATH - 1] = '\0';
    }
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
    if (n)
    {
        printf("\nData size :%ld\n", n);
    }

    delCacheWaveFile(data);
    data = NULL;
    return 0;
}
