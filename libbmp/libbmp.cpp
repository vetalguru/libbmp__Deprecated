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


    // GET INFO HEADER
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

bool BMPImage::parseBitmapV5Header  (FILE *file, BITMAPV5HEADER&   aV5Header  )
{
    if(!file)
        return false;

    if(!fread(&aV5Header, BITMAPV5HEADER_SIZE, 1, file))
        return false;

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

