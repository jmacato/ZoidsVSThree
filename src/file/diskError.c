#pragma readonly_strings on
#include "dvd_file.h"
#include "video.h"
#include "fog.h"
#include "disk_error.h"

extern HSD_Fog *fogG;
extern s32 dOpen;
extern char *ZoidsVs;
extern char *strNameGame;
extern char *strNameMake;
extern void sPadAllRumbleOFF(void);
extern u8 adr[];
extern void sbk(s32 result, DVDFileInfo *file);
extern void OSReport(const char *format, ...);
extern void VIWaitForRetrace(void);
extern void HSD_FogSet(HSD_Fog *fog);
extern s32 DVDCheckDisk(void);
extern s32 DVDGetDriveStatus(void);
extern s32 DVDGetCommandBlockStatus(DVDCommandBlock *block);
extern void sPadAll(void);
extern void TEA_VoiceOff(void);
extern s32 strncmp(const char *a, const char *b, u32 n);

static inline void setEraseColor(GXColor color)
{
    HSD_VIData.current.vi.clear_clr = color;
}

void diskError(s32 mode)
{
    DVDFileInfo file;
    DVDDiskID *id;
    s32 bad;
    s32 opened = 0;

    (void)"LOADing\n";
    dOpen = 0;
    HSD_VISetBlack(0);
    HSD_VICopyXFB(HSD_RP_SCREEN);
    HSD_VISetXFBDrawDone();
    VIWaitForRetrace();
    HSD_VICopyXFB(HSD_RP_SCREEN);
    HSD_VISetXFBDrawDone();
    VIWaitForRetrace();
    sPadAllRumbleOFF();
    for (;;) {
        diskError2(mode);
        DVDCancelAll();
        OSReport("D-");
        if (DVDConvertPathToEntrynum(ZoidsVs) == -1) {
            mode = DISK_ERROR_WRONG_DISK;
            OSReport("D3");
            continue;
        }
        if (!(opened = DVDOpen(ZoidsVs, &file))) {
            mode = DISK_ERROR_WRONG_DISK;
            OSReport("D4");
            continue;
        }
        if (!DVDReadAsyncPrio(&file, adr, 32, 0, sbk, 2)) {
            mode = DISK_ERROR_WRONG_DISK;
            OSReport("D6");
            continue;
        }
        for (;;) {
            /* MWCC counts each read with this loop's weight before discarding it. */
            (void)mode;
            (void)mode;
            (void)mode;
            (void)mode;
            (void)mode;
            (void)mode;
            (void)mode;
            DVDCheckDisk();
            {
                s32 state = DVDGetCommandBlockStatus(&file.cb);
                OSReport("%d.", state);
                if (state == DVD_STATE_END)
                    break;
                if (state == DVD_STATE_BUSY)
                    continue;
                if (state == DVD_STATE_WAITING)
                    continue;
                if (state == DVD_STATE_NO_DISK)
                    diskError2(DISK_ERROR_NO_DISK);
                else if (state == DVD_STATE_WRONG_DISK)
                    diskError2(DISK_ERROR_WRONG_DISK);
                break;
            }
        }
        DVDClose(&file);
        if (!DVDCheckDisk()) {
            OSReport("D/");
            mode = DISK_ERROR_COVER_OPEN;
            DVDClose(&file);
            continue;
        }
        bad = 0;
        id = DVDGetCurrentDiskID();
        if (id == (void *)0)
            bad = 1;
        if (id != 0 && strncmp(id->gameName, strNameGame, 4) != 0)
            bad = 1;
        if (id != 0 && strncmp(id->company, strNameMake, 2) != 0)
            bad = 1;
        if (bad != 0) {
            OSReport("Din");
            mode = DISK_ERROR_WRONG_DISK;
            continue;
        }
        if (!(opened = DVDOpen(ZoidsVs, &file))) {
            mode = DISK_ERROR_WRONG_DISK;
            OSReport("D7");
            continue;
        }
        break;
    }
    DVDCancelAll();
    DVDClose(&file);
    TEA_VoiceOff();
    OSReport("Dh");
    setEraseColor((GXColor){ 0, 0, 0, 0 });
    HSD_FogSet(0);
    HSD_StartRender(HSD_RP_SCREEN);
    HSD_EndRender();
    HSD_VICopyXFB(HSD_RP_SCREEN);
    HSD_VISetXFBDrawDone();
    VIWaitForRetrace();
    sPadAll();
    DVDGetDriveStatus();
    if (fogG != 0)
        HSD_FogSet(fogG);
    if (fogG != 0)
        setEraseColor(fogG->color);
}
