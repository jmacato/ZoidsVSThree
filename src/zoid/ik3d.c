#pragma auto_inline off
#pragma readonly_strings on
#include "zoid3.h"
#include "ground_collision.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern void sGlobal2Local(HSD_JObj *joint);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *expr);
extern f32 zdColPosY(f32 *point, u16 *selector);
extern void PSMTXRotRad(f32 m[3][4], s8 axis, f32 rad);
extern void PSMTXMultVecSR(f32 m[3][4], Vec3 *src, Vec3 *dst);
extern void PSMTXConcat(f32 a[3][4], f32 b[3][4], f32 ab[3][4]);

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

static inline void HSD_JObjSetTranslateX(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 952, "jobj");
    jobj->translation.x = value;
    if (!(jobj->flags & 0x02000000))
        HSD_JObjSetMtxDirty(jobj);
}

static inline f32 HSD_JObjGetTranslationY(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 1021, "jobj");
    return jobj->translation.y;
}

static inline f32 HSD_JObjGetRotationX(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 748, "jobj");
    return jobj->rotation[0];
}

static inline f32 HSD_JObjGetRotationY(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 762, "jobj");
    return jobj->rotation[1];
}

static inline f32 HSD_JObjGetRotationZ(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 776, "jobj");
    return jobj->rotation[2];
}

static inline void HSD_JObjSetRotationX(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 676, "jobj");
    !(jobj->flags & 0x20000) ? (void)0 : __assert("jobj.h", 677, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    jobj->rotation[0] = value;
    if (!(jobj->flags & 0x02000000))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetRotationZ(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 716, "jobj");
    !(jobj->flags & 0x20000) ? (void)0 : __assert("jobj.h", 717, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    jobj->rotation[2] = value;
    if (!(jobj->flags & 0x02000000))
        HSD_JObjSetMtxDirty(jobj);
}

static inline f32 fabsf(f32 *v)
{
    return (*(u32 *)v &= 0x7FFFFFFF, *v);
}

extern f32 angLimitAbs(f32 value, f32 limit);

void ik3d(ZoidState *zoid, FootJoint *foot)
{
    Vec3 point;
    f32 ry;
    f32 ty;
    u16 selector;
    Vec3 normal;
    Vec3 front;
    f32 m[3][4];
    f32 (*mtx)[4];
    HSD_JObj *joint;
    Vec3 *n;
    f32 offset;
    f32 y;
    f32 val;
    f32 zero_a;
    f32 zero_b;
    s32 mode;
    s32 hit;
    u16 sel;
    s32 flag;
    s32 i;

    hit = 0;
    flag = 0;
    if (foot == (void *)0)
        return;
    foot->flags &= ~FOOT_FLAG_CONTACT;
    joint = foot->joint;
    if (joint == (void *)0)
        return;
    mode = zoid->current_animation;
    if (mode == 2)
        mode = 1;
    offset = foot->offset;
    mtx = joint->matrix;
    ty = HSD_JObjGetTranslationY(joint);
    point.x = mtx[0][3];
    point.y = foot->height - offset;
    point.z = mtx[2][3];
    y = zdColPosY(&point.x, &selector);
    sel = selector;
    if (y > zoid->field_1AA8) {
        selector = GROUND_POLYGON_NONE;
        y = point.y - 10.0f;
    }
    if (zoid->field_1DD4 != 0 || zoid->field_1DD8 != 0)
        mtx[1][3] = (mtx[1][3] + (y + offset)) / 2.0f;
    foot->ground_polygon_index = selector;
    foot->ground = y;
    foot->depth = y - point.y;
    if (zoid->death_pending != 0)
        return;
    zero_a = 0.0f;
    zero_b = 0.0f;
    ry = HSD_JObjGetRotationY(joint);
    if (mode != 1) {
        if (foot->field_2C < 0.0f)
            foot->field_2C += 0.1;
        if (foot->field_2C >= 0.0f)
            foot->field_2C = 0.0f;
    }
    if (y >= point.y)
        hit = 1;
    if (y > mtx[1][3])
        hit = 1;
    if (sel == GROUND_POLYGON_NONE)
        hit = 0;
    if (hit == 0) {
        foot->rot_z = 1.0f;
        foot->rot_x = 1.0f;
    }
    foot->no_contact_frames++;
    if (hit != 0) {
        zoid->grounded = 1;
        foot->no_contact_frames = 0;
        val = 0.002 + (y + offset);
        if (flag == 0)
            mtx[1][3] = val;
        foot->flags |= FOOT_FLAG_CONTACT | FOOT_FLAG_SUPPORTED;
        if (selector != GROUND_POLYGON_NONE) {
            n = &grdcNormal[grdcPolygon[selector].normal_index];
            zoid->ground_normal_count++;
            for (i = 0; i < 3; i++)
                zoid->ground_normal_sum[i] += (&n->x)[i];
            normal.x = n->x;
            normal.y = n->y;
            normal.z = n->z;
            front.x = mtx[0][1];
            front.y = mtx[1][1];
            front.z = mtx[2][1];
            PSMTXRotRad(m, 'Y', -zoid->heading);
            PSMTXMultVecSR(m, &normal, &normal);
            PSMTXMultVecSR(m, &front, &front);
            if (normal.x < front.x) {
                if (foot->rot_z < 0.0f)
                    foot->rot_z = -0.95 * foot->rot_z;
                if (foot->rot_z < 0.001)
                    foot->rot_z = 0.001f;
                PSMTXRotRad(m, 'Z', 0.017453292f * foot->rot_z);
                PSMTXConcat(mtx, m, mtx);
            }
            if (normal.x > front.x) {
                if (foot->rot_z > 0.0f)
                    foot->rot_z = -0.95 * foot->rot_z;
                if (foot->rot_z > -0.001)
                    foot->rot_z = -0.001f;
                PSMTXRotRad(m, 'Z', 0.017453292f * foot->rot_z);
                PSMTXConcat(mtx, m, mtx);
            }
            if (normal.z > front.z) {
                if (foot->rot_x < 0.0f)
                    foot->rot_x = -0.95 * foot->rot_x;
                if (foot->rot_x < 0.001)
                    foot->rot_x = 0.001f;
                PSMTXRotRad(m, 'X', 0.017453292f * foot->rot_x);
                PSMTXConcat(mtx, m, mtx);
            }
            if (normal.z < front.z) {
                if (foot->rot_x > 0.0f)
                    foot->rot_x = -0.95 * foot->rot_x;
                if (foot->rot_x > -0.001)
                    foot->rot_x = -0.001f;
                PSMTXRotRad(m, 'X', 0.017453292f * foot->rot_x);
                PSMTXConcat(mtx, m, mtx);
            }
            foot->field_14 = zero_a;
            foot->field_18 = zero_b;
        }
        HSD_JObjSetTranslateX(joint, 0.0f);
        sGlobal2Local(joint);
        zero_a = HSD_JObjGetRotationX(joint);
        zero_b = HSD_JObjGetRotationZ(joint);
        zero_a = angLimitAbs(zero_a, 0.7853981f);
        zero_b = angLimitAbs(zero_b, 0.7853981f);
        HSD_JObjSetRotationX(joint, zero_a);
        HSD_JObjSetRotationZ(joint, zero_b);
    } else {
        if (mtx[1][3] > point.y + zoid->senter_translation_y) {
            mtx[1][3] = point.y + zoid->senter_translation_y;
            HSD_JObjSetTranslateX(joint, 0.0f);
            sGlobal2Local(joint);
        }
    }
    if (foot->no_contact_frames > 15) {
        if (foot->no_contact_frames > 600)
            foot->no_contact_frames = 600;
        foot->flags &= ~FOOT_FLAG_SUPPORTED;
    }
}
