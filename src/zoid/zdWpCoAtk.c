#include "zoid3.h"

typedef struct CoObj3 {
    HSD_JObj *joint;
    u8 pad_04[0x64];
    s32 hit_flag;
    s32 health;
} CoObj3;

extern s32 sChkCubeInSphere(f32 (*cube)[4], f32 (*sphere)[4]);
extern void sEffectSet(s32 effect, s32 a, f32 *position, s32 b, s32 c);

s32 zdWpCoAtk(CoObj3 *object, ZoidAttackObject *target, s32 kind, s32 damage)
{
    s32 hit;
    f32 position[3];
    s32 i;

    if (object == (void *)0) {
        return 0;
    }
    if (object->joint == (void *)0) {
        return 0;
    }
    if (target == (void *)0) {
        return 0;
    }
    if (target->joint == 0) {
        return 0;
    }
    {
        f32 (*inverse)[4] = target->inverse;
        hit = sChkCubeInSphere(object->joint->matrix, inverse);
    }
    if (hit == 0) {
        return 0;
    }
    if (kind != -1) {
        for (i = 0; i < 3; i++) {
            position[i] = (object->joint->matrix[i][3] + target->joint->matrix[i][3]) / 2.0f;
        }
        sEffectSet(kind, 0, position, 0, 0);
    }
    object->health -= damage;
    if (object->health < 0) {
        object->health = 0;
    }
    object->hit_flag = 1;
    return hit;
}
