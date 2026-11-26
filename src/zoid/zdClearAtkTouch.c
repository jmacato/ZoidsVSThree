#include "zoid3.h"

void zdClearAtkTouch(ZoidState *zoid)
{
    s32 i, j;
    for (i = 0; i < 10; i++) {
        ZoidAttackObject *attack = &zoid->attack_objects[i];
        if (attack != (void *)0 && attack->joint != 0) {
            for (j = 0; j < 16; j++)
                attack->touched[j] = 0;
        }
    }
}
