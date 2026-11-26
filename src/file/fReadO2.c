#pragma readonly_strings on
#include "dvd_file.h"
#include "archive.h"
#include "disk_error.h"

extern void OSReport(const char *, ...);
extern s32 rCbkR;
extern void rCbk(s32 result, DVDFileInfo *file);
extern void dspLoadNowAnim(void);

static s32 fReadO2(DVDFileInfo *file, void *memory, s32 length, s32 offset)
{
    s32 result;

    rCbkR = 0;
    OSReport("Syns");
    if (offset < 0) {
        OSReport("fReadO2 ofst<0 ofst=%d error------------------------\n", offset);
        offset = 0;
    }
    result = DVDReadAsyncPrio(file, memory, (length + 31) & ~31, offset, rCbk, 2);
    OSReport("Syne");
    if (result == 0) {
        OSReport("Synr");
        return -1;
    }
    for (;;) {
        s32 state;

        if (!DVDCheckDisk())
            diskError(DISK_ERROR_NONE);
        state = DVDGetCommandBlockStatus(&file->cb);
        if (state == DVD_STATE_END)
            break;
        if (state == DVD_STATE_BUSY || state == DVD_STATE_WAITING) {
            dspLoadNowAnim();
            continue;
        }
        diskError(DISK_ERROR_NONE);
    }
    return 1;
}
