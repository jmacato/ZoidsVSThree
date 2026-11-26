#pragma readonly_strings on
#include "zoid3.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern u8 Tea_zoiddat[];
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void HSD_JObjSetupMatrixSub(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *expr);
extern f32 sLenPoint3d(Vec3 *first, Vec3 *second);
extern f32 beSide(f32 value, f32 target, f32 step);

static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & 0x00800000) && (jobj->flags & 0x40);
}

static inline void HSD_JObjSetMtxDirty(HSD_JObj *jobj)
{
    if (jobj != NULL && !HSD_JObjMtxIsDirty(jobj))
        HSD_JObjSetMtxDirtySub(jobj);
}

static inline f32 HSD_JObjGetTranslationZ(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 1033, "jobj");
    return jobj->translation.z;
}

static inline void HSD_JObjSetTranslateZ(HSD_JObj *jobj, f32 z)
{
    jobj ? (void)0 : __assert("jobj.h", 980, "jobj");
    jobj->translation.z = z;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetupMatrix(HSD_JObj *jobj)
{
    if (!jobj || !HSD_JObjMtxIsDirty(jobj))
        return;
    HSD_JObjSetupMatrixSub(jobj);
}

void zdAtkSubForPull(ZoidState *zoid, s32 attack)
{
    f32 z;
    f32 scale;
    f32 range;
    f32 dist;
    f32 value;
    ZoidState *target;
    u8 *data;

    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        if (zoid->field_1A78 > 1.0f) {
            zoid->field_1A78 = 1.0f;
        }
        if (zoid->field_1A78 < 0.0f) {
            zoid->field_1A78 = 0.0f;
        }
        if (zoid->attack_target < 0) {
            scale = zoid->field_1A78;
            z = HSD_JObjGetTranslationZ(zoid->joint->child);
            HSD_JObjSetTranslateZ(zoid->joint->child, z * scale);
            sMakeMatrix(zoid->joint);
            HSD_JObjSetupMatrix(zoid->joint);
        } else {
            target = &Zoid[zoid->attack_target];
            if (target->joint == (void *)0) {
                return;
            }
            data = zoid->anim_data;
            if (zoid->ground_turn != 0 || zoid->field_1A74 != 0) {
                return;
            }
            if (*(s16 *)(Tea_zoiddat + zoid->type * 0x7fc + attack * 2 + 0x76e) == 0) {
                return;
            }
            range = *(s16 *)(Tea_zoiddat + zoid->type * 0x7fc + attack * 2 + 0x6c6);
            if (0.0f == range) {
                return;
            }
            range = range + (f32) * (s32 *)(data + 0x2e4) / 10.0;
            if (0.0f == range) {
                return;
            }
            dist = sLenPoint3d((Vec3 *)zoid->position, (Vec3 *)target->position);
            if (dist < 1.0f) {
                dist = 1.0f;
            }
            scale = dist / range;
            if (scale < 0.1) {
                scale = 0.1f;
            }
            if (scale > 1.0f) {
                scale = 1.0f;
            }
            zoid->field_1A78 = beSide(zoid->field_1A78, scale, 0.1f);
            z = zoid->child_translation[2];
            value = z * zoid->field_1A78;
            HSD_JObjSetTranslateZ(zoid->joint->child, value);
            sMakeMatrix(zoid->joint);
            HSD_JObjSetupMatrix(zoid->joint);
        }
    }
}
