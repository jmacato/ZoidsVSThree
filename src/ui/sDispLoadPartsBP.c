#include "types.h"
#include "model_archive.h"

extern void *dspBP;

void sDispLoadPartsBP(void)
{
    if (dspBP == 0) {
        dspBP = LoadArc2("disp/div/bp.dat");
    }
}
