#include <stdlib.h>
#include "Player_Channel.h"

MOD_Player_Channel* MOD_Player_Channel_create(){
    MOD_Player_Channel* channel = (MOD_Player_Channel*) malloc(sizeof(MOD_Player_Channel));
    return channel;
}
