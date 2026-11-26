#pragma auto_inline off
#pragma readonly_strings on
#include "zoid3.h"
#include "model_archive.h"

extern ModelArchive *dspBP;
extern s32 gameEndF;
extern s32 bpTm;
extern s32 bp[12];
extern s32 GameMode[];
extern s32 sprintf(char *buffer, const char *format, ...);
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern s32 jobjAnim(HSD_JObj *joint);
extern void jobjDispAll(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);
extern void jobjCopyPos(HSD_JObj *dst, HSD_JObj *src);
extern void HiddenParts(HSD_JObj *joint, s32 hidden);
extern f32 putAscJobj(HSD_JObj *joint, s32 font, char *text);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, u32 line, const char *expr);

static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & 0x00800000) && (jobj->flags & 0x40);
}

#define HSD_JObjSetMtxDirty(jobj) \
    do { \
        if ((jobj) != 0 && !HSD_JObjMtxIsDirty(jobj)) \
            HSD_JObjSetMtxDirtySub(jobj); \
    } while (0)

void sDispBP(void *enable)
{
    char text[20];
    HSD_JObj *root;
    HSD_JObj *hide;
    HSD_JObj *show;
    HSD_JObj *child;
    s32 total;
    s32 i;

    if (dspBP == 0)
        return;
    root = dspBP->models[0];
    if (enable == 0)
        return;
    if (GameMode[1] != 1)
        return;
    if (GameMode[4] != 2)
        return;
    if (gameEndF != 11)
        return;
    if (bpTm == 0) {
        SetAnimArc2(dspBP, 0, 0);
        bpTm = 1;
    }
    if (jobjAnim(root) != 0)
        SetAnimArc2(dspBP, 0, 1);
    if (root != 0) {
        hide = GetChild(root, 0, 9, -1, -1, -1);
        show = GetChild(root, 0, 10, -1, -1, -1);
        for (i = 0; i < 5; i++)
            HiddenParts(GetChild(root, 0, 9, i, -1, -1), 5 - GameMode[16] != i);
        if (GameMode[1] == 1) {
            HiddenParts(show, 1);
        } else {
            HiddenParts(hide, 1);
            for (i = 0; i < 5; i++)
                jobjCopyPos(show, GetChild(root, 0, 9, i, -1, -1));
        }
        HiddenParts(GetChild(root, 0, 11, -1, -1, -1), 1);
        HiddenParts(GetChild(root, 0, 12, -1, -1, -1), 1);
        HSD_JObjSetMtxDirty(root);
    }
    sMakeMatrix(root);
    jobjDispAll(root);
    for (i = 0, total = 0; i < 6; i++) {
        s32 index[6] = { 0, 1, 3, 4, 5, 6 };
        child = GetChild(root, 0, index[i], 0, -1, -1);
        if (i == 5)
            sprintf(text, "%06d", (&bp[6])[i]);
        else
            sprintf(text, "%04d", (&bp[6])[i]);
        if (i != 5)
            total += (&bp[6])[i];
        bp[11] = total;
        putAscJobj(child, 3, text);
    }
}
