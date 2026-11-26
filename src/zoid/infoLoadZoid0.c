#include "zoid3.h"

typedef struct ZoidInfo {
    s32 type;
    s16 additional_parts[3];
    s16 health_bonus;
    u8 reserved_0C[0xC];
    s16 weapon_slots[10];
    s16 weapon_parts[10];
    u8 reserved_40[0xF];
    s8 color;
    s8 person;
} ZoidInfo;

extern s32 ZoidInit_(ZoidState *zoid, s32 type, s32 flags);
extern s32 ZoidColor(ZoidState *zoid, s32 color, s32 flags);

s32 infoLoadZoid0(ZoidState *zoid, ZoidInfo *info)
{
    if (zoid == (void *)0) {
        return 0;
    }
    if (info == (void *)0) {
        return 0;
    }
    ZoidInit_(zoid, info->type, 0);
    zoid->max_health += info->health_bonus;
    zoid->health += info->health_bonus;
    zoid->person = info->person;
    ZoidColor(zoid, info->color, 0);
    return 1;
}
