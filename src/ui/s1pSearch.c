#pragma auto_inline off
#pragma readonly_strings on
#include "zoid3.h"
#include "model_archive.h"
#include "game_mode.h"
#include "ground_collision.h"

typedef struct CameraState3 {
    u8 pad_000[0x214];
    Vec3 eye;
    u8 pad_220[0x40];
    f32 yaw;
} CameraState3;

typedef struct MgState3 {
    u8 pad_0000[0x2AA4];
    s32 kind;
} MgState3;

extern ModelArchive *dspSearch;
extern MgState3 *mgP;
extern s32 gameStartF;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjCopyPosS(HSD_JObj *source, HSD_JObj *target);
extern void sMakeMatrix(HSD_JObj *joint);
extern void jobjDispAll(HSD_JObj *joint);
extern void getWarn(Vec3 *from, Vec3 *to);
extern f32 calcAng(Vec3 *from, Vec3 *to);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *jobj);
extern void __assert(const char *file, u32 line, const char *condition);

static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & 0x00800000) && (jobj->flags & 0x40);
}

static inline void HSD_JObjSetRotationY(HSD_JObj *jobj, f32 z)
{
    jobj ? (void)0 : __assert("jobj.h", 696, "jobj");
    !(jobj->flags & 0x20000) ? (void)0 : __assert("jobj.h", 697, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    jobj->rotation[1] = z;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj))
            HSD_JObjSetMtxDirtySub(jobj);
    }
}

void s1pSearch(CameraState3 *camera, ZoidState *zoid, HSD_JObj *joint)
{
    u16 material;

    s32 kind;
    HSD_JObj *search;
    s32 mode;
    HSD_JObj *child;
    f32 angle;
    s32 state;
    u16 polygon;
    Vec3 pos;
    GroundMask *mask;

    state = 0;
    if (dspSearch == 0)
        return;
    search = dspSearch->models[0];
    if (search == 0)
        return;
    if (zoid == 0)
        return;
    if (zoid->joint == 0)
        return;
    mode = GameMode.game_type;
    if (mode == 9)
        return;
    if (gameStartF != 0)
        return;
    if (mode == 1 || mode == 4) {
        kind = mgP->kind;
        if (kind == 3 || kind == 7) {
            pos.x = (f32) * (s16 *)((u8 *)mgP + 0x3082);
            pos.z = (f32) * (s16 *)((u8 *)mgP + 0x3084);
            state = 1;
            if (*(s8 *)((u8 *)mgP + 0x321A) != 0)
                state = 0;
        }
    }
    polygon = zoid->ground_polygon;
    if (polygon != GROUND_POLYGON_NONE) {
        material = grdcPolygon[polygon].material;
        mask = &grdcMat[material];
        if ((mask->bits[0] & 6) != 0) {
            pos.x = 0.0f;
            pos.y = 0.0f;
            pos.z = 0.0f;
            state = 2;
            getWarn((Vec3 *)zoid->position, &pos);
        }
    }
    if (state == 0)
        return;
    {
        HSD_JObj *GetChild_joint = joint;
        child = GetChild(GetChild_joint, 0, state == 1 ? 9 : 13, -1, -1, -1);
    }
    if (child == 0)
        return;
    jobjCopyPosS(child, search);
    sMakeMatrix(search);
    angle = calcAng(&pos, &camera->eye);
    if (100.0f == angle)
        return;
    angle -= camera->yaw;
    child = GetChild(search, 0, 0, -1, -1, -1);
    if (child != 0)
        HSD_JObjSetRotationY(child, angle);
    jobjDispAll(search);
}
