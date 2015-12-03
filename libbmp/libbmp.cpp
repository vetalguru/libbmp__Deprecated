#include "libbmp.h"
#include "common.h"
#include <cstdio>
#include <iostream>
#include <vector>

BMPImage::BMPImage(const std::string& aFileName)
    : m_isValid(false)
    , m_bmpFile(NULL)
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
