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
    bool parseBitmapCoreHeader(FILE *file, BITMAPCOREHEADER& aCoreHeader);
    bool parseBitmapInfoHeader(FILE *file, BITMAPINFOHEADER& aInfoHeader);
    bool parseBitmapV4Header  (FILE *file, BITMAPV4HEADER&   aV4Header  );
    bool parseBitmapV5Header  (FILE *file, BITMAPV5HEADER&   aV5Header  );

private:
    bool m_isValid;

    FILE *m_bmpFile;

    int m_width;
    int m_height;
};

#endif // LIB_BMP_H

