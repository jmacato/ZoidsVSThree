#include "math_support.h"

typedef struct CameraState3 {
    u8 pad_000[0x1F0];
    Vec3 relative_origin;
    Vec3 focus;
} CameraState3;

void sCamBallOut(CameraState3 *camera, f32 radius)
{
    f32 length;
    f32 delta[3];
    s32 axis;

    for (axis = 0; axis < 3; axis++)
        delta[axis] = (&camera->focus.x)[axis] - (&camera->relative_origin.x)[axis];
    length = square_root(delta[0] * delta[0] + delta[2] * delta[2]);
    if (length > radius)
        return;
    if (length != 0.0f) {
        for (axis = 0; axis < 3; axis++)
            (&camera->focus.x)[axis] = (&camera->relative_origin.x)[axis] + radius * delta[axis] / length;
    }
}
