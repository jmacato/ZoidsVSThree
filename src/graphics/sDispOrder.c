#include "zoid3.h"
#include "model_archive.h"
#include "game_mode.h"

typedef struct CameraState3 {
    u8 pad_000[0x1C4];
    ZoidState *zoid;
} CameraState3;

extern ModelArchive *dspOrder;
extern s32 dspOrderAI;
extern s32 sCamNN;
extern s32 gameEndF;
extern u8 mgI[];
extern void jobjDispAll(HSD_JObj *joint);

void sDispOrder(CameraState3 *camera)
{
    s32 order[5] = {-1, 0, 3, 1, 2};
    HSD_JObj *root;

    if (sCamNN == 1 && *(s32 *)((u8 *)&GameMode + 0x44) == 0 && dspOrder != 0
        && *(s8 *)(mgI + 0x3218) == 0 && camera->zoid != 0 && camera->zoid == &Zoid[0]
        && Zoid[2].joint != 0 && Zoid[0].slot == Zoid[2].slot && gameEndF <= 3
        && dspOrderAI >= 0 && camera != (void *)0 && *(s32 *)((u8 *)&Zoid[2] + 0x1E6C) == 0) {
        root = dspOrder->models[0];
        if (root != 0) {
            jobjDispAll(root);
        }
    }
}
