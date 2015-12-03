#ifndef LIB_BMP_H
#define LIB_BMP_H

#include "headers.h"
#include <string>

class BMPImage
{
public:
    BMPImage(const std::string& aFileName);
    ~BMPImage();

    bool isValid();

    unsigned width();
    unsigned height();

private:
    bool parseFile(const std::string& aFileName);

    bool parseBitmapFileHeader(FILE *file, BITMAPFILEHEADER& aFileHeader);
    bool parseBitmapInfoHeader(FILE *file, BITMAPINFOHEADER& aInfoHeader);

private:
    bool m_isValid;

    FILE *m_bmpFile;

    int m_width;
    int m_height;
};

#endif // LIB_BMP_H

