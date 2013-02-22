#ifndef MOD_H
#define MOD_H

#include <stdint.h>
#include "MOD_Sample.h"
#include "MOD_Pattern.h"

#define EFFECT_ARPEGGIO 0
#define EFFECT_SLIDE_UP 1
#define EFFECT_SLIDE_DOWN 2
#define EFFECT_SLIDE_TO_NOTE 3
#define EFFECT_VIBRATO 4
#define EFFECT_CONTINUE_SLIDE_TO_NOTE_AND_VOLUME_SLIDE 5
#define EFFECT_CONTINUE_VIBRATO_TO_NOTE_AND_VOLUME_SLIDE 6
#define EFFECT_TREMOLO 7
#define EFFECT_UNUSED 8
#define EFFECT_SET_SAMPLE_OFFSET 9
#define EFFECT_VOLUME_SLIDE 10
#define EFFECT_POSITION_JUMP 11
#define EFFECT_SET_VOLUME 12
#define EFFECT_PATTERN_BREAK 13
#define EFFECT_EXTRAS 14
#define EFFECT_SET_SPEED 15



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

MOD* MOD_load(int8_t *data);
void MOD_free(MOD*mod);

#endif
