#pragma auto_inline off
#pragma readonly_strings on
#include "zoid3.h"
#include "ground_collision.h"

typedef struct CoObjPoly {
    HSD_JObj *joint;
    HSD_JObj *base_joint;
    u8 reserved_08[0x10];
    u32 ground_contact;
    u8 reserved_1C[0xC];
    s16 ground_polygon_index;
    u8 reserved_2A[0xE];
    f32 inverse[3][4];
} CoObjPoly;

extern GroundMask GXColorZoid;
extern s32 zdGrdCoPo00(CoObjPoly *object, GroundPolygon *polygon);
extern void sGlobal2Local(HSD_JObj *joint);
extern u32 PSMTXInverse(f32 src[3][4], f32 dst[3][4]);
extern f32 zdCoGrdRot(ZoidState *zoid, CoObjPoly *object, Vec3 *direction, s32 mode);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, u32 line, const char *expr);

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

static inline void HSD_JObjSetScaleZ(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 833, "jobj");
    jobj->scale.z = value;
    if (!(jobj->flags & 0x02000000))
        HSD_JObjSetMtxDirty(jobj);
}

s32 zdGroundCoPoly(ZoidState *zoid, CoObjPoly *object, s16 index, GroundPolygon *polygon, s32 mode, f32 *out, s32 *counter, f32 scale)
{
    s32 i;
    s32 k;
    Vec3 *normal;
    s32 flag;
    s32 count;
    f32 len;
    f32 push;
    f32 rate;
    f32 diff;
    void *anim;
    f32 unused_len;
    f32 pos[3];
    f32 tip[3];
    GroundMask mask;

    if (object->joint == (void *)0)
        return 0;
    normal = &grdcNormal[polygon->normal_index];
    flag = 1;
    zoid = zoid;
    zoid = zoid;
    zoid = zoid;
    zoid = zoid;
    zoid = zoid;
    zoid = zoid;
    zoid = zoid;
    zoid = zoid;
    zoid = zoid;
    zoid = zoid;
    zoid = zoid;
    zoid = zoid;
    zoid = zoid;
    zoid = zoid;
    zoid = zoid;
    zoid = zoid;
    k = k;
    k = k;
    k = k;
    k = k;
    k = k;
    k = k;
    k = k;
    k = k;
    k = k;
    k = k;
    k = k;
    k = k;
    k = k;
    k = k;
    k = k;
    k = k;
    counter = counter;
    counter = counter;
    switch (zoid->action) {
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
        flag = 0;
        break;
    }
    if (zoid->field_1360 != 0 && zoid->weapon_mount == 19)
        flag = 0;
    anim = zoid->anim_data;
    unused_len = GROUND_NO_HIT;
    if (mode == 2 || mode == 3) {
        for (i = 0; i < 3; i++) {
            pos[i] = zoid->joint->child->matrix[i][3];
            tip[i] = object->joint->matrix[i][3];
        }
        pos[1] = zoid->field_1A7C->matrix[1][3];
        mask = GXColorZoid;
        len = sColPt00((Vec3 *)pos, (Vec3 *)tip, polygon, &mask);
        count = (s32)(scale / 4.0f);
        if (flag == 0)
            count = (s32)(scale / 10.0f);
        if (GROUND_NO_HIT != len) {
            for (i = 0; i < 3; i++) {
                if (i == 1 && mode == 3)
                    continue;
                out[i] += (f32)count * (&normal->x)[i];
            }
            (*counter)++;
            object->ground_polygon_index = index;
            object->ground_contact |= 1;
            zoid->grounded = 1;
        }
    }
    if (zdGrdCoPo00(object, polygon) == 0)
        return 0;
    object->ground_polygon_index = index;
    object->ground_contact |= 1;
    if (mode == 0)
        return 1;
    zoid->grounded = 1;
    k = 0;
    push = 0.2f;
    for (; k < 40; k++) {
        for (i = 0; i < 3; i++) {
            if (object->base_joint != 0)
                object->base_joint->matrix[i][3] += push * (&normal->x)[i];
            object->joint->matrix[i][3] += push * (&normal->x)[i];
        }
        PSMTXInverse(object->joint->matrix, object->inverse);
        if (zdGrdCoPo00(object, polygon) == 0)
            break;
    }
    if (object->base_joint != 0) {
        sGlobal2Local(object->base_joint);
        HSD_JObjSetScaleX(object->base_joint, 1.0f);
        HSD_JObjSetScaleY(object->base_joint, 1.0f);
        HSD_JObjSetScaleZ(object->base_joint, 1.0f);
    }
    if (k != 0)
        zoid->field_1C8C += zdCoGrdRot(zoid, object, normal, 1);
    if (zoid->ground_turn == 0 && k != 0) {
        rate = 0.14f;
        if (mode <= 1)
            rate = 0.002f;
        for (i = 0; i < 3; i++) {
            if (i == 1 && mode == 3)
                continue;
            out[i] += scale * ((f32)k * (rate * (&normal->x)[i]) / 2.0f);
        }
        (*counter)++;
        if (mode >= 2) {
            for (i = 0; i < 3; i++) {
                if (i == 1)
                    continue;
                diff = 0.3 * (zoid->joint->child->matrix[i][3]
                              - *(f32 *)(*(u8 **)((u8 *)zoid->pose + 4) + 0x40 + i * 16));
                out[i] -= 0.1 * (diff * scale);
            }
            (*counter)++;
        }
    }
    return 1;
}
