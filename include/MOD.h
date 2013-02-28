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
#define EFFECT_VOLUME_SLIDE 0xA
#define EFFECT_POSITION_JUMP 0xB
#define EFFECT_SET_VOLUME 0xC
#define EFFECT_PATTERN_BREAK 0xD
#define EFFECT_EXTRAS 0xE
#define EFFECT_SET_SPEED 0xF

#define AMIGA_FREQUENCY 3546895

/* http://www.mediatel.lu/workshop/audio/fileformat/h_mod.html */
/* http://archive.cs.uu.nl/pub/MIDI/DOC/MOD-info */

typedef struct {
    const char* title;
    MOD_Sample* samples;
    int8_t n_samples;
    int8_t n_song_positions;
    int8_t historical_127;
    const int8_t* pattern_table;
    MOD_Pattern* patterns;
    const int8_t* sample_datas[31];
} MOD;

MOD* MOD_load(const int8_t *data);
void MOD_free(MOD*mod);

#endif
