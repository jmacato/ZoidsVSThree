#include "model_archive.h"
#include "game_camera.h"

extern ModelArchive *dsp1p;
extern s32 sCamNN;
extern s32 sCamNS;
extern s32 jobjAnim(HSD_JObj *joint);
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjCopyPos(HSD_JObj *dst, HSD_JObj *src);
extern void jobjDispAll(HSD_JObj *joint);

void sDispFrame(CameraState *camera, HSD_JObj *src)
{
    s32 index;
    HSD_JObj *child;

    if (sCamNN == 1)
        return;
    if (sCamNN == 4)
        index = camera->half + 4;
    if (sCamNN == 2)
        index = camera->half + sCamNS * 2;
    child = GetChild(dsp1p->models[15], 0, index, -1, -1, -1);
    if (child != 0) {
        jobjCopyPos(src, child);
        jobjDispAll(child);
    }
}
