#include "zoid3.h"
#include "model_archive.h"

#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USE_QUATERNION 0x20000

typedef struct CameraState3 {
    u8 pad_000[0x260];
    f32 yaw;
} CameraState3;

extern ModelArchive *dspRader;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjCopyPosS(HSD_JObj *source, HSD_JObj *target);
extern void HSD_JObjDisp(HSD_JObj *joint, s32 mtx, u32 flags, s32 rendermode);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, u32 line, const char *condition);
extern void sMakeMatrix(HSD_JObj *joint);
extern void s1pRaderBattleZoid(CameraState3 *camera, ZoidState *zoid, s32 kind, HSD_JObj *base);

#pragma readonly_strings on
#pragma auto_inline off
static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & 0x00800000) && (jobj->flags & 0x40);
}

static inline void HSD_JObjSetRotationZ(HSD_JObj *jobj, f32 z)
{
    jobj ? (void)0 : __assert("jobj.h", 716, "jobj");
    !(jobj->flags & JOBJ_USE_QUATERNION) ? (void)0 : __assert("jobj.h", 717, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    jobj->rotation[2] = z;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj))
            HSD_JObjSetMtxDirtySub(jobj);
    }
}

void s1pRaderBattle(CameraState3 *camera, ZoidState *zoid, HSD_JObj *joint, HSD_JObj *base)
{
    HSD_JObj *jobjCopyPosS_target;

    ZoidState *other;
    HSD_JObj *child;
    f32 value;
    s32 i;
    s32 kind;

    if (dspRader == 0)
        return;
    {
        jobjCopyPosS_target = dspRader->models[0];
        jobjCopyPosS(joint, jobjCopyPosS_target);
    }
    sMakeMatrix(dspRader->models[0]);
    child = GetChild(dspRader->models[0], 0, 0, -1, -1, -1);
    HSD_JObjDisp(child, 0, 7, 0);
    child = GetChild(dspRader->models[0], 0, 0, 0, -1, -1);
    value = 3.1415926 + -camera->yaw;
    HSD_JObjSetRotationZ(child, value);
    HSD_JObjDisp(child, 0, 7, 0);
    s1pRaderBattleZoid(camera, zoid, 0, base);
    for (i = 0; i < 16; i++) {
        other = &Zoid[i];
        if (zoid != other && other->joint != (void *)0) {
            if (zoid->slot == other->slot)
                kind = 3;
            else
                kind = 1;
            s1pRaderBattleZoid(camera, other, kind, base);
        }
    }
}
