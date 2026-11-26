#include "model_archive.h"

extern ModelArchive *dsp1p;
extern u8 sCamera[];
extern void *camTmp;
extern s32 jobjAnim(HSD_JObj *joint);
extern void dispAnim(void *arg);

void sDispAnim(void)
{
    void *camera;
    s32 i;

    if (dsp1p != 0)
        jobjAnim(dsp1p->models[14]);
    for (i = 0; i < 4; i++) {
        camera = sCamera + i * 0x590;
        camTmp = camera;
        if (*(void **)((u8 *)camTmp + 0x244) != 0)
            dispAnim(camera);
    }
    camTmp = sCamera;
}
