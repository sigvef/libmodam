#ifndef PLAYER_H
#define PLAYER_H

#include "MOD.h"
#include "Player_Channel.h"

typedef struct{
    MOD_Player_Channel* channels[4];
    long tick;
    int song_position;
    int active_division;
    int ticks_per_division;
} MOD_Player;

MOD_Player* MOD_Player_create();
void MOD_Player_play(MOD_Player* player, MOD* mod);

#endif
