#pragma readonly_strings on
#include "types.h"
#include "zoid3.h"
#include "joint.h"
#include "joint_matrix.h"
#include "model_archive.h"

typedef struct PartData3 {
    u8 reserved_00[0x64];
    u32 flags;
    u8 reserved_68[0x124 - 0x68];
} PartData3;

typedef struct WeaponInverse3 {
    HSD_JObj *joint;
    f32 inverse[3][4];
    u8 reserved_34[4];
} WeaponInverse3;

typedef struct WeaponState3 {
    s32 active;
    u32 flags;
    u32 state_flags;
    s32 type;
    ModelArchive *archive;
    s32 model;
    void *pose;
    HSD_JObj *mount_joint;
    u8 reserved_20[0x24 - 0x20];
    HSD_JObj *field_24;
    HSD_JObj *field_28;
    HSD_JObj *field_2C;
    HSD_JObj *field_30;
    u8 reserved_34[0x3C - 0x34];
    ZoidState *owner;
    u8 reserved_40[0x148 - 0x40];
    WeaponInverse3 inverses[12];
    u8 reserved_5A4[0x6DC - 0x5A4];
} WeaponState3;

extern WeaponState3 sWeapon[100];
extern PartData3 Tea_partsdat[];
extern void sGlobal2Local(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);
extern void sWeaponTarget(WeaponState3 *weapon, HSD_JObj *target);
extern void sWeaponTargetColli(WeaponState3 *weapon);
extern void sWeaponSight(WeaponState3 *weapon);
extern void sWeaponSightCom(WeaponState3 *weapon);
extern void sWeaponTrace(WeaponState3 *weapon);
extern void sWeaponFire(WeaponState3 *weapon);
extern void PSMTXInverse(f32 src[3][4], f32 inv[3][4]);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);

static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & 0x00800000) && (jobj->flags & 0x40);
}

#define HSD_JObjSetMtxDirty(jobj) \
    do { \
        if ((jobj) != 0 && !HSD_JObjMtxIsDirty(jobj)) \
            HSD_JObjSetMtxDirtySub(jobj); \
    } while (0)

void sWeaponMove(WeaponState3 *weapon)
{
    s32 type;
    HSD_JObj *target_joint;
    HSD_JObj *joint;
    HSD_JObj *mount;
    HSD_JObj *b;
    s32 model;
    ZoidState *target;
    ZoidState *owner;
    HSD_JObj *d;
    s32 j;
    HSD_JObj *a;
    s32 i;
    HSD_JObj *c;
    u32 part_flags;

    if (weapon == 0)
        return;
    mount = weapon->mount_joint;
    model = weapon->model;
    if (mount == (void *)0)
        return;
    joint = weapon->archive->models[model];
    if (joint == (void *)0)
        return;
    if (weapon->flags & 4)
        return;
    type = weapon->type;
    if (type <= 0)
        return;
    owner = weapon->owner;
    part_flags = Tea_partsdat[type].flags;
    target = 0;
    target_joint = 0;
    if (owner != 0) {
        if (owner->target_pending != 0) {
            target = &Zoid[owner->target_slot];
            if (target->joint == (void *)0)
                target = 0;
        }
        if (owner->death_started != 0)
            target = 0;
    }
    if (target != 0 && target->joint == (void *)0)
        target = 0;
    if (target != 0) {
        target_joint = target->joint;
        if ((HSD_JObj *)target->camera_joint != 0)
            target_joint = (HSD_JObj *)target->camera_joint;
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            joint->matrix[i][j] = mount->matrix[i][j];
        }
    }
    sGlobal2Local(joint);
    HSD_JObjSetMtxDirty(joint);
    if (weapon->field_24 != 0 && weapon->field_28 != 0) {
        a = weapon->field_24;
        a ? (void)0 : __assert("jobj.h", 952, "jobj");
        a->translation.x = 1.0f;
        if (!(a->flags & 0x02000000))
            HSD_JObjSetMtxDirty(a);
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 4; j++) {
                weapon->field_24->matrix[i][j] = weapon->field_28->matrix[i][j];
            }
        }
        sGlobal2Local(weapon->field_24);
        b = weapon->field_24;
        HSD_JObjSetMtxDirty(b);
    }
    if (weapon->field_2C != 0 && weapon->field_30 != 0) {
        c = weapon->field_2C;
        c ? (void)0 : __assert("jobj.h", 952, "jobj");
        c->translation.x = 1.0f;
        if (!(c->flags & 0x02000000))
            HSD_JObjSetMtxDirty(c);
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 4; j++) {
                weapon->field_2C->matrix[i][j] = weapon->field_30->matrix[i][j];
            }
        }
        sGlobal2Local(weapon->field_2C);
        d = weapon->field_2C;
        HSD_JObjSetMtxDirty(d);
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            joint->matrix[i][j] = mount->matrix[i][j];
        }
    }
    if (part_flags & 0x100)
        sWeaponTargetColli(weapon);
    else
        sWeaponTarget(weapon, target_joint);
    sWeaponSight(weapon);
    sWeaponSightCom(weapon);
    sWeaponTrace(weapon);
    HSD_JObjSetMtxDirty(joint);
    sMakeMatrix(joint);
    sWeaponFire(weapon);
    for (i = 0; i < 12; i++) {
        if (weapon->inverses[i].joint != 0)
            PSMTXInverse(weapon->inverses[i].joint->matrix, weapon->inverses[i].inverse);
    }
}
