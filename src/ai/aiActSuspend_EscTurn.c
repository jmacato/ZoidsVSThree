#include "types.h"

extern s32 aiDontMove(s32 index);
extern void aiActSuspend_zoid(s16 index);
extern void aiZoidRunMode(s16 index, s32 a, s32 b, s32 c);

s32 aiActSuspend_EscTurn(s16 index)
{
    register s32 dead = 0;

    if (aiDontMove(index)) {
        return 0;
    }
    aiActSuspend_zoid(index);
    aiZoidRunMode(index, -1, 0, -1);
    return 1;
}
