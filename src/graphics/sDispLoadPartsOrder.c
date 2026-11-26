#include "model_archive.h"

extern ModelArchive *dspOrder;
extern s32 dspOrderAI;

void sDispLoadPartsOrder(void)
{
    dspOrderAI = 0;
    if (dspOrder == 0)
        dspOrder = LoadArc2("disp/order.dat");
}
