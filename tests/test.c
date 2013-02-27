#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "MOD.h"
#include "Player.h"
#include "modfiles.h"

int main(){

    MOD* mod = MOD_load(MODFILES_CLASS05_MOD);

    MOD_Player* player = MOD_Player_create();

    while(1){
        int16_t out = MOD_Player_play(player, mod);
        putchar((out&0xff00) >> 8);
        putchar(out&0xff);
    }

    return 0;
}
