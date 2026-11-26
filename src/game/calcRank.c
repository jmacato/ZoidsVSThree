#include "game_mode.h"

s32 calcRank(s32 score)
{
    s32 rank = 1;

    if (GameMode.game_type == 1) {
        if (score >= 0x28) {
            rank = 2;
        }
        if (score >= 0x3C) {
            rank = 3;
        }
        if (score >= 0x50) {
            rank = 4;
        }
        if (score >= 0x5A) {
            rank = 5;
        }
    } else {
        if (score >= 0x14) {
            rank = 2;
        }
        if (score >= 0x32) {
            rank = 3;
        }
        if (score >= 0x41) {
            rank = 4;
        }
        if (score >= 0x50) {
            rank = 5;
        }
    }
    return rank;
}
