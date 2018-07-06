#ifndef _DATA_TYPE
#define _DATA_TYPE
typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef unsigned char BYTE;
typedef long LONG;
#endif

#ifndef _WAVE
#define _WAVE
typedef struct __RIFF_HEADER
{
    char strRiffID[4];
    DWORD dwRiffSize;
    char strRiffType[4];
} WAVE_RIFF;

typedef struct __WAVE_FORMAT_BLOCK
{
    WORD wFormatTag;
    WORD wChannels;
    DWORD dwSamplesPerSec;
    DWORD dwAvgBytesPerSec;
    WORD wBlockAlign;
    WORD wBitsPerSample;
} WAVE_FORMAT;

typedef struct __FMT_BLOCK
{
    char strFmtID[4];
    DWORD dwFmtSize;
    WAVE_FORMAT wavFormat;
} WAVE_FMT;

typedef struct __WAVE_FACT_BLOCK
{
    char strFactID[4];
    DWORD dwFactSize;
    void *pFactData;
} WAVE_FACT;

typedef struct __WAVE_DATA_BLOCK
{
    char strDataID[4];
    DWORD dwDataSize;
    void *pWaveData;
} WAVE_DATA;

typedef struct __PCM8BIT1CH //8位单声道PCM样本结构
{
    BYTE CH0Data;
} PCM_8B1C_SAMP;

typedef struct __PCM8BIT2CH //8位双声道PCM样本结构
{
    BYTE CH0Data;
    BYTE CH1Data;
} PCM_8B2C_SAMP;

typedef struct __PCM16BIT1CH //16位单声道PCM样本结构
{
    WORD CH0Data;
} PCM_16B1C_SAMP;

typedef struct __PCM16BIT2CH //16位双声道PCM样本结构
{
    WORD CH0Data;
    WORD CH1Data;
} PCM_16B2C_SAMP;

typedef struct __CODE_FORMAT
{
    WORD wFormatTag;
    char *strName;
} CODE_FORMAT;
CODE_FORMAT CODE_FORMAT_LIST[104] =
    {
        {0x0,"Microsoft Unknown Wave Format"},
        {0x1,"Microsoft PCM Format"},
        {0x2,"Microsoft ADPCM Format"},
        {0x3,"IEEE Float"},
        {0x4,"Compaq Computer\'s VSELP"},
        {0x5,"IBM CVSD"},
        {0x6,"Microsoft ALAW"},
        {0x7,"Microsoft MULAW"},
        {0x10,"OKI ADPCM"},
        {0x11,"Intel\'s DVI ADPCM"},
        {0x12,"Videologic\'s MediaSpace ADPCM"},
        {0x13,"Sierra ADPCM"},
        {0x14,"G.723 ADPCM"},
        {0x15,"DSP Solution\'s DIGISTD"},
        {0x16,"DSP Solution\'s DIGIFIX"},
        {0x17,"Dialogic OKI ADPCM"},
        {0x18,"MediaVision ADPCM"},
        {0x19,"HP CU"},
        {0x20,"Yamaha ADPCM"},
        {0x21,"Speech Compression\'s Sonarc"},
        {0x22,"DSP Group\'s True Speech"},
        {0x23,"Echo Speech\'s EchoSC1"},
        {0x24,"Audiofile AF36"},
        {0x25,"APTX"},
        {0x26,"AudioFile AF10"},
        {0x27,"Prosody 1612"},
        {0x28,"LRC"},
        {0x30,"Dolby AC2"},
        {0x31,"GSM610"},
        {0x32,"MSNAudio"},
        {0x33,"Antex ADPCME"},
        {0x34,"Control Res VQLPC"},
        {0x35,"Digireal"},
        {0x36,"DigiADPCM"},
        {0x37,"Control Res CR10"},
        {0x38,"NMS VBXADPCM"},
        {0x39,"Roland RDAC"},
        {0x03A,"EchoSC3"},
        {0x03B,"Rockwell ADPCM"},
        {0x03C,"Rockwell Digit LK"},
        {0x03D,"Xebec"},
        {0x40,"Antex Electronics G.721"},
        {0x41,"G.728 CELP"},
        {0x42,"MSG723"},
        {0x50,"MPEG"},
        {0x52,"RT24"},
        {0x53,"PAC"},
        {0x55,"MPEG Layer 3"},
        {0x59,"Lucent G.723"},
        {0x60,"Cirrus"},
        {0x61,"ESPCM"},
        {0x62,"Voxware"},
        {0x63,"Canopus Atrac"},
        {0x64,"G.726 ADPCM"},
        {0x65,"G.722 ADPCM"},
        {0x66,"DSAT"},
        {0x67,"DSAT Display"},
        {0x69,"Voxware Byte Aligned"},
        {0x70,"Voxware AC8"},
        {0x71,"Voxware AC10"},
        {0x72,"Voxware AC16"},
        {0x73,"Voxware AC20"},
        {0x74,"Voxware MetaVoice"},
        {0x75,"Voxware MetaSound"},
        {0x76,"Voxware RT29HW"},
        {0x77,"Voxware VR12"},
        {0x78,"Voxware VR18"},
        {0x79,"Voxware TQ40"},
        {0x80,"Softsound"},
        {0x81,"Voxware TQ60"},
        {0x82,"MSRT24"},
        {0x83,"G.729A"},
        {0x84,"MVI MV12"},
        {0x85,"DF G.726"},
        {0x86,"DF GSM610"},
        {0x88,"ISIAudio"},
        {0x89,"Onlive"},
        {0x91,"SBC24"},
        {0x92,"Dolby AC3 SPDIF"},
        {0x97,"ZyXEL ADPCM"},
        {0x98,"Philips LPCBB"},
        {0x99,"Packed"},
        {0x100,"Rhetorex ADPCM"},
        {0x101,"BeCubed Software\'s IRAT"},
        {0x111,"Vivo G.723"},
        {0x112,"Vivo Siren"},
        {0x123,"Digital G.723"},
        {0x200,"Creative ADPCM"},
        {0x202,"Creative FastSpeech8"},
        {0x203,"Creative FastSpeech10"},
        {0x220,"Quarterdeck"},
        {0x300,"FM Towns Snd"},
        {0x400,"BTV Digital"},
        {0x680,"VME VMPCM"},
        {0x1000,"OLIGSM"},
        {0x1001,"OLIADPCM"},
        {0x1002,"OLICELP"},
        {0x1003,"OLISBC"},
        {0x1004,"OLIOPR"},
        {0x1100,"LH Codec"},
        {0x1400,"Norris"},
        {0x1401,"ISIAudio"},
        {0x1500,"Soundspace Music Compression"},
        {0x2000,"DVM"}
    };

typedef struct __WAV_CACHE
{
    WAVE_FORMAT Format;
    DWORD DataSize;
    void * DataCache;
} WAV_CACHE;
#endif
