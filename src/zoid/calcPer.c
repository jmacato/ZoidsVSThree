#include "zoid3.h"

f32 calcPer(ZoidState *zoid)
{
    f32 max_health = zoid->max_health;
    f32 health = zoid->health;

    if (health == 0.0f) {
        return 0.0f;
    }
    if (max_health == 0.0f) {
        return 100.0f;
    }
    return (100.0f * health) / max_health;
}
