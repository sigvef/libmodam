#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "MOD.h"
#include "Player.h"
#include "modfiles.h"


#define ONE_SECOND_IN_MICROSECONDS 1000000

int main(){

    MOD* mod = MOD_load(MODFILES_BANANASPLIT_MOD);

    int sample_rate = 48000;

    MOD_Player* player = MOD_Player_create(sample_rate);

    MOD_Player_set_mod(player, mod);

    int spillage = 0;

    while(1){

        spillage += ONE_SECOND_IN_MICROSECONDS % sample_rate;
        MOD_Player_step(player, ONE_SECOND_IN_MICROSECONDS / sample_rate);
        while(spillage > sample_rate){
            spillage -= sample_rate;
            MOD_Player_step(player, 1);
        }

        int16_t out = MOD_Player_play(player);
        putchar(out&0xff);
        putchar((out&0xff00) >> 8);
    }

    return 0;
}
