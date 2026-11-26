#pragma readonly_strings on
#pragma auto_inline off
#include "zoid3.h"

extern void sGlobal2Local(HSD_JObj *joint);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, u32 line, const char *expr);
extern f32 zdColPosY(f32 *point, u16 *selector);

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

static inline void HSD_JObjSetScaleX(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 805, "jobj");
    jobj->scale.x = value;
    if (!(jobj->flags & 0x02000000))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetScaleY(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 819, "jobj");
    jobj->scale.y = value;
    if (!(jobj->flags & 0x02000000))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetScaleZ(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 833, "jobj");
    jobj->scale.z = value;
    if (!(jobj->flags & 0x02000000))
        HSD_JObjSetMtxDirty(jobj);
}

void ZoidTo(ZoidState *zoid, ZoidLimb *limb, s32 ground)
{
    HSD_JObj *joint;
    f32 y;
    f32 *position;
    f32 saved[3];
    s32 i;

    if (zoid == (void *)0)
        return;
    if (zoid->joint == (void *)0)
        return;
    if (limb == (void *)0)
        return;
    joint = limb->joint;
    if (joint == (void *)0)
        return;
    position = limb->position;
    for (i = 0; i < 3; i++)
        saved[i] = joint->matrix[i][3];
    for (i = 0; i < 3; i++)
        position[i] = joint->matrix[i][3];
    y = zdColPosY(position, 0);
    if (y > zoid->field_1AA8 && zoid->field_0170 != 0 && y > position[1])
        y = position[1];
    if (position[1] < y)
        position[1] = y;
    for (i = 0; i < 3; i++)
        joint->matrix[i][3] = position[i];
    sGlobal2Local(joint);
    HSD_JObjSetScaleX(joint, 1.0f);
    HSD_JObjSetScaleY(joint, 1.0f);
    HSD_JObjSetScaleZ(joint, 1.0f);
}
