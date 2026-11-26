#include "types.h"
#include "zoid3.h"

typedef struct Missile3 {
    u8 reserved_00[0x24];
    HSD_JObj *joint;
    u8 reserved_28[0xF4 - 0x28];
    s32 purge_timer;
    s32 hit;
} Missile3;

typedef struct WeaponMarker3 {
    f32 position[3];
    s32 locked;
    s32 field_10;
    ZoidState *target;
    Missile3 *source;
    HSD_JObj *joint;
    s32 object_index;
} WeaponMarker3;

typedef struct WeaponState3 {
    s32 active;
    u8 reserved_04[0x3C - 0x04];
    ZoidState *owner;
    u8 reserved_40[0x3F0 - 0x40];
    f32 range;
    f32 rate;
    u8 reserved_3F8[0x3FC - 0x3F8];
    s32 bullet_kind;
    s32 marker_count;
    u8 reserved_404[0x40C - 0x404];
    WeaponMarker3 markers[20];
} WeaponState3;

extern f32 sLiner(f32 target, f32 current, f32 fraction);
extern f32 sLenPoint3dR(f32 *point);
extern f32 sLenJobj(HSD_JObj *a, HSD_JObj *b);

void sWeaponSight(WeaponState3 *weapon)
{
    WeaponMarker3 *marker;
    s32 i;
    s32 k;
    Missile3 *source;
    ZoidState *target;
    f32 delta[3];
    f32 goal;
    f32 length;

    if (weapon == (void *)0)
        return;
    if (weapon->active == 0)
        return;
    if (weapon->bullet_kind != 1)
        return;
    for (i = 0; i < 20; i++) {
        marker = &weapon->markers[i];
        if (marker->joint == (void *)0)
            continue;
        source = marker->source;
        if (source != 0 && (source->joint == 0 || source->purge_timer != 0 || source->hit != 0)) {
            marker->joint = 0;
            marker->source = 0;
            marker->target = 0;
            marker->object_index = -1;
            continue;
        }
        target = marker->target;
        if (target != 0 && (target->death_started != 0 || target->stel_state == ZOID_STEL_ON)) {
            marker->joint = 0;
            marker->target = 0;
            marker->source = 0;
            marker->object_index = -1;
            continue;
        }
        for (k = 0; k < 3; k++) {
            goal = marker->joint->matrix[k][3];
            (&marker->position[0])[k] = sLiner(goal, (&marker->position[0])[k], weapon->rate);
            delta[k] = goal - (&marker->position[0])[k];
        }
        length = sLenPoint3dR(delta);
        if (length < 0.5)
            marker->locked = 1;
        if (marker->locked != 0) {
            for (k = 0; k < 3; k++) {
                (&marker->position[0])[k] = marker->joint->matrix[k][3];
            }

            length = sLenJobj(marker->joint, weapon->owner->joint);
            if (length > weapon->range)
                marker->joint = 0;
        }
    }
}
