#include "types.h"
#include "model_archive.h"

extern void *dspContinue;

void sDispPurgePartsContinue(void)
{
    if (dspContinue != 0) {
        PurgeArc2(dspContinue);
        dspContinue = 0;
    }
}
