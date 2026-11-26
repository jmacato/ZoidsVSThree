#include "zoid3.h"

#pragma readonly_strings on

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern void sGlobal2Local(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *expr);
extern void jobjAnim(HSD_JObj *joint);

extern ModelArchive *csrFile;
extern s32 csrDispON;
extern s32 csrNum;
extern void SetAnimArc2(ModelArchive *file, s32 a, s32 b);

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

static inline void HSD_JObjSetTranslateY(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 966, "jobj");
    jobj->translation.y = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetTranslateZ(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 980, "jobj");
    jobj->translation.z = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

void zdDispCursorSet(ZoidState *zoid, s32 slot, s32 unused)
{
    f32 matrix[3][4];
    f32 (*source)[4];
    s32 i;
    s32 j;
    WeaponSlot *weapon;

    if (csrFile != (void *)0 && zoid != (void *)0 && zoid->joint != (void *)0) {
        csrDispON = 0;
        if (slot >= 0) {
            weapon = &zoid->weapon_slots[slot];
            if (weapon->joint != (void *)0) {
                csrDispON = 1;
                source = weapon->joint->matrix;
                slot = 0;
                if (csrNum != slot) {
                    SetAnimArc2(csrFile, 0, slot);
                    csrNum = slot;
                }
                jobjAnim(csrFile->models[0]);
                for (i = 0; i < 3; i++) {
                    for (j = 0; j < 4; j++) {
                        matrix[i][j] = source[i][j];
                        csrFile->models[0]->matrix[i][j] = source[i][j];
                    }
                }
                sGlobal2Local(csrFile->models[0]);
                HSD_JObjSetTranslateX(csrFile->models[0], matrix[0][3]);
                HSD_JObjSetTranslateY(csrFile->models[0], matrix[1][3]);
                HSD_JObjSetTranslateZ(csrFile->models[0], matrix[2][3]);
                sMakeMatrix(csrFile->models[0]);
            }
        }
    }
    unused = unused;
}
