#include "types.h"
#include "zoid3.h"
#include "joint.h"
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
    u8 reserved_00[0x1E];
    s16 fire_effect;
    u8 reserved_20[0x4C - 0x20];
} BulletDat3;

typedef struct WeaponMarker3 {
    f32 position[3];
    s32 locked;
    s32 field_10;
    ZoidState *target;
    void *source;
    HSD_JObj *joint;
    s32 object_index;
} WeaponMarker3;

typedef struct WeaponState3 {
    s32 active;
    u32 flags;
    u32 state_flags;
    s32 type;
    struct ModelArchive3 *archive;
    s32 model;
    void *pose;
    HSD_JObj *mount_joint;
    u8 reserved_20[0x3C - 0x20];
    ZoidState *owner;
    u8 reserved_40[0x48 - 0x40];
    HSD_JObj *barrels[12];
    u8 reserved_78[0x3EC - 0x78];
    s32 ammo;
    u8 reserved_3F0[0x3FC - 0x3F0];
    s32 bullet_kind;
    s32 marker_count;
    s32 marker_cursor;
    u8 reserved_408[0x40C - 0x408];
    WeaponMarker3 markers[20];
} WeaponState3;

typedef struct ModelArchive3 {
    u8 reserved_00[0x3C];
    HSD_JObj *models[1];
} ModelArchive3;

static inline f32 HSD_JObjGetScaleX(HSD_JObj *jobj)
{
    f32 scale;

    jobj ? (void)0 : __assert("jobj.h", 899, "jobj");
    scale = jobj->scale.x;
    return scale;
}

extern PartData3 Tea_partsdat[];
extern BulletDat3 Tea_bulletdat[];
extern void sEffectSet(s32 type, s32 mode, f32 *position, HSD_JObj *source, ZoidState *zoid);
extern void sMissileFire(ZoidState *owner, ZoidState *target_zoid, void *target_missile, s32 lock, f32 matrix[3][4], s32 bullet, s32 extra_damage);

void sWeaponFire(WeaponState3 *weapon)
{
    s32 i;
    s32 k;
    HSD_JObj *joint;
    s32 bullet;
    s32 extra_damage;
    s32 effect;
    WeaponMarker3 *marker;
    s32 model;
    s32 type;
    s32 bullets[2];

    if (weapon == (void *)0)
        return;
    if (weapon->active == 0)
        return;
    model = weapon->model;
    type = weapon->type;
    if (type <= 0)
        return;
    bullets[0] = Tea_partsdat[type].bullets[0];
    bullets[1] = Tea_partsdat[type].bullets[1];
    if (bullets[0] <= 0)
        return;
    if (bullets[1] <= 0)
        bullets[1] = bullets[0];
    if (weapon->archive->models[model] == (void *)0)
        return;
    if (weapon->flags & 4)
        return;
    if (weapon->state_flags & 0x10)
        return;
    if (weapon->owner->death_started != 0) {
        weapon->flags |= 8;
        return;
    }
    extra_damage = Tea_partsdat[type].power;
    if (weapon->owner != 0)
        extra_damage += weapon->owner->bullet_power_bonus;
    for (i = 0; i < 12; i++) {
        joint = weapon->barrels[i];
        if (joint == (void *)0)
            continue;
        if (HSD_JObjGetScaleX(joint) < 1.0)
            continue;
        if (weapon->ammo == 0)
            continue;
        weapon->ammo--;
        bullet = bullets[i & 1];
        effect = Tea_bulletdat[bullet].fire_effect;
        if (effect > 0)
            sEffectSet(effect, 1, 0, joint, 0);
        if (weapon->bullet_kind == 6) {
            sMissileFire(weapon->owner, weapon->markers[0].target, 0, -1, joint->matrix, bullet, extra_damage);
        } else if (weapon->bullet_kind != 1) {
            sMissileFire(weapon->owner, weapon->owner->target_pending != 0 ? &Zoid[weapon->owner->target_slot] : 0, 0, weapon->owner->lock_active != 0 ? weapon->owner->lock_obj : -1, joint->matrix, bullet, extra_damage);
        } else {
            for (k = 0; k < 20; k++) {
                weapon->marker_cursor++;
                if (weapon->marker_cursor >= weapon->marker_count)
                    weapon->marker_cursor = 0;
                marker = &weapon->markers[weapon->marker_cursor];
                if (marker->joint != (void *)0)
                    break;
            }
            if (k != 20)
                sMissileFire(weapon->owner, marker->target, marker->source, marker->object_index, joint->matrix, bullet, extra_damage);
            else
                sMissileFire(weapon->owner, 0, 0, -1, joint->matrix, bullet, extra_damage);
        }
    }
}
