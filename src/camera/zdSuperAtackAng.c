#include "zoid3.h"

typedef struct CameraState3 {
    u8 pad_000[0x2FB];
    s8 flag;
    f32 fov;
} CameraState3;

extern void angLimit(f32 *angle);

void zdSuperAtackAng(ZoidState *zoid, CameraState3 *camera)
{
    ZoidControlData *data;
    f32 angle;
    s32 kind;
    f32 limit;
    s32 flag;
    s32 mount;
    s32 state;

    flag = 0;
    limit = 0.3490658402442932f;
    if (zoid == 0)
        return;
    if (zoid->joint == 0)
        return;
    data = zoid->anim_data;
    if (data == 0)
        return;
    mount = zoid->weapon_mount;
    if (mount == -1) {
        kind = 0;
        state = 0;
    } else {
        state = zoid->weapon_mounts[mount].state;
        kind = data->field_0140[mount];
    }
    if (zoid->animation_frame == 0)
        kind = 0;
    if (mount == -1)
        kind = 0;
    if (kind == 2) {
        if (state == 2 || state == 3 || state == 1 || state == 6)
            flag = 1;
    }
    if (mount == -1)
        flag = 0;
    if (flag != 0) {
        angle = -zoid->field_1C74 * (2.0 * (3.1415926 * (f32)(*(s32 *)((u8 *)data + 0xDC) / 1000.0)) / 360.0);
        if (camera->flag != 0)
            angle = angle * camera->fov / 60.0;
        angle = angle + zoid->heading;
        angLimit(&angle);
        zoid->heading = angle;
    }
    if (flag != 0) {
        angle = -zoid->field_1C78 * (2.0 * (3.1415926 * (f32)(*(s32 *)((u8 *)data + 0xDC) / 1000.0)) / 360.0);
        if (camera->flag != 0)
            angle = angle * camera->fov / 60.0;
        angle = angle + zoid->high_angle;
    } else {
        angle = zoid->high_angle;
        if (zoid->field_0170 == 0) {
            if (angle < 0.0f) {
                angle += 0.026179938333333336;
                if (angle > 0.0f)
                    angle = 0.0f;
            }
            if (angle > 0.0f) {
                angle = angle - 0.026179938333333336;
                if (angle < 0.0f)
                    angle = 0.0f;
            }
        } else {
            limit = 1.0471975803375244f;
        }
    }
    angLimit(&angle);
    if (angle > limit)
        angle = limit;
    if (angle < -limit)
        angle = -limit;
    zoid->high_angle = angle;
}
