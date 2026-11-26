#include "zoid3.h"

typedef struct CameraState3 {
    u8 pad_000[0x2C];
    f32 focus_distance;
    u8 pad_030[0x1BC - 0x30];
    s32 field_1BC;
    u8 pad_1C0[4];
    ZoidState *zoid;
    u8 pad_1C8[0x1E4 - 0x1C8];
    s32 field_1E4;
} CameraState3;

extern s32 sctblLen;
extern s32 sCamNN;
extern s32 sCamNS;
extern s32 camZdLimit2(void *camera, ZoidState *zoid);
extern s32 sCameraIn2(void *camera, HSD_JObj *joint);
extern HSD_JObj *grdObjGetJObj(s32 index);

void camLimit(CameraState3 *camera)
{
    ZoidState *zoid;
    ZoidState *target;
    s32 zoid_flags;
    HSD_JObj *joint;
    s32 target_flags;
    f32 middle;

    middle = sctblLen;
    if (sCamNN == 2) {
        (void)0;
    }
    if (sCamNN == 2 && sCamNS == 0) {
        middle = sctblLen / 2;
    }
    if (camera != (void *)0 && (zoid = camera->zoid, zoid != (void *)0) && zoid->joint != (void *)0) {
        zoid_flags = camZdLimit2(camera, zoid);
        if (zoid->target_pending != 0) {
            target = &Zoid[zoid->target_slot];
            if (target != 0 && target->joint == (void *)0) {
                target = 0;
            }
            target_flags = camZdLimit2(camera, target);
        } else if (zoid->lock_active != 0) {
            joint = grdObjGetJObj(zoid->lock_obj);
            target_flags = sCameraIn2(camera, joint);
        } else {
            target_flags = 0x10;
        }
        if (camera->field_1E4 <= 0x3C) {
            if (target_flags & 0xF) {
                camera->focus_distance += 0.5;
            } else if (zoid_flags & 0xF) {
                camera->field_1BC = 0x3C;
                camera->focus_distance -= 0.2;
            } else {
                if (camera->focus_distance > 100.0f) {
                    camera->focus_distance -= 0.02;
                }
                if (camera->focus_distance < 100.0f) {
                    camera->focus_distance += 0.02;
                }
            }
            if (camera->focus_distance <= 0.0f) {
                camera->focus_distance = 0.0f;
            }
            if (camera->focus_distance >= 200.0f) {
                camera->focus_distance = 200.0f;
            }
        }
    }
}
