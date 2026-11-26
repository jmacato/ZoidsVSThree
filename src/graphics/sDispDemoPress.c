#include "model_archive.h"
#include "game_mode.h"

extern ModelArchive *dspDemoPress;
extern s32 vsyncN;
extern void jobjDispAll(HSD_JObj *joint);

void sDispDemoPress(void *enable)
{
    if (enable == 0)
        return;
    if (dspDemoPress == 0)
        return;
    if (GameMode.game_type != 9)
        return;
    if ((vsyncN & 0x10) == 0)
        return;
    jobjDispAll(dspDemoPress->models[0]);
}
