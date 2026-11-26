#include "types.h"
extern s32 sprintf(char *, const char *, ...);
extern s32 fexist(char *name);
extern void *sReadFileLenU(char *name, s32 mode, s32 *length);
extern void *LoadArc2(char *name);
extern void purgeMsgHelp(void);
extern s32 fBtl;
extern s32 fMapNo;
extern char *rdMapStr[];
extern void *fMsgHelp;
extern s32 lenMsgHelp;
extern void *dspMsgHelp;

void loadMsgHelp(void)
{
    char path[0x100];
    s32 len;
    purgeMsgHelp();
    sprintf(path, "menu/map_info_dat/%s%03d.msg", rdMapStr[fBtl], fMapNo);
    if (fexist(path) != 0) {
        fMsgHelp = sReadFileLenU(path, 0, &len);
        lenMsgHelp = (u32)len / 0x110;
        dspMsgHelp = LoadArc2("disp/top_message.dat");
    }
}
