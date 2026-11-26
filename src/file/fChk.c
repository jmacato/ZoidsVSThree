#include "dvd_file.h"

extern char *ZoidsVs;
extern void sbk(s32 result, DVDFileInfo *file);

s32 fChk(char *path)
{
    DVDFileInfo file;

    if (DVDCheckDisk() == 0)
        return 0;
    if (DVDConvertPathToEntrynum(ZoidsVs) == -1)
        return 0;
    if (DVDOpen(path, &file) == 0)
        return 0;
    DVDSeekAsyncPrio(&file, 10, sbk, 2);
    DVDClose(&file);
    if (DVDCheckDisk() == 0)
        return 0;
    if (DVDConvertPathToEntrynum(ZoidsVs) == -1)
        return 0;
    if (DVDOpen(path, &file) == 0)
        return 0;
    DVDSeekAsyncPrio(&file, 0, sbk, 2);
    DVDClose(&file);
    if (DVDCheckDisk() == 0)
        return 0;
    return 1;
}
