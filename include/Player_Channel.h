#ifndef MOD_PLAYER_CHANNEL_H
#define MOD_PLAYER_CHANNEL_H

typedef struct {
} MOD_Player_Channel;

MOD_Player_Channel* MOD_Player_Channel_create();
void MOD_Player_Channel_free(MOD_Player_Channel* channel);

#endif
