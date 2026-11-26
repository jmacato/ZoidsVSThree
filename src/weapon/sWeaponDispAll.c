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

typedef struct TeaPart3 {
    u8 pad_00[0x64];
    s32 flags;
    u8 pad_68[0xEE - 0x68];
    s16 cam_a[3];
    s16 cam_b[3];
    u8 pad_FA[0x124 - 0xFA];
} TeaPart3;

extern TeaPart3 Tea_partsdat[];

extern struct HSD_Fog *fogG;
extern void HSD_FogSet(struct HSD_Fog *fog);
extern void sWeaponDisp(WeaponState3 *weapon);

void sWeaponDispAll(void)
{
    register s32 use_fog = 1;
    WeaponState3 *weapon;
    s32 index;
    s32 flag = 1;

    for (index = 0; index < 100; index++) {
        weapon = &sWeapon[index];
        if (weapon->active != 0) {
            s32 type = weapon->type;

            if ((Tea_partsdat[type].flags & 0x80) != 0) {
                use_fog = 0;
            } else {
                use_fog = 1;
            }
            if (fogG != 0) {
                HSD_FogSet(use_fog != 0 ? fogG : 0);
            }
            sWeaponDisp(weapon);
            flag = 0;
        }
    }
    if (fogG != 0) {
        HSD_FogSet(fogG);
    }
}
