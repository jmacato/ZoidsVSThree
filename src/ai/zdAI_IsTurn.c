#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);

s32 zdAI_IsTurn(s32 index)
{
    ZoidState *zoid;
    ZoidAIState *ai;
    s32 mode;

    aiCmdReport("aiCmd-IsTurn \n");
    if (index < 0) {
        return 0;
    }
    if (index >= 16) {
        return 0;
    }
    zoid = &Zoid[index];
    if (zoid->joint == (void *)0) {
        return 0;
    }
    ai = zoid->ai;
    if (ai == 0) {
        return 0;
    }
    mode = ai->mode;
    switch (mode) {
    case 4:
    case 5:
    case 6:
        return 1;
    }
    return 0;
}
