#include "types.h"

extern char *ZoidsVs;
extern void *sReadFileU(char *name, s32 mode);
extern void free(void *memory);

s32 chkVS(void)
{
    free(sReadFileU(ZoidsVs, 0));
    return 0;
}
