#ifndef MOD_PATTERN_H
#define MOD_PATTERN_H

#include "MOD_PatternDivision.h"

typedef struct{
    MOD_PatternDivision* divisions[64];
} MOD_Pattern;

MOD_Pattern* MOD_Pattern_load(int8_t *data);

#endif
