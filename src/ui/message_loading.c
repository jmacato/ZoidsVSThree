#pragma readonly_strings on
#include "model_archive.h"

extern ModelArchive *dspMessage;

void sDispLoadPartsMessage(void)
{
    if (dspMessage == 0)
        dspMessage = LoadArc2("disp/div/message.dat");
}
