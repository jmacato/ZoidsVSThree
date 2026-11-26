#include "zoid3.h"
#include "ground_collision.h"

extern f32 zdColPosY(f32 *point, u16 *selector);
extern Vec3 *grdcGetNormal(u16 polygon);
extern f32 zdDownBody(ZoidState *zoid, u8 *coobj, s32 *count, f32 *accum);
extern void zdDownBodyIK(ZoidState *zoid, FootJoint *foot, f32 offset, s32 *count, f32 *accum);
extern void zdSetXYZ(ZoidState *zoid);
extern void sMakeMatrix(HSD_JObj *joint);
extern f32 beSide(f32 value, f32 target, f32 step);
extern f32 sLenPoint3dR(Vec3 *point);
extern GroundMask GXColorZoid;

void ZoidDownBody(ZoidState *zoid)
{
    f32 cur[3];
    f32 prev[3];
    f32 diff[3];
    f32 end[3];
    f32 start[3];
    f32 accum[3];
    void *anim;
    s32 count;
    u16 selector;
    GroundMask mask;
    u16 *info;
    Vec3 *normal;
    HSD_JObj *joint;
    s32 i;
    f32 y;
    f32 ground;
    f32 scale;
    f32 sum;
    f32 delta;
    f32 len;
    f32 step;
    f32 hit;

    if (zoid == (void *)0)
        return;
    if (zoid->joint == (void *)0)
        return;
    info = zoid->slider_info;
    anim = zoid->anim_data;
    if (info == 0)
        return;
    if (zoid->death_pending == 0)
        return;
    joint = 0;
    if (joint == 0)
        joint = *(HSD_JObj **)zoid->hip_coobj;
    if (joint == 0)
        joint = zoid->buckle_joint;
    if (joint == 0)
        joint = *(HSD_JObj **)&zoid->camera_joint;
    if (joint == 0)
        joint = zoid->joint->child;
    if (joint == 0)
        joint = zoid->joint;
    count = 0;
    for (i = 0; i < 3; i++)
        accum[i] = 0.0f;
    y = zoid->position[1];
    ground = zdColPosY(zoid->position, &selector);
    if (y > ground) {
        if (y - ground < 1.0f)
            zoid->launch_velocity[1] = 0.0f;
        if (zoid->launch_velocity[1] > 0.0f)
            zoid->launch_velocity[1] = 0.0f;
        zoid->launch_velocity[1] -= 0.025;
        zoid->position[1] += zoid->launch_velocity[1];
    }
    if ((normal = grdcGetNormal(selector)) == 0)
        normal = zoid->ground_normal;
    if (normal != 0) {
        scale = zoid->field_20C0;
        if (scale < 100.0f)
            scale = 100.0f;
        zoid->position[0] += 0.01 * normal->x * (100.0 / scale);
        zoid->position[2] += 0.01 * normal->z * (100.0 / scale);
    }
    ground = ground;
    y = y;
    sum = 0.0f;
    sum += zdDownBody(zoid, zoid->head_coobj, &count, accum);
    sum += zdDownBody(zoid, zoid->neck_coobj, &count, accum);
    sum += zdDownBody(zoid, zoid->hip_coobj, &count, accum);
    sum += zdDownBody(zoid, zoid->tail_coobjs[0], &count, accum);
    sum += zdDownBody(zoid, zoid->tail_coobjs[1], &count, accum);
    zdDownBodyIK(zoid, &zoid->feet[0], 0.0f, &count, accum);
    zdDownBodyIK(zoid, &zoid->feet[1], 0.0f, &count, accum);
    zdDownBodyIK(zoid, &zoid->feet[2], zoid->feet[2].offset, &count, accum);
    zdDownBodyIK(zoid, &zoid->feet[3], zoid->feet[3].offset, &count, accum);
    if (zoid->death_started == 0)
        zoid->position[1] += sum / 10.0f;
    if (count != 0) {
        for (i = 0; i < 3; i++)
            zoid->position[i] += accum[i] / (f32)count;
    }
    zdColPosY(zoid->position, &selector);
    if (selector == GROUND_POLYGON_NONE) {
        for (i = 0; i < 3; i++)
            zoid->position[i] = zoid->previous_position[i];
    }
    zdSetXYZ(zoid);
    sMakeMatrix(zoid->joint);
    for (i = 0; i < 3; i++)
        cur[i] = joint->matrix[i][3];
    ground = zdColPosY(cur, 0);
    y = ground - (cur[1] - 0.7);
    if (y > 0.0f) {
        zoid->height_offset += y;
        if (zoid->height_offset > 2.0f)
            zoid->height_offset = 2.0f;
    }
    if (((u8 *)info)[0x70B] & 4)
        zoid->height_offset = beSide(zoid->height_offset, 0.0f, 0.075f);
    zdSetXYZ(zoid);
    sMakeMatrix(zoid->joint);
    for (i = 0; i < 3; i++) {
        prev[i] = zoid->child_matrix[i][3];
        cur[i] = zoid->joint->child->matrix[i][3];
    }
    if (cur[0] == prev[0] && cur[2] == prev[2] && ground > prev[1] && ground < cur[1])
        return;
    delta = zoid->field_1A7C->matrix[1][3] - cur[1];
    cur[1] += delta;
    prev[1] += delta;
    for (i = 0; i < 3; i++)
        diff[i] = cur[i] - prev[i];
    len = sLenPoint3dR((Vec3 *)diff);
    step = len;
    if (0.0f == len)
        return;
    if (step < 0.7)
        step = 0.7f;
    for (i = 0; i < 3; i++) {
        start[i] = prev[i] - 2.0f * diff[i];
        end[i] = step * (diff[i] / len) + cur[i];
    }
    mask = GXColorZoid;
    hit = sColPt((Vec3 *)start, (Vec3 *)end, &mask);
    if (GROUND_NO_HIT == hit)
        return;
    for (i = 0; i < 3; i++)
        zoid->position[i] -= diff[i];
    zdSetXYZ(zoid);
    sMakeMatrix(zoid->joint);
}
