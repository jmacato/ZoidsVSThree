#include "types.h"

extern u32 VIGetRetraceCount(void);
extern s64 OSGetTime(void);
extern s32 vc000;
extern s64 vc001;

void vcStart(void)
{
    vc000 = VIGetRetraceCount();
    vc001 = OSGetTime();
}
