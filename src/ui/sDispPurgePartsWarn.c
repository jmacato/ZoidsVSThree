#include "types.h"
#include "model_archive.h"

extern void *dspWarn;

void sDispPurgePartsWarn(void)
{
    if (dspWarn != 0) {
        PurgeArc2(dspWarn);
        dspWarn = 0;
    }
}
