#include "libbmp.h"
#include "common.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdio.h>

BMPImage::BMPImage(const std::string& aFileName)
    : m_isValid(false)
    , m_bmpFile(NULL)
    , m_width(0)
    , m_height(0)
    , m_imageSize(0)
    , m_bitCount(0)
    , m_compresionType(BI_RGB)
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

unsigned short BMPImage::fileHeaderType()
{
    return m_fileHeader.bfType;
}

unsigned int   BMPImage::fileHeaderSize()
{
    return m_fileHeader.bfSize;
}

unsigned short BMPImage::fileHeaderBitsOffset()
{
    return m_fileHeader.bfOffBits;
}

unsigned BMPImage::width()
{
    return m_width;
}

unsigned BMPImage::height()
{
    return abs(m_height);
}

unsigned short BMPImage::bitCount()
{
    return m_bitCount;
}

BMPImage::CompressionType BMPImage::compressionType()
{
   return m_compresionType;
}

bool BMPImage::parseFile(const std::string& aFileName)
{
    if(aFileName.empty())
        return false;

    m_bmpFile = fopen(aFileName.c_str(), "rb");
    if(!m_bmpFile)
        return false;

    // GET FILE HEADER
    if(!decodeBitmapFileHeader(m_bmpFile, m_fileHeader))
    {
        fclose(m_bmpFile);
        m_bmpFile = NULL;
        return false;
    }

    if (m_fileHeader.bfType != 0x4D42)
    {
        fclose(m_bmpFile);
        m_bmpFile = NULL;
        return false;
    }

    if(!decodeBitmapInfoHeader(m_bmpFile))
        return false;

    return true;
}

bool BMPImage::decodeBitmapFileHeader(FILE *file, BITMAPFILEHEADER& aFileHeader)
{
    if(!file)
        return false;

    bool result = true;
    result &= fread(&aFileHeader.bfType,      2, 1, file);
    result &= fread(&aFileHeader.bfSize,      4, 1, file);
    result &= fread(&aFileHeader.bfReserved1, 2, 1, file);
    result &= fread(&aFileHeader.bfReserved2, 2, 1, file);
    result &= fread(&aFileHeader.bfOffBits,   4, 1, file);

    if(isBigEndian())
        aFileHeader.changeBytesOrder();

    return result;
}

bool BMPImage::decodeBitmapInfoHeader(FILE *file)
{
    if(!file)
        return false;

    fpos_t file_loc;
    if(fgetpos(m_bmpFile, &file_loc))
    {
        fclose(m_bmpFile);
        m_bmpFile = NULL;
        return false;
    }

    unsigned int headerSize = 0;
    if(!fread(&headerSize, 4, 1, m_bmpFile))
    {
        fclose(m_bmpFile);
        m_bmpFile = NULL;
        return false;
    }

    if(fsetpos(m_bmpFile, &file_loc))
    {
        fclose(m_bmpFile);
        m_bmpFile = NULL;
        return false;
    }

    switch(headerSize)
    {
        case BITMAPCOREHEADER_SIZE:
        {
            BITMAPCOREHEADER coreHeader;
            if(!parseBitmapCoreHeader(m_bmpFile, coreHeader))
            {
                fclose(m_bmpFile);
                m_bmpFile = NULL;
                return false;
            }

            m_width  = coreHeader.biWidth;
            m_height = coreHeader.biHeight;
            m_bitCount = coreHeader.biBitCount;

            break;
        }
        case BITMAPINFOHEADER_SIZE:
        {
            BITMAPINFOHEADER infoHeader;
            if(!parseBitmapInfoHeader(m_bmpFile, infoHeader))
            {
                fclose(m_bmpFile);
                m_bmpFile = NULL;
                return false;
            }

            m_width  = infoHeader.biWidth;
            m_height = infoHeader.biHeight;
            m_imageSize = infoHeader.biSizeImage;
            m_bitCount = infoHeader.biBitCount;
            m_compresionType = geTypeByIndex(infoHeader.biCompression);

            break;
        }
        case BITMAPV4HEADER_SIZE:
        {
            BITMAPV4HEADER v4Header;
            if(!parseBitmapV4Header(m_bmpFile, v4Header))
            {
                fclose(m_bmpFile);
                m_bmpFile = NULL;
                return false;
            }

            m_width  = v4Header.biWidth;
            m_height = v4Header.biHeight;
            m_imageSize = v4Header.biSizeImage;
            m_bitCount = v4Header.biBitCount;
            m_compresionType = geTypeByIndex(v4Header.biCompression);

            break;
        }
        case BITMAPV5HEADER_SIZE:
        {
            BITMAPV5HEADER v5Header;
            if(!parseBitmapV5Header(m_bmpFile, v5Header))
            {
                fclose(m_bmpFile);
                m_bmpFile = NULL;
                return false;
            }

            m_width  = v5Header.biWidth;
            m_height = v5Header.biHeight;
            m_imageSize = v5Header.biSizeImage;
            m_bitCount = v5Header.biBitCount;
            m_compresionType = geTypeByIndex(v5Header.biCompression);

            break;
        }
        default:
        {
            fclose(m_bmpFile);
            m_bmpFile = NULL;
            return false;
        }
    }

    if(!m_imageSize)
        m_imageSize = (m_width * m_bitCount + m_width % 4) * abs(m_height);

    return true;
}

bool BMPImage::parseBitmapCoreHeader(FILE *file, BITMAPCOREHEADER& aCoreHeader)
{
    if(!file)
        return false;

    bool result = true;
    result &= fread(&aCoreHeader.biSize,     4, 1, file);
    result &= fread(&aCoreHeader.biWidth,    2, 1, file);
    result &= fread(&aCoreHeader.biHeight,   2, 1, file);
    result &= fread(&aCoreHeader.biPlanes,   2, 1, file);
    result &= fread(&aCoreHeader.biBitCount, 2, 1, file);

    if(isBigEndian())
        aCoreHeader.changeBytesOrder();

    return true;
}

bool BMPImage::parseBitmapInfoHeader(FILE *file, BITMAPINFOHEADER& aInfoHeader)
{
    if(!file)
        return false;

    bool result = true;
    result &= fread(&aInfoHeader.biSize,          4, 1, file);
    result &= fread(&aInfoHeader.biWidth,         4, 1, file);
    result &= fread(&aInfoHeader.biHeight,        4, 1, file);
    result &= fread(&aInfoHeader.biPlanes,        2, 1, file);
    result &= fread(&aInfoHeader.biBitCount,      2, 1, file);
    result &= fread(&aInfoHeader.biCompression,   4, 1, file);
    result &= fread(&aInfoHeader.biSizeImage,     4, 1, file);
    result &= fread(&aInfoHeader.biXPelsPerMeter, 4, 1, file);
    result &= fread(&aInfoHeader.biYPelsPerMeter, 4, 1, file);
    result &= fread(&aInfoHeader.biClrUsed,       4, 1, file);
    result &= fread(&aInfoHeader.biClrImportant,  4, 1, file);

    if(isBigEndian())
        aInfoHeader.changeBytesOrder();

    return true;
}

bool BMPImage::parseBitmapV4Header(FILE *file, BITMAPV4HEADER& aV4Header)
{
    if(!file)
        return false;

    bool result = true;
    result &= fread(&aV4Header.biSize,          4, 1, file);
    result &= fread(&aV4Header.biWidth,         4, 1, file);
    result &= fread(&aV4Header.biHeight,        4, 1, file);
    result &= fread(&aV4Header.biPlanes,        2, 1, file);
    result &= fread(&aV4Header.biBitCount,      2, 1, file);
    result &= fread(&aV4Header.biCompression,   4, 1, file);
    result &= fread(&aV4Header.biSizeImage,     4, 1, file);
    result &= fread(&aV4Header.biXPelsPerMeter, 4, 1, file);
    result &= fread(&aV4Header.biYPelsPerMeter, 4, 1, file);
    result &= fread(&aV4Header.biClrUsed,       4, 1, file);
    result &= fread(&aV4Header.biClrImportant,  4, 1, file);
    result &= fread(&aV4Header.biRedMask,       4, 1, file);
    result &= fread(&aV4Header.biGreenMask,     4, 1, file);
    result &= fread(&aV4Header.biBlueMask,      4, 1, file);
    result &= fread(&aV4Header.biAlphaMask,     4, 1, file);
    result &= fread(&aV4Header.biCSType,        4, 1, file);

    result &= fread(&aV4Header.biEndpoints.ciexyzRed.ciexyzX,   4, 1, file);
    result &= fread(&aV4Header.biEndpoints.ciexyzRed.ciexyzY,   4, 1, file);
    result &= fread(&aV4Header.biEndpoints.ciexyzRed.ciexyzZ,   4, 1, file);
    result &= fread(&aV4Header.biEndpoints.ciexyzGreen.ciexyzX, 4, 1, file);
    result &= fread(&aV4Header.biEndpoints.ciexyzGreen.ciexyzY, 4, 1, file);
    result &= fread(&aV4Header.biEndpoints.ciexyzGreen.ciexyzZ, 4, 1, file);
    result &= fread(&aV4Header.biEndpoints.ciexyzBlue.ciexyzX,  4, 1, file);
    result &= fread(&aV4Header.biEndpoints.ciexyzBlue.ciexyzY,  4, 1, file);
    result &= fread(&aV4Header.biEndpoints.ciexyzBlue.ciexyzZ,  4, 1, file);

    result &= fread(&aV4Header.biGammaRed,      4, 1, file);
    result &= fread(&aV4Header.biGammaGreen,    4, 1, file);
    result &= fread(&aV4Header.biGammaBlue,     4, 1, file);

    if(isBigEndian())
        aV4Header.changeBytesOrder();

    return result;
}

bool BMPImage::parseBitmapV5Header  (FILE *file, BITMAPV5HEADER& aV5Header)
{
    if(!file)
        return false;

    bool result = true;
    result &= fread(&aV5Header.biSize,          4, 1, file);
    result &= fread(&aV5Header.biWidth,         4, 1, file);
    result &= fread(&aV5Header.biHeight,        4, 1, file);
    result &= fread(&aV5Header.biPlanes,        2, 1, file);
    result &= fread(&aV5Header.biBitCount,      2, 1, file);
    result &= fread(&aV5Header.biCompression,   4, 1, file);
    result &= fread(&aV5Header.biSizeImage,     4, 1, file);
    result &= fread(&aV5Header.biXPelsPerMeter, 4, 1, file);
    result &= fread(&aV5Header.biYPelsPerMeter, 4, 1, file);
    result &= fread(&aV5Header.biClrUsed,       4, 1, file);
    result &= fread(&aV5Header.biClrImportant,  4, 1, file);
    result &= fread(&aV5Header.biRedMask,       4, 1, file);
    result &= fread(&aV5Header.biGreenMask,     4, 1, file);
    result &= fread(&aV5Header.biBlueMask,      4, 1, file);
    result &= fread(&aV5Header.biAlphaMask,     4, 1, file);
    result &= fread(&aV5Header.biCSType,        4, 1, file);

    result &= fread(&aV5Header.biEndpoints.ciexyzRed.ciexyzX,   4, 1, file);
    result &= fread(&aV5Header.biEndpoints.ciexyzRed.ciexyzY,   4, 1, file);
    result &= fread(&aV5Header.biEndpoints.ciexyzRed.ciexyzZ,   4, 1, file);
    result &= fread(&aV5Header.biEndpoints.ciexyzGreen.ciexyzX, 4, 1, file);
    result &= fread(&aV5Header.biEndpoints.ciexyzGreen.ciexyzY, 4, 1, file);
    result &= fread(&aV5Header.biEndpoints.ciexyzGreen.ciexyzZ, 4, 1, file);
    result &= fread(&aV5Header.biEndpoints.ciexyzBlue.ciexyzX,  4, 1, file);
    result &= fread(&aV5Header.biEndpoints.ciexyzBlue.ciexyzY,  4, 1, file);
    result &= fread(&aV5Header.biEndpoints.ciexyzBlue.ciexyzZ,  4, 1, file);

    result &= fread(&aV5Header.biGammaRed,      4, 1, file);
    result &= fread(&aV5Header.biGammaGreen,    4, 1, file);
    result &= fread(&aV5Header.biGammaBlue,     4, 1, file);
    result &= fread(&aV5Header.biIntent,        4, 1, file);
    result &= fread(&aV5Header.biProfileData,   4, 1, file);
    result &= fread(&aV5Header.biProfileSize,   4, 1, file);
    result &= fread(&aV5Header.biReserved,      4, 1, file);

    if(isBigEndian())
        aV5Header.changeBytesOrder();

    return false;
}

BMPImage::CompressionType BMPImage::geTypeByIndex(unsigned aIndex)
{
    CompressionType result = BI_RGB;

    switch(aIndex)
    {
        case 0:
            {
                result = BI_RGB;
                break;
            }
        case 1:
            {
                result = BI_RLE8;
                break;
            }
        case 2:
            {
                result = BI_RLE4;
                break;
            }
        case 3:
            {
                result = BI_BITFIELDS;
                break;
            }
        case 4:
            {
                result = BI_JPEG;
                break;
            }
        case 5:
            {
                result = BI_PNG;
                break;
            }
        case 6:
            {
                result = BI_ALPHABITFIELDS;
                break;
            }
    }

    return result;
}

