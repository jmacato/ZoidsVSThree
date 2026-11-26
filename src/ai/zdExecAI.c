#pragma readonly_strings on
#include "zoid3.h"

typedef struct AI3 {
    u8 pad_00[0x40];
    s32 mode;
    s32 flags;
    s32 target_index;
    f32 destination[3];
    f32 field_58[3];
    f32 target_distance;
    f32 field_68;
    f32 target_angle;
    s32 turn_speed;
    u8 pad_74[4];
    f32 goal[3];
    u8 pad_84[0x1C];
    f32 field_A0;
    f32 field_A4;
    u8 pad_A8[8];
    f32 field_B0;
    s32 counter;
} AI3;

extern f64 __frsqrte(f64);
extern f32 atan2f(f32 y, f32 x);
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern void angLimit(f32 *angle);
extern f32 sLenPoint3dR(f32 *point);
extern f32 sLenPoint3dR2(f32 *point);
extern s32 sprintf(char *buf, const char *fmt, ...);
extern void aiReport(s32 level, const char *msg);
extern void calcHigh(ZoidState *zoid, AI3 *ai);
extern void moveHigh(ZoidState *zoid, AI3 *ai);
extern void zdChgNormal(ZoidState *zoid);

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

static inline f32 absf(f32 *value)
{
    *(u32 *)value &= 0x7FFFFFFF;
    return *value;
}

static inline f32 wsinf(f32 x)
{
    return sinf(x);
}

static inline f32 wcosf(f32 x)
{
    return cosf(x);
}

static inline f32 angleY(f32 x, f32 z)
{
    return atan2f(x, z);
}

void zdExecAI(ZoidState *zoid)
{
    f32 base;
    f32 d[3];
    f32 angle;
    f32 turn;
    s32 pad0;
    char buf[512];
    f32 abs0;
    f32 pad1;
    f32 pad2;
    volatile f32 root;
    f32 abs1;
    f32 abs2;
    AI3 *ai;
    ZoidState *target;
    f32 *dest;
    s32 index;
    f32 dist;
    f32 len;
    f32 sum;
    f32 t;
    s32 i;
    f32 measured_distance;
    f32 desired_distance;

    if (zoid == (void *)0)
        return;
    if (zoid->joint == (void *)0)
        return;
    ai = (AI3 *)zoid->ai;
    if (ai == (void *)0)
        return;
    ai->counter++;
    if (zoid->field_1360 != 0) {
        if (zoid->requested_action == 2)
            zoid->requested_action = 0;
        zoid->field_1C54 = 0.0f;
        return;
    }
    calcHigh(zoid, ai);
    moveHigh(zoid, ai);
    sprintf(buf, "aiExec:%0d-%04X z=%d m=%d-%04X v=%f rate=%f %s", ai->mode, ai->flags, ai->target_index, zoid->action, zoid->action_phase, zoid->field_1C90[1], zoid->anim_rate, zoid->animation_looped != 0 ? "L" : "n");
    aiReport(0, buf);
    index = ai->target_index;
    if (index != -1) {
        (void)0;
    }
    if (index == -1)
        target = 0;
    else
        target = &Zoid[index];
    if (target != (void *)0 && target->joint == (void *)0)
        target = 0;
    desired_distance = ai->target_distance;
    dist = desired_distance;
    switch (ai->mode) {
    case 0:
        return;
    case 1:
        dest = ai->destination;
        base = 0.0f;
        break;
    case 2:
        if (target == (void *)0)
            return;
        base = target->heading;
        dest = target->position;
        break;
    case 3:
        zoid->step_heading = zoid->heading + 2.0 * (3.1415926 * (f32)ai->turn_speed) / 360.0;
        zoid->field_1C54 = 1.0f;
        angLimit(&zoid->step_heading);
        return;
    case 16:
        zoid->step_heading = ai->field_68;
        zoid->field_1C54 = 1.0f;
        zoid->stick_angle = 0.0f;
        return;
    case 4:
        zoid->step_heading = zoid->heading + 2.0 * (3.1415926 * (f32)ai->turn_speed) / 360.0;
        angLimit(&zoid->step_heading);
        ai->field_68 = zoid->step_heading;
        zoid->field_1C54 = 1.0f;
        ai->mode = 16;
        zoid->stick_angle = 0.0f;
        return;
    case 5:
    case 6:
        angLimit(&ai->target_angle);
        base = ai->target_angle - zoid->heading;
        angLimit(&base);
        if (0.0f == base) {
            zdChgNormal(zoid);
            zoid->step_heading = zoid->heading;
            if (ai->mode == 5) {
                ai->mode = 999;
                return;
            }
        }
        abs0 = base;
        if (absf(&abs0) < 2.0 * (3.1415926 * 3) / 360.0 && ai->mode == 6) {
            zoid->heading = ai->target_angle;
            zoid->step_heading = zoid->heading;
            zoid->field_1C54 = 1.0f;
            ai->mode = 999;
            return;
        }
        if (zoid->field_1C90[2] > 0.01) {
            zoid->field_1C54 = 0.0f;
            return;
        }
        zoid->field_1C58 = ai->target_angle;
        if (base > 0.0f) {
            if (zoid->action == 6)
                ai->target_angle = zoid->heading;
            zoid->requested_action = 7;
        } else {
            if (zoid->action == 7)
                ai->target_angle = zoid->heading;
            zoid->requested_action = 6;
        }
        if (ai->target_angle == zoid->heading)
            zdChgNormal(zoid);
        return;
    case 999:
    default:
        return;
    }
    if (ai->flags == 0) {
        zoid->field_1C54 = 0.0f;
        return;
    }
    if (ai->flags & 0x100) {
        if (dist < 1.0f)
            dist = 1.0f;
        sum = 0.0f;
        for (i = 0; i < 3; i++) {
            t = dest[i] - ai->field_58[i];
            d[i] = t;
            sum += t * t;
        }
        sum = sqrtf(sum, &root);
        if (0.0f == sum) {
            for (i = 0; i < 3; i++)
                ai->goal[i] = ai->field_58[i];
        } else {
            for (i = 0; i < 3; i++)
                ai->goal[i] = ai->field_58[i] - dist * d[i] / sum;
        }
    } else {
        for (i = 0; i < 3; i++)
            d[i] = zoid->position[i] - dest[i];
        angle = angleY(d[0], d[2]);
        turn = angle;
        len = sLenPoint3dR(d);
        ai->field_A0 = len;
        ai->field_A4 = sLenPoint3dR2(d);
        pad0 = 0;
        measured_distance = ai->field_A4;
        len = measured_distance;
        switch (ai->flags & 0xF) {
        case 1:
            len = dist;
            break;
        case 2:
            if (len >= dist)
                len = dist - 0.2;
            break;
        case 3:
            if (len <= dist)
                len = 0.2 + dist;
            break;
        }
        switch (ai->flags & 0xF0) {
        case 0x10:
            turn = base + ai->target_angle - angle;
            angLimit(&turn);
            if (turn > 2.0 * (3.1415926 * 30) / 360.0)
                turn = 2.0 * (3.1415926 * 30) / 360.0;
            if (turn < -(2.0 * (3.1415926 * 30) / 360.0))
                turn = -(2.0 * (3.1415926 * 30) / 360.0);
            angle = turn + angle;
            break;
        case 0x20:
            angle += 2.0 * (3.1415926 * (f32)ai->turn_speed) / 360.0;
            break;
        }
        angLimit(&angle);
        if (len < 0.0f)
            len = 0.0f;
        ai->goal[0] = len * wsinf(angle) + dest[0];
        ai->goal[2] = len * wcosf(angle) + dest[2];
        ai->goal[1] = dest[1];
    }
    for (i = 0; i < 3; i++)
        d[i] = ai->goal[i] - zoid->position[i];
    angle = angleY(d[0], d[2]);
    base = angle - zoid->heading;
    angLimit(&base);
    aiReport(0, "calc");
    abs1 = base;
    if (absf(&abs1) > 2.0 * (3.1415926 * 80) / 360.0) {
        if (zoid->ai != 0 && ((AI3 *)zoid->ai)->mode != 0) {
            zoid->field_1C54 = 1.0f;
        } else {
            if (base > 0.0f)
                zoid->requested_action = 7;
            else
                zoid->requested_action = 6;
            zoid->field_1C58 = angle;
            zoid->field_1C54 = 0.0f;
            aiReport(0, "turn-A");
            return;
        }
    }
    if (zoid->action >= 3 && zoid->action <= 11) {
        aiReport(0, "turn-E");
        return;
    }
    aiReport(0, "ang");
    zoid->step_heading = angle;
    zoid->field_1C54 = 0.2f;
    dist = sLenPoint3dR2(d);
    if (dist > 3.0f)
        zoid->field_1C54 = 1.0f;
    if (dist <= 0.1)
        zoid->field_1C54 = 0.0f;
    if (ai != 0 && ai->mode != 0) {
        zoid->field_1C54 = 1.0f;
        zoid->field_1C54 = ai->field_B0;
        aiReport(0, "set");
        return;
    }
    if (dist <= 3.0f && (abs2 = base, absf(&abs2)) > 2.0 * (3.1415926 * 20) / 360.0) {
        if (base > 0.0f)
            zoid->requested_action = 7;
        else
            zoid->requested_action = 6;
        zoid->field_1C54 = 0.0f;
        zoid->field_1C58 = angle;
        aiReport(0, "turn-LA");
        return;
    }
    aiReport(0, "end");
}
