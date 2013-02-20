#include <stdlib.h>
#include "Player.h"
#include "MOD.h"

MOD_Player* MOD_Player_create(){
    MOD_Player* player = (MOD_Player*) malloc(sizeof(MOD_Player));
    return player;
}

void MOD_Player_play(MOD_Player* player, MOD*mod){

    MOD_Sample* sample = mod->samples[5];

    while(1){

        putchar(sample->data[player->tick%sample->length]);

        player->tick++;
    }
}
