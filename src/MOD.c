#include <stdlib.h>
#include <stdio.h>
#include "MOD.h"
#include "MOD_Sample.h"
#include "MOD_Pattern.h"
#include "utils.h"


MOD* MOD_load(const int8_t* _data){

    const int8_t* data = _data;

    MOD* mod = (MOD*) malloc(sizeof(MOD));

    /* get a pointer to the title */
    mod->title = data;
    data += 20;

    /* for now we assume there are always 31 samples. Later,
     * it is probably wise to check for the magic letters. */
    mod->n_samples = 31;

    /* read the samples */
    mod->samples = (MOD_Sample*) data;
    for(int i=0;i<mod->n_samples;i++){
        data += 30;
    }

    mod->n_song_positions = *data++;

    mod->historical_127 = *data++;

    int n_patterns = 0;

    mod->pattern_table = data;
    data += 128;
    for(int i=0;i<128;i++){
        n_patterns = MAX(mod->pattern_table[i]+1, n_patterns);
    }

    data += 4; /* skip magic letters (usually "M.K") */

    mod->patterns = (MOD_Pattern*) data;
    for(int i=0;i<n_patterns;i++){
        data += 1024;
    }

    for(int i=0;i<mod->n_samples;i++){
        mod->sample_datas[i] = data;
        data += MOD_Sample_get_length(&mod->samples[i])*2;
    }

    return mod;
}
