#include "zoid3.h"
#include "game_camera.h"
#include "model_archive.h"
#include "game_text.h"

#pragma readonly_strings on

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

typedef struct GameModeState3 {
    u8 reserved_00[4];
    s32 game_type;
    u8 reserved_08[0x80];
} GameModeState3;

typedef struct ZoidName3 {
    u8 bytes[0x7FC];
} ZoidName3;

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

static inline void HSD_JObjSetScaleX(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 805, "jobj");
    jobj->scale.x = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

extern ModelArchive *dsp1p;
extern GameModeState3 GameMode;
extern ZoidName3 Tea_zoiddat[];
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern HSD_JObj *GetChild2(ModelArchive *archive, s32 model, s32 second, s32 third, s32 fourth, s32 fifth);
extern s32 sCameraPt2d(CameraState *camera, Vec3 *position, s32 *screen_point);
extern void jobjDisp(HSD_JObj *joint);
extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);
extern void jobjDispAll(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);
extern s32 sprintf(char *buffer, const char *format, ...);

void s1pTarget(CameraState *camera, ZoidState *zoid)
{
    s32 j;
    HSD_JObj *digit;
    HSD_JObj *bar;
    HSD_JObj *lock0;
    HSD_JObj *lock1;
    HSD_JObj *lock2;
    HSD_JObj *lock3;
    HSD_JObj *lock4;
    s32 flags;
    ZoidState *other;
    HSD_JObj *joint;
    s32 i;
    s32 health;
    s32 visible;
    s32 slot;
    s32 pt[2];
    f32 pos[3];
    char buf[12];
    f32 x;
    f32 y;
    f32 ratio;

    if (dsp1p == NULL)
        return;
    slot = zoid->slot;
    lock0 = GetChild(dsp1p->models[14], 0, 0, -1, -1, -1);
    lock1 = GetChild(dsp1p->models[14], 0, 1, -1, -1, -1);
    lock2 = GetChild(dsp1p->models[14], 0, 2, -1, -1, -1);
    lock3 = GetChild(dsp1p->models[14], 0, 3, -1, -1, -1);
    lock4 = GetChild(dsp1p->models[14], 0, 4, -1, -1, -1);
    bar = dsp1p->models[16];
    if (bar == NULL)
        return;
    for (i = 0; i < 16; i++) {
        other = &Zoid[i];
        if (other->joint == (void *)0)
            continue;
        if (other == zoid)
            continue;
        if (slot == other->slot)
            continue;
        joint = (HSD_JObj *)other->camera_joint;
        flags = 0;
        if (joint == NULL)
            continue;
        for (j = 0; j < 3; j++)
            pos[j] = joint->matrix[j][3];
        visible = sCameraPt2d(camera, (Vec3 *)pos, pt);
        if (visible == 0)
            continue;
        if (zoid->attack_in_range[i] == 1)
            flags |= 4;
        if (other->field_1E50 != 0)
            flags = 0;
        if (zoid->target_pending != 0 && zoid->target_slot == i)
            flags |= 0x10;
        x = (pt[0] - 320) / 10.0;
        y = (240 - pt[1]) / 10.0;
        if (other->stel_state == 2)
            flags = 0;
        if (lock0 == NULL)
            flags = 0;
        if (lock1 == NULL)
            flags = 0;
        if (lock2 == NULL)
            flags = 0;
        if (lock4 == NULL)
            flags = 0;
        if (flags != 0) {
            HSD_JObjSetTranslateX(lock0, x);
            HSD_JObjSetTranslateY(lock0, y);
            HSD_JObjSetTranslateX(lock1, x);
            HSD_JObjSetTranslateY(lock1, y);
            HSD_JObjSetTranslateX(lock2, x);
            HSD_JObjSetTranslateY(lock2, y);
            HSD_JObjSetTranslateX(lock4, x);
            HSD_JObjSetTranslateY(lock4, y);
            if (flags & 1)
                jobjDisp(lock0);
            if (flags & 2)
                jobjDisp(lock1);
            if (flags & 4)
                jobjDisp(lock2);
            if (flags & 0x10)
                jobjDispAll(lock4);
        }
        health = other->health;
        if (other->health_bar_timer != 0) {
            HSD_JObj *child;
            HSD_JObjSetTranslateX(bar, 2.0f + x);
            HSD_JObjSetTranslateY(bar, y - 2.0f);
            ratio = (f32)health / (f32)other->max_health;
            child = GetChild(bar, 0, 1, -1, -1, -1);
            HSD_JObjSetScaleX(child, ratio);
            sMakeMatrix(bar);
            jobjDispAll(bar);
            if (health > 9999)
                health = 9999;
            sprintf(buf, "%04d", health);
            for (j = 0; j < 4; j++) {
                digit = GetChild(dsp1p->models[12], 0, 0, buf[j] - '0', -1, -1);
                jobjCopyPos(GetChild(bar, 0, 0, j, -1, -1), digit);
                jobjDispAll(digit);
            }
            putAscJobj(GetChild(bar, 0, 0, 4, -1, -1), 0, (char *)&Tea_zoiddat[other->type]);
        }
        if (GameMode.game_type == 5 && i < 4 && other->stel_state == 0) {
            digit = GetChild2(dsp1p, 18, i | i, -1, -1, -1);
            if (digit != NULL) {
                HSD_JObjSetTranslateX(digit, 2.0f + x);
                HSD_JObjSetTranslateY(digit, y - 2.0f);
                sMakeMatrix(digit);
                jobjDispAll(digit);
            }
        }
    }
}
