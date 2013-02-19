#ifndef MOD_H
#define MOD_H

#include <stdint.h>
#include "MOD_Sample.h"
#include "MOD_Pattern.h"

/* http://www.mediatel.lu/workshop/audio/fileformat/h_mod.html */

typedef struct {
    char title[20];
    MOD_Sample** samples;
    int8_t n_samples;
    int8_t n_song_positions;
    int8_t historical_127;
    int8_t pattern_table[128];
    char magic_letters[4]; /* usually "M.K." */
    MOD_Pattern** patterns;
    int8_t n_patterns;
} MOD;

MOD* MOD_load(const char* filename);
void MOD_free(MOD*mod);

#endif
