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


// BITMAP INFO HEADER
struct BITMAPINFOHEADER
{
    unsigned int   biSize;
    int            biWidth;
    int            biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int   biCompression;
    unsigned int   biSizeImage;
    int            biXPelsPerMeter;
    int            biYPelsPerMeter;
    unsigned int   biClrUsed;
    unsigned int   biClrImportant;

    BITMAPINFOHEADER& operator = (const BITMAPINFOHEADER& arg)
    {
         biSize = arg.biSize;
         biWidth = arg.biWidth;
         biHeight = arg.biHeight;
         biPlanes = arg.biPlanes;
         biBitCount = arg.biBitCount;
         biCompression = arg.biCompression;
         biSizeImage = arg.biSizeImage;
         biXPelsPerMeter = arg.biXPelsPerMeter;
         biYPelsPerMeter = arg.biYPelsPerMeter;
         biClrUsed = arg.biClrUsed;
         biClrImportant = arg.biClrImportant;

         return *this;
    }

};

const unsigned BITMAPFILEHEADER_SIZE = 14;
const unsigned BITMAPINFOHEADER_SIZE = 40;

