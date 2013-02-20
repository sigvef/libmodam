#include <stdlib.h>
#include <stdio.h>
#include "MOD.h"
#include "MOD_Sample.h"
#include "MOD_Pattern.h"


MOD* MOD_load(int8_t* data){

    MOD* mod = (MOD*) malloc(sizeof(MOD));

    /* read the title */
    for(int i=0;i<20;i++){
        mod->title[i] = *data++;
    }

    printf("The title is: %.20s\n", mod->title);

    /* for now we assume there are always 31 samples. Later,
     * it is probably wise to check for the magic letters. */
    mod->n_samples = 31;

    /* read the samples */
    mod->samples = (MOD_Sample**) malloc(sizeof(MOD_Sample)*mod->n_samples);
    for(int i=0;i<mod->n_samples;i++){
        mod->samples[i] = MOD_Sample_load(data);
    }

    mod->n_song_positions = *data++;

    mod->historical_127 = *data++;

    for(int i=0;i<128;i++){
        mod->pattern_table[i] = *data++;
    }

    for(int i=0;i<4;i++){
        mod->magic_letters[i] = *data++; /* usually "M.K." */
    }

    mod->patterns = (MOD_Pattern**) malloc(sizeof(MOD_Pattern)*128);
    for(int i=0;i<128;i++){
        mod->patterns[i] = MOD_Pattern_load(data);
    }

    for(int i=0;i<mod->n_samples;i++){
        MOD_Sample_loadData(mod->samples[i], data);
    }

    return mod;
}
