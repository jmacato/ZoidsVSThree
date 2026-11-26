#include "types.h"

extern u32 __OSBusClock : 0x800000F8;
extern char *MC_FILENAME_MSG;
extern char menusaveloadfilename[];
extern s32 MemcardNowSlot;
extern s64 OSGetTime(void);
extern s32 CARDDelete(s32 chan, const char *fileName);
extern char *strcpy(char *destination, const char *source);
extern void OSReport(const char *format, ...);

s32 TEA_mcFileDel(void)
{
    s32 retry = 0;
    s32 slot = MemcardNowSlot;
    s64 time = OSGetTime() / (__OSBusClock / 4) + 60;
    s32 result;

    strcpy(menusaveloadfilename, MC_FILENAME_MSG);
    OSReport("MemCardDel\t%s ", menusaveloadfilename);
    for (;;) {
        result = CARDDelete(slot, menusaveloadfilename);
        if (result == 0) {
            break;
        }
        retry++;
        if (retry < 10) {
            continue;
        }
        OSReport("FileDel failed. (%d)\n", result);
        if (result == -1) {
            continue;
        }
        if (result == -10) {
            return 0;
        }
        return 0;
    }
    return 1;
}
