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

extern void *camTmp;
extern void camSeTmJobj(void *camera, s32 x, void *joint, s32 y);
extern void setAnimRate(HSD_JObj *joint, f32 rate);
extern s32 jobjAnim(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);

void sWeaponSetAnimWp(WeaponState3 *weapon, s32 animation)
{
    s32 index;
    HSD_JObj *joint;
    s32 model;
    TeaPart3 *part;
    s32 type;
    s16 cam_a;

    if (weapon == 0) {
        return;
    }
    if (weapon->active == 0) {
        return;
    }
    if (weapon->archive->models[weapon->model] == (void *)0) {
        return;
    }
    model = weapon->model;
    SetAnimArc2(weapon->archive, model, animation);
    joint = weapon->archive->models[model];
    if (joint != 0) {
        setAnimRate(joint, 1.0f);
        jobjAnim(joint);
        sMakeMatrix(joint);
    }
    weapon->animation = animation;
    weapon->state_flags &= ~0x10;
    type = weapon->type;
    part = &Tea_partsdat[type];
    index = -1;
    if (animation == 0) {
        index = 0;
    }
    if (animation == 2) {
        index = 1;
    }
    if (animation == 3) {
        index = 2;
    }
    if (index == -1) {
        return;
    }
    cam_a = part->cam_a[index];
    camSeTmJobj(camTmp, cam_a, weapon->field_1C, part->cam_b[index]);
}
