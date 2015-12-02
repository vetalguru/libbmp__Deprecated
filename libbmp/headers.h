// BMP headers

#include <stdint.h>

// BITMAP FILE HEADER
struct BITMAPFILEHEADER
{
    unsigned short bfType;
    unsigned int   bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int   bfOffBits;

    BITMAPFILEHEADER& operator = (const BITMAPFILEHEADER& arg)
    {
        bfType = arg.bfType;
        bfSize = arg.bfSize;
        bfReserved1 = arg.bfReserved1;
        bfReserved2 = arg.bfReserved2;
        bfOffBits = arg.bfOffBits;

        return *this;
    }

};

const unsigned BITMAPFILEHEADER_SIZE = 14;
