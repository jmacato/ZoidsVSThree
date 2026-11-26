#include "weapon.h"
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

extern BulletDat3 Tea_bulletdat[131];
extern void PSMTXMultVec(f32 m[3][4], Vec3 *src, Vec3 *dst);
extern void sEffectSet(s32 type, s32 mode, f32 *position, HSD_JObj *source, struct ZoidState *zoid);
extern void sMissileSetAnim(Missile3 *missile, s32 selected);
extern f32 sColCube4LineConnect(Vec3 *start, Vec3 *end);

s32 sMissileAtk(Missile3 *missile, WeaponInverse *target)
{
    Vec3 end;
    Vec3 start;
    f32 t;
    f32 delta;
    f32 (*inverse)[4];
    s32 i;

    if (target == (void *)0)
        return 0;
    if (target->joint == (void *)0)
        return 0;
    inverse = target->inverse;
    for (i = 0; i < 3; i++) {
        (&end.x)[i] = missile->matrix[i][3];
        (&start.x)[i] = missile->previous[i][3];
    }
    PSMTXMultVec(inverse, &end, &end);
    PSMTXMultVec(inverse, &start, &start);
    if ((t = sColCube4LineConnect(&start, &end)) == -1.0f)
        return 0;
    for (i = 0; i < 3; i++) {
        delta = missile->matrix[i][3] - missile->previous[i][3];
        missile->matrix[i][3] = delta * t + missile->previous[i][3];
    }

    if (missile->hit == 0) {
        missile->hit = 1;
        sMissileSetAnim(missile, 1);
    }
    return 1;
}
