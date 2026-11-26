#include "zoid3.h"

extern void zdCalcWeaponS(ZoidState *zoid, s32 part);

typedef struct SWeaponEntry {
    s32 active;
    u8 pad_04[8];
    s32 type;
    u8 pad_10[0x6dc - 0x10];
} SWeaponEntry;

extern SWeaponEntry sWeapon[];

void zdCalcWeapon(ZoidState *zoid, s32 weapon)
{
    SWeaponEntry *entry;

    if (zoid != 0 && weapon >= 0) {
        entry = &sWeapon[weapon];
        if (entry->active != 0) {
            zdCalcWeaponS(zoid, entry->type);
        }
    }
}
