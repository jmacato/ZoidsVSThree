#include "model_archive.h"
#include "angle.h"
#include "jobj.h"

extern void setAnimRate(HSD_JObj *joint, f32 value);
extern void sEffectSet(s32 type, s32 mode, f32 *position, HSD_JObj *source, struct ZoidState *zoid);
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

void sMissileSetAnim(Missile3 *missile, s32 selected)
{
    ModelAnimationTable *table;

    if (missile == (void *)0)
        return;
    if (missile->joint == (void *)0)
        return;
    table = missile->archive->animations;
    if (table->models == (void *)0)
        return;
    if (table->models[0]->joint_animations == (void *)0)
        return;
    HSD_JObjRemoveAnimAll(missile->joint);
    HSD_JObjAddAnimAll(missile->joint,
        table->models[0]->joint_animations != 0 ? table->models[0]->joint_animations[selected] : 0,
        table->models[0]->material_animations != 0 ? table->models[0]->material_animations[selected] : 0,
        table->models[0]->shape_animations != 0 ? table->models[0]->shape_animations[selected] : 0);
    HSD_JObjReqAnimAll(missile->joint, 0.0f);
    missile->animation = selected;
    setAnimRate(missile->joint, 1.0f);
    if (selected == 1) {
        sEffectSet(Tea_bulletdat[missile->bullet].hit_effect, 1, 0, missile->joint, 0);
    }
}
