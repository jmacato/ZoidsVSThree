#include "types.h"
#include "zoid3.h"

typedef struct WeaponMarker3 {
    f32 position[3];
    s32 locked;
    s32 field_10;
    ZoidState *target;
    void *source;
    HSD_JObj *joint;
    s32 object_index;
} WeaponMarker3;

typedef struct WeaponState3 {
    s32 active;
    u8 reserved_04[0x3C - 0x04];
    ZoidState *owner;
    ZoidState *target;
    u8 reserved_44[0x3F0 - 0x44];
    f32 range;
    u8 reserved_3F4[0x3FC - 0x3F4];
    s32 bullet_kind;
    u8 reserved_400[0x40C - 0x400];
    WeaponMarker3 markers[20];
} WeaponState3;

extern s32 sWeaponGetBarrel(WeaponState3 *weapon, Vec3 *out, f32 distance);
extern s32 sWeaponGetBarrelParabola(WeaponState3 *weapon, Vec3 *out, f32 distance);
extern f32 sLenJobj(HSD_JObj *a, HSD_JObj *b);
extern f32 sLenPoint3dR(f32 *point);

void sWeaponSightCom(WeaponState3 *weapon)
{
    WeaponMarker3 *marker;
    ZoidState *owner;
    ZoidState *target;
    Vec3 out;
    f32 delta[3];
    s32 i;
    s32 found;
    f32 length;

    if (weapon == (void *)0)
        return;
    if (weapon->active == 0)
        return;
    if (weapon->bullet_kind == 1)
        return;
    owner = weapon->owner;
    if (owner == 0)
        return;
    if (owner->camera != 0)
        return;
    target = weapon->target;
    if (target != 0 && target->joint == 0)
        target = 0;
    if (target != 0 && target->stel_state == 2)
        target = 0;
    if (target != 0 && target->death_started != 0)
        target = 0;
    found = 1;
    if (target == 0)
        found = 0;
    if (target != 0) {
        length = owner->field_1F48[target->index];
        if (weapon->bullet_kind == 0)
            found = sWeaponGetBarrel(weapon, &out, length);
        else
            found = sWeaponGetBarrelParabola(weapon, &out, length);
    }
    if (found != 0) {
        length = sLenJobj((HSD_JObj *)target->camera_joint, weapon->owner->joint);
        if (length > weapon->range)
            found = 0;
    }
    if (found != 0) {
        for (i = 0; i < 3; i++) {
            delta[i] = ((HSD_JObj *)target->camera_joint)->matrix[i][3] - (&out.x)[i];
        }
        length = sLenPoint3dR(delta);
        if (length > 2.0f)
            found = 0;
    }
    if (found == 0) {
        for (i = 0; i < 20; i++) {
            marker = &weapon->markers[i];
            marker->joint = 0;
            marker->target = 0;
            marker->source = 0;
            marker->object_index = -1;
        }
    } else {
        for (i = 0; i < 20; i++) {
            marker = &weapon->markers[i];
            marker->joint = (HSD_JObj *)target->camera_joint;
            marker->target = target;
        }
    }
}
