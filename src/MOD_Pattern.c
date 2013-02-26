#include <stdio.h>
#include <stdlib.h>
#include "MOD_Pattern.h"


MOD_Pattern* MOD_Pattern_load(const int8_t **data){

    MOD_Pattern* pattern = (MOD_Pattern*) malloc(sizeof(MOD_Pattern));
    for(int i=0;i<64;i++){
        pattern->divisions[i] = MOD_PatternDivision_load(data);
    }

    return pattern;
}
