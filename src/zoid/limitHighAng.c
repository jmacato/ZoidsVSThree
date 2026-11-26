#include "zoid3.h"

extern f32 limitHighH(void);
extern f32 limitHighL(void);
extern f32 limitHighB(f32 value);

void limitHighAng(ZoidState *zoid)
{
    f32 bound;
    f32 angle;
    f32 base;
    f32 high;
    f32 low;
    f32 high_rel;
    f32 low_rel;

    base = zoid->position[1];
    angle = zoid->high_angle;
    high = limitHighH();
    low = limitHighL();
    high_rel = high - base;
    low_rel = low - base;
    if (angle < 0.0f) {
        if (high_rel < 0.0f) {
            bound = 0.0f;
        } else {
            bound = -limitHighB(high_rel);
        }
        if (angle < bound) {
            angle = bound;
        }
    }
    if (angle > 0.0f) {
        if (low_rel > 0.0f) {
            bound = 0.0f;
        } else {
            bound = limitHighB(low_rel);
        }
        if (angle > bound) {
            angle = bound;
        }
    }
    zoid->high_angle = angle;
}
