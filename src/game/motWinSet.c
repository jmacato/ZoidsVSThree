#include "game_mode.h"

extern void motWinSet4p(void);
extern void motWinSetN(void);

void motWinSet(void)
{
    if (GameMode.game_type == 5) {
        motWinSet4p();
    } else {
        motWinSetN();
    }
}
