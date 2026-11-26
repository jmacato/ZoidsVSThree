#pragma readonly_strings on
#include "zoid3.h"
#include "model_archive.h"
#include "game_mode.h"

typedef struct CameraState3 {
    u8 pad_000[0x08];
    struct HSD_LObj *lights;
    u8 pad_00C[0x1B8];
    struct ZoidState *zoid;
    u8 pad_1C8[0x7C];
    struct HSD_CObj *cobj;
} CameraState3;

extern ModelArchive *dsp1p;
extern ModelArchive *dspMessage;
extern s32 gameEndF;
extern void dummyFunc(const char *);
extern void HSD_CObjGetScissor(struct HSD_CObj *cobj, u16 *scissor);
extern void HSD_CObjSetScissor(struct HSD_CObj *cobj, u16 *scissor);
extern void HSD_SetZSortMode(s32, s32);
extern s32 HSD_CObjSetCurrent(struct HSD_CObj *);
extern void HSD_CObjEndCurrent(void);
extern void HSD_LObjSetCurrentAll(struct HSD_LObj *);
extern void HSD_LObjSetupInit(struct HSD_CObj *);
extern void GXSetCullMode(s32);
extern void sDispFilter(CameraState3 *camera, struct ZoidState *zoid);
extern void sDispFilterG(void);
extern void sDispFilterB(void);
extern void sDisp1pA(CameraState3 *camera);
extern void sDispPause(CameraState3 *camera);
extern void sDispDemoPress(CameraState3 *camera);
extern void sDispPurgePartsGame(void);
extern void sDispLoadPartsMessage(void);
extern void sDispLoadPartsContinue(void);
extern void sDispLoadPartsBP(void);
extern void dispMsgHelpPage(void);
extern void sDispMessage(CameraState3 *camera);
extern void sDispBP(CameraState3 *camera);
extern void sDispMissionBP(CameraState3 *camera);
extern void sDispNext(CameraState3 *camera);

void sDisp(CameraState3 *camera)
{
    u16 scissor[6];
    s32 filtered;
    struct HSD_CObj *cobj;

    if (camera == (void *)0)
        return;
    cobj = camera->cobj;
    if (cobj == (void *)0)
        return;
    filtered = 0;
    dummyFunc("cam-");
    HSD_CObjGetScissor(camera->cobj, scissor);
    if (dsp1p != 0)
        HSD_CObjSetScissor(dsp1p->camera, scissor);
    if (dspMessage != 0)
        HSD_CObjSetScissor(dspMessage->camera, scissor);
    HSD_SetZSortMode(0, 0);
    if (dsp1p != 0 && HSD_CObjSetCurrent(dsp1p->camera) != 0) {
        HSD_LObjSetCurrentAll(camera->lights);
        HSD_LObjSetupInit(dsp1p->camera);
        GXSetCullMode(0);
        sDispFilter(camera, camera->zoid);
        filtered = 1;
        sDispFilterG();
        dummyFunc("3");
        sDisp1pA(camera);
        dummyFunc("4");
        sDispPause(camera);
        sDispDemoPress(camera);
        HSD_CObjEndCurrent();
    }
    if (gameEndF >= 4)
        sDispPurgePartsGame();
    if (gameEndF >= 4)
        sDispLoadPartsMessage();
    if (gameEndF >= 9)
        sDispLoadPartsContinue();
    if (gameEndF == 11 && (GameMode.game_type == 1 || GameMode.game_type == 4))
        sDispLoadPartsBP();
    dispMsgHelpPage();
    if (dspMessage != 0 && HSD_CObjSetCurrent(dspMessage->camera) != 0) {
        HSD_LObjSetCurrentAll(camera->lights);
        HSD_LObjSetupInit(dspMessage->camera);
        GXSetCullMode(0);
        if (filtered == 0)
            sDispFilterG();
        if (gameEndF >= 4)
            sDispMessage(camera);
        sDispFilterB();
        if (GameMode.game_type == 1)
            sDispBP(camera);
        if (GameMode.game_type == 4)
            sDispMissionBP(camera);
        sDispNext(camera);
        HSD_CObjEndCurrent();
        GXSetCullMode(2);
    }
    HSD_SetZSortMode(1, 1);
    dummyFunc("-- cam-- end\n");
}
