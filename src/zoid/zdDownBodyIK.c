#pragma readonly_strings on
#include "zoid3.h"

extern f32 zdColPosY(f32 *point, u16 *selector);
extern void sGlobal2Local(HSD_JObj *joint);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern f32 *grdcGetNormal(u16 selector);
extern void __assert(const char *file, s32 line, const char *expr);

#pragma auto_inline off
static inline s32 matrix_is_dirty(HSD_JObj *joint)
{
    joint ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(joint->flags & 0x00800000) && (joint->flags & 0x40);
}

void zdDownBodyIK(ZoidState *zoid, HSD_JObj **joint_ref, f32 offset, s32 *count, f32 *offsets)
{
    f32 point[3];
    u16 selector;
    f32 delta[3];
    HSD_JObj *joint;
    f32 *normal;
    f32 ground;
    f32 height;
    f32 value;
    s32 i;

    joint = *joint_ref;
    if (joint != 0 && zoid != (void *)0 && zoid->joint != (void *)0) {
        for (i = 0; i < 3; i++) {
            point[i] = joint->matrix[i][3];
        }
        ground = zdColPosY(point, &selector);
        height = ground - (point[1] + offset);
        if (height < -0.1) {
            height = -0.1f;
        }
        if (height > 0.1) {
            height = 0.1f;
        }
        joint->matrix[1][3] += height;
        sGlobal2Local(joint);
        if (joint != 0 && !matrix_is_dirty(joint)) {
            HSD_JObjSetMtxDirtySub(joint);
        }
        normal = grdcGetNormal(selector);
        if (normal != 0) {
            if (normal[1] < 0.5) {
                for (i = 0; i < 3; i++) {
                    value = 0.015 * normal[i];
                    delta[i] = value;
                }
                *count = *count + 1;
                for (i = 0; i < 3; i++) {
                    offsets[i] += delta[i];
                }
            }
        }
    }
}
