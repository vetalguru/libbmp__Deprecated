#ifndef LIB_BMP_H
#define LIB_BMP_H

#include "headers.h"
#include <string>
#include <vector>

class BMPImage
{
    public:
        struct PixelColor
        {
            unsigned char Red;
            unsigned char Green;
            unsigned char Blue;
            unsigned char Alpha;

            PixelColor()
                : Red(0)
                , Green(0)
                , Blue(0)
                , Alpha(0)
            {}
        };

    public:
        BMPImage();
        BMPImage(const std::string& aFileName);

        ~BMPImage();

        size_t width();
        size_t height();

        bool pixelColor(const size_t aX, const size_t aY, PixelColor& aPixelColor);

        bool saveToFile(const std::string& aFileName);

    private:
        bool parseFile(const std::string& aFileName);

        bool decodeBitmapFileHeader(std::ifstream& aStream, BITMAPFILEHEADER& aFileHeader);
        bool decodeBitmapInfoHeader(std::ifstream& aStream, BITMAPINFOHEADER& aInfoHeader);

        bool writeBitmapFileHeader(std::ofstream& aStream, BITMAPFILEHEADER& aFileHeader);
        bool writeBitmapInfoHeader(std::ofstream& aStream, BITMAPINFOHEADER& aInfoHeader);

    private:
        size_t m_width;
        size_t m_height;

        std::vector<std::vector<PixelColor> > m_bitmap;

};

#endif // LIB_BMP_H
