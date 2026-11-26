#include "model_archive.h"

extern ModelArchive *dspMsgHelp;
extern ModelArchive *dspMsgHelpPage;
extern char fileMsgHelp[];
extern void *fMsgHelp;
extern void free(void *);

void purgeMsgHelp(void)
{
    if (dspMsgHelp != 0) {
        PurgeArc2(dspMsgHelp);
        dspMsgHelp = 0;
    }
    if (dspMsgHelpPage != 0) {
        PurgeArc2(dspMsgHelpPage);
        dspMsgHelpPage = 0;
        fileMsgHelp[0] = 0;
    }
    if (fMsgHelp != 0) {
        free(fMsgHelp);
        fMsgHelp = 0;
    }
}
