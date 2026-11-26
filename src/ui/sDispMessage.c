#include "types.h"

extern void sDispMessageMe(s32 player);
extern void sDispContinue(s32 player);

void sDispMessage(s32 player)
{
    sDispMessageMe(player);
    sDispContinue(player);
}
