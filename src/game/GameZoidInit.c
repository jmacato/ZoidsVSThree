#include "game_zoid_entry.h"

void GameZoidInit(void)
{
    s32 i;
    for (i = 0; i < 16; i++) {
        GameZoid[i].type = -1;
    }
}
