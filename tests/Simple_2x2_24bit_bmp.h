#ifndef SIMPLE_2x2_24_BIT_BMP_H
#define SIMPLE_2x2_24_BIT_BMP_H

#include "libbmp.h"

TEST(Simple_2x2_24bit_bmp, Open_File)
{
    BMPImage *bmp = new BMPImage("test_data/initial/bmp_2x2_24bit.bmp");
    ASSERT_TRUE(bmp != NULL);

    delete bmp;
}

TEST(Simple_2x2_24bit_bmp, Check_Width_And_Height)
{
    BMPImage *bmp = new BMPImage("test_data/initial/bmp_2x2_24bit.bmp");
    ASSERT_TRUE(bmp != NULL);

    ASSERT_EQ(2, bmp->width());
    ASSERT_EQ(2, bmp->height());

    delete bmp;
}

#endif // SIMPLE_2x2_24_BIT_BMP_H

