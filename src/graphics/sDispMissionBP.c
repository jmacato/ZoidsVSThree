#pragma readonly_strings on
#include "model_archive.h"
#include "game_mode.h"

extern ModelArchive *dspBP;
extern s32 gameEndF;
extern s32 bpTm;
extern s32 jobjAnim(HSD_JObj *joint);
extern void jobjDispAll(HSD_JObj *joint);
extern void jobjDispPos(HSD_JObj *joint, HSD_JObj *target);
extern void sMakeMatrix(HSD_JObj *joint);
extern void HiddenParts(HSD_JObj *joint, s32 hidden);
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void SetAnimArc2(ModelArchive *archive, s32 model, s32 selected);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *);
extern void __assert(const char *file, u32 line, const char *condition);

#pragma auto_inline off
static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & 0x00800000) && (jobj->flags & 0x40);
}

void sDispMissionBP(void *enable)
{
    HSD_JObj *root;
    HSD_JObj *unused;
    HSD_JObj *point;
    HSD_JObj *child;
    s32 i;

    if (dspBP == 0)
        return;
    root = dspBP->models[0];
    if (enable == 0)
        return;
    if (GameMode.game_type != 4)
        return;
    if (*(s32 *)((u8 *)&GameMode + 0x10) != 2)
        return;
    if (gameEndF != 11)
        return;
    if (bpTm == 0) {
        SetAnimArc2(dspBP, 0, 0);
        bpTm = 1;
    }
    if (root == 0)
        return;
    if (jobjAnim(root) != 0) {
        SetAnimArc2(dspBP, 0, 1);
    }
    if (root != 0 && !HSD_JObjMtxIsDirty(root)) {
        HSD_JObjSetMtxDirtySub(root);
    }
    sMakeMatrix(root);
    unused = GetChild(root, 0, 9, -1, -1, -1);
    point = GetChild(root, 0, 10, -1, -1, -1);
    for (i = 0; i < 5; i++) {
        child = GetChild(root, 0, 9, i, -1, -1);
        if (child != 0) {
            HiddenParts(child, 0);
        }
    }
    jobjDispAll(point);
    root = root;
    root = root;
    child = GetChild(root, 0, 9, 5 - *(s32 *)((u8 *)&GameMode + 0x40), -1, -1);
    jobjDispPos(child, point);
}
