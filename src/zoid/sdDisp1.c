#pragma auto_inline off
#pragma readonly_strings on
#include "zoid3.h"
#include "model_archive.h"
#include "ground_collision.h"

#define NULL 0
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern ModelArchive *sdTest;
extern f64 __frsqrte(f64);
extern f32 zdColPosY(f32 *point, u16 *selector);
extern void PSMTXRotTrig(f32 m[3][4], s32 axis, f32 sin, f32 cos);
extern void PSMTXConcat(f32 a[3][4], f32 b[3][4], f32 ab[3][4]);
extern void PSMTXCopy(f32 src[3][4], f32 dst[3][4]);
extern void HSD_JObjDispAll(HSD_JObj *joint, s32 a, s32 b, s32 c);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *expr);

static inline f32 sqrtf(f32 x)
{
    static const f64 _half = 0.5;
    static const f64 _three = 3.0;
    volatile f32 y;

    if (x > 0.0f) {
        f64 guess = __frsqrte((f64)x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        y = (f32)(x * guess);
        return y;
    }
    return x;
}

static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & 0x00800000) && (jobj->flags & 0x40);
}

#define HSD_JObjSetMtxDirty(jobj) \
    do { \
        if ((jobj) != NULL && !HSD_JObjMtxIsDirty(jobj)) \
            HSD_JObjSetMtxDirtySub(jobj); \
    } while (0)

static inline void HSD_JObjCopyMtx(HSD_JObj *jobj, f32 mtx[3][4])
{
    jobj ? (void)0 : __assert("jobj.h", 1173, "jobj");
    mtx ? (void)0 : __assert("jobj.h", 1174, "mtx");
    PSMTXCopy(mtx, jobj->matrix);
    jobj->flags |= 0x03800000;
    HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjClearUserMtx(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 1199, "jobj");
    jobj->flags &= ~0x03800000;
    HSD_JObjSetMtxDirty(jobj);
}

void sdDisp1(HSD_JObj *joint)
{
    Vec3 *normal;
    f32 m[3][4];
    f32 x;
    f32 rot[3][4];
    f32 z;
    s32 j;
    f32 pos[3];
    u16 selector;
    f32 len;
    GroundPolygon *poly;
    f32 y;
    s32 i;

    if (joint == (void *)0)
        return;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++)
            m[i][j] = joint->matrix[i][j];
        pos[i] = m[i][3];
    }
    for (j = 0; j < 3; j++) {
        m[1][j] *= 0.1;
        m[0][j] *= 2.0f;
        m[2][j] *= 2.0f;
    }
    m[1][3] = zdColPosY(pos, &selector);
    poly = NULL;
    if (selector != GROUND_POLYGON_NONE)
        poly = &grdcPolygon[selector];
    if (poly != NULL) {
        normal = &grdcNormal[poly->normal_index];
        x = normal->x;
        y = normal->y;
        len = sqrtf(x * x + y * y);
        if (len > 0.0f) {
            x /= len;
            y /= len;
            PSMTXRotTrig(rot, 'Z', -x, -y);
            PSMTXConcat(m, rot, m);
        }
        y = normal->y;
        z = normal->z;
        len = sqrtf(z * z + y * y);
        if (len > 0.0f) {
            z /= len;
            y /= len;
            PSMTXRotTrig(rot, 'X', -z, -y);
            PSMTXConcat(m, rot, m);
        }
        y = normal->y;
        x = normal->x;
        z = normal->z;
        len = sqrtf(x * x + y * y + z * z);
        if (len) {
            y /= len;
            for (j = 0; j < 3; j++) {
                m[0][j] /= y;
                m[2][j] /= y;
            }
        }
    }
    HSD_JObjCopyMtx(sdTest->models[0], m);
    HSD_JObjDispAll(sdTest->models[0], 0, 7, 0);
    HSD_JObjClearUserMtx(sdTest->models[0]);
}
