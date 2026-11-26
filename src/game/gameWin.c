#include "game_mode.h"

extern s32 calcEnd(void);

s32 gameWin(void)
{
    s32 result = 0;

    result = calcEnd();
    if (GameMode.game_type == 5) {
        if (result == GAME_RESULT_NONE) {
            return GAME_RESULT_DRAW;
        }
        return GAME_RESULT_WIN;
    }
    if (result == GAME_RESULT_NONE) {
        return GAME_RESULT_DRAW;
    }
    return result;
}
