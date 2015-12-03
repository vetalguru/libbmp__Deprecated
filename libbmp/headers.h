// BMP headers

#ifndef BMP_HEADERS_H
#define BMP_HEADERS_H

#include <stdint.h>
#include "common.h"

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

    void changeBytesOrder()
    {
        bfType      = swapBytes_16(bfType);
        bfSize      = swapBytes_32(bfSize);
        bfReserved1 = swapBytes_16(bfReserved1);
        bfReserved2 = swapBytes_16(bfReserved2);
        bfOffBits   = swapBytes_32(bfOffBits);
    }

};

// BITMAP CORE HEADER
struct BITMAPCOREHEADER
{
    unsigned int   biSize;
    int            biWidth;
    int            biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;

    BITMAPCOREHEADER& operator = (const BITMAPCOREHEADER& arg)
    {
        biSize     = arg.biSize;
        biWidth    = arg.biWidth;
        biHeight   = arg.biHeight;
        biPlanes   = arg.biPlanes;
        biBitCount = arg.biBitCount;

        return *this;
    }

    void changeBytesOrder()
    {
        biSize     = swapBytes_32(biSize);
        biWidth    = swapBytes_32(biWidth);
        biHeight   = swapBytes_32(biHeight);
        biPlanes   = swapBytes_16(biPlanes);
        biBitCount = swapBytes_16(biBitCount);
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
         biSize          = arg.biSize;
         biWidth         = arg.biWidth;
         biHeight        = arg.biHeight;
         biPlanes        = arg.biPlanes;
         biBitCount      = arg.biBitCount;
         biCompression   = arg.biCompression;
         biSizeImage     = arg.biSizeImage;
         biXPelsPerMeter = arg.biXPelsPerMeter;
         biYPelsPerMeter = arg.biYPelsPerMeter;
         biClrUsed       = arg.biClrUsed;
         biClrImportant  = arg.biClrImportant;

         return *this;
    }

    void changeBytesOrder()
    {
        biSize          = swapBytes_32(biSize);
        biWidth         = swapBytes_32(biWidth);
        biHeight        = swapBytes_32(biHeight);
        biPlanes        = swapBytes_16(biPlanes);
        biBitCount      = swapBytes_16(biBitCount);
        biCompression   = swapBytes_32(biCompression);
        biSizeImage     = swapBytes_32(biSizeImage);
        biXPelsPerMeter = swapBytes_32(biXPelsPerMeter);
        biYPelsPerMeter = swapBytes_32(biYPelsPerMeter);
        biClrUsed       = swapBytes_32(biClrUsed);
        biClrImportant  = swapBytes_32(biClrImportant);
    }

};

// BITMAP V4 HEADER
struct CIEXYZ
{
    typedef int FXPT2DOT30;

    FXPT2DOT30 ciexyzX;
    FXPT2DOT30 ciexyzY;
    FXPT2DOT30 ciexyzZ;

    CIEXYZ& operator = (const CIEXYZ& arg)
    {
        ciexyzX = arg.ciexyzX;
        ciexyzY = arg.ciexyzY;
        ciexyzZ = arg.ciexyzZ;

        return *this;
    }

    void changeBytesOrder()
    {
        ciexyzX = swapBytes_32(ciexyzX);
        ciexyzY = swapBytes_32(ciexyzY);
        ciexyzZ = swapBytes_32(ciexyzZ);
    }
};


struct CIEXYZTRIPLE
{
    CIEXYZ ciexyzRed;
    CIEXYZ ciexyzGreen;
    CIEXYZ ciexyzBlue;

    CIEXYZTRIPLE& operator = (const CIEXYZTRIPLE& arg)
    {
        ciexyzRed   = arg.ciexyzRed;
        ciexyzGreen = arg.ciexyzGreen;
        ciexyzBlue  = arg.ciexyzBlue;
    }

    void changeBytesOrder()
    {
        ciexyzRed.changeBytesOrder();
        ciexyzGreen.changeBytesOrder();
        ciexyzBlue.changeBytesOrder();
    }
};

struct BITMAPV4HEADER
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
    unsigned int   biRedMask;
    unsigned int   biGreenMask;
    unsigned int   biBlueMask;
    unsigned int   biAlphaMask;
    unsigned int   biCSType;
    CIEXYZTRIPLE   biEndpoints;
    unsigned int   biGammaRed;
    unsigned int   biGammaGreen;
    unsigned int   bibV4GammaBlue;

    BITMAPV4HEADER& operator = (const BITMAPV4HEADER& arg)
    {
        biSize          = arg.biSize;
        biWidth         = arg.biWidth;
        biHeight        = arg.biHeight;
        biPlanes        = arg.biPlanes;
        biBitCount      = arg.biBitCount;
        biCompression   = arg.biCompression;
        biSizeImage     = arg.biSizeImage;
        biXPelsPerMeter = arg.biXPelsPerMeter;
        biYPelsPerMeter = arg.biYPelsPerMeter;
        biClrUsed       = arg.biClrUsed;
        biClrImportant  = arg.biClrImportant;
        biRedMask       = arg.biRedMask;
        biGreenMask     = arg.biGreenMask;
        biBlueMask      = arg.biBlueMask;
        biAlphaMask     = arg.biAlphaMask;
        biCSType        = arg.biCSType;
        biEndpoints     = arg.biEndpoints;
        biGammaRed      = arg.biGammaRed;
        biGammaGreen    = arg.biGammaGreen;
        bibV4GammaBlue  = arg.bibV4GammaBlue;

        return *this;
    }

    void changeBytesOrder()
    {
        biSize          = swapBytes_32(biSize);
        biWidth         = swapBytes_32(biWidth);
        biHeight        = swapBytes_32(biHeight);
        biPlanes        = swapBytes_16(biPlanes);
        biBitCount      = swapBytes_16(biBitCount);
        biCompression   = swapBytes_32(biCompression);
        biSizeImage     = swapBytes_32(biSizeImage);
        biXPelsPerMeter = swapBytes_32(biXPelsPerMeter);
        biYPelsPerMeter = swapBytes_32(biYPelsPerMeter);
        biClrUsed       = swapBytes_32(biClrUsed);
        biClrImportant  = swapBytes_32(biClrImportant);
        biRedMask       = swapBytes_32(biRedMask);
        biGreenMask     = swapBytes_32(biGreenMask);
        biBlueMask      = swapBytes_32(biBlueMask);
        biAlphaMask     = swapBytes_32(biAlphaMask);
        biCSType        = swapBytes_32(biCSType);

        biEndpoints.changeBytesOrder();

        biGammaRed      = swapBytes_32(biGammaRed);
        biGammaGreen    = swapBytes_32(biGammaGreen);
        bibV4GammaBlue  = swapBytes_32(bibV4GammaBlue);
    }

};

// BITMAP V5 HEADER
struct BITMAPV5HEADER
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
    unsigned int   biRedMask;
    unsigned int   biGreenMask;
    unsigned int   biBlueMask;
    unsigned int   biAlphaMask;
    unsigned int   biCSType;
    CIEXYZTRIPLE   biEndpoints;
    unsigned int   biGammaRed;
    unsigned int   biGammaGreen;
    unsigned int   biGammaBlue;
    unsigned int   biIntent;
    unsigned int   biProfileData;
    unsigned int   biProfileSize;
    unsigned int   biReserved;


    BITMAPV5HEADER& operator = (const BITMAPV5HEADER& arg)
    {
        biSize          = arg.biSize;
        biWidth         = arg.biWidth;
        biHeight        = arg.biHeight;
        biPlanes        = arg.biPlanes;
        biBitCount      = arg.biBitCount;
        biCompression   = arg.biCompression;
        biSizeImage     = arg.biSizeImage;
        biXPelsPerMeter = arg.biXPelsPerMeter;
        biYPelsPerMeter = arg.biYPelsPerMeter;
        biClrUsed       = arg.biClrUsed;
        biClrImportant  = arg.biClrImportant;
        biRedMask       = arg.biRedMask;
        biGreenMask     = arg.biGreenMask;
        biBlueMask      = arg.biBlueMask;
        biAlphaMask     = arg.biAlphaMask;
        biCSType        = arg.biCSType;
        biEndpoints     = arg.biEndpoints;
        biGammaRed      = arg.biGammaRed;
        biGammaGreen    = arg.biGammaGreen;
        biGammaBlue     = arg.biGammaBlue;
        biIntent        = arg.biIntent;
        biProfileData   = arg.biProfileData;
        biProfileSize   = arg.biProfileSize;
        biReserved      = arg.biReserved;

        return *this;
    }

    void changeBytesOrder()
    {
        biSize          = swapBytes_32(biSize);
        biWidth         = swapBytes_32(biWidth);
        biHeight        = swapBytes_32(biHeight);
        biPlanes        = swapBytes_16(biPlanes);
        biBitCount      = swapBytes_16(biBitCount);
        biCompression   = swapBytes_32(biCompression);
        biSizeImage     = swapBytes_32(biSizeImage);
        biXPelsPerMeter = swapBytes_32(biXPelsPerMeter);
        biYPelsPerMeter = swapBytes_32(biYPelsPerMeter);
        biClrUsed       = swapBytes_32(biClrUsed);
        biClrImportant  = swapBytes_32(biClrImportant);
        biRedMask       = swapBytes_32(biRedMask);
        biGreenMask     = swapBytes_32(biGreenMask);
        biBlueMask      = swapBytes_32(biBlueMask);
        biAlphaMask     = swapBytes_32(biAlphaMask);
        biCSType        = swapBytes_32(biCSType);

        biEndpoints.changeBytesOrder();

        biGammaRed      = swapBytes_32(biGammaRed);
        biGammaGreen    = swapBytes_32(biGammaGreen);
        biGammaBlue     = swapBytes_32(biGammaBlue);
        biIntent        = swapBytes_32(biIntent);
        biProfileData   = swapBytes_32(biProfileData);
        biProfileSize   = swapBytes_32(biProfileSize);
        biReserved      = swapBytes_32(biReserved);
    }

};


const unsigned BITMAPFILEHEADER_SIZE = 14;

const unsigned BITMAPCOREHEADER_SIZE = 12;
const unsigned BITMAPINFOHEADER_SIZE = 40;
const unsigned BITMAPV4HEADER_SIZE   = 108;
const unsigned BITMAPV5HEADER_SIZE   = 124;

#endif // BMP_HEADERS_H
