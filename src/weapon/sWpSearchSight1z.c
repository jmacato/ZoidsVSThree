#include "zoid3.h"
#include "game_camera.h"
#include "joint.h"

typedef struct SightMarker3 {
    f32 position[3];
    s32 locked;
    s32 pad_10;
    ZoidState *target;
    s32 source;
    HSD_JObj *joint;
    s32 field_20;
} SightMarker3;

typedef struct SightWeapon3 {
    u8 pad_000[0x3F0];
    f32 range;
    u8 pad_3F4[0x400 - 0x3F4];
    s32 marker_count;
    u8 pad_404[0x40C - 0x404];
    SightMarker3 markers[1];
} SightWeapon3;

s32 sWpSearchSight1z(SightWeapon3 *weapon, ZoidState *zoid, ZoidState *target)
{
    s32 i;
    s32 count;
    SightMarker3 *marker;
    s32 pt[3];
    f32 range;

    if (target == (void *)0)
        return 0;
    if (target->joint == (void *)0)
        return 0;
    count = weapon->marker_count;
    if (count < 1)
        return 1;
    for (i = 0; i < count; i++) {
        marker = &weapon->markers[i];
        if (marker->joint != (void *)0 && marker->target == target)
            return 0;
    }
    for (i = 0; i < count; i++) {
        marker = &weapon->markers[i];
        if (marker->joint == (void *)0)
            break;
    }
    if (i == count)
        return 1;
    range = weapon->range;
    if (range < zoid->distances[target->index])
        return 0;
    if (zoid != 0 && zoid->camera != 0 && sCameraPt2d(zoid->camera, (Vec3 *)target->position, pt) == 0)
        return 0;
    marker->target = target;
    marker->locked = 0;
    marker->joint = (HSD_JObj *)target->camera_joint;
    marker->source = 0;
    marker->field_20 = -1;
    for (i = 0; i < 3; i++) {
        if (zoid != 0)
            marker->position[i] = ((HSD_JObj *)zoid->camera_joint)->matrix[i][3];
        else
            marker->position[i] = ((HSD_JObj *)target->camera_joint)->matrix[i][3];
    }

    marker->position[1] -= 100.0f;
    return 0;
}
