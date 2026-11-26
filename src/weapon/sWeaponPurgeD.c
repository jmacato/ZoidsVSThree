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

extern void sWeaponPurge(s32 index);

void sWeaponPurgeD(ModelArchive *archive)
{
    WeaponState3 *weapon;
    s32 index;

    for (index = 0; index < 100; index++) {
        weapon = &sWeapon[index];
        if (weapon->active != 0 && weapon->model != 0 && weapon->archive == archive) {
            sWeaponPurge(index);
        }
    }
}
