#include "zoid3.h"
#include "ground_collision.h"

extern s32 zdGroundCoPoly(ZoidState *zoid, u8 *object, s32 a, s32 b, s32 mode, s32 c, s32 d, f32 scale);
extern void zdGrBallMovePoly(ZoidState *zoid, s32 a, s32 c, s32 d, s32 e);
extern void angLimit(f32 *angle);
extern s32 sCamNN;

s32 zdGroundPoly(ZoidState *zoid, s32 a, s32 b, s32 c, s32 d, s32 e)
{
    s32 *data = zoid->anim_data;
    s32 limit;
    s32 part;
    f32 scale;
    s32 dead;
    f32 angle;
    const f64 turn_limit = 2.0 * 3.1415926 * 0.5 / 360.0;

    limit = 3;
    scale = 0.0f;
    if (data != 0)
        scale = *(s32 *)((u8 *)data + 0xCC);
    if (zoid->field_1C14 != 0)
        limit = 1;
    if (zdGroundCoPoly(zoid, zoid->body_coobj, a, b, 0, c, d, 1.0f) == 0)
        return 0;
    zdGroundCoPoly(zoid, zoid->bust_coobj, a, b, data[2], c, d, 3.0f);
    zdGroundCoPoly(zoid, zoid->neck_coobj, a, b, data[1], c, d, 2.0f);
    if (sCamNN != 4) {
        zdGroundCoPoly(zoid, zoid->head_coobj, a, b, data[0], c, d, 0.7f);
        for (part = 0; part < 8; part++)
            zdGroundCoPoly(zoid, zoid->tail_coobjs[part], a, b, (data + 4)[part], c, d, 0.7f);
    }
    dead = 0;
    zdGroundCoPoly(zoid, zoid->hip_coobj, a, b, data[3], c, d, 2.0f);
    zdGroundCoPoly(zoid, zoid->l_arm1_coobj, a, b, limit < data[14] ? limit : data[14], c, d, 1.0f);
    zdGroundCoPoly(zoid, zoid->r_arm1_coobj, a, b, limit < data[16] ? limit : data[16], c, d, 1.0f);
    zdGroundCoPoly(zoid, zoid->l_leg1_coobj, a, b, limit < data[18] ? limit : data[18], c, d, 1.0f);
    zdGroundCoPoly(zoid, zoid->r_leg1_coobj, a, b, limit < data[20] ? limit : data[20], c, d, 1.0f);
    zdGroundCoPoly(zoid, zoid->l_arm2_coobj, a, b, limit < data[15] ? limit : data[15], c, d, 0.7f);
    zdGroundCoPoly(zoid, zoid->r_arm2_coobj, a, b, limit < data[17] ? limit : data[17], c, d, 0.7f);
    zdGroundCoPoly(zoid, zoid->l_leg2_coobj, a, b, limit < data[19] ? limit : data[19], c, d, 0.7f);
    zdGroundCoPoly(zoid, zoid->r_leg2_coobj, a, b, limit < data[21] ? limit : data[21], c, d, 0.7f);
    zdGrBallMovePoly(zoid, a, c, d, e);
    angle = zoid->field_1C8C;
    angLimit(&angle);
    if (angle < -turn_limit)
        angle = -turn_limit;
    if (angle > turn_limit)
        angle = turn_limit;
    zoid->field_1C8C = angle;
    return 1;
}
