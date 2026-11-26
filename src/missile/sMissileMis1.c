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

typedef struct BulletDat3 {
    char name[8];
    s32 damage;
    s16 speed;
    u8 pad_0E[0x12 - 0x0E];
    s16 kind;
    u8 pad_14[0x16 - 0x14];
    s16 trace_rate;
    u8 pad_18[0x1A - 0x18];
    s16 zoid_hit;
    s16 hit_effect;
    s16 fire_effect;
    s16 se;
    u8 pad_22[0x28 - 0x22];
    s16 turn_angle;
    u8 pad_2A[0x4C - 0x2A];
} BulletDat3;

#pragma readonly_strings on
extern void PSMTXMultVec(f32 m[3][4], Vec3 *src, Vec3 *dst);
extern f32 sLenJobj(HSD_JObj *a, HSD_JObj *b);
extern s32 sDivLineVn(Vec3 *a, Vec3 *b, s32 axis, f32 value, Vec3 *out);
extern void sMissileSetAnim(Missile3 *missile, s32 anim);

void sMissileMis1(Missile3 *missile, Missile3 *other)
{
    Vec3 end;
    Vec3 start;
    f32 radius;
    f32 dist;
    f32 (*inverse)[4];
    s32 i;

    if (missile == 0)
        return;
    if (other == (void *)0)
        return;
    if (other->joint == (void *)0)
        return;
    if (other->purge_timer != 0)
        return;
    if (missile->owner == other->owner)
        return;
    radius = missile->step_length;
    inverse = missile->inverse;
    dist = sLenJobj(missile->joint, other->joint);
    if (dist > radius + other->step_length)
        return;
    for (i = 0; i < 3; i++) {
        (&end.x)[i] = other->matrix[i][3];
        (&start.x)[i] = other->previous[i][3];
    }
    PSMTXMultVec(inverse, &end, &end);
    PSMTXMultVec(inverse, &start, &start);
    if (start.x < -(0.5 + radius) && end.x < -(0.5 + radius))
        return;
    if (start.x > 0.5 && end.x > 0.5)
        return;
    if (start.x < -(0.5 + radius) && sDivLineVn(&start, &end, 0, -(0.5 + radius), &start) == 0)
        return;
    if (end.x < -(0.5 + radius) && sDivLineVn(&start, &end, 0, -(0.5 + radius), &end) == 0)
        return;
    if (start.x > 0.5 && sDivLineVn(&start, &end, 0, 0.5f, &start) == 0)
        return;
    if (end.x > 0.5 && sDivLineVn(&start, &end, 0, 0.5f, &end) == 0)
        return;
    if (start.z < -0.5 && end.z < -0.5)
        return;
    if (start.z > 0.5 && end.z > 0.5)
        return;
    if (start.z < -0.5 && sDivLineVn(&start, &end, 2, -0.5f, &start) == 0)
        return;
    if (end.z < -0.5 && sDivLineVn(&start, &end, 2, -0.5f, &end) == 0)
        return;
    if (start.z > 0.5 && sDivLineVn(&start, &end, 2, 0.5f, &start) == 0)
        return;
    if (end.z > 0.5 && sDivLineVn(&start, &end, 2, 0.5f, &end) == 0)
        return;
    if (start.x < -(0.5 + radius) && end.x < -(0.5 + radius))
        return;
    if (start.x > 0.5 && end.x > 0.5)
        return;
    if (start.y < -0.5 && end.y < -0.5)
        return;
    if (start.y > 0.5 && end.y > 0.5)
        return;
    if (start.z < -0.5 && end.z < -0.5)
        return;
    if (start.z > 0.5 && end.z > 0.5)
        return;
    if (missile->hit == 0) {
        missile->hit = 1;
        sMissileSetAnim(missile, 1);
    }
    if (other->hit == 0) {
        other->hit = 1;
        sMissileSetAnim(other, 1);
    }
}
