#pragma readonly_strings on
#include "zoid3.h"
#include "ground_collision.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern void sGlobal2Local(HSD_JObj *joint);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *expr);
extern f32 zdColPosY(f32 *point, u16 *selector);

#pragma auto_inline off
static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & JOBJ_USER_DEF_MTX) && (jobj->flags & JOBJ_MTX_DIRTY);
}

#define HSD_JObjSetMtxDirty(jobj) \
    do { \
        if ((jobj) != NULL && !HSD_JObjMtxIsDirty(jobj)) \
            HSD_JObjSetMtxDirtySub(jobj); \
    } while (0)

static inline void HSD_JObjSetTranslateX(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 952, "jobj");
    jobj->translation.x = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

typedef f32 (*MtxPtr)[4];

void ik3dOn(ZoidState *zoid, FootJoint *foot)
{
    HSD_JObj *joint;
    MtxPtr matrix;
    f32 offset;
    f32 y;
    Vec3 point;
    u16 selector;

    if (zoid == (void *)0) {
        return;
    }
    if (zoid->joint == (void *)0) {
        return;
    }
    joint = foot->joint;
    if (joint == (void *)0) {
        return;
    }
    matrix = joint->matrix;
    offset = foot->offset;
    point.x = matrix[0][3];
    point.y = foot->height - offset;
    point.z = matrix[2][3];
    y = zdColPosY(&point.x, &selector);
    if (y > zoid->field_1AA8) {
        y = point.y - 10.0f;
        selector = GROUND_POLYGON_NONE;
    }
    foot->ground_polygon_index = selector;
    foot->ground = y;
    if (zoid->death_pending != 0) {
        return;
    }
    matrix[1][3] = (y + offset) - 10.0f;
    foot->depth = 0.0f;
    HSD_JObjSetTranslateX(foot->joint, 0.0f);
    sGlobal2Local(foot->joint);
}
