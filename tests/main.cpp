#include <iostream>
#include "gtest/gtest.h"
#include "libbmp.h"
#include "Simple_2x2_24bit_bmp.h"


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

