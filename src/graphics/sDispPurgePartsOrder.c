#include "model_archive.h"

extern ModelArchive *dspOrder;
extern void PurgeArc2(ModelArchive *archive);

void sDispPurgePartsOrder(void)
{
    if (dspOrder != 0) {
        PurgeArc2(dspOrder);
        dspOrder = 0;
    }
}
