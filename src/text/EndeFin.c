#pragma readonly_strings on
#include "game_text.h"
#include "gx_tev.h"
#include "video.h"
#include "vi.h"

extern void *sPad1;
extern s32 sPutFontCamPrologue(void);
extern void sPutStringXYC2(char *text, f32 x, f32 y, f32 z, f32 scale_x, f32 scale_y, GXColor color,
                           GXColor shadow, s32 alpha, s32 flags, s32 align);
extern void HSD_StateInvalidate(s32 state);
extern void HSD_CObjEndCurrent(void);
extern void sPadAll(void);
extern void resetSkipOp(void);

void EndeFin(void)
{
    s32 i;

    for (i = 0; i < 600; i++) {
        HSD_StartRender(HSD_RP_SCREEN);
        if (sPutFontCamPrologue() != 0) {
            sPutStringXYC2("G A M E   C L E A R .", 0.0f, 0.0f, -200.0f, 0.6f, 0.7f, (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF },
                           (GXColor){ 0x00, 0x00, 0x32, 0x00 }, 0, 2, 3);
            sPutStringXYC2("Thank you for your playing!", 0.0f, -50.0f, -250.0f, 0.6f, 0.7f,
                           (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF }, (GXColor){ 0x00, 0x00, 0x32, 0x00 }, 0, 2, 3);
            HSD_StateInvalidate(-1);
            HSD_CObjEndCurrent();
        }
        HSD_EndRender();
        HSD_VICopyXFB(HSD_RP_SCREEN);
        HSD_VISetXFBDrawDone();
        VIWaitForRetrace();
        sPadAll();
        if (*(s8 *)((u8 *)sPad1 + 0x63) != 0) {
            break;
        }
    }
    resetSkipOp();
}
