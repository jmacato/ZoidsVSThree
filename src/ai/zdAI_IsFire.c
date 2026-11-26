#include "zoid3.h"
#include "zoid_ai.h"

typedef struct WeaponSlot3 {
    u8 reserved_00[0x0C];
    s32 field_0C;
    u8 reserved_10[4];
    ZoidState *target;
    u8 reserved_18[4];
    void *field_1C;
    u8 reserved_20[4];
} WeaponSlot3;

typedef struct WeaponState3 {
    u8 reserved_000[0x400];
    s32 count;
    u8 reserved_404[8];
    WeaponSlot3 slots[16];
    u8 reserved_64C[0x90];
} WeaponState3;

extern WeaponState3 sWeapon[100];
extern void aiCmdReport(const char *msg);

s32 zdAI_IsFire(s32 index)
{
    WeaponSlot3 *slot;
    s32 count;
    s32 weapon;
    s32 i;
    ZoidState *zoid;
    WeaponState3 *w;
    ZoidState *target;

    aiCmdReport("aiCmd-isFire \n");
    if (index < 0) {
        return 0;
    }
    if (index >= 16) {
        return 0;
    }
    zoid = &Zoid[index];
    if (zoid->joint == 0) {
        return 0;
    }
    if (zoid->death_started != 0) {
        return 0;
    }
    weapon = zdAI_WeaponGetID(index);
    if (weapon == -1) {
        return 0;
    }
    w = &sWeapon[weapon];
    if (w == 0) {
        return 0;
    }
    count = w->count;
    if (count < 1) {
        return 0;
    }
    for (i = 0; i < count; i++) {
        slot = &w->slots[i];
        if (slot->field_1C == 0) {
            continue;
        }
        if (slot->field_0C == 0) {
            continue;
        }
        target = slot->target;
        if (target == 0) {
            break;
        }
        if (target->joint == 0) {
            continue;
        }
        if (target->death_started == 0) {
            break;
        }
    }
    if (i == count) {
        return 0;
    }
    return 1;
}
