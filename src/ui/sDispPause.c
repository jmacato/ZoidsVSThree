#include "model_archive.h"
#include "game_camera.h"
#include "game_pad.h"
#include "game_mode.h"
#include "gx_tev.h"
#include "map_info.h"

typedef struct PauseCamera {
    u8 pad_000[0x1E8];
    PadState *pad;
} PauseCamera;

extern ModelArchive *dspPause;
extern s32 pause;
extern s32 menuRet;
extern PadState *sPad1, *sPad2;
extern MapInfo mgI;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void sDispGameFilter(s32 index, s32 mode);
extern void HiddenParts(HSD_JObj *joint, s32 hidden);
extern void sSetAnim1(ModelArchive *archive, s32 model, HSD_JObj *joint, s32 animation);
extern s32 jobjAnim(HSD_JObj *joint);
extern void jobjDispAll(HSD_JObj *joint);
extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);
extern void sMakeMatrix(HSD_JObj *joint);
extern void sPutFontRect(char *text, HSD_JObj *top_left, HSD_JObj *bottom_right, GXColor color, GXColor shadow, s32 alpha, s32 flags);
extern void sPutFontRectC(char *text, HSD_JObj *top_left, HSD_JObj *bottom_right, GXColor color, GXColor shadow, s32 alpha, s32 flags);

#define PAD_START(p) (*(s8 *)((u8 *)(p) + 0x4E))

void sDispPause(PauseCamera *camera)
{
    s32 i;
    HSD_JObj *child;
    HSD_JObj *root;
    s32 vs;
    HSD_JObj *info;
    HSD_JObj *select;
    PadState *pad;
    s32 mine;
    HSD_JObj *cursor;
    HSD_JObj *end;

    if (camera == (void *)0)
        return;
    if (dspPause == 0)
        return;
    root = dspPause->models[0];
    select = dspPause->models[7];
    info = dspPause->models[8];
    cursor = dspPause->models[9];
    if (root == 0)
        return;
    pad = sPad1;
    if (pause == 2)
        pad = sPad2;
    if (pause != 0)
        pad = (PadState *)((u8 *)sPad + (pause - 1) * 0x88);
    if (camera->pad == pad)
        mine = 1;
    else
        mine = 0;
    sDispGameFilter(4, (pause == 0 || PAD_START(pad) != 0) ? 0 : 1);
    if (pause == 0)
        return;
    if (pause == 0 || PAD_START(pad) == 0) {
        vs = 0;
        switch (GameMode.game_type) {
        case 2:
            vs = 1;
            break;
        case 5:
            vs = 1;
            break;
        }
        HiddenParts(GetChild(root, 0, 0, -1, -1, -1), 1);
        HiddenParts(GetChild(root, 0, 1, -1, -1, -1), 0);
        for (i = 0; i < 4; i++) {
            HiddenParts(GetChild(root, 0, i + 2, -1, -1, -1), vs == 0 || pause != i + 1);
        }
        if (mine != 0) {
            if (jobjAnim(root) != 0) {
                SetAnimArc2(dspPause, 0, 1);
                jobjAnim(root);
            }
        }
        jobjDispAll(root);
        if (select != 0 && cursor != 0) {
            if (mine != 0) {
                child = GetChild(select, 0, 0, -1, -1, -1);
                if (jobjAnim(child) != 0) {
                    sSetAnim1(dspPause, 7, child, menuRet == 0 ? 2 : 1);
                    jobjAnim(child);
                }
                child = GetChild(select, 0, 1, -1, -1, -1);
                if (jobjAnim(child) != 0) {
                    sSetAnim1(dspPause, 7, child, menuRet == 1 ? 2 : 1);
                    jobjAnim(child);
                }
            }
            jobjDispAll(select);
            if (GameMode.game_type == GAME_TYPE_VS) {
                child = GetChild(select, 0, menuRet, pause, -1, -1);
                jobjCopyPos(child, cursor);
                sMakeMatrix(cursor);
                jobjDispAll(GetChild(cursor, 0, 2 - pause, -1, -1, -1));
            }
        }
        if (GameMode.game_type == GAME_TYPE_MISSION && info != 0) {
            if (jobjAnim(info) != 0) {
                SetAnimArc2(dspPause, 8, 1);
                jobjAnim(info);
            }
            jobjDispAll(info);
            sMakeMatrix(info);
            child = GetChild(info, 0, 0, -1, -1, -1);
            end = GetChild(info, 0, 0, 0, -1, -1);
            sPutFontRect("\x8f\x9f\x97\x98\x8f\xf0\x8c\x8f", child, end, (GXColor){ 0, 255, 0, 255 }, (GXColor){ 0, 0, 0, 0 }, 0, 2);
            child = GetChild(info, 0, 1, -1, -1, -1);
            end = GetChild(info, 0, 1, 0, -1, -1);
            sPutFontRectC(mgI.victory_text, child, end, (GXColor){ 255, 255, 255, 255 }, (GXColor){ 0, 0, 0, 0 }, 0, 2);
        }
    }
    (void)mine;
    (void)child;
    (void)child;
    (void)child;
}
