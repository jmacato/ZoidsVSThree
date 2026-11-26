#include "types.h"
#include "zoid3.h"
#include "joint_matrix.h"
#include "ground_collision.h"

typedef struct WeaponState3 {
    u8 reserved_00[0x34];
    HSD_JObj *target_joint;
    u8 reserved_38[0x3E8 - 0x38];
    s32 animation;
    u8 reserved_3EC[0x6DC - 0x3EC];
} WeaponState3;

extern f32 sColRealPt(Vec3 *a, Vec3 *b, GroundMask *mask);
extern void sGlobal2Local(HSD_JObj *joint);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);

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

void sWeaponTargetColli(WeaponState3 *weapon)
{
    HSD_JObj *child;
    s32 i;
    f32 a[3];
    f32 b[3];
    GroundMask mask = {{0x17, 0, 0, 0}};
    GroundMask mask_copy;
    f32 hit;

    if (weapon == (void *)0)
        return;
    if (weapon->animation >= 4)
        return;
    {
        HSD_JObj *joint = weapon->target_joint;
        if (joint == 0)
            return;
        child = joint->parent;
        if (child == 0)
            return;
        for (i = 0; i < 3; i++) {
            a[i] = child->matrix[i][3];
            b[i] = a[i] + 300.0f * child->matrix[i][0];
        }
        mask_copy = mask;
        hit = sColRealPt((Vec3 *)a, (Vec3 *)b, &mask_copy);
        for (i = 0; i < 3; i++) {
            joint->matrix[i][3] = b[i];
            if (hit != 10000.0f)
                joint->matrix[i][3] = a[i] + 300.0f * child->matrix[i][0] * hit;
        }
        joint ? (void)0 : __assert("jobj.h", 833, "jobj");
        joint->scale.z = 1.0f;
        if (!(joint->flags & 0x02000000))
            HSD_JObjSetMtxDirty(joint);
        sGlobal2Local(joint);
        HSD_JObjSetMtxDirty(joint);
    }
}
