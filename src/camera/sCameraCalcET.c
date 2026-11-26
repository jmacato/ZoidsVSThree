#include "zoid3.h"
#include "cobj.h"

typedef struct CameraState3 {
    u8 pad_000[0x10];
    f32 focus_heading;
    u8 pad_014[0x10];
    f32 focus_elevation;
    u8 pad_028[0x08];
    s32 mount_index;
    u8 pad_034[0x190];
    ZoidState *zoid;
    u8 pad_1C8[0x34];
    Vec3 focus;
    u8 pad_208[0x3C];
    HSD_CObj *cobj;
    Vec3 direction;
} CameraState3;

extern f64 __frsqrte(f64);
extern f32 atan2f(f32 y, f32 x);
extern f32 acosf(f32 x);
extern f32 sLenPoint3dR(Vec3 *point);

static inline f32 sqrtf(f32 x, volatile f32 *y)
{
    static const f64 _half = 0.5;
    static const f64 _three = 3.0;

    if (x > 0.0f) {
        f64 guess = __frsqrte((f64)x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        *y = (f32)(x * guess);
        return *y;
    }
    return x;
}

void sCameraCalcET(CameraState3 *camera)
{
    ZoidState *zoid;
    HSD_JObj *joint;
    u8 *control;
    void *anim;
    s32 *mount;
    s32 axis;
    f32 planar;
    f32 length;
    volatile f32 root;
    f32 z;
    f32 x;

    if (camera != (void *)0 && camera->cobj != (void *)0 && (zoid = camera->zoid) != (void *)0) {
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
        for (axis = 0; axis < 3; axis++)
            (&camera->direction.x)[axis] = (&camera->focus.x)[axis] - joint->matrix[axis][3];
        z = camera->direction.z;
        x = camera->direction.x;
        planar = sqrtf(z * z + x * x, &root);
        length = sLenPoint3dR(&camera->direction);
        if (0.0f != length) {
            camera->focus_elevation = acosf(planar / length);
            camera->focus_heading = atan2f(x, z);
        }
    }
}
