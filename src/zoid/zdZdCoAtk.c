#include "zoid3.h"
#include "missile.h"

extern s32 sChkCubeInSphere(f32 (*cube)[4], f32 (*sphere)[4]);

typedef struct CoObjV3 {
    HSD_JObj *joint;
    u8 reserved[0x64];
    u32 field_5C;
    s32 health;
} CoObjV3;

s32 zdZdCoAtk(CoObjV3 *co, ZoidAttackObject *attack, s32 effect, s32 damage)
{
    s32 hit;
    f32 position[3];
    s32 i;
    f32 (*inverse)[4];

    if (co == (void *)0) {
        return 0;
    }
    if (co->joint == (void *)0) {
        return 0;
    }
    if (attack == (void *)0) {
        return 0;
    }
    inverse = attack->inverse;
    hit = sChkCubeInSphere(co->joint->matrix, inverse);
    if (hit == 0) {
        return 0;
    }
    if (effect != -1) {
        for (i = 0; i < 3; i++) {
            position[i] = (co->joint->matrix[i][3] + attack->joint->matrix[i][3]) / 2.0f;
        }
        sEffectSet(effect, 0, position, 0, 0);
    }
    co->health -= damage;
    if (co->health < 0) {
        co->health = 0;
    }
    co->field_5C = 1;
    return hit;
}
