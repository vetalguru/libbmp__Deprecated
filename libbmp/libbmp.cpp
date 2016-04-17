#include "libbmp.h"
#include "fstream"
#include "cstdlib"
#include "algorithm"

BMPImage::BMPImage()
    : m_width(0)
    , m_height(0)
{
}

BMPImage::BMPImage(const std::string& aFileName)
    : m_width(0)
    , m_height(0)
{
    parseFile(aFileName);
}

BMPImage::~BMPImage()
{
}

bool BMPImage::parseFile(const std::string& aFileName)
{
    if(aFileName.empty())
        return false;

    std::ifstream stream(aFileName.c_str(), std::ios::binary);
    if(!stream)
        return false;

    BITMAPFILEHEADER bmpFileHeader;
    if(!decodeBitmapFileHeader(stream, bmpFileHeader))
    {
        stream.close();
        return false;

    }
    if(bmpFileHeader.bfType != 19778)
    {
        stream.close();
        return false;
    }

    BITMAPINFOHEADER bmpInfoHeader;
    if(!decodeBitmapInfoHeader(stream, bmpInfoHeader))
    {
        stream.close();
        return false;
    }

    // FIXME: Now we decode only 24 bit bitmaps
    if(bmpInfoHeader.biBitCount != 24)
    {
        stream.close();
        return false;
    }

    m_width = bmpInfoHeader.biWidth;
    m_height = abs(bmpInfoHeader.biHeight);

    int bytesPerPixel = bmpInfoHeader.biBitCount >> 3;
    int padding = 4 - ((m_width * bytesPerPixel) % 4);

    for(unsigned int i = 0; i < m_height; i++)
    {
       std::vector<PixelColor> row;

       for(unsigned int k = 0; k < m_width; k++)
       {
           unsigned char red = 0;
           unsigned char green = 0;
           unsigned char blue = 0;

           readFromStream(stream, blue);
           readFromStream(stream, green);
           readFromStream(stream, red);

           PixelColor color;
           color.Red = red;
           color.Green = green;
           color.Blue = blue;

           row.push_back(color);
       }

       m_bitmap.push_back(row);

       for(int p = 0; p < padding; ++p)
       {
           unsigned char tmpByte = 0;
           readFromStream(stream, tmpByte);
       }
    }

    std::reverse(m_bitmap.begin(), m_bitmap.end());

    return true;
}

bool BMPImage::decodeBitmapFileHeader(std::ifstream& aStream, BITMAPFILEHEADER& aFileHeader)
{
    if(!aStream)
        return false;

    readFromStream(aStream, aFileHeader.bfType);
    readFromStream(aStream, aFileHeader.bfSize);
    readFromStream(aStream, aFileHeader.bfReserved1);
    readFromStream(aStream, aFileHeader.bfReserved2);
    readFromStream(aStream, aFileHeader.bfOffBits);

    if(isBigEndian())
        aFileHeader.changeBytesOrder();

    return true;
}

bool BMPImage::decodeBitmapInfoHeader(std::ifstream& aStream, BITMAPINFOHEADER& aInfoHeader)
{
    if(!aStream)
        return false;

    readFromStream(aStream, aInfoHeader.biSize);
    readFromStream(aStream, aInfoHeader.biWidth);
    readFromStream(aStream, aInfoHeader.biHeight);
    readFromStream(aStream, aInfoHeader.biPlanes);
    readFromStream(aStream, aInfoHeader.biBitCount);
    readFromStream(aStream, aInfoHeader.biCompression);
    readFromStream(aStream, aInfoHeader.biSizeImage);
    readFromStream(aStream, aInfoHeader.biXPelsPerMeter);
    readFromStream(aStream, aInfoHeader.biYPelsPerMeter);
    readFromStream(aStream, aInfoHeader.biClrUsed);
    readFromStream(aStream, aInfoHeader.biClrImportant);

    if(isBigEndian())
        aInfoHeader.changeBytesOrder();

    return true;
}

bool BMPImage::saveToFile(const std::string& aFileName)
{
    if(aFileName.empty())
        return false;

    if(m_bitmap.empty())
        return false;

    std::ofstream stream(aFileName.c_str(), std::ios::binary);
    if(!stream)
        return false;

    BITMAPFILEHEADER bmpFileHeader;
    BITMAPINFOHEADER bmpInfoHeader;

    bmpInfoHeader.biWidth = m_width;
    bmpInfoHeader.biHeight = m_height;
    bmpInfoHeader.biBitCount = 24;
    bmpInfoHeader.biClrImportant = 0;
    bmpInfoHeader.biClrUsed = 0;
    bmpInfoHeader.biCompression = 0;
    bmpInfoHeader.biPlanes = 1;
    bmpInfoHeader.biSize = 40;
    bmpInfoHeader.biXPelsPerMeter = 0;
    bmpInfoHeader.biYPelsPerMeter = 0;
    bmpInfoHeader.biSizeImage = (((bmpInfoHeader.biWidth * 3) + 3) & 0x0000FFFC) * bmpInfoHeader.biHeight;

    bmpFileHeader.bfType = 19778;
    bmpFileHeader.bfSize = 55 + bmpInfoHeader.biSizeImage;
    bmpFileHeader.bfReserved1 = 0;
    bmpFileHeader.bfReserved2 = 0;
    bmpFileHeader.bfOffBits = 40 + 14;

    if(!writeBitmapFileHeader(stream, bmpFileHeader))
    {
        stream.close();
        return false;
    }

    if(!writeBitmapInfoHeader(stream, bmpInfoHeader))
    {
        stream.close();
        return false;
    }

    int bytesPerPixel = bmpInfoHeader.biBitCount >> 3;
    int padding = 4 - ((m_width * bytesPerPixel) % 4);

    for(int i = m_height - 1; i >= 0; --i)
    {
       for(int k = 0; k < m_width; ++k)
       {
           PixelColor curPixel = m_bitmap.at(i).at(k);

           writeToStream(stream, curPixel.Blue);
           writeToStream(stream, curPixel.Green);
           writeToStream(stream, curPixel.Red);
       }

       for(int p = 0; p < padding; p++)
       {
           unsigned char tmpByte = 0;
           writeToStream(stream, tmpByte);
       }
    }

    return true;
}

bool BMPImage::writeBitmapFileHeader(std::ofstream& aStream, BITMAPFILEHEADER& aFileHeader)
{
    if(!aStream)
        return false;

    if(isBigEndian())
        aFileHeader.changeBytesOrder();

    writeToStream(aStream, aFileHeader.bfType);
    writeToStream(aStream, aFileHeader.bfSize);
    writeToStream(aStream, aFileHeader.bfReserved1);
    writeToStream(aStream, aFileHeader.bfReserved2);
    writeToStream(aStream, aFileHeader.bfOffBits);

    return true;
}

bool BMPImage::writeBitmapInfoHeader(std::ofstream& aStream, BITMAPINFOHEADER& aInfoHeader)
{
    if(!aStream)
        return false;

    if(isBigEndian())
        aInfoHeader.changeBytesOrder();

    writeToStream(aStream, aInfoHeader.biSize);
    writeToStream(aStream, aInfoHeader.biWidth);
    writeToStream(aStream, aInfoHeader.biHeight);
    writeToStream(aStream, aInfoHeader.biPlanes);
    writeToStream(aStream, aInfoHeader.biBitCount);
    writeToStream(aStream, aInfoHeader.biCompression);
    writeToStream(aStream, aInfoHeader.biSizeImage);
    writeToStream(aStream, aInfoHeader.biXPelsPerMeter);
    writeToStream(aStream, aInfoHeader.biYPelsPerMeter);
    writeToStream(aStream, aInfoHeader.biClrUsed);
    writeToStream(aStream, aInfoHeader.biClrImportant);

    return true;
}
