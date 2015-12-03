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

public:
    BMPImage(const std::string& aFileName);
    ~BMPImage();

    bool isValid();

    unsigned width();
    unsigned height();

    unsigned short bitCount();
    CompressionType compressionType();

private:
    bool parseFile(const std::string& aFileName);

    bool parseBitmapFileHeader(FILE *file, BITMAPFILEHEADER& aFileHeader);
    bool parseBitmapCoreHeader(FILE *file, BITMAPCOREHEADER& aCoreHeader);
    bool parseBitmapInfoHeader(FILE *file, BITMAPINFOHEADER& aInfoHeader);
    bool parseBitmapV4Header  (FILE *file, BITMAPV4HEADER&   aV4Header  );
    bool parseBitmapV5Header  (FILE *file, BITMAPV5HEADER&   aV5Header  );


    CompressionType geTypeByIndex(unsigned aIndex);

private:
    bool m_isValid;

    FILE *m_bmpFile;

    int m_width;
    int m_height;

    unsigned short m_bitCount;
    CompressionType m_compresionType;
};

#endif // LIB_BMP_H
