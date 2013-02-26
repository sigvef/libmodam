#include <stdio.h>
#include <stdlib.h>
#include "MOD_PatternDivision.h"


MOD_PatternDivision* MOD_PatternDivision_load(const int8_t **data){
    MOD_PatternDivision* pd = (MOD_PatternDivision*) malloc(sizeof(MOD_PatternDivision));

    for(int i=0;i<4;i++){
        pd->channels[i] = MOD_Channel_load(data);
    }

    return pd;
}
