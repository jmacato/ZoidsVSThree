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
    u8 reserved_00[0x3F0];
    f32 range;
    u8 reserved_3F4[0x400 - 0x3F4];
    s32 marker_count;
    u8 reserved_404[0x40C - 0x404];
    WeaponMarker3 markers[20];
} WeaponState3;

extern s32 grdObjAliveN(s32 index);
extern s32 grdObjGetGrp(s32 index);
extern HSD_JObj *grdObjGetJObj(s32 index);
extern f32 sLenJobj(HSD_JObj *a, HSD_JObj *b);
extern s32 sCameraJobjPt2d(void *camera, HSD_JObj *joint, s32 *screen_point);

s32 sWpSearchSight1g(WeaponState3 *weapon, ZoidState *zoid, s32 index)
{
    s32 i;
    s32 count;
    WeaponMarker3 *marker;
    HSD_JObj *joint;
    s32 pt[3];
    f32 range;
    f32 distance;

    if (index < 0)
        return 0;
    if (grdObjAliveN(index) == 0)
        return 0;
    if (zoid->slot == grdObjGetGrp(index))
        return 0;
    count = weapon->marker_count;
    if (count < 1)
        return 1;
    for (i = 0; i < count; i++) {
        marker = &weapon->markers[i];
        if (marker->joint != (void *)0 && marker->object_index == index)
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
    joint = grdObjGetJObj(index);
    if (joint == 0)
        return 0;
    distance = sLenJobj(zoid->joint, joint);
    if (range < distance)
        return 0;
    if (zoid->camera != 0 && sCameraJobjPt2d(zoid->camera, joint, pt) == 0)
        return 0;
    marker->target = 0;
    marker->locked = 0;
    marker->joint = joint;
    marker->source = 0;
    marker->object_index = index;
    for (i = 0; i < 3; i++) {
        marker->position[i] = joint->matrix[i][3];
    }

    marker->position[1] -= 50.0f;
    return 0;
}
