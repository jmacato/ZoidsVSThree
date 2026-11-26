#include "types.h"
#include "joint_matrix.h"

typedef struct PartData3 {
    u8 reserved_00[0x5C];
    s32 bullets[2];
    u32 flags;
    s16 category;
    s16 armor_bonus;
    s16 power;
    s16 range;
    s16 ammo;
    u8 reserved_72[0x124 - 0x72];
} PartData3;

typedef struct BulletDat3 {
    u8 reserved_00[0xC];
    s16 speed;
    u8 reserved_0E[0x4C - 0x0E];
} BulletDat3;

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
extern BulletDat3 Tea_bulletdat[];
extern f64 __frsqrte(f64 value);

s32 sWeaponGetBarrelParabola(WeaponState3 *weapon, Vec3 *out, f32 distance)
{
    s32 j;
    s32 i;
    s32 bullet;
    s32 model;
    s32 type;
    HSD_JObj *joint;
    f32 horizontal_root;
    f32 direction_root;
    f32 drop;
    f32 horizontal_length;
    f32 length;
    f32 horizontal_squared;
    f32 speed;
    f32 t;
    s32 bullets[2];
    Vec3 dir;
    /* Volatile stores round the square-root refinements to f32. */
    volatile f32 rounded_horizontal;
    volatile f32 rounded_direction;

    if (weapon == (void *)0)
        return 0;
    if (weapon->active == 0)
        return 0;
    model = weapon->model;
    type = weapon->type;
    bullets[0] = Tea_partsdat[type].bullets[0];
    bullets[1] = Tea_partsdat[type].bullets[1];
    if (distance == 0.0f)
        distance = (f32)Tea_partsdat[type].range;
    if (bullets[0] <= 0)
        return 0;
    if (bullets[1] <= 0)
        bullets[1] = bullets[0];
    if (weapon->archive->models[model] == (void *)0)
        return 0;
    for (i = 0; i < 12; i++) {
        joint = weapon->barrels[i];
        if (joint == (void *)0)
            continue;
        joint ? (void)0 : __assert("jobj.h", 899, "jobj");
        length = joint->scale.x;
        if (length < 0.2)
            continue;
        {
            f32 x = joint->matrix[1][0] * joint->matrix[1][0] +
                    joint->matrix[0][0] * joint->matrix[0][0] +
                    joint->matrix[2][0] * joint->matrix[2][0];
            if (x > 0.0f) {
                f64 guess = __frsqrte(x);
                guess = 0.5 * guess * (3.0 - guess * guess * x);
                guess = 0.5 * guess * (3.0 - guess * guess * x);
                guess = 0.5 * guess * (3.0 - guess * guess * x);
                rounded_direction = x * guess;
                direction_root = rounded_direction;
            } else {
                direction_root = x;
            }
        }
        length = direction_root;
        bullet = bullets[i & 1];
        if (bullet < 0)
            continue;
        speed = 0.1 * Tea_bulletdat[bullet].speed;
        for (j = 0; j < 3; j++) {
            (&dir.x)[j] = joint->matrix[j][0] * speed / length;
        }
        {
            static const f64 _half = 0.5;
            static const f64 _three = 3.0;
            horizontal_squared = (&dir.x)[0] * (&dir.x)[0] + (&dir.x)[2] * (&dir.x)[2];
            if (horizontal_squared > 0.0f) {
                f64 guess = __frsqrte((f64)horizontal_squared);
                guess = _half * guess * (_three - guess * guess * horizontal_squared);
                guess = _half * guess * (_three - guess * guess * horizontal_squared);
                guess = _half * guess * (_three - guess * guess * horizontal_squared);
                guess = _half * guess * (_three - guess * guess * horizontal_squared);
                rounded_horizontal = (f32)(horizontal_squared * guess);
                horizontal_root = rounded_horizontal;
            } else {
                horizontal_root = horizontal_squared;
            }
        }
        horizontal_length = horizontal_root;
        if (0.0f == horizontal_length)
            return 0;
        t = distance / horizontal_length;
        drop = 0.025 * (t * (1.0f + t) / 2.0f);
        for (j = 0; j < 3; j++) {
            (&out->x)[j] = t * (&dir.x)[j] + joint->matrix[j][3];
        }
        out->y -= drop;
        break;
    }
    if (i == 12)
        return 0;
    return 1;
}
