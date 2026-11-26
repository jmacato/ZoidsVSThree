#include "zoid3.h"
#include "ground_collision.h"
#pragma readonly_strings on

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern void sGlobal2Local(HSD_JObj *joint);
extern f32 zdColPosY(Vec3 *point, u16 *selector);
extern f32 sLenPoint3dR(Vec3 *point);
extern f32 *grdcGetNormal(u16 selector);
extern u32 GXColorZoid;
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *expr);

#pragma auto_inline off
static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & JOBJ_USER_DEF_MTX) && (jobj->flags & JOBJ_MTX_DIRTY);
}

static inline void HSD_JObjSetMtxDirty(HSD_JObj *jobj)
{
    if (jobj != NULL && !HSD_JObjMtxIsDirty(jobj))
        HSD_JObjSetMtxDirtySub(jobj);
}

typedef struct CoObj3 {
    HSD_JObj *joint;
    HSD_JObj *base_joint;
    f32 minimum_scale;
} CoObj3;

f32 zdDownBody(ZoidState *zoid, CoObj3 *co, s32 *count, f32 *push)
{
    Vec3 position;
    Vec3 delta;
    Vec3 b;
    Vec3 a;
    u16 sel;
    f32 slide[3];
    u32 color;
    f32 radius;
    f32 floor_y;
    f32 depth;
    f32 len;
    f32 s;
    f32 *normal;
    s32 i;

    if (zoid == (void *)0)
        return 0.0f;
    if (zoid->joint == (void *)0)
        return 0.0f;
    if (co == (void *)0)
        return 0.0f;
    if (co->joint == (void *)0)
        return 0.0f;
    if (co->base_joint == (void *)0)
        return 0.0f;
    radius = co->minimum_scale;
    for (i = 0; i < 3; i++) {
        (&position.x)[i] = co->joint->matrix[i][3];
    }
    floor_y = zdColPosY(&position, &sel);
    depth = floor_y - (position.y - radius);
    if (depth < -0.1)
        depth = -0.1f;
    if (depth > 0.1)
        depth = 0.1f;
    co->base_joint->matrix[1][3] += depth;
    if (co->base_joint->matrix[1][3] < floor_y)
        co->base_joint->matrix[1][3] = floor_y;
    normal = grdcGetNormal(sel);
    if (normal != 0 && normal[1] < 0.5) {
        for (i = 0; i < 3; i++) {
            s = 0.02 * normal[i];
            slide[i] = s;
        }
        (*count)++;
        for (i = 0; i < 3; i++) {
            push[i] += slide[i];
        }
    }
    sGlobal2Local(co->base_joint);
    HSD_JObjSetMtxDirty(co->base_joint);
    for (i = 0; i < 3; i++) {
        (&delta.x)[i] = (&position.x)[i] - zoid->position[i];
    }
    len = sLenPoint3dR(&delta);
    if (0.0f == len)
        return depth;
    for (i = 0; i < 3; i++) {
        (&a.x)[i] = 0.3 * (&delta.x)[i] + (&position.x)[i];
        (&b.x)[i] = zoid->joint->child->matrix[i][3];
    }
    b.y = zoid->field_1A7C->matrix[1][3];
    a.y = zoid->field_1A7C->matrix[1][3];
    color = GXColorZoid;
    if (10000.0f == sColPt(&b, &a, (GroundMask *)&color))
        return depth;
    for (i = 0; i < 3; i++) {
        slide[i] = 0.2 * (-(&delta.x)[i] / len);
    }
    if (slide[1] < 0.0f)
        slide[1] = 0.0f;
    (*count)++;
    for (i = 0; i < 3; i++) {
        push[i] += slide[i];
    }
    return depth;
}
