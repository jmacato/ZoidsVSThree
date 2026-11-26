#include "types.h"

typedef struct TeaAi {
    u8 b[0x160];
} TeaAi;

extern TeaAi Tea_aidat[];

s32 aiEnemySupplement_AfterMove(s16 index)
{
    if (*(s8 *)&Tea_aidat[index].b[0x25]) {
        return 1;
    }
    if (*(s8 *)&Tea_aidat[index].b[0x27]) {
        return 1;
    }
    if (*(s8 *)&Tea_aidat[index].b[0x26]) {
        return 1;
    }
    return 0;
}
