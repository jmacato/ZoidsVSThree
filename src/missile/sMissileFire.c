#include "zoid3.h"
#include "model_archive.h"
#include "angle.h"

typedef struct Missile3 {
    s32 flags;
    s32 bullet;
    s32 kind;
    s32 zoid_hit;
    s32 hit_ground;
    u8 pad_14[0x1C - 0x14];
    s32 animation;
    ModelArchive *archive;
    HSD_JObj *joint;
    struct ZoidState *owner;
    s32 owner_weapon_mount;
    struct ZoidState *target_zoid;
    struct Missile3 *target_missile;
    void *field_30;
    u8 pad_3C[0x50 - 0x3C];
    f32 speed;
    f32 turn_rate;
    f32 matrix[3][4];
    f32 previous[3][4];
    f32 step_length;
    f32 inverse[3][4];
    s32 update_count;
    s32 damage;
    s32 purge_timer;
    s32 hit;
    f32 max_speed;
    f32 accel;
    u8 pad_104[0x108 - 0x104];
    s32 proc;
    s32 proc_delay;
    HSD_JObj *beam_joints[7];
    f32 beam_positions[7][3];
    HSD_JObj *a1_joint;
    struct HSD_LObj *light;
    u8 hit_zoids[16];
    s32 se;
    s32 se_playing;
    u32 se_voice;
} Missile3;
extern f64 __frsqrte(f64);
extern void sMissileSet(ZoidState *owner, ZoidState *target_zoid, Missile3 *target_missile, s32 lock, f32 matrix[3][4], s32 bullet, s32 extra_damage);
static inline f32 sqrtf(f32 x, volatile f32 *y)
{

    if (x > 0.0f) {
        f64 guess = __frsqrte((f64)x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        *y = (f32)(x * guess);
        return *y;
    }
    return x;
}

void sMissileFire(ZoidState *owner, ZoidState *target_zoid, Missile3 *target_missile, s32 lock, f32 matrix[3][4], s32 bullet, s32 extra_damage)
{
    f32 copy[3][4];
    s32 i;
    s32 j;
    f32 length;
    volatile f32 root;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++)
            copy[i][j] = matrix[i][j];
    }
    length = sqrtf(matrix[1][0] * matrix[1][0] + matrix[0][0] * matrix[0][0] + matrix[2][0] * matrix[2][0], &root);
    for (i = 0; i < 3; i++)
        copy[i][0] = matrix[i][0] / length;
    sMissileSet(owner, target_zoid, target_missile, lock, copy, bullet, extra_damage);
}
