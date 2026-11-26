#pragma auto_inline off
#pragma readonly_strings on
#include "zoid3.h"
#include "model_archive.h"
#include "matrix.h"

typedef struct StageInfo3 {
    u8 reserved_00[6];
    s16 radar_length;
    u8 reserved_08[0x58];
} StageInfo3;

typedef struct GameMode3 {
    s32 reserved_00;
    s32 game_type;
    u8 reserved_08[0x40];
} GameMode3;

extern ModelArchive *dspRader;
extern StageInfo3 Stg;
extern GameMode3 GameMode;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjCopyPosS(HSD_JObj *source, HSD_JObj *target);
extern struct HSD_TObj *searchTObjN(HSD_JObj *joint, s32 *index);
extern void texScrollMtx(struct HSD_TObj *tobj, Mtx matrix);
extern void jobjDisp(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);
extern void s1pRaderMapZoid(ZoidState *zoid, s32 kind, HSD_JObj *joint);
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

static inline f32 HSD_JObjGetScaleX(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 899, "jobj");
    return jobj->scale.x;
}

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

static inline void HSD_JObjSetTranslateX(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 952, "jobj");
    jobj->translation.x = value;
    if (!(jobj->flags & 0x02000000))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetTranslateY(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 966, "jobj");
    jobj->translation.y = value;
    if (!(jobj->flags & 0x02000000))
        HSD_JObjSetMtxDirty(jobj);
}

void s1pRaderMap(ZoidState *zoid, HSD_JObj *joint, HSD_JObj *base)
{
    s32 kind;
    s32 i;
    ZoidState *other;
    HSD_JObj *child;
    struct HSD_TObj *tobj;
    f32 range;
    f32 stg;
    f32 unit;
    f32 factor;
    f32 base_scale;
    f32 x;
    f32 y;
    s32 index;
    Mtx matrix;

    if (dspRader == 0)
        return;
    range = zoid->field_1EF8;
    jobjCopyPosS(joint, dspRader->models[0]);
    child = GetChild(dspRader->models[0], 0, 1, -1, -1, -1);
    index = 0;
    tobj = searchTObjN(child, &index);
    PSMTXTrans(matrix, 0.0f, 0.0f, 0.0f);
    texScrollMtx(tobj, matrix);
    jobjDisp(child);
    child = GetChild(dspRader->models[0], 0, 0, 1, 0, 0);
    stg = Stg.radar_length;
    if (child != 0 && stg) {
        unit = 2.0 * (range / stg);
        base_scale = HSD_JObjGetScaleX(base);
        factor = 12.8 * base_scale / stg;
        if (GameMode.game_type == 2)
            factor = 2.0 * (12.8 * base_scale / stg);
        HSD_JObjSetScaleX(child, 1.0f);
        HSD_JObjSetScaleY(child, 1.0f);
        x = zoid->position[0] * factor;
        HSD_JObjSetTranslateX(child, x);
        y = -zoid->position[2] * factor;
        HSD_JObjSetTranslateY(child, y);
        HSD_JObjSetScaleX(child, unit);
        HSD_JObjSetScaleY(child, unit);
        sMakeMatrix(child);
        jobjDisp(child);
    }
    s1pRaderMapZoid(zoid, 0, base);
    for (i = 0; i < 16; i++) {
        other = &Zoid[i];
        if (zoid == other)
            continue;
        if (other->joint == (void *)0)
            continue;
        kind = zoid->slot == other->slot ? 3 : 1;
        if (zoid->distances[i] > range)
            continue;
        s1pRaderMapZoid(other, kind, base);
    }
}
