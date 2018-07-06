#include <stdio.h>
/*错误ID设定*/
typedef enum
{
    UnKErr = 0,
    FileErr,
    TypeErr,
    DecodeErr,
    MemErr
} ERRID;

char *errStr[] =
    {
        "Unknown err",
        "File open failed",
        "File Type Wrong",
        "Can not decode format"
        "memory allocation Wrong"
    };

int err(const ERRID errID) //错误处理
{
    puts(errStr[errID]);
    return errID;
}

