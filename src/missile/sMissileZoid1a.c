#include "zoid3.h"

#define NULL ((void *)0)

typedef struct Missile3 {
    u8 pad_000[0x58];
    f32 matrix[3][4];
    f32 previous[3][4];
    u8 pad_0B8[0xF0 - 0xB8];
    s32 damage;
} Missile3;

extern void PSMTXMultVec(f32 m[3][4], Vec3 *src, Vec3 *dst);
extern f32 sColCube4LineConnect(Vec3 *first, Vec3 *second);
extern void ZoidCoObjMove(CoObj *object, Vec3 *move, f32 ratio);

f32 sMissileZoid1a(Missile3 *missile, ZoidState *zoid, CoObj *object, s32 push)
{
    f32 (*inverse)[4];
    Vec3 current;
    Vec3 previous;
    Vec3 move;
    f32 t;
    f32 ratio;
    f32 dot;
    s32 i;

    if (object == NULL)
        return -1.0f;
    if (object->joint == NULL)
        return -1.0f;
    ratio = 0.0f;
    if (zoid != 0 && zoid->joint != 0 && missile != 0) {
        if (zoid->armor < 1)
            zoid->armor = 1;
        ratio = 10.0 * (f32)missile->damage / (f32)zoid->armor;
    }
    inverse = (f32 (*)[4])((u8 *)object + 0x38);
    for (i = 0; i < 3; i++) {
        ((f32 *)&current)[i] = missile->matrix[i][3];
        ((f32 *)&previous)[i] = missile->previous[i][3];
    }
    PSMTXMultVec(inverse, &current, &current);
    PSMTXMultVec(inverse, &previous, &previous);
    t = sColCube4LineConnect(&previous, &current);
    if (-1.0f != t && push != 0) {
        dot = 0.0f;
        for (i = 0; i < 3; i++) {
            ((f32 *)&move)[i] = 2.0f * missile->matrix[i][0];
            dot += ((f32 *)&move)[i] * ((f32 *)&move)[i];
        }
        ZoidCoObjMove(object, &move, ratio);
    }
    return t;
}
