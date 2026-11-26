#include "zoid3.h"

typedef struct ZoidDataVS3 {
    u8 pad_0000[0x74];
    s16 default_parts[8];
    s16 mount[8];
    u8 pad_0094[0x28];
    s16 weapon_flag[4];
    u8 pad_00C4[0x7FC - 0xC4];
} ZoidDataVS3;

extern ZoidDataVS3 Tea_zoiddat[];
extern void zdCalcPre(ZoidState *zoid);
extern void zdCalcWeaponS(ZoidState *zoid, s32 part);
extern void zdCalcMan(ZoidState *zoid, s32 part);
extern void zdCalcEpi(ZoidState *zoid);

void zdCalcZoid(ZoidState *zoid, s32 type, s32 arg)
{
    ZoidDataVS3 *data;
    s32 part;
    s32 i;
    s32 weapon;

    if (zoid == 0) {
        return;
    }
    zoid->type = type;
    data = &Tea_zoiddat[type];
    zdCalcPre(zoid);
    for (i = 0; i < 8; i++) {
        part = data->default_parts[i];
        if (part != -1) {
            zdCalcWeaponS(zoid, part);
        }
    }
    weapon = -1;
    if (data->weapon_flag[0] != 0) {
        weapon = data->mount[0];
    }
    if (data->weapon_flag[1] != 0) {
        weapon = data->mount[1];
    }
    if (data->weapon_flag[2] != 0) {
        weapon = 0x115;
    }
    if (data->weapon_flag[3] != 0) {
        weapon = 0x18E;
    }
    if (weapon > 0) {
        zdCalcWeaponS(zoid, weapon);
    }
    zdCalcMan(zoid, -1);
    zdCalcEpi(zoid);
    arg = arg;
}
