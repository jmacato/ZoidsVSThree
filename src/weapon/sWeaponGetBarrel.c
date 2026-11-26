#pragma readonly_strings on
#include "types.h"
#include "joint_matrix.h"

typedef struct PartData3 {
    u8 reserved_00[0x48];
    char model_name[8];
    u8 reserved_50[0x5C - 0x50];
    s32 bullets[2];
    u32 flags;
    s16 category;
    s16 armor_bonus;
    s16 power;
    s16 range;
    s16 ammo;
    u8 reserved_72[0x124 - 0x72];
} PartData3;

typedef struct WeaponState3 {
    s32 active;
    u8 reserved_04[0x0C - 0x04];
    s32 type;
    struct ModelArchive3 *archive;
    s32 model;
    u8 reserved_18[0x48 - 0x18];
    HSD_JObj *barrels[12];
    u8 reserved_78[0x6DC - 0x78];
} WeaponState3;

typedef struct ModelArchive3 {
    u8 reserved_00[0x3C];
    HSD_JObj *models[1];
} ModelArchive3;

extern PartData3 Tea_partsdat[];
extern f64 __frsqrte(f64 value);

static inline f32 sqrtf(f32 x, volatile f32 *y)
{
    if (x > 0.0f) {
        f64 guess = __frsqrte(x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        *y = x * guess;
        return *y;
    }
    return x;
}

s32 sWeaponGetBarrel(WeaponState3 *weapon, Vec3 *out, f32 distance)
{
    /* MWCC binds this return value before removing its copies. */
    s32 result;
    s32 bullets[2];
    s32 type;
    s32 model;
    s32 i;
    s32 j;
    f32 length;
    volatile f32 root;

    if (weapon == (void *)0) {
        result = 0;
        return result;
    }
    if (weapon->active == 0) {
        result = 0;
        return result;
    }
    type = weapon->type;
    model = weapon->model;
    bullets[0] = Tea_partsdat[type].bullets[0];
    bullets[1] = Tea_partsdat[type].bullets[1];
    if (distance == 0.0f)
        distance = (f32)Tea_partsdat[type].range;
    if (bullets[0] <= 0) {
        result = 0;
        return result;
    }
    if (bullets[1] <= 0)
        bullets[1] = bullets[0];
    if (weapon->archive->models[model] == (void *)0) {
        result = 0;
        return result;
    }
    for (i = 0; i < 12; i++) {
        HSD_JObj *barrel = weapon->barrels[i];
        if (barrel == (void *)0)
            continue;
        barrel ? (void)0 : __assert("jobj.h", 899, "jobj");
        length = barrel->scale.x;
        if (length < 0.2)
            continue;
        /* MWCC drops the widened addresses' high words after allocation.
         * Their temporary lifetimes reproduce the original schedule. */
        length = sqrtf(
            ((HSD_JObj *)(s32)(s64)(s32)barrel)->matrix[1][0] *
                ((HSD_JObj *)(s32)(s64)(s32)barrel)->matrix[1][0] +
            ((HSD_JObj *)(s32)(s64)(s32)barrel)->matrix[0][0] *
                ((HSD_JObj *)(s32)(s64)(s32)barrel)->matrix[0][0] +
            barrel->matrix[2][0] * barrel->matrix[2][0], &root);
        for (j = 0; j < 3; j++) {
            (&out->x)[j] = distance * (barrel->matrix[j][0] / length) + barrel->matrix[j][3];
        }
        break;
    }
    if (i == 12) {
        result = 0;
        return result;
    }
    result = 1;
    return result;
}
