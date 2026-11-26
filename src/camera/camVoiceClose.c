#include "types.h"

extern char vcSeekStr[];
extern s32 vcSeekMode;
extern u8 vcSeekIfo[];
extern void sReadPre(void);
extern void HSD_AudioStreamVolume(s32 volume);
extern void HSD_AudioStreamStop(s32 stream);
extern s32 DVDClose(void *fileInfo);

void camVoiceClose(void)
{
    sReadPre();
    HSD_AudioStreamVolume(0);
    HSD_AudioStreamStop(0);
    vcSeekStr[0] = 0;
    if (vcSeekMode != 0) {
        DVDClose(vcSeekIfo);
        vcSeekMode = 0;
    }
}
