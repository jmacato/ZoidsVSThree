#include "zoid3.h"

typedef struct ZoidDataSuper {
    u8 reserved_0000[0x74];
    s16 params[0x20];
    u8 reserved_00B4[0x7FC - 0xB4];
} ZoidDataSuper;

extern ZoidDataSuper Tea_zoiddat[];
extern void sWeaponMount(s32 part, ZoidState *zoid, s32 slot, s32 mount);
extern void OSReport(const char *format, ...);

void zdLoadSuperAtackWp(ZoidState *zoid)
{
    s32 index = 0;
    s32 type = zoid->type;
    s32 part;
    s32 slot;
    s32 w;
    slot = Tea_zoiddat[type].params[index * 2 + 20];
    part = Tea_zoiddat[type].params[index * 2 + 21];

    if (part > 0 && slot >= 0) {
        sWeaponMount(part, zoid, slot, 0x13);
        w = zoid->weapon_slots[slot].weapon;
        OSReport("mount [%s] -- ", zoid);
    }
}
