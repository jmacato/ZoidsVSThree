#include "zoid3.h"

typedef struct CameraState3 {
    u8 reserved_000[0x1C4];
    ZoidState *zoid;
    u8 reserved_1C8[0x214 - 0x1C8];
    Vec3 eye;
    u8 reserved_220[0x260 - 0x220];
    f32 yaw;
} CameraState3;

extern f32 cosf(f32 angle);
extern f32 sinf(f32 angle);

void sCameraRela(CameraState3 *camera, Vec3 *position, Vec3 *relative)
{
    f32 dx;
    f32 dz;
    f32 cosine;
    f32 sine;
    f32 cosine_angle;
    f32 sine_angle;
    ZoidState *zoid;

    cosine_angle = camera->yaw;
    cosine = cosf(cosine_angle);
    sine_angle = camera->yaw;
    sine = sinf(sine_angle);
    zoid = camera->zoid;
    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        dz = position->z - camera->eye.z;
        dx = position->x - camera->eye.x;
        relative->x = -dx * cosine + dz * sine;
        relative->z = dx * sine + dz * cosine;
    }
}
