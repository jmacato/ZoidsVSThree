#include "types.h"
#include "zoid3.h"
#include "model_archive.h"

typedef struct WeaponState3 {
    s32 active;
    u32 flags;
    u32 state_flags;
    s32 type;
    ModelArchive *archive;
    s32 model;
    JointPose *pose;
    u8 reserved_1C[0x3C - 0x1C];
    ZoidState *owner;
    u8 reserved_40[0x6DC - 0x40];
} WeaponState3;

extern WeaponState3 sWeapon[100];
extern void stCopyMatReset(HSD_JObj *joint, JointPose *pose);
extern void stStJobjUnref(JointPose *pose);
extern void sWeaponPurgeD(ModelArchive *archive);
extern void PurgeArc2(ModelArchive *archive);
extern void ZeroMemory(void *memory, s32 size);

void sWeaponPurge(s32 index)
{
    WeaponState3 *weapon;
    ZoidState *zoid;
    WeaponMount *mount;
    s32 selected;
    s32 component;

    if (index >= 0 && index < 100) {
        weapon = &sWeapon[index];
        if (weapon->active == 0) {
            return;
        }
        stCopyMatReset(weapon->archive->models[weapon->model], weapon->pose);
        stStJobjUnref(weapon->pose);
        weapon->pose = 0;
        if (weapon->model == 0) {
            sWeaponPurgeD(weapon->archive);
            PurgeArc2(weapon->archive);
        }
        weapon->archive = 0;
        zoid = weapon->owner;
        if (zoid != 0) {
            s32 slot;

            for (slot = 0; slot < 30; slot++) {
                if (zoid->weapon_slots[slot].weapon == index) {
                    zoid->weapon_slots[slot].weapon = -1;
                    for (selected = 0; selected < 20; selected++) {
                        mount = &zoid->weapon_mounts[selected];
                        if (mount->active != 0) {
                            for (component = 0; component < 4; component++) {
                                WeaponMountEntry *entry = &mount->entries[component];

                                if (entry->active != 0 && entry->slot == slot) {
                                    entry->slot = -1;
                                    entry->active = 0;
                                }
                            }
                        }
                    }
                }
            }
            weapon->owner = 0;
        }
        weapon->active = 0;
        ZeroMemory(weapon, sizeof(*weapon));
    }
}
