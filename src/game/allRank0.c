#include "types.h"
#include "model_archive.h"

extern ModelArchive *dspBP;
extern s32 jobjAnim(HSD_JObj *joint);
extern void SetAnimArc2(ModelArchive *archive, s32 model, s32 selected);
extern void allRank1(s32 rank);

void allRank0(s32 rank)
{
    if (dspBP != 0) {
        if (jobjAnim(dspBP->models[0]) != 0) {
            SetAnimArc2(dspBP, 0, 1);
            jobjAnim(dspBP->models[0]);
        }
        allRank1(rank);
    }
}
