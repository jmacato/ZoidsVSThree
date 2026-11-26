#include "types.h"
#include "model_archive.h"

extern void *dspBP;

void sDispPurgePartsBP(void)
{
    if (dspBP != 0) {
        PurgeArc2(dspBP);
        dspBP = 0;
    }
}
