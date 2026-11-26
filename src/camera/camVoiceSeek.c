#include "types.h"

extern char vcSeekStr[];
extern char *strcpy(char *dst, const char *src);

s32 camVoiceSeek(const char *name)
{
    strcpy(vcSeekStr, name);
    return 0;
}
