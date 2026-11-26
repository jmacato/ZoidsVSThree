#include "model_archive.h"
#include "game_mode.h"

extern ModelArchive *dspMessage;
extern s32 gameEndF;
extern s32 jobjAnim(HSD_JObj *joint);
extern void jobjDispAll(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void SetAnimArc2(ModelArchive *archive, s32 model, s32 selected);

void sDispNext(void *enable)
{
    HSD_JObj *joint;
    HSD_JObj *child;
    s32 index;

    if (enable == 0)
        return;
    if (dspMessage == 0)
        return;
    joint = dspMessage->models[5];
    if (gameEndF != 13)
        return;
    if (GameMode.game_type != GAME_TYPE_BATTLE)
        return;
    if (*(s32 *)((u8 *)&GameMode + 0x20) == 9)
        index = 6;
    else
        index = 5;
    child = GetChild(joint, 0, index, -1, -1, -1);
    if (jobjAnim(joint) != 0)
        SetAnimArc2(dspMessage, 5, 1);
    sMakeMatrix(joint);
    jobjDispAll(child);
}
