#include "model_archive.h"

extern ModelArchive *csrFile;

void zDispCursorEpilogue(void)
{
    PurgeArc2(csrFile);
    csrFile = 0;
}
