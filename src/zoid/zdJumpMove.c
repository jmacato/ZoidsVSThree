#include "zoid3.h"
#include "ground_collision.h"

extern f32 sinf(f32 angle);
extern f32 cosf(f32 angle);

void zdJumpMove(ZoidState *zoid)
{
    u16 selector;
    f32 saved[3];
    GroundMask mask;
    f32 t;
    f32 sine_angle;
    f32 cosine_angle;
    ZoidAIState *ai;
    s32 i;

    if (zoid->grounded != 0) {
        for (i = 0; i < 3; i++) {
            if (i != 1) {
                zoid->displacement[i] *= 0.7;
            }
        }
    }
    for (i = 0; i < 3; i++) {
        saved[i] = zoid->position[i];
    }
    zoid->velocity[1] -= 0.025;
    zoid->position[0] += zoid->velocity[0];
    zoid->position[1] += zoid->velocity[1];
    zoid->position[2] += zoid->velocity[2];
    ai = zoid->ai;
    if (ai != 0 && ai->mode == 0) {
        ai = 0;
    }
    if (ai == 0) {
        t = zoid->field_1C54 / 200.0f;
        if (t > 1.0f) {
            t = 1.0f;
        }
        sine_angle = zoid->step_heading;
        zoid->position[0] += t * sinf(sine_angle);
        cosine_angle = zoid->step_heading;
        zoid->position[2] += t * cosf(cosine_angle);
    }
    mask = (GroundMask){ { 0xff, 0x00, 0x00, 0x00 } };
    sColPosAndY((Vec3 *)zoid->position, &selector, &mask);
    if (selector == 0xffff) {
        zoid->velocity[0] *= -0.9;
        zoid->velocity[2] *= -0.9;
        zoid->position[2] = saved[2];
    }
}
