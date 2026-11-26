#include "missile.h"
#include "lobj.h"

#define NULL ((void *)0)

void sEffectLight(void)
{
    s32 i;
    Effect *effect;

    for (i = 0; i < 100; i++) {
        effect = (Effect *)((u8 *)sEffect + i * 0x428);
        if (effect->root != NULL) {
            if (*(HSD_LObj **)((u8 *)effect + 0x424) != 0)
                HSD_LObjAddCurrent(*(HSD_LObj **)((u8 *)effect + 0x424));
        }
    }
}
