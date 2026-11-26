#include "zoid3.h"
#include "model_archive.h"

typedef struct CameraState3 {
    u8 pad_000[0x1C4];
    ZoidState *zoid;
} CameraState3;

typedef struct OrderData {
    u8 pad_00[0x8C];
    s32 field_8C;
    s32 field_90;
} OrderData;

extern ModelArchive *dspOrder;
extern s32 dspOrderAI;
extern s32 dspPartnerMsgTm;
extern s32 dspPartnerMsgF;
extern s32 sCamNN;
extern s32 gameEndF;
extern u8 mgI[];
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void HiddenParts(HSD_JObj *joint, s32 hidden);

void sDispOrderAnim(CameraState3 *camera)
{
    s32 order[5] = {-1, 0, 3, 1, 2};
    ZoidState *zoid;
    OrderData *data;
    s32 ai;
    s32 current;
    s32 other;
    HSD_JObj *root;
    HSD_JObj *child;
    s32 i;

    if (sCamNN == 1 && dspOrder != 0 && gameEndF <= 3 && dspOrderAI >= 0
        && *(s8 *)(mgI + 0x3218) == 0 && camera != (void *)0
        && (zoid = camera->zoid, zoid != 0)
        && (data = *(OrderData **)((u8 *)&Zoid[2] + 0x2098), data != 0)) {
        if (dspPartnerMsgTm == 0 && data->field_8C != 0) {
            dspOrderAI = data->field_8C;
        }
        ai = dspOrderAI;
        current = order[ai];
        other = order[data->field_90];
        root = dspOrder->models[0];
        if (root != 0) {
            for (i = 0; i < 4; i++) {
                child = GetChild(root, 0, i, -1, -1, -1);
                HiddenParts(child, current != i);
                child = GetChild(root, 0, i, 0, -1, -1);
                HiddenParts(child, current == i);
                child = GetChild(root, 0, i, 0, 0, -1);
                HiddenParts(child, 1);
                if (dspPartnerMsgF != 0) {
                    HiddenParts(child, current == i || other == i);
                }
            }
        }
    }
}
