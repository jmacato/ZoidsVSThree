#include "zoid3.h"
#include "ground_collision.h"

extern GroundMask GXColorZoid;
extern f32 sinf(f32);
extern f32 cosf(f32);
extern f32 zdColPosY(f32 *point, u16 *polygon);
extern void limitHigh(f32 *position);
extern void limitHighAng(ZoidState *zoid);
extern void getWarn(f32 *position, f32 *out);
extern f32 ZoidCalcAngle(ZoidState *zoid, f32 *point);

static inline f32 wsinf(f32 x)
{
    return sinf(x);
}

static inline f32 wcosf(f32 x)
{
    return cosf(x);
}

s32 zdActFlyB_susumu(ZoidState *zoid)
{
    u16 sel;
    f32 unused[3] = { 0.0f, 0.0f, 0.0f };
    f32 c[3];
    f32 a[3];
    f32 d[3];
    f32 b[3];
    f32 e[3];
    f32 w[3];
    GroundMask mask;
    f32 ratio;
    f32 y;
    f32 h;
    f32 v;
    f32 vx;
    f32 vz;
    f32 hit;
    s32 i;

    if (0.0f == zoid->field_1D60) {
        return 1;
    }
    h = zoid->field_1D60 * wcosf(zoid->field_1D58);
    v = zoid->field_1D60 * wsinf(zoid->field_1D58);
    if (0.0f == h && 0.0f == v) {
        return 1;
    }
    vx = h * wsinf(zoid->field_1D5C);
    vz = h * wcosf(zoid->field_1D5C);
    ratio = (*(HSD_JObj **)zoid->body_coobj)->scale.x / zoid->field_1D60;
    for (i = 0; i < 3; i++) {
        a[i] = zoid->position[i];
        b[i] = a[i];
        c[i] = zoid->position[i];
        if (i == 1) {
            c[i] = zoid->field_1A7C->matrix[i][3];
        }
        d[i] = c[i];
    }
    e[0] = vx;
    e[2] = vz;
    e[1] = -v;
    for (i = 0; i < 3; i++) {
        a[i] += e[i];
        d[i] += ratio * e[i] / 2.0f;
        c[i] -= ratio * e[i] / 4.0f;
    }
    limitHigh(a);
    limitHighAng(zoid);
    mask = GXColorZoid;
    hit = sColPt((Vec3 *)c, (Vec3 *)d, &mask);
    if (10000.0f != hit) {
        zoid->field_1C90[0] = 0.0f;
        zoid->field_1C90[2] = 0.0f;
        zoid->field_1D60 = 0.0f;
        zoid->field_1C90[1] = 0.0f;
        return 1;
    }
    for (i = 0; i < 3; i++) {
        zoid->position[i] = a[i];
    }
    y = zdColPosY(zoid->position, &sel);
    if (sel == 0xFFFF) {
        for (i = 0; i < 3; i++) {
            zoid->position[i] = zoid->field_1C24[i];
        }
        zoid->field_1D60 = 0.0f;
        getWarn(zoid->position, w);
        zoid->heading += ZoidCalcAngle(zoid, w);
        return 1;
    }
    if (y > 0.3 + zoid->field_1AA8) {
        return 0;
    }
    if (y > zoid->position[1]) {
        if (y < zoid->position[1] - 1.0f) {
            for (i = 0; i < 3; i++) {
                zoid->position[i] = b[i];
            }
            return 1;
        }
        zoid->position[1] = 0.5 + y;
        zoid->field_1D60 *= 0.7;
        if (zoid->field_1D58 > 0.0f) {
            zoid->field_1D58 = 0.7 * -zoid->field_1D58;
        }
        return 1;
    }
    return 0;
}
