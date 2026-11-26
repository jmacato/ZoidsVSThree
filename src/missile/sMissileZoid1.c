#include "zoid3.h"
#include "model_archive.h"

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

extern f32 sMissileZoid1a(Missile3 *missile, ZoidState *zoid, CoObj *object, s32 push);
extern void sMissileSetAnim(Missile3 *missile, s32 anim);
extern void ZoidCopyAnim(ZoidState *zoid);
extern s32 hitCalc2(ZoidState *attacker, s32 damage, ZoidState *zoid);
extern void zdVoiceSc(ZoidState *zoid, s32 voice);
extern ZoidState Zoid[];

typedef struct AI3 {
    u8 reserved_00[0x84];
    s32 missile_hit;
} AI3;

s32 sMissileZoid1(Missile3 *missile, ZoidState *zoid)
{
    f32 t;
    f32 delta;
    f32 rate;
    s32 damage;
    s32 health;
    s32 i;
    ZoidState *owner;

    if (zoid == (void *)0)
        return 0;
    if (zoid->joint == (void *)0)
        return 0;
    if (missile == (void *)0)
        return 0;
    if (missile->update_count < 2)
        return 0;
    if (zoid == missile->owner && missile->update_count < 180)
        return 0;
    t = sMissileZoid1a(missile, zoid, (CoObj *)zoid->body_coobj, 0);
    if (-1.0f == t)
        return 0;
    t = sMissileZoid1a(missile, zoid, (CoObj *)zoid->bust_coobj, 1);
    if (-1.0f == t)
        t = sMissileZoid1a(missile, zoid, (CoObj *)zoid->bust_coobj, 1);
    if (-1.0f == t)
        t = sMissileZoid1a(missile, zoid, (CoObj *)zoid->neck_coobj, 1);
    if (-1.0f == t)
        t = sMissileZoid1a(missile, zoid, (CoObj *)zoid->hip_coobj, 1);
    if (-1.0f == t)
        t = sMissileZoid1a(missile, zoid, (CoObj *)zoid->tail_coobjs[0], 1);
    if (-1.0f == t)
        t = sMissileZoid1a(missile, zoid, (CoObj *)zoid->tail_coobjs[1], 1);
    if (-1.0f == t)
        t = sMissileZoid1a(missile, zoid, (CoObj *)zoid->tail_coobjs[2], 1);
    if (-1.0f == t)
        t = sMissileZoid1a(missile, zoid, (CoObj *)zoid->head_coobj, 1);
    if (-1.0f == t)
        t = sMissileZoid1a(missile, zoid, (CoObj *)zoid->l_arm1_coobj, 1);
    if (-1.0f == t)
        t = sMissileZoid1a(missile, zoid, (CoObj *)zoid->r_arm1_coobj, 1);
    if (-1.0f == t)
        t = sMissileZoid1a(missile, zoid, (CoObj *)zoid->l_arm2_coobj, 1);
    if (-1.0f == t)
        t = sMissileZoid1a(missile, zoid, (CoObj *)zoid->r_arm2_coobj, 1);
    if (-1.0f == t)
        t = sMissileZoid1a(missile, zoid, (CoObj *)zoid->l_leg1_coobj, 1);
    if (-1.0f == t)
        t = sMissileZoid1a(missile, zoid, (CoObj *)zoid->r_leg1_coobj, 1);
    if (-1.0f == t)
        t = sMissileZoid1a(missile, zoid, (CoObj *)zoid->l_leg2_coobj, 1);
    if (-1.0f == t)
        t = sMissileZoid1a(missile, zoid, (CoObj *)zoid->r_leg2_coobj, 1);
    if (-1.0f == t)
        return 0;
    for (i = 0; i < 3; i++) {
        delta = missile->matrix[i][3] - missile->previous[i][3];
        missile->matrix[i][3] = delta * t + missile->previous[i][3];
    }
    if (missile->hit == 0) {
        missile->hit = 1;
        sMissileSetAnim(missile, 1);
    }
    if (missile->owner != 0 && missile->owner->ai != 0) {
        ((AI3 *)missile->owner->ai)->missile_hit = missile->owner->slot == zoid->slot ? 3 : 1;
    }
    if (missile->owner != 0 && missile->owner != zoid && (u8)zoid->slot == missile->owner->slot && (u8)zoid->slot == Zoid[0].slot && zoid->health != 0)
        zdVoiceSc(zoid, 14);
    if (zoid->field_1E50 == 0) {
        ZoidCopyAnim(zoid);
        health = zoid->health;
        damage = missile->damage;
        damage = hitCalc2(missile->owner, damage, zoid);
        zoid->interpolation_remaining = 13;
        zoid->interpolation_duration = 15;
        for (i = 0; i < 3; i++) {
            zoid->knockback[i] += missile->matrix[i][0] * damage / 300.0f;
        }
        zoid->health -= damage;
        rate = (f32)damage / 100.0;
        if (rate > 1.0f)
            rate = 1.0f;
        if (zoid->field_20C0 != 0)
            rate = 46.0f * rate / zoid->field_20C0;
        if (rate > 1.0f)
            rate = 1.0f;
        zoid->position[0] += missile->matrix[0][0] * rate;
        zoid->position[2] += missile->matrix[2][0] * rate;
        if (damage > 0)
            zoid->health_bar_timer = 60;
        if (zoid->health < 0)
            zoid->health = 0;
        if (health != 0 && zoid->health == 0) {
            owner = missile->owner;
            if (owner != 0 && zoid->slot != owner->slot) {
                owner->kills++;
                owner->field_1EF0 += zoid->max_health;
                if (missile->owner_weapon_mount == 19)
                    owner->field_1EF4 += zoid->max_health;
            }
        }
        zoid->rumble_timer = 15;
    }
    return 1;
}
