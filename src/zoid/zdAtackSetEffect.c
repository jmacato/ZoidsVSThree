#include "zoid3.h"

typedef struct ZoidData3 {
    u8 reserved_0000[0x666];
    s16 attack_effects[12][2];
    s16 attack_effect_mounts[12][2];
    u8 reserved_06C6[0x70E - 0x6C6];
    s16 field_070E[12];
    u8 reserved_0726[0x7FC - 0x726];
} ZoidData3;

extern ZoidData3 Tea_zoiddat[];
extern void zdEffectMountTm(ZoidState *zoid, s32 mount, s32 effect, s32 tm);

void zdAtackSetEffect(ZoidState *zoid, s32 attack)
{
    s32 i;
    s32 effect;
    s32 mount;
    s32 tm;

    tm = Tea_zoiddat[zoid->type].field_070E[attack];
    for (i = 0; i < 2; i++) {
        effect = Tea_zoiddat[zoid->type].attack_effects[attack][i];
        mount = Tea_zoiddat[zoid->type].attack_effect_mounts[attack][i];
        if (effect > 0 && zoid->weapon_slots[mount].joint != (void *)0) {
            zdEffectMountTm(zoid, mount, effect, tm);
        }
    }
}
