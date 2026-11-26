#include "zoid3.h"
#include "model_archive.h"
#include "angle.h"
#pragma readonly_strings on

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
    s8 hit_zoids[16];
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

extern BulletDat3 Tea_bulletdat[131];
#define NULL 0
extern s32 chk12(CoObj *object, HSD_JObj *target, f32 range);
extern f32 sColPosY(Vec3 *point, u16 *selector);
extern f32 sLenPoint3dR(Vec3 *point);
extern void ZoidCopyAnim(ZoidState *zoid);
extern void sEffectSet(s32 id, s32 a, s32 b, HSD_JObj *joint, s32 c);
extern void __assert(const char *file, s32 line, const char *expr);
static inline f32 HSD_JObjGetScaleX(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 899, "jobj");
    return jobj->scale.x;
}

extern void sMissileSetAnim(Missile3 *missile, s32 anim);

void sMissileZoid1Mine(Missile3 *missile, ZoidState *zoid)
{
    ZoidState *owner;
    HSD_JObj *a1_joint;
    HSD_JObj *camera_joint;
    s32 hit_anim;
    s32 health;
    f32 range;
    register f32 dist;
    register f32 delta;
    Vec3 position;
    ZoidState *killer;
    s32 i;

    if (zoid == (void *)0)
        return;
    if (zoid->joint == (void *)0)
        return;
    camera_joint = (HSD_JObj *)zoid->camera_joint;
    if (camera_joint == 0)
        return;
    if (missile == (void *)0)
        return;
    a1_joint = missile->a1_joint;
    owner = missile->owner;
    if (a1_joint == (void *)0)
        return;
    if (owner) {
        (void)0;
    }
    if (missile->update_count < 6)
        return;
    if ((s32)missile->hit_zoids[zoid->index] == 1)
        return;
    range = HSD_JObjGetScaleX(a1_joint);
    if (range < 0.2)
        return;
    for (i = 0; i < 3; i++) {
        (&position.x)[i] = camera_joint->matrix[i][3];
    }
    position.y = sColPosY(&position, 0);
    dist = 0.0f;
    for (i = 0; i < 3; i++) {
        delta = (&position.x)[i] - a1_joint->matrix[i][3];
        dist += delta * delta;
    }
    range *= 0.5f;
    {
        s32 hit_parts = 0;
        if (chk12((CoObj *)zoid->l_arm2_coobj, a1_joint, range))
            hit_parts |= 1;
        if (chk12((CoObj *)zoid->l_arm1_coobj, a1_joint, range))
            hit_parts |= 2;
        if (chk12((CoObj *)zoid->r_arm2_coobj, a1_joint, range))
            hit_parts |= 4;
        if (chk12((CoObj *)zoid->r_arm1_coobj, a1_joint, range))
            hit_parts |= 8;
        if (chk12((CoObj *)zoid->l_leg2_coobj, a1_joint, range))
            hit_parts |= 16;
        if (chk12((CoObj *)zoid->l_leg1_coobj, a1_joint, range))
            hit_parts |= 32;
        if (chk12((CoObj *)zoid->r_leg2_coobj, a1_joint, range))
            hit_parts |= 64;
        if (chk12((CoObj *)zoid->r_leg1_coobj, a1_joint, range))
            hit_parts |= 128;
        if (chk12((CoObj *)zoid->hip_coobj, a1_joint, range))
            hit_parts |= 128;
        if (hit_parts == 0)
            return;
        if (zoid == missile->owner && missile->update_count < 180)
            return;
        missile->hit_zoids[zoid->index] = 1;
        if (missile->hit == 0) {
            missile->hit = 1;
            {
                hit_anim = 1;
                sMissileSetAnim(missile, hit_anim);
            }
        }
        if (zoid->field_1E50 == 0) {
            ZoidCopyAnim(zoid);
            zoid->interpolation_remaining = 13;
            zoid->interpolation_duration = 15;
            for (i = 0; i < 3; i++) {
                (&zoid->knockback[0])[i] = camera_joint->matrix[i][3] - missile->matrix[i][0];
            }
            dist = sLenPoint3dR((Vec3 *)&zoid->knockback[0]);
            if (dist > 0.2) {
                for (i = 0; i < 3; i++) {
                }
            }
            health = zoid->health;
            zoid->health -= missile->damage;
            if (zoid->health < 0)
                zoid->health = 0;
            if (health != 0 && zoid->health == 0) {
                killer = missile->owner;
                if (killer != 0 && zoid->slot != killer->slot) {
                    killer->kills++;
                    killer->field_1EF0 += zoid->max_health;
                }
            }
            zoid->health_bar_timer = 60;
            zoid->rumble_timer = 15;
        }
    }
}
