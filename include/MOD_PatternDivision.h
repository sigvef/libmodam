#ifndef MOD_PATTERNDIVISION_H
#define MOD_PATTERNDIVISION_H

#include "MOD_Channel.h"

typedef struct { 
    MOD_Channel* channels[4];
} MOD_PatternDivision;

MOD_PatternDivision* MOD_PatternDivision_load(const int8_t **data);
#endif
