#include "types.h"

extern u8 sCamera[];
extern void sCameraSetShadow(void *camera);

void sCameraSetShadowAll(void)
{
    s32 i;
    for (i = 0; i < 4; i++)
        sCameraSetShadow(&sCamera[i * 0x590]);
}
