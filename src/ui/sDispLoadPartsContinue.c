#include "types.h"
#include "model_archive.h"

extern void *dspContinue;

void sDispLoadPartsContinue(void)
{
    if (dspContinue == 0) {
        dspContinue = LoadArc2("disp/div/continue.dat");
        if (dspContinue != 0)
            SetAnimArc2(dspContinue, 0, 0);
    }
}
