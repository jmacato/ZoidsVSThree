#include "types.h"
#include "model_archive.h"
#include "game_mode.h"
#include "cobj.h"
#include "lobj.h"
#include "video.h"

extern ModelArchive *dspBP;
extern GameModeState GameMode;
extern void HSD_StartRender(int pass);
extern void HSD_EndRender(void);
extern s32 HSD_CObjSetCurrent(HSD_CObj *cobj);
extern void HSD_CObjEndCurrent(void);
extern void HSD_LObjSetCurrentAll(HSD_LObj *lobj);
extern void HSD_LObjSetupInit(HSD_CObj *cobj);
extern void HSD_VISetXFBDrawDone(void);
extern void VIWaitForRetrace(void);
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);
extern void jobjDispAll(HSD_JObj *joint);
extern void OSReport(const char *format, ...);

void allRank1(s32 rank)
{
    HSD_JObj *left;
    HSD_JObj *right;
    HSD_JObj *root;

    root = dspBP->models[0];
    if (root != 0) {
        left = GetChild(root, 0, GameMode.game_type == 4 ? 11 : 12, -1, -1, -1);
        if (left != 0) {
            right = GetChild(root, 0, 9, 5 - rank, -1, -1);
            if (right != 0) {
                jobjCopyPos(left, right);
                if (dspBP->camera == 0)
                    OSReport("unfound dspBP->cobj\n");
                HSD_StartRender(0);
                if (HSD_CObjSetCurrent(dspBP->camera) != 0) {
                    HSD_LObjSetCurrentAll(dspBP->lights);
                    HSD_LObjSetupInit(dspBP->camera);
                    jobjDispAll(left);
                    jobjDispAll(right);
                    HSD_CObjEndCurrent();
                }
                HSD_EndRender();
                HSD_VICopyXFB(0);
                HSD_VISetXFBDrawDone();
                VIWaitForRetrace();
            }
        }
    }
}
