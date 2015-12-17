#ifndef LIB_BMP_H
#define LIB_BMP_H

#include "headers.h"
#include <string>

class BMPImage
{
public:
    enum CompressionType
    {
        BI_RGB = 0,
        BI_RLE8,
        BI_RLE4,
        BI_BITFIELDS,
        BI_JPEG,
        BI_PNG,
        BI_ALPHABITFIELDS,
    };

    struct PixelColor
    {
        unsigned char redColor;
        unsigned char greenColor;
        unsigned char blueColor;
    };

public:
    BMPImage(const std::string& aFileName);
    ~BMPImage();

    bool isValid();

    // File Header
    unsigned short fileHeaderType();
    unsigned int   fileHeaderSize();
    unsigned short fileHeaderBitsOffset();

    unsigned width();
    unsigned height();

    unsigned short bitCount();
    CompressionType compressionType();

private:
    bool parseFile(const std::string& aFileName);

    bool decodeBitmapFileHeader(FILE *file, BITMAPFILEHEADER& aFileHeader);
    bool decodeBitmapInfoHeader(FILE *file);

    bool parseBitmapCoreHeader(FILE *file, BITMAPCOREHEADER& aCoreHeader);
    bool parseBitmapInfoHeader(FILE *file, BITMAPINFOHEADER& aInfoHeader);
    bool parseBitmapV4Header  (FILE *file, BITMAPV4HEADER&   aV4Header  );
    bool parseBitmapV5Header  (FILE *file, BITMAPV5HEADER&   aV5Header  );


    CompressionType geTypeByIndex(unsigned aIndex);

private:
    bool m_isValid;

    FILE *m_bmpFile;

    BITMAPFILEHEADER m_fileHeader;

    int m_width;
    int m_height;

    int m_imageSize;

    unsigned short m_bitCount;
    CompressionType m_compresionType;
};

#endif // LIB_BMP_H
