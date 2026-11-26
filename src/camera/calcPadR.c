#include "zoid3.h"

typedef struct PadState3 {
    u8 pad_000[0x6C];
    f32 stick_y;
    f32 stick_x;
} PadState3;

typedef struct CameraState3 {
    u8 pad_000[0x1C4];
    ZoidState *zoid;
    u8 pad_1C8[0x20];
    PadState3 *pad;
    u8 pad_1EC[0x74];
    f32 yaw;
} CameraState3;

extern void angLimit(f32 *angle);
extern f32 atan2f(f32 y, f32 x);

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

void calcPadR(CameraState3 *camera)
{
    ZoidState *zoid;
    PadState3 *pad;
    f32 angle;
    volatile f32 root;
    f32 y;
    f32 x;
    f32 magnitude;
    f32 turn;

    zoid = camera->zoid;
    pad = camera->pad;
    if (zoid != 0) {
        x = pad->stick_x;
        y = pad->stick_y;
        magnitude = y * y + x * x;
        zoid->field_1C6C = magnitude;
        zoid->field_1C70 = sqrtf(magnitude, &root);
        if (magnitude < 0.1) {
            zoid->field_1C68 = 0.0f;
        } else {
            turn = atan2f(-y, x);
            angle = turn + camera->yaw - zoid->heading;
            angLimit(&angle);
            zoid->field_1C68 = angle;
        }
    }
}
