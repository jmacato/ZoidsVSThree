#include "zoid3.h"

typedef struct CameraState3 {
    u8 pad_000[0x10];
    f32 focus_heading;
    u8 pad_014[0x18];
    f32 focus_distance;
    s32 mount_index;
    u8 pad_034[0x190];
    ZoidState *zoid;
    u8 pad_1C8[0x34];
    f32 focus[3];
} CameraState3;

extern void angLimit(f32 *angle);
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);

static inline f32 wsinf(f32 x)
{
    return sinf(x);
}

static inline f32 wcosf(f32 x)
{
    return cosf(x);
}

void setCamTgtLockOFF(CameraState3 *camera)
{
    f32 angle;
    f32 position[3];
    void *anim;
    s32 i;
    HSD_JObj *joint;
    ZoidState *zoid;
    u8 *control;
    s32 *mount;
    f32 distance;
    f32 horizontal;

    if (camera != (void *)0) {
    zoid = camera->zoid;
    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        control = zoid->field_2090;
        anim = zoid->anim_data;
        mount = (s32 *)(control + camera->mount_index * 16);
        if (*mount == -1)
            joint = zoid->field_1ACC;
        else
            joint = zoid->weapon_slots[*mount].joint;
        if (joint == (void *)0)
            joint = *(HSD_JObj **)zoid->body_coobj;
        if (joint == (void *)0)
            joint = zoid->joint;
        if (joint == (void *)0)
            return;
        angle = zoid->heading;
        distance = camera->focus_distance;
        if (distance < 0.5)
            distance = 0.5f;
        camera->focus_heading = angle;
        angLimit(&angle);
        for (i = 0; i < 3; i++)
            position[i] = joint->matrix[i][3];
        if (zoid->field_0170 != 0) {
            horizontal = distance * wcosf(zoid->high_angle);
            position[0] += horizontal * wsinf(angle);
            position[2] += horizontal * wcosf(angle);
            position[1] += 2.0f;
            position[1] -= distance * wsinf(zoid->high_angle);
        } else {
            position[0] += distance * wsinf(angle);
            position[2] += distance * wcosf(angle);
            position[1] += 2.0f;
        }
        for (i = 0; i < 3; i++)
            (&camera->focus[0])[i] = position[i];
    }
    }
}
