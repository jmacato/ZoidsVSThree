#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);
extern void zdAtack1(ZoidState *zoid);

void zdAI_Atack1(s32 index)
{
    aiCmdReport("aiCmd-atack1 \n");
    if (index >= 0 && index < 16) {
        zdAtack1(&Zoid[index]);
    }
}
