#include "types.h"

extern u8 sCamera[];
extern void sCameraReset(void *camera);

void sCameraPurge(void)
{
    s32 i;
    for (i = 0; i < 4; i++) {
        void *camera = &sCamera[i * 0x590];
        sCameraReset(camera);
    }
}
