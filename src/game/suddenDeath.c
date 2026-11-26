#include "zoid3.h"

extern s32 gameTime;
extern f32 calcPer(ZoidState *zoid);

s32 suddenDeath(ZoidState *a, ZoidState *b)
{
    f32 per_a;
    f32 per_b;

    if (gameTime != 0) {
        return 0;
    }
    per_a = calcPer(a);
    per_b = calcPer(b);
    if (per_a == per_b) {
        return 2;
    }
    if (per_a > per_b) {
        return 1;
    }
    return 3;
}
