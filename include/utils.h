#ifndef MOD_UTILS_H
#define MOD_UTILS_H

#define LARP(A,B,T) ((B)*(T))+((A)*(1-(T)))

#define MAX(A,B) ((A)<(B)?(B):(A))
#define MIN(A,B) ((A)>(B)?(B):(A))

int16_t MOD_utils_read16(const int8_t **data);


#endif
