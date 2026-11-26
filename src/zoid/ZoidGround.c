#pragma auto_inline off
#pragma readonly_strings on
#include "zoid3.h"
#include "ground_collision.h"

extern Vec3 CubeTBL[9];
extern s32 sCamNN;
extern void dummyFunc(const char *text);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, u32 line, const char *expr);
extern void PSMTXMultVecArray(f32 m[3][4], Vec3 *src, Vec3 *dst, u32 count);
extern void PSMTXMultVec(f32 m[3][4], Vec3 *src, Vec3 *dst);
extern void zdCgTblClear(ZoidState *zoid);
extern s32 addPolyList(s32 count, u16 *table, u16 **list);
extern u16 *sColPosTBL(Vec3 *point);
extern u16 *zdColPosTBL(HSD_JObj *joint);
extern f32 sLiner(f32 target, f32 current, f32 fraction);
extern void sLinier3d(Vec3 *current, Vec3 *target, f32 fraction);
extern void ZoidCoObjMtxI(ZoidState *zoid);
extern s32 zdGroundTBL(ZoidState *zoid, u16 *table, f32 *accum, s32 *count, s32 flag);
extern f32 zdColPosY(f32 *point, u16 *selector);
extern void zdSetXYZ(ZoidState *zoid);
extern void zdSetXYZ2(ZoidState *zoid);
extern void sMakeMatrix(HSD_JObj *joint);
extern void sGlobal2Local(HSD_JObj *joint);

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

static inline void HSD_JObjSetMtxDirtyInline(HSD_JObj *jobj)
{
    HSD_JObjSetMtxDirty(jobj);
}

s32 ZoidGround(ZoidState *zoid)
{
    s32 unused[102];
    u16 *list[9];
    u16 selector;
    s32 pad[6];
    Vec3 points[9];
    f32 pos2[3];
    f32 pos3[3];
    f32 accum[3];
    s32 count;
    Vec3 vec;
    f32 cur[3];
    f32 prev[3];
    s32 i;
    s32 n;
    u16 *table;
    s32 flag;
    s32 hit;
    s32 moved;
    s32 mount;
    u8 *info;
    u8 *co;
    s32 dead;
    void *anim;
    f32 frac;
    f32 scale;
    f32 damp;
    f32 sweep;

    dead = 0;
    if (zoid == (void *)0)
        return 0;
    anim = zoid->anim_data;
    if (anim == 0)
        return 0;
    info = (u8 *)zoid->slider_info;
    if (info == 0)
        return 0;
    zoid->field_1EAE = GROUND_POLYGON_NONE;
    co = zoid->body_coobj;
    if (*(HSD_JObj **)co == (void *)0)
        return 0;
    flag = 1;
    flag = flag;
    flag = flag;
    flag = flag;
    flag = flag;
    flag = flag;
    flag = flag;
    flag = flag;
    flag = flag;
    switch (zoid->action) {
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
        flag = 0;
        break;
    }
    mount = zoid->weapon_mount;
    if (zoid->field_1360 != 0 && mount != -1) {
        if (mount == 19)
            mount = 0;
        else
            mount = mount + 1;
        if (((s8 *)info + 8)[mount * 16] == 1)
            return 0;
        flag = 0;
    }
    zoid->field_1EAC = 0;
    dummyFunc("0");
    for (i = 0; i < 3; i++)
        accum[i] = 0.0f;
    count = 0;
    PSMTXMultVecArray((*(HSD_JObj **)co)->matrix, CubeTBL, points, 9);
    zdCgTblClear(zoid);
    for (i = 0, n = 0; i < 9; i++) {
        table = sColPosTBL(&points[i]);
        n = addPolyList(n, table, list);
    }
    table = zdColPosTBL(*(HSD_JObj **)zoid->head_coobj);
    n = addPolyList(n, table, list);
    table = zdColPosTBL(*(HSD_JObj **)zoid->neck_coobj);
    n = addPolyList(n, table, list);
    table = zdColPosTBL(*(HSD_JObj **)zoid->bust_coobj);
    n = addPolyList(n, table, list);
    table = zdColPosTBL(*(HSD_JObj **)zoid->hip_coobj);
    n = addPolyList(n, table, list);
    table = zdColPosTBL(zoid->joint);
    n = addPolyList(n, table, list);
    for (i = 0; i < 100; i++) {
        frac = (f32)(i % 10) / 10.0f;
        vec.x = sLiner(0.5f, -0.5f, frac);
        frac = (f32)(i / 10) / 10.0f;
        vec.z = sLiner(0.5f, -0.5f, frac);
        vec.y = 0.0f;
        PSMTXMultVec((*(HSD_JObj **)co)->matrix, &vec, &points[0]);
        table = sColPosTBL(&points[0]);
        n = addPolyList(n, table, list);
    }
    if (n == 0)
        return 0;
    list[n] = 0;
    for (i = n; i < 9; i++)
        list[i] = 0;
    dummyFunc("1");
    ZoidCoObjMtxI(zoid);
    hit = 0;
    zoid->field_1C8C = 0.0f;
    for (i = 0; i < n; i++) {
        table = list[i];
        if (table != (void *)0 && zdGroundTBL(zoid, table, accum, &count, flag) != 0)
            hit = 1;
    }
    scale = zoid->field_20C0;
    if (scale < 100.0f)
        scale = 100.0f;
    if (zoid->action >= 0x22 && zoid->action <= 0x2B) {
        damp = 100.0 / scale;
        if (scale > 100.0f)
            damp *= 0.3;
    } else {
        damp = 1.0f;
    }
    for (i = 0; i < 3; i++) {
        if (flag != 0)
            pos2[i] = zoid->position[i];
        else
            pos2[i] = zoid->joint->child->matrix[i][3];
        pos3[i] = pos2[i];
    }
    moved = 0;
    if (count > 0) {
        for (i = 0; i < 3; i++) {
            accum[i] *= 10.0 / (f32)count;
            pos2[i] += damp * accum[i];
        }
        for (i = 0; i < 3; i++) {
            if (flag != 0)
                zoid->position[i] = pos2[i];
            else
                zoid->joint->child->matrix[i][3] = pos2[i];
        }
        if (zoid->field_1CCC == 0) {
            for (i = 0; i < 3; i++)
                zoid->field_1CC0[i] = damp * accum[i];
            zoid->field_1CCC = 30;
        }
        moved = 1;
    }
    zdColPosY(pos2, &selector);
    if (selector == GROUND_POLYGON_NONE) {
        for (i = 0; i < 3; i++) {
            if (flag != 0)
                zoid->position[i] = zoid->field_1C24[i];
            else
                zoid->joint->child->matrix[i][3] = zoid->child_matrix[i][3];
        }
        moved = 1;
    }
    if (moved != 0) {
        if (flag != 0) {
            zdSetXYZ2(zoid);
        } else {
            sGlobal2Local(zoid->joint->child);
            HSD_JObjSetMtxDirtyInline(zoid->joint->child);
        }
    }
    if (sCamNN == 4)
        zoid->field_1C8C = 0.0f;
    if (0.0f != zoid->field_1C8C) {
        zoid->heading += zoid->field_1C8C;
        zdSetXYZ(zoid);
        sMakeMatrix(zoid->joint);
    }
    sMakeMatrix(zoid->joint);
    dummyFunc("2");
    if (zoid->field_1A7C != 0) {
        GroundMask dead_mask = {{3, 0, 0, 0}};

        for (i = 0; i < 3; i++) {
            cur[i] = zoid->field_1A7C->matrix[i][3];
            prev[i] = zoid->field_1A80[i];
        }
        zoid->field_1A98 = 0;
        dummyFunc("3");
        {
            GroundMask mask2;
            GroundMask mask = {{0x17, 0, 0, 0}};

            mask2 = mask;
            sweep = sColPt((Vec3 *)prev, (Vec3 *)cur, &mask2);
        }
        if (GROUND_NO_HIT != sweep) {
            sLinier3d((Vec3 *)prev, (Vec3 *)cur, sweep);
            zoid->field_1A98 = 1;
            zoid->field_1C90[0] = 0.0f;
            zoid->field_1C90[1] = 0.0f;
            zoid->field_1C90[2] = 0.0f;
        }
        dummyFunc("4");
        if (zoid->field_1A98 != 0) {
            (void)0;
        }
        if (*(u32 *)(zoid->head_coobj + 0x18) & 1) {
            (void)0;
        }
    }
    dummyFunc("5");
    dead = dead;
    return hit;
}
