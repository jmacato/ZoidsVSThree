#include "zoid3.h"

#pragma readonly_strings on

typedef struct Missile3 {
    s32 flags;
    u8 pad_04[0x0C - 0x04];
    s32 kind;
    u8 pad_10[0x24 - 0x10];
    HSD_JObj *joint;
    u8 pad_28[0x34 - 0x28];
    struct Missile3 *target_missile;
    u8 pad_38[0x3C - 0x38];
    void *field_3C;
    u8 pad_40[0xF4 - 0x40];
    s32 purge_timer;
    s32 field_F8;
    u8 pad_FC[0x180 - 0xFC];
    u32 field_180;
    u8 pad_184[0x1A4 - 0x184];
} Missile3;

typedef struct WeaponInverse3 {
    HSD_JObj *joint;
    u8 pad_04[0x38 - 0x04];
} WeaponInverse3;

typedef struct WeaponState3 {
    s32 active;
    u8 pad_04[0x3C - 0x04];
    ZoidState *owner;
    u8 pad_40[0x148 - 0x40];
    WeaponInverse3 inverses[12];
    u8 pad_3E8[0x408 - 0x3E8];
    s16 drain;
    u8 pad_40A[0x6DC - 0x40A];
} WeaponState3;

extern Missile3 missileStart[200];
extern WeaponState3 sWeapon[100];
#define NULL 0
extern void __assert(const char *file, s32 line, const char *expr);
extern void sMissileZoid1Smoke(Missile3 *missile, ZoidState *zoid);
extern void sMissileZoid1Mine(Missile3 *missile, ZoidState *zoid);
extern s32 sMissileZoid1(Missile3 *missile, ZoidState *zoid);
extern s32 sMissileAtk(Missile3 *missile, WeaponInverse3 *target);
extern void sMissileMis1(Missile3 *missile, Missile3 *other);

static inline f32 HSD_JObjGetScaleX(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 899, "jobj");
    return jobj->scale.x;
}

void sMissileZoid(void)
{
    Missile3 *missile = missileStart;
    s32 i;
    s32 j;
    s32 k;
    WeaponState3 *weapon;
    ZoidState *owner;
    HSD_JObj *joint;
    Missile3 *other;
    s32 m;

    for (i = 0; i < 200; i++, missile++) {
        if (missile == (void *)0)
            return;
        if (!(missile->flags & 1))
            continue;
        if (missile->purge_timer != 0)
            continue;
        if (missile->kind != 6 && missile->field_180 == 0 && missile->field_F8 > 1)
            continue;
        if (missile->joint == (void *)0)
            continue;
        if (missile->field_3C != (void *)0)
            continue;
        switch (missile->kind) {
        case 5:
            for (j = 0; j < 16; j++) {
                sMissileZoid1Smoke(missile, &Zoid[j]);
            }
            break;
        case 6:
            for (j = 0; j < 16; j++) {
                sMissileZoid1Mine(missile, &Zoid[j]);
            }
            break;
        default:
            if (missile->field_180 != 0) {
                for (j = 0; j < 16; j++) {
                    sMissileZoid1Mine(missile, &Zoid[j]);
                }
            }
            if (missile->field_F8 > 1)
                continue;
            for (j = 0; j < 16; j++) {
                if (sMissileZoid1(missile, &Zoid[j]) != 0)
                    break;
            }
            for (j = 0; j < 100; j++) {
                weapon = &sWeapon[j];
                owner = weapon->owner;
                if (weapon->active == 0)
                    continue;
                for (k = 0; k < 12; k++) {
                    joint = weapon->inverses[k].joint;
                    if (joint == (void *)0)
                        continue;
                    if (HSD_JObjGetScaleX(joint) < 0.8)
                        continue;
                    if (sMissileAtk(missile, &weapon->inverses[k]) == 0)
                        continue;
                    if (weapon->drain != 0 && owner != 0 && owner->option_type == 1) {
                        owner->option_energy -= 200;
                        if (owner->option_energy < 0)
                            owner->option_energy = 0;
                    }
                    break;
                }
            }
            break;
        }
        if (missile->target_missile != 0)
            sMissileMis1(missile, missile->target_missile);
        other = missileStart;
        for (m = 0; m < 200; m++, other++) {
            if (other == missile)
                continue;
            if (other == (void *)0)
                break;
            if (!(other->flags & 1))
                continue;
            if (other->joint == (void *)0)
                continue;
            if (other->purge_timer != 0)
                continue;
            if (other->field_3C != (void *)0)
                continue;
            sMissileMis1(missile, other);
        }
    }
}
