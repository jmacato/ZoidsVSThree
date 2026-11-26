#include "types.h"

extern s16 TEA_VOICEVOL;
extern s32 sReadPre(void);
extern s32 sprintf(char *buffer, const char *format, ...);
extern s32 fexist(char *path);
extern void TEA_VoiceFilePlay(char *path, u8 volume, s32 mode);
extern void OSReport(const char *format, ...);

void TEA_VoiceOn(u8 character, s16 voice)
{
    char path[80];
    sReadPre();
    sprintf(path, "voice/%03d/%03d_%02d.adp", character, character, voice);
    if (fexist(path))
        TEA_VoiceFilePlay(path, TEA_VOICEVOL, 0);
    OSReport("voice [%s] start \n", path);
}
