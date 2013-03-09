#ifndef MOD_UTILS_H
#define MOD_UTILS_H

#define MAX(A,B) ((A)<(B)?(B):(A))
#define MIN(A,B) ((A)>(B)?(B):(A))

#define CLAMP(A,B,C) (MIN((C), MAX((A),(B))))

//#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    //#define FLIP_ENDIANNESS_INT16(a) ((((a)&0xff)<<8)|(((a)&0xff00)>>8))
//#else
    #define FLIP_ENDIANNESS_INT16(a) (a)
//#endif

int16_t MOD_utils_read16(const int8_t **data);

#endif
