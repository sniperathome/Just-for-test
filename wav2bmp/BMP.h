#ifndef _DATA_TYPE
#define _DATA_TYPE
typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef unsigned char BYTE;
typedef long LONG;
#endif

#ifndef _BMP
#define _BMP
typedef struct __BMP_FILE_HEADER
{
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffset;
} BMP_FILEHEADER;

typedef struct __BMP_INFO_HEADER
{
    DWORD biSize;
    DWORD biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biComperession;
    DWORD biSizeImage;
    DWORD biXPelsPerMeter;
    DWORD biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BMP_INFOHEADER;

typedef struct __RGBQUAD
{
    BYTE rgbBlue;
    BYTE rgbGreen;
    BYTE rgbRed;
    BYTE rgbAlpha;
} BMP_RGBQUAD;

#endif
