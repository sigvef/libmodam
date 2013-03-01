#ifndef MOD_UTILS_H
#define MOD_UTILS_H

#define LARP(A,B,T) ((B)*(T))+((A)*(1-(T)))

#define MAX(A,B) ((A)<(B)?(B):(A))
#define MIN(A,B) ((A)>(B)?(B):(A))

//#define FLIP_ENDIANNESS_INT16(a) ((((a)&0xff)<<8)|(((a)&0xff00)>>8))

#define FLIP_ENDIANNESS_INT16(a) (a)

int16_t MOD_utils_read16(const int8_t **data);


#endif
