#include "zoid3.h"

extern s32 sWeaponGetAnim(s32 weapon);
extern void sWeaponSetAnim(s32 weapon, s32 animation);
extern void sWeaponLoopOFF(s32 weapon);
extern void sWeaponLoopON(s32 weapon);
extern void sWeaponStopOFF(s32 weapon);
extern void zdWeaponFireVoice(ZoidState *zoid);

void zdWeaponFireON_(ZoidState *zoid, s32 selected)
{
    WeaponMount *mount = &zoid->weapon_mounts[selected];
    s32 slot;
    s32 index;
    s32 animation;

    if (mount->active != 0) {
        zoid->anim1_frames = 0;
        for (index = 0; index < 4; index++) {
            if (mount->entries[index].active != 0) {
                slot = mount->entries[index].slot;
                if (slot != -1) {
                    if (zoid->death_started != 0) {
                        sWeaponLoopOFF(zoid->weapon_slots[slot].weapon);
                    } else {
                        animation = sWeaponGetAnim(zoid->weapon_slots[slot].weapon);
                        if (animation == 2) {
                            sWeaponLoopON(zoid->weapon_slots[slot].weapon);
                            sWeaponStopOFF(zoid->weapon_slots[slot].weapon);
                        }
                        if (animation == 1) {
                            zdWeaponFireVoice(zoid);
                            sWeaponSetAnim(zoid->weapon_slots[slot].weapon, 2);
                            sWeaponLoopON(zoid->weapon_slots[slot].weapon);
                            sWeaponStopOFF(zoid->weapon_slots[slot].weapon);
                        }
                    }
                }
            }
        }
    }
}
