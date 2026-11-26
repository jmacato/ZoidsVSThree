#include "types.h"

extern char *fMsgHelp;
extern s32 lenMsgHelp;
extern s32 pgMsgHelp;
extern char fileMsgHelp[];
extern void *dspMsgHelpPage;
extern s32 sprintf(char *buf, const char *fmt, ...);
extern s32 strcmp(const char *a, const char *b);
extern char *strcpy(char *dst, const char *src);
extern void PurgeArc2(void *arc);
extern void *LoadArc2(char *name);

s32 isMsgHelpPage(s32 index)
{
    char buf[0x100];
    pgMsgHelp = -1;
    if (fMsgHelp == 0)
        return 0;
    if (lenMsgHelp <= index)
        return 0;
    if (index < 0)
        return 0;
    sprintf(buf, "disp/%s", fMsgHelp + index * 0x110);
    if (strcmp(buf, fileMsgHelp) != 0) {
        strcpy(fileMsgHelp, buf);
        if (dspMsgHelpPage != 0)
            PurgeArc2(dspMsgHelpPage);
        dspMsgHelpPage = 0;
        dspMsgHelpPage = LoadArc2(buf);
    }
    pgMsgHelp = index;
    return 1;
}
