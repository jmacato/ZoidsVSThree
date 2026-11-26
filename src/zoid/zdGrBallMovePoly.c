#include "zoid3.h"
#include "ground_collision.h"

extern GroundMask GXColorZoid;
extern f32 sinf(f32);
extern f32 cosf(f32);

void zdGrBallMovePoly(ZoidState *zoid, u16 index, f32 *position, s32 *count, s32 flag)
{
    f32 speed;
    s32 i;
    f32 p[3];
    f32 q[3];
    f32 d[3];
    GroundMask mask;
    GroundPolygon *polygon;
    Vec3 *normal;
    f32 hit;
    f32 weight;
    f32 sine_angle;
    f32 cosine_angle;
    void *data;

    if (index != 0xFFFF && zoid != 0 && zoid->joint != 0) {
        data = zoid->anim_data;
        if (data != 0) {
            speed = 2.0f;
            if (zoid->field_0170 != 0) {
                speed = 5.0f;
            }
            if (speed) {
                for (i = 0; i < 3; i++) {
                    p[i] = zoid->position[i];
                    if (flag == 0) {
                        p[i] = zoid->joint->child->matrix[i][3];
                    }
                    if (i == 1) {
                        p[i] = zoid->field_1A7C->matrix[1][3];
                    }
                    q[i] = p[i];
                }
                sine_angle = zoid->heading;
                d[0] = speed * sinf(sine_angle);
                cosine_angle = zoid->heading;
                d[2] = speed * cosf(cosine_angle);
                d[1] = 0.0f;
                for (i = 0; i < 3; i++) {
                    p[i] += 0.5 * d[i];
                    q[i] -= d[i];
                }
                q[1] += 0.7;
                polygon = &grdcPolygon[index];
                normal = &grdcNormal[polygon->normal_index];
                mask = GXColorZoid;
                hit = sColPt00((Vec3 *)p, (Vec3 *)q, polygon, &mask);
                if (hit != 10000.0f) {
                    for (i = 0; i < 3; i++) {
                        weight = 0.2f;
                        if (i == 1) {
                            weight = 0.1f;
                        }
                        position[i] += weight * ((f32 *)normal)[i];
                    }
                    zoid->field_1EAC |= 1;
                    (*count)++;
                }
            }
        }
    }
    (void)count;
}
