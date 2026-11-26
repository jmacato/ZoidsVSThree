#include "zoid3.h"
#include "model_archive.h"
#include "game_mode.h"
#include "game_person_data.h"
#include "game_text.h"

extern ModelArchive *dspPartner;
extern s32 sCamNN;
extern s32 gameEndF;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjDispAll(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);
void sDispPartner(void *enable)
{
    HSD_JObj *root;
    s32 u1;
    s32 u2;
    s32 u3;
    s32 u4;
    s32 u5;
    HSD_JObj *child;
    ZoidState *partner;
    char *name;

    if (*(s32 *)((u8 *)&GameMode + 0x44) != 0)
        return;
    if (sCamNN != 1)
        return;
    if (dspPartner == 0)
        return;
    if (gameEndF > 3)
        return;
    partner = &Zoid[2];
    if (partner->joint == (void *)0)
        return;
    if (enable == (void *)0)
        return;
    root = dspPartner->models[0];
    if (root == 0)
        return;
    jobjDispAll(root);
    sMakeMatrix(root);
    child = GetChild(root, 0, 2, 0, -1, -1);
    name = Tea_persondat[Zoid[2].person].name;
    putAscJobj(child, 0, name);
}
