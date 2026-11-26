#include "zoid3.h"

extern f32 atan2f(f32 y, f32 x);
extern Vec3 *grdObjGetPt(s32 index);

void calcAngA(ZoidState *zoid)
{
    ZoidState *target;

    if (zoid != 0) {
        if (zoid->target_slot == -1) {
            zoid->target_pending = 0;
        }
        zoid->field_1E94 = zoid->heading;
        if (zoid->target_pending != 0) {
            f32 dx;
            f32 dz;

            target = &Zoid[zoid->target_slot];
            if (zoid->ai != 0 && zoid->ai->mode == 2) {
                target = &Zoid[*(s32 *)((u8 *)zoid->ai + 0x74)];
            }
            if (target->joint == 0) {
                zoid->target_pending = 0;
            }
            dz = target->position[2] - zoid->position[2];
            dx = target->position[0] - zoid->position[0];
            zoid->field_1E94 = atan2f(dx, dz);
        } else if (zoid->lock_active != 0) {
            Vec3 *point;
            f32 dx;
            f32 dz;

            point = grdObjGetPt(zoid->lock_obj);
            dz = point->z - zoid->position[2];
            dx = point->x - zoid->position[0];
            zoid->field_1E94 = atan2f(dx, dz);
        }
    }
}
