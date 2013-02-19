#include <stdio.h>
#include <stdlib.h>
#include "MOD_PatternDivision.h"


MOD_PatternDivision* MOD_PatternDivision_load(FILE*fp){
    /*
    printf("MOD_PatternDivision_load(fp: %p)\n", fp);
    */
    MOD_PatternDivision* pd = (MOD_PatternDivision*) malloc(sizeof(MOD_PatternDivision));

    for(int i=0;i<4;i++){
        pd->channels[i] = MOD_Channel_load(fp);
    }

    /*
    printf("<--\n");
    */
    return pd;
}
