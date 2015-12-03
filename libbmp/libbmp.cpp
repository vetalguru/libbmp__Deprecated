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
        aFileHeader.changeBytesOrder();

    return true;
}

bool BMPImage::parseBitmapCoreHeader(FILE *file, BITMAPCOREHEADER& aCoreHeader)
{
    if(!file)
        return false;

    if(!fread(&aCoreHeader, BITMAPCOREHEADER_SIZE, 1, file))
        return false;

    if(isBigEndian())
        aCoreHeader.changeBytesOrder();

    return true;
}

bool BMPImage::parseBitmapInfoHeader(FILE *file, BITMAPINFOHEADER& aInfoHeader)
{
    if(!file)
        return false;

    if(!fread(&aInfoHeader, BITMAPINFOHEADER_SIZE, 1, file))
        return false;

    if(isBigEndian())
        aInfoHeader.changeBytesOrder();

    return true;
}

bool BMPImage::parseBitmapV4Header(FILE *file, BITMAPV4HEADER& aV4Header)
{
    if(!file)
        return false;

    if(!fread(&aV4Header, BITMAPV4HEADER_SIZE, 1, file))
        return false;

    if(isBigEndian())
        aV4Header.changeBytesOrder();

    return true;
}
