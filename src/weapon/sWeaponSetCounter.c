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

extern s32 sWeaponGetBullet(s32 weapon);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, u32 line, const char *expr);

#pragma auto_inline off
static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & 0x00800000) && (jobj->flags & 0x40);
}

void sWeaponSetCounter(s32 index)
{
    s32 ammo;
    WeaponState3 *weapon;
    HSD_JObj *joint;

    if (index < 0) {
        return;
    }
    if (index >= 100) {
        return;
    }
    weapon = &sWeapon[index];
    if (weapon->active == 0) {
        return;
    }
    if (weapon->counter_joint == 0) {
        return;
    }
    ammo = sWeaponGetBullet(index);
    joint = weapon->counter_joint;
    joint != 0 ? (void)0 : __assert("jobj.h", 952, "jobj");
    joint->translation.x = (f32)ammo;
    if ((joint->flags & 0x02000000) != 0) {
        return;
    }
    if (joint != 0 && !HSD_JObjMtxIsDirty(joint)) {
        HSD_JObjSetMtxDirtySub(joint);
    }
}
