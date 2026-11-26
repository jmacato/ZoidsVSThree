#pragma readonly_strings on
#include "types.h"
#include "joint.h"

typedef struct GroundObject3 {
    u8 pad_00[0x74];
    HSD_JObj *joint;
    u8 pad_78[0x90 - 0x78];
    f32 field_90;
    u8 pad_94[0xE4 - 0x94];
} GroundObject3;

#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40
#define JOBJ_USE_QUATERNION 0x20000

extern GroundObject3 obj[50];
extern s32 objNow;
extern s32 grdCamChkObjR(HSD_JObj *joint);
extern void HSD_JObjDispAll(HSD_JObj *joint, void *mtx, u32 flags, u32 rendermode);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *condition);

#pragma auto_inline off
static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    (jobj) ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & JOBJ_USER_DEF_MTX) && (jobj->flags & JOBJ_MTX_DIRTY);
}

#define HSD_JObjSetMtxDirty(jobj) \
    do { \
        if ((jobj) != 0 && !HSD_JObjMtxIsDirty(jobj)) \
            HSD_JObjSetMtxDirtySub(jobj); \
    } while (0)

static inline void HSD_JObjSetRotationY(HSD_JObj *jobj, f32 value)
{
    (jobj) ? (void)0 : __assert("jobj.h", 696, "jobj");
    (!(jobj->flags & JOBJ_USE_QUATERNION)) ? (void)0 : __assert("jobj.h", 697, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    jobj->rotation[1] = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

void grdObjDispOpa(void)
{
    GroundObject3 *object;
    s32 i;

    for (i = 0; i < objNow; i++) {
        object = &obj[i];
        if (object->joint != (void *)0 && grdCamChkObjR(object->joint) != 0) {
            HSD_JObjSetRotationY(object->joint, object->field_90);
            HSD_JObjDispAll(object->joint, 0, HSD_TRSP_OPA, 0);
        }
    }
}
