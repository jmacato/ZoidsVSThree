#include "types.h"
#include "model_archive.h"

extern void *dspPause;

void sDispPurgePartsPause(void)
{
    if (dspPause != 0) {
        PurgeArc2(dspPause);
        dspPause = 0;
    }
}
