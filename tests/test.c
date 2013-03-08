#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "MOD.h"
#include "Player.h"
#include "modfiles.h"

int main(){

    MOD* mod = MOD_load(MODFILES_ELEKFUNK_MOD);

    int sample_rate = 48000;

    MOD_Player* player = MOD_Player_create(sample_rate);

    MOD_Player_set_mod(player, mod);

    while(1){

        MOD_Player_step(player, 1000000/sample_rate+1);

        int16_t out = MOD_Player_play(player);
        putchar(out&0xff);
        putchar((out&0xff00) >> 8);
    }

    return 0;
}
