#include "types.h"
#include "gx_tev.h"
#include "model_archive.h"

extern char *fMsgHelp;
extern ModelArchive *dspMsgHelp;
extern ModelArchive *dspMsgHelpPage;
extern s32 pgMsgHelp;
extern s32 isMsgHelpPage(s32 page);
extern HSD_JObj *GetChild(HSD_JObj *, s32, s32, s32, s32, s32);
extern s32 jobjAnim(HSD_JObj *joint);
extern void jobjDispAll(HSD_JObj *joint);
extern void sPutFontRect(char *, HSD_JObj *, HSD_JObj *, GXColor, GXColor, s32, u32);

void dispMsgHelpPage(void)
{
    GXColor white = {255, 255, 255, 255};
    GXColor clear = {0, 0, 0, 0};
    HSD_JObj *joint;
    HSD_JObj *page_joint;
    HSD_JObj *top_left;
    HSD_JObj *bottom_right;
    s32 page;
    if (fMsgHelp != 0 && dspMsgHelp != 0 && (joint = dspMsgHelp->models[0]) != 0) {
        top_left = GetChild(joint, 0, 1, -1, -1, -1);
        bottom_right = GetChild(joint, 0, 1, 0, -1, -1);
        page = pgMsgHelp;
        if (isMsgHelpPage(page) != 0) {
            jobjAnim(joint);
            jobjDispAll(joint);
            sPutFontRect(fMsgHelp + page * 0x110 + 0x10, top_left, bottom_right, white, clear, 0, 2);
            if (dspMsgHelpPage != 0) {
                page_joint = dspMsgHelpPage->models[0];
                jobjAnim(page_joint);
                jobjDispAll(page_joint);
            }
        }
    }
}
