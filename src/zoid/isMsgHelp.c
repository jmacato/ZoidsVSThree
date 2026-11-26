#include "types.h"

extern void loadMsgHelp(void);
extern s32 fMsgHelp;

s32 isMsgHelp(void)
{
    loadMsgHelp();
    return fMsgHelp != 0;
}
