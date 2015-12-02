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

    return true;
}

bool BMPImage::parseBitmapFileHeader(FILE *file, BITMAPFILEHEADER& aFileHeader)
{
    if(!file)
        return false;

    if(!fread(&aFileHeader, sizeof(BITMAPFILEHEADER), 1, file))
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
