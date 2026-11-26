#include "types.h"
#include "model_archive.h"

extern void *dspPause;

void sDispLoadPartsPause(void)
{
    if (dspPause == 0) {
        dspPause = LoadArc2("disp/div/pause.dat");
    }
}
