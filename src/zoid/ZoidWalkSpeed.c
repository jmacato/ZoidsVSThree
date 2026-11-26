#include "zoid3.h"

#define DEG(x) (2.0 * (3.1415926 * (x)) / 360.0)

typedef struct ZoidAnim3 {
    u8 pad_00[0xA8];
    s32 anim7_rate;
    u8 pad_AC[4];
    s32 anim4_rate;
    s32 anim5_min_speed;
    s32 anim5_rate;
    u8 pad_BC[4];
    s32 anim6_rate;
    s32 max_steer;
    u8 pad_C8[0x2C];
    s32 f0F4;
    s32 f0F8;
} ZoidAnim3;

extern u32 vsyncN;
extern f64 sin(f64 x);
extern void angLimit(f32 *angle);
extern void ZoidSetAnim(ZoidState *zoid, s32 anim);
extern void zdAnimRate(ZoidState *zoid, f32 rate);

static inline f32 fabsf(f32 *v)
{
    return (*(u32 *)v &= 0x7FFFFFFF, *v);
}

void ZoidWalkSpeed(ZoidState *zoid)
{
    s32 anim;
    s32 cur;
    s32 half;
    s32 broken;
    s32 rate_anim;
    s32 slow;
    s32 sub;
    f32 max;
    f32 limit;
    f32 rate;
    ZoidAnim3 *control;
    f32 speed;
    f32 steer;
    f32 diff;

    if (zoid == (void *)0)
        return;
    if (zoid->joint == (void *)0)
        return;
    anim = zoid->current_animation;
    half = 0;
    control = zoid->anim_data;
    cur = zoid->current_animation;
    speed = zoid->field_1C90[0];
    steer = zoid->steer;
    if ((anim == 2 || anim == 4 || anim == 5) && control->f0F8 == 0 && zoid->field_0170 == 0)
        half = 1;
    if (control->f0F4 == 0)
        half = 0;
    if (zoid->feet[2].joint == 0 && zoid->feet[3].joint == 0)
        half = 0;
    if (half != 0 && zoid->feet[2].joint != 0 && zoid->feet[2].no_contact_frames < 90)
        half = 0;
    if (half != 0 && zoid->feet[3].joint != 0 && zoid->feet[3].no_contact_frames < 90)
        half = 0;
    if (half != 0 && zoid->feet[0].joint != 0 && zoid->feet[0].no_contact_frames < 90)
        half = 0;
    if (half != 0 && zoid->feet[1].joint != 0 && zoid->feet[1].no_contact_frames < 90)
        half = 0;
    if (half != 0) {
        zoid->field_1C90[1] *= 0.5f;
        zoid->field_1C90[0] *= 0.5f;
        zoid->field_1C90[2] *= 0.5f;
    }
    broken = 0;
    if (zoid->damages[4].maximum_health != 0 && zoid->damages[4].health == 0)
        broken |= 1;
    if (zoid->damages[5].maximum_health != 0 && zoid->damages[5].health == 0)
        broken |= 2;
    if (zoid->damages[2].maximum_health != 0 && zoid->damages[2].health == 0)
        broken |= 4;
    if (zoid->damages[3].maximum_health != 0 && zoid->damages[3].health == 0)
        broken |= 8;
    if (zoid->damages[0].maximum_health != 0 && zoid->damages[0].health == 0)
        broken |= 16;
    if ((broken & 3) && (anim == 4 || anim == 5) && anim != 4) {
        slow = 0;
        if (broken & 1)
            slow += 5;
        if (broken & 2)
            slow += 5;
    }
    if ((broken & 0x10) && (anim == 4 || anim == 5)) {
        angLimit(&steer);
        if (speed >= 0.5) {
            steer = steer / 2.0;
            steer = DEG(10) * ((1.0 + sin(3.141592 * (vsyncN * 2) / 120.0)) / 2.0) + steer;
            if (steer > DEG(175))
                steer = DEG(175);
            if (steer < -DEG(175))
                steer = -DEG(175);
        }
    }
    if (0.0f < speed && speed < 0.1)
        speed = 0.0f;
    if (speed < -0.3)
        speed = -0.3f;
    if (-0.05 < speed && speed < 0.0f)
        speed = 0.0f;
    if (speed < 0.5) {
        diff = steer;
        if (fabsf(&diff) < 0.02)
            steer = 0.0f;
    }
    sub = 0;
    if (broken & 0xC)
        sub = 10;
    limit = DEG((f32)(control->max_steer + zoid->turn_bonus - sub));
    if (limit < 0.0f)
        limit = 0.0f;
    zoid->field_1C84 = limit;
    if (steer > limit)
        steer = limit;
    if (steer < -limit)
        steer = -limit;
    if (0.0f == speed)
        steer = 0.0f;
    if (0.0f != steer && 0.0f == speed) {
        speed = 0.1f;
        if (zoid->field_1C90[1] < 0.1)
            zoid->field_1C90[1] = 0.1f;
    }
    zoid->field_1C90[0] = speed;
    speed = zoid->field_1C90[1];
    if (0.0f < speed && speed < 0.1)
        speed = 0.0f;
    if (-0.05 < speed && speed < 0.0f)
        speed = 0.0f;
    max = (zoid->field_1F04 - slow) / 100.0;
    if (speed > max && zoid->booster_on == 0 && zoid->field_016C == 0)
        speed = max;
    if (speed > zoid->field_1F04 / 100.0)
        anim = 6;
    else if (speed > control->anim5_min_speed / 100.0)
        anim = 5;
    else if (speed >= 0.1)
        anim = 4;
    else if (0.0f == speed)
        anim = 1;
    else if (speed < 0.0f)
        anim = 7;
    if (zoid->booster_on == 0 && anim == 6)
        anim = 5;
    if (anim == 6 || anim == 5 || anim == 4) {
        if (anim != cur) {
            if (cur == 6 || cur == 5 || cur == 4) {
                if (zoid->field_1DF8 < 15) {
                    zoid->field_1DF8++;
                    anim = cur;
                } else {
                    zoid->field_1DF8 = 120;
                }
            } else {
                zoid->field_1DF8 = 0;
            }
        } else {
            zoid->field_1DF8 = 0;
        }
    } else {
        zoid->field_1DF8 = 0;
    }
    if (anim != 1)
        zoid->anim1_frames = 0;
    if (anim == 1 && zoid->anim1_frames > 600 && zoid->animation_looped != 0) {
        zoid->anim1_frames = 0;
        anim = 2;
    }
    if (zoid->current_animation == 2 && anim == 1)
        anim = 2;
    if (zoid->field_016C != 0) {
        switch (anim) {
        case 2:
            anim = 1;
            break;
        case 3:
            break;
        case 4:
        case 5:
        case 6:
            anim = 6;
            break;
        }
    }
    zoid->anim1_frames++;
    rate_anim = anim;
    if (zoid->field_016C == 0 && anim == 6)
        anim = 5;
    if (zoid->current_animation == 2 && zoid->animation_stopped != 0)
        anim = 1;
    if (anim != zoid->current_animation)
        ZoidSetAnim(zoid, anim);
    rate = 1.0f;
    if (anim == 7)
        rate = (f32)-control->anim7_rate * speed;
    if (anim == 4)
        rate = (f32)control->anim4_rate * speed;
    if (rate_anim == 5)
        rate = 0.1 * control->anim5_rate * speed;
    if (rate_anim == 6)
        rate = 0.1 * control->anim6_rate * speed;
    zdAnimRate(zoid, rate);
    zoid->steer = steer;
    if (zoid->field_1C90[2] > 0.0f)
        zoid->heading += 0.1 * zoid->steer;
    if (zoid->field_1C90[2] < 0.0f)
        zoid->heading -= 0.1 * zoid->steer;
}
