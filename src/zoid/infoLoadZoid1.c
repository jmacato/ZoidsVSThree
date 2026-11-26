#include "zoid3.h"

typedef struct ZoidInfo {
    s32 type;
    s16 additional_parts[3];
    u8 reserved_0A[0xE];
    s16 weapon_slots[10];
    s16 weapon_parts[10];
    u8 weapon_colors[10];
    s16 option;
    u8 field_4C;
    u8 field_4D;
    u8 field_4E;
} ZoidInfo;

extern void sWeaponMount(s32 part, ZoidState *zoid, s32 slot, s32 mount);
extern void zdWeaponColor(ZoidState *zoid, s32 slot, s32 color);
extern void zdLoadOption(ZoidState *zoid, s32 option);

s32 infoLoadZoid1(ZoidState *zoid, ZoidInfo *info)
{
    s32 i;
    s32 slot;
    s32 part;

    if (zoid == (void *)0) {
        return 0;
    }
    if (info == (void *)0) {
        return 0;
    }
    zoid->field_20A0 = info->field_4E + (info->field_4C << 8);
    for (i = 0; i < 10; i++) {
        slot = info->weapon_slots[i];
        part = info->weapon_parts[i];
        if (slot != 27 && slot != -1 && part > 0) {
            sWeaponMount(part, zoid, slot, i);
            zdWeaponColor(zoid, slot, (s8)info->weapon_colors[i]);
        }
    }
    zdLoadOption(zoid, info->option);
    for (i = 0; i < 3; i++) {
        zoid->additional_parts[i] = info->additional_parts[i];
    }
    return 1;
}
