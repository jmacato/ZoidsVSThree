#include "model_archive.h"

extern ModelArchive *csrFile;

void zDispCursorPrologue(void)
{
    csrFile = LoadArc2("debug/mtp_grid.dat");
}
