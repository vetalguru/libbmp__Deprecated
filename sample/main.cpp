#include <iostream>
#include "libbmp.h"

int main()
{
    BMPImage *bmp = new BMPImage(std::string());

    delete bmp;

    return 0;
}
