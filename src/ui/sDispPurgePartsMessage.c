#include "types.h"
#include "model_archive.h"

extern void *dspMessage;

void sDispPurgePartsMessage(void)
{
    if (dspMessage != 0) {
        PurgeArc2(dspMessage);
        dspMessage = 0;
    }
}
