#include <iostream>
#include "gtest/gtest.h"
#include "libbmp.h"

TEST(TestTest, Test)
{
    EXPECT_EQ(2, 2);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

