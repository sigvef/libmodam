#ifndef MOD_UTILS_H
#define MOD_UTILS_H

#define LARP(A,B,T) ((A)*(T))+((B)*(1-(T)))

#define MAX(A,B) ((A)<(B)?(B):(A))

int16_t MOD_utils_read16(int8_t **data);


#endif
