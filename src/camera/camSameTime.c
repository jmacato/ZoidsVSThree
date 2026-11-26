#include "zoid3.h"

typedef struct CameraState3 {
    u8 pad_000[0x1C4];
    ZoidState *zoid;
    u8 pad_1C8[0x4];
    f32 prev_zoid_pos[3];
    f32 prev_target_pos[3];
    s32 same_time;
} CameraState3;

extern s32 chkPos(f32 *a, f32 *b);
extern f32 *grdObjGetPt(u8 id);

void camSameTime(CameraState3 *camera)
{
    ZoidState *zoid;
    ZoidState *enemy;
    f32 *target;
    s32 slot;
    s32 i;

    if (camera != 0 && (zoid = camera->zoid) != 0 && zoid->joint != 0) {
        camera->same_time++;
        if (chkPos(camera->prev_zoid_pos, zoid->position) == 0)
            camera->same_time = 0;
        slot = zoid->target_slot;
        if (slot < 0 || slot >= 16)
            zoid->target_pending = 0;
        target = 0;
        if (zoid->target_pending != 0) {
            enemy = &Zoid[slot];
            if (enemy->joint == 0)
                enemy = 0;
            if (enemy != 0)
                target = enemy->position;
        }
        if (zoid->lock_active != 0)
            target = grdObjGetPt(zoid->lock_obj);
        if (target != 0) {
            if (chkPos(camera->prev_target_pos, target) == 0)
                camera->same_time = 0;
        }
        for (i = 0; i < 3; i++) {
            camera->prev_zoid_pos[i] = zoid->position[i];
            if (target != 0)
                camera->prev_target_pos[i] = target[i];
        }
    }
}
