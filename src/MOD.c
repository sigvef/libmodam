#include <stdlib.h>
#include <stdio.h>
#include "MOD.h"
#include "MOD_Sample.h"
#include "MOD_Pattern.h"


MOD* MOD_load(const char* filename){

    MOD* mod = (MOD*) malloc(sizeof(MOD));

    FILE* fp = fopen(filename, "r");

    /* read the title */
    for(int i=0;i<20;i++){
        mod->title[i] = fgetc(fp);
    }

    printf("The title is: %.20s\n", mod->title);

    /* for now we assume there are always 31 samples. Later,
     * it is probably wise to check for the magic letters. */
    mod->n_samples = 31;

    /* read the samples */
    mod->samples = (MOD_Sample**) malloc(sizeof(MOD_Sample)*mod->n_samples);
    for(int i=0;i<mod->n_samples;i++){
        mod->samples[i] = MOD_Sample_load(fp);
    }

    mod->n_song_positions = fgetc(fp);

    mod->historical_127 = fgetc(fp);

    for(int i=0;i<128;i++){
        mod->pattern_table[i] = fgetc(fp);
    }

    for(int i=0;i<4;i++){
        mod->magic_letters[i] = fgetc(fp); /* usually "M.K." */
    }

    mod->patterns = (MOD_Pattern**) malloc(sizeof(MOD_Pattern)*128);
    for(int i=0;i<128;i++){
        mod->patterns[i] = MOD_Pattern_load(fp);
    }

    for(int i=0;i<mod->n_samples;i++){
        MOD_Sample_loadData(mod->samples[i], fp);
    }

    fclose(fp);

    return mod;
}
