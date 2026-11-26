#include "model_archive.h"
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

extern s32 getEndF(HSD_JObj *joint);

s32 sWeaponEndF(s32 index)
{
    WeaponState3 *weapon;

    if (index < 0) {
        return 0;
    }
    if (index >= 100) {
        return 0;
    }
    weapon = &sWeapon[index];
    if (weapon->active == 0) {
        return 0;
    }
    if ((weapon->state_flags & 0x10) != 0) {
        return 1;
    }
    return getEndF(weapon->archive->models[weapon->model]);
}
