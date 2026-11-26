#include "zoid3.h"

typedef struct ZoidData3 {
    u8 reserved_000[0x6C6];
    s16 attack_ranges[12];
    s16 attack_angles_a[12];
    s16 attack_angles[12];
    u8 reserved_70E[0x7FC - 0x70E - 0x18];
    u8 tail[0x18];
} ZoidData3;

extern ZoidData3 Tea_zoiddat[];
extern f32 ZoidCalcAngle(ZoidState *zoid, Vec3 *point);

inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

void zdAtk(ZoidState *zoid)
{
    ZoidState *target;
    s32 attack;
    s32 index;
    f32 range;
    f32 half_angle;
    f32 other_angle;
    f32 height;
    f32 angle;

    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        attack = 0;
        if (zoid->action == 13) attack = 0;
        if (zoid->action == 14) attack = 1;
        if (zoid->action == 15) attack = 2;
        if (zoid->action == 16) attack = 3;
        if (zoid->action == 17) attack = 4;
        if (zoid->action == 18) attack = 5;
        if (zoid->action == 19) attack = 6;
        if (zoid->action == 20) attack = 7;
        if (zoid->action == 21) attack = 8;
        if (zoid->action == 22) attack = 9;
        range = Tea_zoiddat[zoid->type].attack_ranges[attack];
        other_angle = 2.0 * (3.1415926 * (f32)Tea_zoiddat[zoid->type].attack_angles_a[attack]) / 360.0;
        half_angle = 2.0 * (3.1415926 * (f32)Tea_zoiddat[zoid->type].attack_angles[attack]) / 360.0 / 2.0;
        for (index = 0; index < 16; index++) {
            target = &Zoid[index];
            zoid->attack_in_range[index] = 0;
            if (target->joint != (void *)0 && target->death_started == 0 &&
                (u32)target->slot != (u32)zoid->slot && !(range < zoid->distances[index])) {
                height = absf(zoid->position[1] - target->position[1]);
                if (!(height > 15.0)) {
                    angle = ZoidCalcAngle(zoid, (Vec3 *)target->position);
                    if (angle != 100.0f) {
                        if (!(absf(angle) > half_angle))
                            zoid->attack_in_range[index] = 1;
                    }
                }
            }
        }
    }
}
