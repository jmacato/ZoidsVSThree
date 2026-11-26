#include "zoid3.h"
#include "zoid_ai.h"

typedef struct AiState3 {
    u8 reserved_00[0x98];
    s32 field_98;
    f32 field_9C;
} AiState3;

extern void sLinear1D(f32 *value, f32 delta, f32 rate);

inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

void moveHigh(ZoidState *zoid, AiState3 *ai)
{
    f32 diff;
    f32 speed;
    f32 height;
    f32 goal;

    if (zoid->field_0170 == 0) {
        return;
    }
    if (ai->field_98 <= 0) {
        return;
    }
    if (ai->field_98 > 2) {
        return;
    }
    height = zoid->position[1];
    goal = ai->field_9C;
    speed = 0.0f;
    diff = absf(goal - height);
    if (diff) {
        speed = 0.0f;
        if (diff > 1.0f) {
            speed = 1.0f;
        }
        if (diff > 5.0f) {
            speed = 3.0f;
        }
        if (diff > 10.0f) {
            speed = 7.0f;
        }
        if (diff > 20.0f) {
            speed = 15.0f;
        }
        if (diff > 40.0f) {
            speed = 30.0f;
        }
    }
    if (goal > height) {
        sLinear1D(&zoid->high_angle, -(2.0 * (3.1415926 * speed) / 360.0), 0.0261799376f);
        if (diff > 1.0f) {
            zoid->position[1] += 0.1;
        }
    }
    if (goal < height) {
        sLinear1D(&zoid->high_angle, 2.0 * (3.1415926 * speed) / 360.0, 0.0261799376f);
        if (diff > 1.0f) {
            zoid->position[1] = zoid->position[1] - 0.1;
        }
    }
}
