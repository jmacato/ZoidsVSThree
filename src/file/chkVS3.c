#include "dvd_file.h"
#include "archive.h"
#include "disk_error.h"

extern char *ZoidsVs;

#pragma dont_inline on
static s32 chkVS3(void)
{
    DVDFileInfo file;
    s32 ok;
    ok = DVDOpen(ZoidsVs, &file);
    if (!ok)
        return 0;
    DVDClose(&file);
    return 1;
}
