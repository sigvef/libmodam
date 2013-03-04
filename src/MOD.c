#include <stdlib.h>
#include <stdio.h>
#include "MOD.h"
#include "MOD_Sample.h"
#include "MOD_Pattern.h"
#include "utils.h"


/* MOD_load makes a MOD struct with pointers to different
 * interesting parts of a MOD file to facilitate playing.
 *
 * Arguments:
 * const int8_t* _data: an array containing an entire MOD
 *                      file. The MOD structs only contains
 *                      pointers to this array, so it must
 *                      not be freed until the MOD struct
 *                      is freed!
 */
MOD* MOD_load(const int8_t* _data){

    /* copy the pointer so that we can edit it without the caller getting mad/confused */
    const int8_t* data = _data;

    /* le malloc */
    MOD* mod = (MOD*) malloc(sizeof(MOD));

    /* get a pointer to the title of the MOD */
    mod->title = data;
    data += 20;

    /* MOD files usually contain 31 or 15 samples. 31 samples
     * is by far the most common, so for now we assume there
     * are always 31 samples. Later, it might be wise to check
     * the magic letters later in the file header - they denote
     * the number of samples. */
    mod->n_samples = 31;

    /* read the samples */
    mod->samples = (MOD_Sample*) data;
    for(int i=0;i<mod->n_samples;i++){
        data += 30;
    }

    /* read the amount of song positions in the MOD */
    mod->n_song_positions = *data++;

    /* This byte is never used, and is usually set to 127. No-one
     * remembers why, but it is here for legacy reasons. */
    mod->historical_127 = *data++;


    /* load the pattern table */
    mod->pattern_table = data;
    data += 128;

    /* we need to manually count how many patterns are included in
     * the song so we can load that many patterns later */
    int n_patterns = 0;
    for(int i=0;i<128;i++){
        n_patterns = MAX(mod->pattern_table[i]+1, n_patterns);
    }

    /* skip magic letters (usually "M.K") */
    data += 4;

    /* load the patterns */
    mod->patterns = (MOD_Pattern*) data;
    for(int i=0;i<n_patterns;i++){
        data += 1024;
    }

    /* load the sample data */
    for(int i=0;i<mod->n_samples;i++){
        mod->sample_datas[i] = data;
        data += MOD_Sample_get_length(&mod->samples[i])*2;
    }

    /* and finally return our freshly loaded MOD! */
    return mod;
}
