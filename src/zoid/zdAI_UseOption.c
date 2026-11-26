#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);

typedef struct AiState3 {
    u8 pad_00[0x94];
    s32 field_94;
} AiState3;

void zdAI_UseOption(s32 index)
{
    ZoidState *zoid;
    AiState3 *ai;

    aiCmdReport("aiCmd-useOption \n");
    if (index < 0) {
        return;
    }
    if (index >= 16) {
        return;
    }
    zoid = &Zoid[index];
    if (zoid->joint == (void *)0) {
        return;
    }
    ai = (AiState3 *)zoid->ai;
    if (ai != 0) {
        ai->field_94 = 1;
    }
}
