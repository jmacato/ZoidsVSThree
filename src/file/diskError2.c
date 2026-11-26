#pragma readonly_strings on
#include "video.h"
#include "gx_geometry.h"
#include "fog.h"
#include "disk_error.h"
#include "dvd.h"
#include "dvd_file.h"

extern HSD_Fog *fogG;
extern char *ZoidsVs;
extern void OSReport(const char *format, ...);
extern void VIWaitForRetrace(void);
extern void HSD_StateInvalidate(s32 state);
extern void HSD_SetZSortMode(s32 a, s32 b);
extern void HSD_FogSet(HSD_Fog *fog);
extern void sPadAll(void);
extern s32 fChk(char *path);

static inline void setEraseColor(GXColor color)
{
    HSD_VIData.current.vi.clear_clr = color;
}

void diskError2(s32 error)
{
    s32 message = DISK_ERROR_NONE;
    s32 pad_b;
    s32 pad_a;
    DVDFileInfo file;
    s32 status;
    s32 timer;
    s32 opened;

    OSReport("error\n");
    pad_a = 0;
    pad_b = 0;
    timer = 15;
    opened = 0;
    VIWaitForRetrace();
    HSD_StateInvalidate(-1);
    HSD_SetZSortMode(0, 0);
    GXSetCullMode(GX_CULL_NONE);
    setEraseColor((GXColor){ 0, 0, 0, 0 });
    HSD_FogSet(0);
    status = DVD_STATE_END;
    for (;;) {
        DVDCheckDisk();
        DVDGetDriveStatus();
        VIWaitForRetrace();
        sPadAll();
        if (timer != 0)
            timer--;
        else
            error = DISK_ERROR_NONE;
        if (error != DISK_ERROR_NONE)
            message = error;
        if (status == DVD_STATE_BUSY) {
            status = DVDGetDriveStatus();
            continue;
        }
        diskError3(message);
        status = DVDGetDriveStatus();
        OSReport("A0");
        message = DISK_ERROR_NONE;
        if (status == DVD_STATE_COVER_OPEN) {
            message = DISK_ERROR_COVER_OPEN;
            error = DISK_ERROR_NONE;
        }
        if (status == DVD_STATE_NO_DISK)
            message = DISK_ERROR_NO_DISK;
        if (status == DVD_STATE_WRONG_DISK)
            message = DISK_ERROR_WRONG_DISK;
        if (status == DVD_STATE_END && error != DISK_ERROR_WRONG_DISK && fChk(ZoidsVs) == 0) {
            (void)0;
            break;
        }
        if (status == DVD_STATE_RETRY)
            message = DISK_ERROR_RETRY;
        if (status == DVD_STATE_FATAL_ERROR)
            message = DISK_ERROR_FATAL;
        OSReport("[%d.%d]", status, message);
        if (message != DISK_ERROR_NONE)
            timer = 60;
        if (timer != 0 && DVDCheckDisk() != 0) {
            message = DISK_ERROR_COVER_OPEN;
            continue;
        }
        if (message != DISK_ERROR_NONE || timer != 0 || (status != DVD_STATE_END && status != DVD_STATE_FATAL_ERROR) || error != DISK_ERROR_NONE || status != DVD_STATE_END)
            continue;
        break;
    }
    if (opened != 0)
        DVDClose(&file);
    OSReport("A9 ");
    if (fogG != 0)
        setEraseColor(fogG->color);
    HSD_StateInvalidate(-1);
    DVDCheckDisk();
    DVDGetDriveStatus();
    VIWaitForRetrace();
    sPadAll();
}
