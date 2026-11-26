#include "zoid3.h"
#include "ground_collision.h"

extern f32 zdColPosY(f32 *point, u16 *polygon);
extern Vec3 *grdcGetNormal(u16 polygon);
extern void sSetRxRzFt(ZoidState *zoid, FootJoint *front, FootJoint *back, f32 *rx, f32 *rz);

void sSetRxRzF(ZoidState *zoid, FootJoint *front, FootJoint *back, f32 *rx, f32 *rz)
{
    f32 position[3];
    u16 polygon;
    f32 a = *rx;
    f32 b = *rz;
    f32 c = *rx;
    f32 d = *rz;
    Vec3 *normal;
    s32 i;

    if (back->joint == (void *)0) {
        return;
    }
    for (i = 0; i < 3; i++) {
        position[i] = (front->joint->matrix[i][3] + back->joint->matrix[i][3]) / 2.0f;
    }
    zdColPosY(position, &polygon);
    normal = grdcGetNormal(polygon);
    if (normal == (void *)0) {
        return;
    }
    sColGetRxRz(normal, zoid->heading, &a, &b);
    sSetRxRzFt(zoid, front, back, &c, &d);
    *rx = (a + c) / 2.0f;
    *rz = b;
}
