#pragma readonly_strings on
#include "joint.h"
#include "ground_collision.h"
#include "model_archive.h"
#include "angle.h"

typedef struct Missile3 {
    u8 reserved_00[0x08];
    s32 kind;
    u8 reserved_0C[0x10 - 0x0C];
    s32 hit_ground;
    u16 hit_polygon;
    u8 reserved_16[0x20 - 0x16];
    ModelArchive *archive;
    HSD_JObj *joint;
    u8 reserved_28[0x50 - 0x28];
    f32 speed;
    u8 reserved_54[0x58 - 0x54];
    f32 matrix[3][4];
    f32 previous[3][4];
    f32 step_length;
    u8 reserved_BC[0xEC - 0xBC];
    s32 update_count;
    u8 reserved_F0[0xF4 - 0xF0];
    s32 purge_timer;
    s32 hit;
} Missile3;

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40
extern f32 sLenPoint3d(Vec3 *first, Vec3 *second);
extern void sLinier3d(Vec3 *first, Vec3 *second, f32 distance);
extern f32 sColPtN(Vec3 *start, Vec3 *end, GroundMask *mask, u16 *polygon);
extern void sMissileSetAnim(Missile3 *missile, s32 animation);
extern void sGlobal2Local(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);
extern void LoadArcAnimModel2(ModelArchive *archive, HSD_JObj *joint, s32 model, s32 animation);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *expr);
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

static inline void HSD_JObjSetScaleX(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 805, "jobj");
    jobj->scale.x = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

void sAtack(Missile3 *missile)
{
    s32 i;
    Vec3 current;
    Vec3 previous;
    u16 polygon;
    Vec3 next;
    Vec3 hit;
    GroundMask mask;
    f32 distance;
    f32 length;

    if (missile == (void *)0)
        return;
    missile->update_count++;
    if (missile->purge_timer != 0)
        return;
    if (missile->hit != 0)
        return;
    if (missile->kind == 4 && missile->update_count < 3)
        return;
    for (i = 0; i < 3; i++) {
        (&current.x)[i] = missile->matrix[i][3];
        (&previous.x)[i] = missile->previous[i][3];
    }
    length = sLenPoint3d(&current, &previous);
    missile->step_length = length;
    for (i = 0; i < 3; i++) {
        (&next.x)[i] = missile->matrix[i][3];
        (&hit.x)[i] = missile->previous[i][3];
    }
    mask = (GroundMask){{0, 0, 1, 0}};
    distance = sColPtN(&hit, &next, &mask, &polygon);
    if (GROUND_NO_HIT == distance)
        return;
    missile->hit_ground = 1;
    if (polygon != 0xFFFF && missile->hit_polygon == 0xFFFF)
        missile->hit_polygon = polygon;
    if (missile->kind != 4)
        missile->hit = 1;
    sLinier3d(&hit, &next, distance);
    for (i = 0; i < 3; i++) {
        missile->matrix[i][3] = (&hit.x)[i];
        missile->joint->matrix[i][3] = (&hit.x)[i];
    }
    HSD_JObjSetScaleX(missile->joint, 1.0f);
    sGlobal2Local(missile->joint);
    sMakeMatrix(missile->joint);
    if (missile->kind != 4) {
        sMissileSetAnim(missile, 1);
        LoadArcAnimModel2(missile->archive, missile->joint, 0, 1);
        return;
    }
    missile->speed = 0.0f;
}
