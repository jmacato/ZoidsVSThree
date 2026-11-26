#pragma readonly_strings on
#include "model_archive.h"
#include "joint_matrix.h"
typedef struct WeaponState3 {
    s32 active;
    s32 flags;
    s32 state_flags;
    s32 type;
    ModelArchive *archive;
    s32 model;
    void *pose;
    void *field_1C;
    HSD_JObj *counter_joint;
    u8 pad_24[0x10];
    HSD_JObj *target_joint;
    u8 pad_38[0x4];
    void *owner;
    u8 pad_40[0x38];
    HSD_JObj *trace_joints[13];
    f32 trace_positions[13][3];
    u8 pad_148[0x3E8 - 0x148];
    s32 animation;
    u8 pad_3EC[0x6DC - 0x3EC];
} WeaponState3;

extern WeaponState3 sWeapon[100];

extern void sGlobal2Local(HSD_JObj *joint);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);

#pragma auto_inline off
static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & 0x00800000) && (jobj->flags & 0x40);
}

void sWeaponTarget(WeaponState3 *weapon, HSD_JObj *target)
{
    HSD_JObj *joint;
    HSD_JObj *parent;
    s32 i;
    s32 j;

    if (weapon == (void *)0) {
        return;
    }
    if (target == (void *)0) {
        return;
    }
    if (weapon->animation >= 4) {
        return;
    }
    joint = weapon->target_joint;
    if (joint == (void *)0) {
        return;
    }
    parent = joint->parent;
    if (parent != 0) {
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                joint->matrix[i][j] = parent->matrix[i][j];
            }
        }
    }
    for (i = 0; i < 3; i++) {
        joint->matrix[i][3] = target->matrix[i][3];
    }
    sGlobal2Local(joint);
    if (joint != 0 && !HSD_JObjMtxIsDirty(joint)) {
        HSD_JObjSetMtxDirtySub(joint);
    }
}
