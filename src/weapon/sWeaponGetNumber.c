#include "zoid3.h"
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

s32 sWeaponGetNumber(ZoidState *zoid, s32 selected)
{
    WeaponMount *mount;
    s32 index;
    s32 slot;
    s32 weapon;

    if (zoid == (void *)0) {
        return -1;
    }
    if (zoid->joint == (void *)0) {
        return -1;
    }
    if (selected == -1) {
        return -1;
    }
    mount = &zoid->weapon_mounts[selected];
    if (mount->active == 0) {
        return -1;
    }
    {
        s32 found = 0;

        for (index = 0; index < 4; index++) {
            if (mount->entries[index].active != 0) {
                slot = mount->entries[index].slot;
                if (slot != -1) {
                    weapon = zoid->weapon_slots[slot].weapon;
                    if (weapon != -1) {
                        return sWeapon[weapon].type;
                    }
                }
            }
        }
    }
    return -1;
}
