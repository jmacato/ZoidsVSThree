#include "types.h"

extern s32 vcSeekMode;

s32 camVoiceSeekCB(void *arg)
{
    s32 a;
    s32 x;
    s32 b;
    if (vcSeekMode == 1)
        vcSeekMode = 2;
    x = (s32)arg;
    return 0;
}
