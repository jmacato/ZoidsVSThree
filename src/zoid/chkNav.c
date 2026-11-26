#pragma auto_inline off
#pragma readonly_strings on
#include "zoid3.h"
#include "ground_collision.h"

extern GroundMask GXColorZoid;
extern void sGlobal2Local(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, u32 line, const char *expr);

static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & 0x00800000) && (jobj->flags & 0x40);
}

#define HSD_JObjSetMtxDirty(jobj) \
    do { \
        if ((jobj) != 0 && !HSD_JObjMtxIsDirty(jobj)) \
            HSD_JObjSetMtxDirtySub(jobj); \
    } while (0)

static inline void HSD_JObjSetTranslateX(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 952, "jobj");
    jobj->translation.x = value;
    if (!(jobj->flags & 0x02000000))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetTranslateZ(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 980, "jobj");
    jobj->translation.z = value;
    if (!(jobj->flags & 0x02000000))
        HSD_JObjSetMtxDirty(jobj);
}

static inline f32 navPt(f32 *a, f32 *b)
{
    GroundMask mask2;
    mask2 = GXColorZoid;
    return sColPt((Vec3 *)a, (Vec3 *)b, &mask2);
}

void chkNav(ZoidState *zoid)
{
    HSD_JObj *child;
    s32 i;
    f32 a[3];
    f32 b[3];
    f32 d[3];
    u16 selector;
    GroundMask mask;
    f32 x;
    f32 z;

    if (zoid == 0)
        return;
    if (zoid->action_phase == 0) {
        zoid->field_1A74 = 0;
        return;
    }
    if (zoid->field_1A74 != 0)
        return;
    child = zoid->joint;
    if (child == 0)
        return;
    child = child->child;
    if (child == 0)
        return;
    for (i = 0; i < 3; i++) {
        a[i] = zoid->child_matrix[i][3];
        b[i] = child->matrix[i][3];
    }
    for (i = 0; i < 3; i++)
        d[i] = b[i] - a[i];
    for (i = 0; i < 3; i++) {
        if (i != 1) {
            a[i] -= d[i];
            b[i] += 2.0f * d[i];
        }
    }
    a[1] = zoid->field_1A8C[1];
    b[1] = zoid->field_1A7C->matrix[1][3];
    mask = (GroundMask){{255, 0, 0, 0}};
    sColPosAndY((Vec3 *)b, &selector, &mask);
    if (selector == GROUND_POLYGON_NONE) {
        zoid->field_1A74 = 1;
        for (i = 0; i < 3; i++)
            child->matrix[i][3] = zoid->child_matrix[i][3];
        sGlobal2Local(child);
        sMakeMatrix(child);
    }
    if (10000.0f == navPt(a, b))
        return;
    x = zoid->field_1A40[0];
    HSD_JObjSetTranslateX(child, x);
    z = zoid->field_1A40[2];
    HSD_JObjSetTranslateZ(child, z);
    sMakeMatrix(child);
    zoid->field_1A74 = 1;
}
