#include "zoid3.h"
#include "game_mode.h"

extern ZoidState Zoid[16];

s32 calcEndBattle(void)
{
    ZoidState *first = &Zoid[0];
    s32 player_slot = first->slot;
    s32 i;
    s32 opponent_alive = 0;

    for (i = 0; i < 16; i++) {
        ZoidState *zoid = &Zoid[i];
        if (zoid->joint != 0 && zoid->slot != player_slot) {
            if (zoid->death_started == 0) {
                opponent_alive = 1;
            } else if (zoid->field_20BC != 0) {
                opponent_alive = 1;
            }
        }
    }
    if (first->death_started == 0) {
        if (opponent_alive != 0) {
            return GAME_RESULT_NONE;
        }
        return GAME_RESULT_WIN;
    }
    if (opponent_alive != 0) {
        return GAME_RESULT_LOSE;
    }
    return GAME_RESULT_DRAW;
}
