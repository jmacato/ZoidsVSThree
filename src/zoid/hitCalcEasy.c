#include "zoid3.h"
#include "game_mode.h"
#include "game_save.h"

s32 hitCalcEasy(ZoidState *zoid, s32 damage)
{
    if (GameMode.game_type != 1 && GameMode.game_type != 4) {
        return damage;
    }
    if (((s8 *)IveSave)[0x1C63] == 0) {
        return damage;
    }
    if (zoid == 0) {
        return damage;
    }
    if (Zoid[0].slot != zoid->slot) {
        return damage;
    }
    damage = damage / 2;
    return damage;
}
