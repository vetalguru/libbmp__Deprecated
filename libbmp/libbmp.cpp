#include "libbmp.h"
#include "common.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

BMPImage::BMPImage(const std::string& aFileName)
    : m_isValid(false)
    , m_bmpFile(NULL)
    , m_width(0)
    , m_height(0)
{
    m_isValid = parseFile(aFileName);
}

BMPImage::~BMPImage()
{
    if(m_bmpFile)
        fclose(m_bmpFile);
}

bool BMPImage::isValid()
{
    return m_isValid;
}

unsigned BMPImage::width()
{
    return m_width;
}

unsigned BMPImage::height()
{
    return abs(m_height);
}

bool BMPImage::parseFile(const std::string& aFileName)
{
    if(aFileName.empty())
        return false;

    m_bmpFile = fopen(aFileName.c_str(), "r");
    if(!m_bmpFile)
        return false;

    BITMAPFILEHEADER fileHeader;
    if(!parseBitmapFileHeader(m_bmpFile, fileHeader))
    {
        fclose(m_bmpFile);
        m_bmpFile = NULL;
        return false;
    }

    if (fileHeader.bfType != 0x4D42)
    {
        fclose(m_bmpFile);
        m_bmpFile = NULL;
        return false;
    }

    BITMAPINFOHEADER infoHeader;
    if(!parseBitmapInfoHeader(m_bmpFile, infoHeader))
    {
        fclose(m_bmpFile);
        m_bmpFile = NULL;
        return false;
    }

    m_width  = infoHeader.biWidth;
    m_height = infoHeader.biHeight;

    return true;
}

bool BMPImage::parseBitmapFileHeader(FILE *file, BITMAPFILEHEADER& aFileHeader)
{
    if(!file)
        return false;

    if(!fread(&aFileHeader, BITMAPFILEHEADER_SIZE, 1, file))
        return false;

    if(isBigEndian())
    {
        aFileHeader.bfType      = swapBytes_16(aFileHeader.bfType);
        aFileHeader.bfSize      = swapBytes_32(aFileHeader.bfSize);
        aFileHeader.bfReserved1 = swapBytes_16(aFileHeader.bfReserved1);
        aFileHeader.bfReserved2 = swapBytes_16(aFileHeader.bfReserved2);
        aFileHeader.bfOffBits   = swapBytes_32(aFileHeader.bfOffBits);
    }

    return true;
}

bool BMPImage::parseBitmapCoreHeader(FILE *file, BITMAPCOREHEADER& aCoreHeader)
{
    if(!file)
        return false;

    if(!fread(&aCoreHeader, BITMAPCOREHEADER_SIZE, 1, file))
        return false;

    if(isBigEndian())
    {
        aCoreHeader.biSize     = swapBytes_32(aCoreHeader.biSize);
        aCoreHeader.biWidth    = swapBytes_32(aCoreHeader.biWidth);
        aCoreHeader.biHeight   = swapBytes_32(aCoreHeader.biHeight);
        aCoreHeader.biPlanes   = swapBytes_16(aCoreHeader.biPlanes);
        aCoreHeader.biBitCount = swapBytes_16(aCoreHeader.biBitCount);
    }

    return true;
}

bool BMPImage::parseBitmapInfoHeader(FILE *file, BITMAPINFOHEADER& aInfoHeader)
{
    if(!file)
        return false;

    if(!fread(&aInfoHeader, BITMAPINFOHEADER_SIZE, 1, file))
        return false;

    if(isBigEndian())
    {
        aInfoHeader.biSize          = swapBytes_32(aInfoHeader.biSize);
        aInfoHeader.biWidth         = swapBytes_32(aInfoHeader.biWidth);
        aInfoHeader.biHeight        = swapBytes_32(aInfoHeader.biHeight);
        aInfoHeader.biPlanes        = swapBytes_16(aInfoHeader.biPlanes);
        aInfoHeader.biBitCount      = swapBytes_16(aInfoHeader.biBitCount);
        aInfoHeader.biCompression   = swapBytes_32(aInfoHeader.biCompression);
        aInfoHeader.biSizeImage     = swapBytes_32(aInfoHeader.biSizeImage);
        aInfoHeader.biXPelsPerMeter = swapBytes_32(aInfoHeader.biXPelsPerMeter);
        aInfoHeader.biYPelsPerMeter = swapBytes_32(aInfoHeader.biYPelsPerMeter);
        aInfoHeader.biClrUsed       = swapBytes_32(aInfoHeader.biClrUsed);
        aInfoHeader.biClrImportant  = swapBytes_32(aInfoHeader.biClrImportant);
    }

    return true;
}

bool BMPImage::parseBitmapV4Header(FILE *file, BITMAPV4HEADER& aV4Header)
{
    if(!file)
        return false;

    if(!fread(&aV4Header, BITMAPV4HEADER_SIZE, 1, file))
        return false;

    if(isBigEndian())
    {
        aV4Header.biSize          = swapBytes_32(aV4Header.biSize);
        aV4Header.biWidth         = swapBytes_32(aV4Header.biWidth);
        aV4Header.biHeight        = swapBytes_32(aV4Header.biHeight);
        aV4Header.biPlanes        = swapBytes_16(aV4Header.biPlanes);
        aV4Header.biBitCount      = swapBytes_16(aV4Header.biBitCount);
        aV4Header.biCompression   = swapBytes_32(aV4Header.biCompression);
        aV4Header.biSizeImage     = swapBytes_32(aV4Header.biSizeImage);
        aV4Header.biXPelsPerMeter = swapBytes_32(aV4Header.biXPelsPerMeter);
        aV4Header.biYPelsPerMeter = swapBytes_32(aV4Header.biYPelsPerMeter);
        aV4Header.biClrUsed       = swapBytes_32(aV4Header.biClrUsed);
        aV4Header.biClrImportant  = swapBytes_32(aV4Header.biClrImportant);
        aV4Header.biRedMask       = swapBytes_32(aV4Header.biRedMask);
        aV4Header.biGreenMask     = swapBytes_32(aV4Header.biGreenMask);
        aV4Header.biBlueMask      = swapBytes_32(aV4Header.biBlueMask);
        aV4Header.biAlphaMask     = swapBytes_32(aV4Header.biAlphaMask);
        aV4Header.biCSType        = swapBytes_32(aV4Header.biCSType);

        //aV4Header.biEndpoints     = aV4Header.biEndpoints;

        aV4Header.biEndpoints.ciexyzBlue.ciexyzX = aV4Header.biEndpoints.ciexyzBlue.ciexyzX;
        aV4Header.biEndpoints.ciexyzBlue.ciexyzY = aV4Header.biEndpoints.ciexyzBlue.ciexyzY;
        aV4Header.biEndpoints.ciexyzBlue.ciexyzZ = aV4Header.biEndpoints.ciexyzBlue.ciexyzZ;

        aV4Header.biEndpoints.ciexyzGreen.ciexyzX = aV4Header.biEndpoints.ciexyzGreen.ciexyzX;
        aV4Header.biEndpoints.ciexyzGreen.ciexyzY = aV4Header.biEndpoints.ciexyzGreen.ciexyzY;
        aV4Header.biEndpoints.ciexyzGreen.ciexyzZ = aV4Header.biEndpoints.ciexyzGreen.ciexyzZ;

        aV4Header.biEndpoints.ciexyzRed.ciexyzX = aV4Header.biEndpoints.ciexyzRed.ciexyzX;
        aV4Header.biEndpoints.ciexyzRed.ciexyzY = aV4Header.biEndpoints.ciexyzRed.ciexyzY;
        aV4Header.biEndpoints.ciexyzRed.ciexyzZ = aV4Header.biEndpoints.ciexyzRed.ciexyzZ;

        aV4Header.biGammaRed      = swapBytes_32(aV4Header.biGammaRed);
        aV4Header.biGammaGreen    = swapBytes_32(aV4Header.biGammaGreen);
        aV4Header.bibV4GammaBlue  = swapBytes_32(aV4Header.bibV4GammaBlue);
    }

    return true;
}
