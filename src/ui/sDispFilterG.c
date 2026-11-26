#include "model_archive.h"

extern ModelArchive *dspFilter;
extern s32 gameEndF;
extern s32 jobjAnim(HSD_JObj *joint);
extern void jobjDispAll(HSD_JObj *joint);

void sDispFilterG(void)
{
    if (dspFilter == (void *)0)
        return;
    if (dspFilter->models[0] == (void *)0)
        return;
    switch (gameEndF) {
    case 0:
    case 1:
        return;
    case 2:
        SetAnimArc2(dspFilter, 0, 0);
        gameEndF = 3;
        break;
    case 3:
        if (jobjAnim(dspFilter->models[0]) != 0) {
            gameEndF = 4;
            SetAnimArc2(dspFilter, 0, 1);
            jobjAnim(dspFilter->models[0]);
        }
        break;
    case 4:
    case 5:
    case 6:
        jobjAnim(dspFilter->models[0]);
        break;
    }
    jobjDispAll(dspFilter->models[0]);
}
