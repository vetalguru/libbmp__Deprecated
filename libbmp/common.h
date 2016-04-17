#ifndef COMMON_H
#define COMMON_H

#include "fstream"

inline bool isBigEndian()
{
    unsigned short x = 1; /* 0x0001 */

    return (*((uint8_t*)&x) == 0);
}

inline unsigned short swapBytes_16(const unsigned short aData)
{
    return (aData >> 8) | (aData << 8);
}

inline unsigned swapBytes_32(const unsigned aData)
{
    return (((aData >> 24)&0xFF)   | ((aData << 8)&0xFF0000) |
            ((aData >>  8)&0xFF00) | ((aData << 24)&0xFF000000));

}

template<typename T>
inline void readFromStream(std::ifstream& aStream,T& aType)
{
   aStream.read(reinterpret_cast<char*>(&aType),sizeof(T));
}

template<typename T>
inline void writeToStream(std::ofstream& aStream, const T& aType)
{
    aStream.write(reinterpret_cast<const char*>(&aType), sizeof(T));
}

#endif // COMMON_H
