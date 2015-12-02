#ifndef COMMON_H
#define COMMON_H

bool isBigEndian()
{
    unsigned short x = 1; /* 0x0001 */

    return (*((uint8_t*)&x) == 0);
}

unsigned short swapBytes_16(const unsigned short aData)
{
    return (aData >> 8) | (aData << 8);
}

unsigned swapBytes_32(const unsigned aData)
{
    return (((aData >> 24)&0xFF)   | ((aData << 8)&0xFF0000) |
            ((aData >>  8)&0xFF00) | ((aData << 24)&0xFF000000));

}

#endif // COMMON_H
