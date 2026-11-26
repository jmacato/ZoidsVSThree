#include "zoid3.h"

typedef struct ZoidDataV3 {
    u8 reserved_0000[0x50];
    s32 field_0050;
    u8 reserved_0054[4];
    s32 field_0058;
    u8 reserved_005C[0xC];
    s16 field_0068;
    s16 field_006A;
    u8 reserved_006C[0x732];
    s16 field_079E;
    u8 reserved_07A0[4];
    s16 field_07A4;
    s16 field_07A6;
    u8 reserved_07A8[0x54];
} ZoidDataV3;

typedef struct AnimDataV3 {
    u8 reserved_0000[0xBC];
    s32 field_00BC;
} AnimDataV3;

extern ZoidDataV3 Tea_zoiddat[];

void zdCalcEpi(ZoidState *zoid)
{
    ZoidDataV3 *data = &Tea_zoiddat[zoid->type];
    AnimDataV3 *anim = zoid->anim_data;

    zoid->field_1EF8 = (f32)(data->field_07A4 + zoid->radar_range_bonus);
    zoid->search_range = (f32)(data->field_07A6 + zoid->search_range_bonus);
    zoid->armor = data->field_0068 + zoid->armor_bonus;
    if (zoid->armor < 1) {
        zoid->armor = 1;
    }
    if (anim != 0) {
        zoid->field_1F04 = anim->field_00BC + zoid->speed_bonus;
    } else {
        zoid->field_1F04 = data->field_006A + zoid->speed_bonus;
    }
    zoid->field_20F8 = data->field_0050 + zoid->field_20F4;
    zoid->field_20C0 = data->field_0058 + zoid->field_20C4;
    if (zoid->field_20C0 < 0) {
        zoid->field_20C0 = 0;
    }
    zoid->field_20EC = data->field_079E + zoid->turn_bonus;
}
