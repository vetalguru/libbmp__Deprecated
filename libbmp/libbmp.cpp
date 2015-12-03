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

            break;
        }
        default:
        {
            fclose(m_bmpFile);
            m_bmpFile = NULL;
            return false;
        }
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
