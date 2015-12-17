#ifndef SIMPLE_2x2_24_BIT_BMP_H
#define SIMPLE_2x2_24_BIT_BMP_H

#include "libbmp.h"

#define TEST_FILE_NAME  "test_data/initial/bmp_2x2_24bit.bmp"

TEST(Simple_2x2_24bit_bmp, Open_File)
{
    BMPImage *bmp = new BMPImage(TEST_FILE_NAME);
    ASSERT_TRUE(bmp);

    delete bmp;
}

TEST(Simple_2x2_24bit_bmp, Check_File_Header)
{
    BMPImage *bmp = new BMPImage(TEST_FILE_NAME);
    ASSERT_TRUE(bmp);

    ASSERT_EQ(0x4D42, bmp->fileHeaderType());
    ASSERT_EQ(138, bmp->fileHeaderSize());
    ASSERT_EQ(122, bmp->fileHeaderBitsOffset());

    delete bmp;
}

TEST(Simple_2x2_24bit_bmp, Check_Width_And_Height)
{
    BMPImage *bmp = new BMPImage(TEST_FILE_NAME);
    ASSERT_TRUE(bmp != NULL);

    ASSERT_EQ(2, bmp->width());
    ASSERT_EQ(2, bmp->height());

    delete bmp;
}

#endif // SIMPLE_2x2_24_BIT_BMP_H

