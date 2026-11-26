#include "model_archive.h"

extern ModelArchive *dspPos00, *dspDemoPress;
extern void PurgeArc2(ModelArchive *archive);
extern void sDispPurgePartsGame(void);
extern void sDispPurgePartsBP(void);
extern void sDispPurgePartsContinue(void);
extern void sDispPurgePartsPause(void);
extern void sDispPurgePartsMessage(void);

void sDispPurgeParts(void)
{
    sDispPurgePartsGame();
    if (dspPos00 != 0)
        PurgeArc2(dspPos00);
    dspPos00 = 0;
    if (dspDemoPress != 0)
        PurgeArc2(dspDemoPress);
    dspDemoPress = 0;
    sDispPurgePartsBP();
    sDispPurgePartsContinue();
    sDispPurgePartsPause();
    sDispPurgePartsMessage();
    sDispPurgePartsPause();
}
