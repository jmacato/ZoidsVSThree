#include "types.h"

extern void *OSGetArenaLo(void);
extern void *OSGetArenaHi(void);
extern void *OSInitAlloc(void *arenaStart, void *arenaEnd, s32 maxHeaps);
extern void OSSetArenaLo(void *newLo);
extern void OSReport(const char *format, ...);
extern void *usrLO;

static void init_alloc(s32 heaps)
{
    void *lo = OSGetArenaLo();
    void *hi = OSGetArenaHi();
    lo = OSInitAlloc(lo, hi, heaps);
    OSSetArenaLo(lo);
    OSReport("mem arena %dk \n", ((s32)hi - (s32)lo) / 1024);
    usrLO = lo;
}
