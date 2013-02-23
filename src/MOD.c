#include <stdlib.h>
#include <stdio.h>
#include "MOD.h"
#include "MOD_Sample.h"
#include "MOD_Pattern.h"
#include "utils.h"


MOD* MOD_load(int8_t* _data){

    int8_t* data = _data;

    MOD* mod = (MOD*) malloc(sizeof(MOD));

    /* read the title */
    for(int i=0;i<20;i++){
        mod->title[i] = *data++;
    }

    /* for now we assume there are always 31 samples. Later,
     * it is probably wise to check for the magic letters. */
    mod->n_samples = 31;

    /* read the samples */
    mod->samples = (MOD_Sample**) malloc(sizeof(MOD_Sample)*mod->n_samples);
    for(int i=0;i<mod->n_samples;i++){
        mod->samples[i] = MOD_Sample_load(&data);
    }

    mod->n_song_positions = *data++;

    mod->historical_127 = *data++;

    int n_patterns = 0;

    for(int i=0;i<128;i++){
        mod->pattern_table[i] = *data++;
        n_patterns = MAX(mod->pattern_table[i]+1, n_patterns);
    }

    for(int i=0;i<4;i++){
        mod->magic_letters[i] = *data++; /* usually "M.K." */
    }

    mod->patterns = (MOD_Pattern**) malloc(sizeof(MOD_Pattern)*128);
    for(int i=0;i<n_patterns;i++){
        mod->patterns[i] = MOD_Pattern_load(&data);
    }

    for(int i=0;i<mod->n_samples;i++){
        MOD_Sample_loadData(mod->samples[i], &data);
    }

    return mod;
}
