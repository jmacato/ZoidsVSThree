#include "zoid3.h"
#include "angle.h"

#define NULL 0

extern u32 vsyncN;
extern f64 __frsqrte(f64);
extern f32 atan2f(f32 y, f32 x);
extern void angLimit(f32 *angle);

static inline f32 sqrtf(f32 x, volatile f32 *y)
{
    static const f64 _half = 0.5;
    static const f64 _three = 3.0;

    if (x > 0.0f) {
        f64 guess = __frsqrte((f64)x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        *y = (f32)(x * guess);
        return *y;
    }
    return x;
}

#define GETPOS(z, v) \
    joint = NULL; \
    if (joint == NULL && (z)->body_base_joint != NULL) \
        joint = (z)->body_base_joint; \
    for (i = 0; i < 3; i++) { \
        if (joint != NULL) \
            (v)[i] = joint->matrix[i][3]; \
        else \
            (v)[i] = (z)->position[i]; \
    }

void zdFace(ZoidState *zoid)
{
    f32 yaw;
    f32 pitch;
    f32 pos[3];
    f32 tpos[3];
    volatile f32 root;
    f32 angle;
    f32 dy;
    f32 dx;
    f32 dz;
    f32 dist;
    ZoidState *target;
    f32 limit;
    f32 yaw_step = DEG2RAD_F(7.0f);
    f32 pitch_limit = DEG2RAD_F(60.0f);
    f32 pitch_step = DEG2RAD_F(0.2f);
    s32 dying = 0;
    u8 *data;
    HSD_JObj *joint;
    s32 i;

    if (zoid == (void *)0)
        return;
    if (zoid->joint == (void *)0)
        return;
    if ((vsyncN & 1) == (zoid->index & 1))
        return;
    data = zoid->anim_data;
    limit = 2.0 * (3.1415926 * (f32)*(s32 *)(data + 0xcc)) / 360.0;
    switch (zoid->action) {
    case 12:
        dying = 1;
    }
    if (zoid->face_lock != 0 || dying != 0)
        limit = 0.0f;
    if (zoid->target_pending != 0) {
        target = &Zoid[zoid->target_slot];
        if (target->joint == (void *)0) {
            yaw = 0.0f;
            pitch = 0.0f;
        } else {
            GETPOS(zoid, pos)
            GETPOS(target, tpos)
            dz = tpos[2] - pos[2];
            dx = tpos[0] - pos[0];
            dy = tpos[1] - pos[1];
            dist = sqrtf(dx * dx + dz * dz, &root);
            angle = atan2f(dx, dz);
            yaw = angle - zoid->heading;
            angLimit(&yaw);
            pitch = atan2f(-dy, dist);
            angLimit(&pitch);
        }
    } else {
        yaw = 0.0f;
        pitch = 0.0f;
    }
    if (yaw < 0.0f && yaw < -limit)
        yaw = -limit;
    if (yaw > 0.0f && yaw > limit)
        yaw = limit;
    if (pitch < 0.0f && pitch < -pitch_limit)
        pitch = -pitch_limit;
    if (pitch > 0.0f && pitch > pitch_limit)
        pitch = pitch_limit;
    angLimit(&zoid->face_yaw);
    angLimit(&zoid->face_pitch);
    if (zoid->face_yaw > yaw) {
        zoid->face_yaw -= yaw_step;
        if (zoid->face_yaw < yaw)
            zoid->face_yaw = yaw;
    }
    if (zoid->face_yaw < yaw) {
        zoid->face_yaw += yaw_step;
        if (zoid->face_yaw > yaw)
            zoid->face_yaw = yaw;
    }
    if (zoid->face_pitch > pitch) {
        zoid->face_pitch -= pitch_step;
        if (zoid->face_pitch < pitch)
            zoid->face_pitch = pitch;
    }
    if (zoid->face_pitch < pitch) {
        zoid->face_pitch += pitch_step;
        if (zoid->face_pitch > pitch)
            zoid->face_pitch = pitch;
    }
}
