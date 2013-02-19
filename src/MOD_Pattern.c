#include <stdio.h>
#include <stdlib.h>
#include "MOD_Pattern.h"


MOD_Pattern* MOD_Pattern_load(FILE*fp){
    /*
    printf("MOD_Pattern_load(fp: %p)\n", fp);
    */
    MOD_Pattern* pattern = (MOD_Pattern*) malloc(sizeof(MOD_Pattern));
    for(int i=0;i<64;i++){
        pattern->divisions[i] = MOD_PatternDivision_load(fp);
    }
    /*
    printf("<--\n");
    */
    return pattern;
}
