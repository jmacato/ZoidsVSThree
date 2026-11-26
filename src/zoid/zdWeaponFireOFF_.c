#include "zoid3.h"

extern s32 sWeaponGetAnim(s32 weapon);
extern void sWeaponLoopOFF(s32 weapon);

void zdWeaponFireOFF_(ZoidState *zoid, s32 selected)
{
    WeaponMount *mount = &zoid->weapon_mounts[selected];
    s32 index;
    s32 slot;
    s32 anim;

    if (mount->active != 0) {
        for (index = 0; index < 4; index++) {
            if (mount->entries[index].active != 0) {
                slot = mount->entries[index].slot;
                if (slot != -1) {
                    anim = sWeaponGetAnim(zoid->weapon_slots[slot].weapon);
                    if (anim == 2) {
                        sWeaponLoopOFF(zoid->weapon_slots[slot].weapon);
                    }
                }
            }
        }
    }
}
