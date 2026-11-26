#include "zoid3.h"

extern ZoidState Zoid[16];
extern s32 gameTime;

s32 calcEndVs4p(void)
{
    s32 teams[10];
    s32 i;
    s32 winner;
    s32 dead;

    for (i = 0; i < 10; i++) {
        teams[i] = 0;
    }
    winner = 0;
    dead = 0;
    for (; winner < 4; winner++) {
        ZoidState *zoid = &Zoid[winner];
        if (zoid->joint != 0) {
            if (zoid->death_started != 0) {
                dead++;
            } else {
                teams[zoid->slot]++;
            }
        }
    }
    if (dead == 4) {
        return 0x63;
    }
    i = 0;
    dead = 0;
    winner = 0x63;
    for (; i < 10; i++) {
        if (teams[i] != 0) {
            winner = i;
            dead++;
        }
    }
    if (dead == 0) {
        return 0x63;
    }
    if (dead == 1) {
        return winner + 1;
    }
    if (gameTime == 0) {
        return 0x63;
    }
    return 0;
}
