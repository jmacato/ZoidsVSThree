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

extern void sLinier3d(f32 *current, f32 *target, f32 fraction);
extern void sGlobal2Local(HSD_JObj *joint);

void sWeaponTrace(WeaponState3 *weapon)
{
    s32 i;
    s32 index;

    if (weapon->trace_joints[0] != (void *)0) {
        for (i = 0; i < 3; i++) {
            weapon->trace_positions[0][i] = weapon->trace_joints[0]->matrix[i][3];
        }
        for (index = 12; index > 0; index--) {
            HSD_JObj *previous_joint = weapon->trace_joints[index - 1];
            HSD_JObj *joint = weapon->trace_joints[index];

            if (previous_joint != (void *)0 && joint != (void *)0) {
                f32 *previous = weapon->trace_positions[index - 1];
                f32 *point = weapon->trace_positions[index];

                sLinier3d(point, previous, 0.8f);
                for (i = 0; i < 3; i++) {
                    joint->matrix[i][3] = point[i];
                }
                sGlobal2Local(joint);
            }
        }
    }
}
