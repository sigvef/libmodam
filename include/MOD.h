#ifndef MOD_H
#define MOD_H

/* http://www.mediatel.lu/workshop/audio/fileformat/h_mod.html */

typedef struct {
    char[20] title;
    MOD_Sample* samples;
    int8_t n_samples;
    int8_t n_song_positions;
    int8_t historical_127;
    int8_t[128] pattern_table;
    char[4] magic_letters; /* usually "M.K." */
    MOD_Pattern* patterns;
    int8_t n_patterns;
} MOD;

#endif
