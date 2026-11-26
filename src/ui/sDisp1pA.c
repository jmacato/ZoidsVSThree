#pragma readonly_strings on
#include "zoid3.h"
#include "model_archive.h"

typedef struct CameraState3 {
    s32 mode;
    s32 half;
    u8 reserved_008[0x1BC];
    ZoidState *zoid;
} CameraState3;

extern ModelArchive *dspPos00, *dsp1p;
extern s32 sCamNN, sCamNS;
extern s32 gameEndF;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);
extern void sDispFrame(CameraState3 *camera, HSD_JObj *joint);
extern void sDispScope(CameraState3 *camera, HSD_JObj *joint);
extern void sDispOrder(CameraState3 *camera);
extern void sDispPartner(CameraState3 *camera);
extern void s1pZdHP(CameraState3 *camera, ZoidState *zoid, ModelArchive *archive, HSD_JObj *joint);
extern void s1pEX(CameraState3 *camera, ZoidState *zoid, HSD_JObj *joint);
extern void s1pOption(CameraState3 *camera, ZoidState *zoid, HSD_JObj *joint);
extern void s1pZdDmg1(ZoidState *zoid, ModelArchive *archive, HSD_JObj *joint);
extern void s1pWeapon(CameraState3 *camera, ZoidState *zoid, HSD_JObj *joint);
extern void s1pRader(CameraState3 *camera, ZoidState *zoid, HSD_JObj *joint);
extern void s1pTimer(HSD_JObj *joint);
extern void s1pTarget(CameraState3 *camera, ZoidState *zoid);
extern void s1pTargetObj(CameraState3 *camera, ZoidState *zoid);
extern void s1pWpTgt(CameraState3 *camera, ZoidState *zoid);
extern void sDispArea(CameraState3 *camera, HSD_JObj *joint);
extern void dummyFunc(const char *);

void sDisp1pA(CameraState3 *camera)
{
    ZoidState *zoid;
    HSD_JObj *joint;
    HSD_JObj *target;

    if (camera != 0) {
        zoid = camera->zoid;
        if (zoid != (void *)0 && zoid->joint != (void *)0 && dspPos00 != 0 && dsp1p != 0) {
            joint = GetChild(dspPos00->models[1], 0, 0, 8, -1, -1);
            target = GetChild(dspPos00->models[1], 0, 1, 8, -1, -1);
            jobjCopyPos(joint, target);
            joint = GetChild(dspPos00->models[2], 0, 0, 8, -1, -1);
            target = GetChild(dspPos00->models[2], 0, 1, 8, -1, -1);
            jobjCopyPos(joint, target);
            joint = 0;
            if (dspPos00 != 0) {
                if (sCamNN == 1) {
                    joint = GetChild(dspPos00->models[0], 0, -1, -1, -1, -1);
                } else if (sCamNN == 4) {
                    joint = GetChild(dspPos00->models[3], 0, camera->half, -1, -1, -1);
                } else {
                    joint = GetChild(dspPos00->models[1 + sCamNS], 0, camera->half, -1, -1, -1);
                }
            }
            if (joint != (void *)0) {
                sDispFrame(camera, joint);
                if (gameEndF < 3) {
                    sDispScope(camera, joint);
                    sDispOrder(camera);
                    sDispPartner(camera);
                    s1pZdHP(camera, zoid, dsp1p, joint);
                    dummyFunc("h");
                    s1pEX(camera, zoid, joint);
                    dummyFunc("i");
                    s1pOption(camera, zoid, joint);
                    dummyFunc("j");
                    s1pZdDmg1(zoid, dsp1p, joint);
                    s1pWeapon(camera, zoid, joint);
                    s1pRader(camera, zoid, joint);
                    s1pTimer(joint);
                    s1pTarget(camera, zoid);
                    s1pTargetObj(camera, zoid);
                    s1pWpTgt(camera, zoid);
                    sDispArea(camera, joint);
                }
            }
        }
    }
}
