#include "types.h"
#include "zoid3.h"
#include "joint.h"
#include "joint_matrix.h"
#include "aobj.h"
#include "model_archive.h"

typedef struct PartData3 {
    u8 reserved_00[0x64];
    u32 flags;
    u8 reserved_68[0x124 - 0x68];
} PartData3;

typedef struct WeaponState3 {
    s32 active;
    u32 flags;
    u32 state_flags;
    s32 type;
    ModelArchive *archive;
    s32 model;
    void *pose;
    HSD_JObj *mount_joint;
    u8 reserved_20[0x3C - 0x20];
    ZoidState *owner;
    u8 reserved_40[0x6DC - 0x40];
} WeaponState3;

extern WeaponState3 sWeapon[100];
extern PartData3 Tea_partsdat[];
extern void sWeaponTarget(WeaponState3 *weapon, HSD_JObj *target);
extern void sWeaponTargetColli(WeaponState3 *weapon);
extern void sMakeMatrix(HSD_JObj *joint);
extern void *getAnimAobj(HSD_JObj *joint);
extern u32 HSD_AObjGetFlags(void *aobj);
extern void HSD_JObjAnimAll(HSD_JObj *joint);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern HSD_JObj *grdObjGetJObj(s32 index);

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

void sWeaponAnim(WeaponState3 *weapon)
{
    HSD_JObj *mount;
    HSD_JObj *joint;
    HSD_JObj *target_joint;
    void *aobj;
    ZoidState *owner;
    ZoidState *target;
    s32 model;
    s32 type;
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
    part_flags = Tea_partsdat[type].flags;
    owner = weapon->owner;
    target_joint = 0;
    if (owner != 0) {
        if (owner->target_pending != 0) {
            target = &Zoid[owner->target_slot];
            if (target->joint == (void *)0)
                target = 0;
            if (owner->death_started != 0)
                target = 0;
            if (target != 0 && target->joint == (void *)0)
                target = 0;
            if (target != 0) {
                target_joint = target->joint;
                if ((HSD_JObj *)target->camera_joint != 0)
                    target_joint = (HSD_JObj *)target->camera_joint;
            }
        }
        if (owner->lock_active != 0)
            target_joint = grdObjGetJObj(owner->lock_obj);
    }
    aobj = getAnimAobj(joint);
    if (!(weapon->state_flags & 0x10)) {
        HSD_JObjAnimAll(joint);
        weapon->state_flags |= 8;
        if (HSD_AObjGetFlags(aobj) & AOBJ_REWINDED) {
            weapon->state_flags &= ~8;
            if (weapon->flags & 8)
                weapon->state_flags |= 0x10;
        }
        sMakeMatrix(joint);
    }
    if (part_flags & 0x100)
        sWeaponTargetColli(weapon);
    else
        sWeaponTarget(weapon, target_joint);
    HSD_JObjSetMtxDirty(joint);
    sMakeMatrix(joint);
}
