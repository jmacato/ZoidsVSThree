#pragma readonly_strings on
#pragma auto_inline off
#include "zoid3.h"
#include "model_archive.h"

#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USE_QUATERNION 0x20000

typedef struct ScopeCamera {
    u8 pad_000[0x1C4];
    ZoidState *zoid;
    u8 pad_1C8[0x2FB - 0x1C8];
    s8 scope_on;
    f32 fov;
} ScopeCamera;

extern ModelArchive *dspScope;
extern s32 sCamNN;
extern s32 gameEndF;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjCopyPosS(HSD_JObj *source, HSD_JObj *target);
extern void sMakeMatrix(HSD_JObj *joint);
extern void jobjDisp(HSD_JObj *joint);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, u32 line, const char *condition);

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

static inline void HSD_JObjSetRotationZ(HSD_JObj *jobj, f32 z)
{
    jobj ? (void)0 : __assert("jobj.h", 716, "jobj");
    !(jobj->flags & JOBJ_USE_QUATERNION) ? (void)0 : __assert("jobj.h", 717, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    jobj->rotation[2] = z;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetTranslateX(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 952, "jobj");
    jobj->translation.x = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetTranslateY(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 966, "jobj");
    jobj->translation.y = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

void sDispScope(ScopeCamera *camera, HSD_JObj *joint)
{
    HSD_JObj *GetChild_joint;

    HSD_JObj *root;
    HSD_JObj *child;
    ZoidState *zoid;
    f32 ang;

    if (dspScope == 0)
        return;
    if (gameEndF > 3)
        return;
    if (camera == (void *)0)
        return;
    if (camera->scope_on == 0)
        return;
    zoid = camera->zoid;
    root = dspScope->models[0];
    if (sCamNN == 2) {
        {
            GetChild_joint = joint;
            child = GetChild(GetChild_joint, 0, -1, -1, -1, -1);
        }
        jobjCopyPosS(child, root);
        sMakeMatrix(root);
    }
    if (root == 0)
        return;
    child = GetChild(root, 0, 1, -1, -1, -1);
    HSD_JObjSetRotationZ(child, camera->fov / 6.0);
    sMakeMatrix(child);
    jobjDisp(child);
    if (zoid != 0) {
        ang = 2.0 * (32.0f * zoid->heading / 3.1415926);
        if (ang > 32.0)
            ang -= 32.0;
        if (ang < -32.0)
            ang += 32.0;
        if (ang > 32.0)
            ang -= 32.0;
        if (ang < -32.0)
            ang += 32.0;
        child = GetChild(root, 0, 3, -1, -1, -1);
        HSD_JObjSetTranslateX(child, ang);
        sMakeMatrix(child);
        jobjDisp(child);
        ang = 2.0 * (32.0f * zoid->high_angle / 3.1415926);
        if (ang > 32.0)
            ang -= 32.0;
        if (ang < -32.0)
            ang += 32.0;
        if (ang > 32.0)
            ang -= 32.0;
        if (ang < -32.0)
            ang += 32.0;
        child = GetChild(root, 0, 2, -1, -1, -1);
        HSD_JObjSetTranslateY(child, ang);
        sMakeMatrix(child);
        jobjDisp(child);
    }
    child = GetChild(root, 0, 0, -1, -1, -1);
    sMakeMatrix(child);
    jobjDisp(child);
    child = GetChild(root, 0, 4, -1, -1, -1);
    sMakeMatrix(child);
    jobjDisp(child);
}
