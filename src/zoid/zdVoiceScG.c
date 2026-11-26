#include "zoid3.h"

extern s32 gameEndF;
extern void zdVoiceSc(ZoidState *zoid, s32 voice);

void zdVoiceScG(ZoidState *zoid, s32 voice)
{
    if (gameEndF == 0) {
        zdVoiceSc(zoid, voice);
    }
}
