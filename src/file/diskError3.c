#pragma readonly_strings on
#include "video.h"
#include "gx_geometry.h"
#include "dvd_file.h"
#include "disk_error.h"

extern char *diskErrMsg[];
extern s32 sPadResetSTOP;
extern s32 sPutFontCamPrologue(void);
extern void sPutStringXYC2(char *text, GXColor color, GXColor shadow, s32 alpha, s32 flags, s32 align, f32 x,
                           f32 y, f32 z, f32 scale_x, f32 scale_y);
extern void OSReport(const char *format, ...);
extern void HSD_StateInvalidate(s32 state);
extern void HSD_CObjEndCurrent(void);
extern void HSD_EndRender(void);
extern void HSD_StartRender(int pass);
extern void HSD_VICopyXFB(HSD_RenderPass pass);
extern void HSD_VISetXFBDrawDone(void);
extern void VIWaitForRetrace(void);
extern void sPadAll(void);
extern s32 DVDGetDriveStatus(void);

void diskError3(s32 message)
{
    s32 i;
    s32 j;

    if (message == DISK_ERROR_FATAL)
        sPadResetSTOP = 1;
    for (i = 0; i < 10; i++) {
        HSD_StartRender(HSD_RP_SCREEN);
        OSReport("E%d.", message);
        if (sPutFontCamPrologue() != 0) {
            if (message != DISK_ERROR_NONE) {
                if (message < 0)
                    message = DISK_ERROR_OTHER;
                if (message > 7)
                    message = DISK_ERROR_OTHER;
                sPutStringXYC2(diskErrMsg[message], (GXColor){255, 255, 255, 255},
                               (GXColor){0, 0, 0, 0}, 0, 2, 3, 0.0F, 0.0F, -300.0F, 0.6F, 0.7F);
                HSD_StateInvalidate(-1);
            }
            HSD_CObjEndCurrent();
        }
        OSReport("n.");
        HSD_EndRender();
        HSD_VICopyXFB(HSD_RP_SCREEN);
        HSD_VISetXFBDrawDone();
        for (j = 0; j < i * 2; j++)
            VIWaitForRetrace();
        sPadAll();
        DVDGetDriveStatus();
    }
}
