#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "MOD.h"
#include "Player.h"
#include "modfiles.h"

int main(){

    MOD* mod = MOD_load(MODFILES_MOD_SLEEPLESS_NIGHTS_);

    MOD_Player* player = MOD_Player_create();

    MOD_Player_play(player, mod);

    return 0;
}
