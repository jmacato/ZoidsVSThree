#include "zoid3.h"
#include "model_archive.h"

extern ModelArchive *csrFile;
extern s32 csrDispON;
extern void jobjDispAll(HSD_JObj *joint);

void zdDispCursor(void)
{
    if (csrFile != (ModelArchive *)0 && csrDispON != 0)
        jobjDispAll(csrFile->models[0]);
}
