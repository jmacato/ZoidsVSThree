#include "game_mode.h"

extern s32 calcEndBattle(void);
extern s32 calcEndVsMan(void);
extern s32 calcEndMission(void);
extern s32 calcEndVs4p(void);

s32 calcEnd(void)
{
    switch (GameMode.game_type) {
    case GAME_TYPE_BATTLE:
        return calcEndBattle();
    case GAME_TYPE_VS:
        return calcEndVsMan();
    case GAME_TYPE_3:
        return calcEndVsMan();
    case GAME_TYPE_MISSION:
        return calcEndMission();
    case 5:
        return calcEndVs4p();
    default:
        return calcEndBattle();
    }
}
