// BMP format headers

#include <stdint.h>

// BITMAP FFILE HEADER
typedef struct tagBITMAPFILEHEADER
{
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint16_t bfOffBits;
} BITMAPFILEHEADER;

const unsigned BITMAPFILEHEADER_SIZE = 12;
