#include "types.h"
#include "model_archive.h"

extern void *dspWarn;

void sDispLoadPartsWarn(void)
{
    if (dspWarn == 0) {
        dspWarn = LoadArc2("disp/div/warning.dat");
        if (dspWarn != 0)
            SetAnimArc2(dspWarn, 6, 1);
    }
}
