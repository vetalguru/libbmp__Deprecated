#ifndef SIMPLE_2x2_24_BIT_BMP_H
#define SIMPLE_2x2_24_BIT_BMP_H

#include "libbmp.h"

TEST(Simple_2x2_24bit_bmp, OpenFile)
{
    BMPImage *bmp = new BMPImage("test_data/initial/bmp_2x2_24bit.bmp");
    ASSERT_TRUE(bmp != NULL);

    delete bmp;
}

#endif // SIMPLE_2x2_24_BIT_BMP_H

