#include "game_mode.h"

extern s32 calcEnd(void);
extern s32 gameTime;
extern s32 gameStartF;

s32 gameEnd(void)
{
    s32 result;

    result = calcEnd();
    if (gameStartF == 0) {
        if (gameTime > 0) {
            gameTime -= 1;
        }
    }
    if (gameTime == 0) {
        return 1;
    }
    if (result != GAME_RESULT_NONE) {
        return 1;
    }
    return 0;
}
