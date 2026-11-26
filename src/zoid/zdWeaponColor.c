#include "zoid3.h"

extern s32 sWeaponColor(s32 weapon, s32 color, s32 unused);

s32 zdWeaponColor(ZoidState *zoid, s32 slot, s32 color)
{
    if (zoid == 0) {
        return 0;
    }
    if (zoid->joint == 0) {
        return 0;
    }
    if (slot < 0) {
        return 0;
    }
    if (slot >= 30) {
        return 0;
    }
    if (sWeaponColor(zoid->weapon_slots[slot].weapon, color, 0) == 0) {
        return 0;
    }
    return 1;
}
