#include "types.h"

typedef struct TeaAi {
    u8 b[0x160];
} TeaAi;

extern TeaAi Tea_aidat[];

s32 aiDontMove(s32 index)
{
    if ((s32)Tea_aidat[index].b[0x38] == 1 && *(s16 *)&Tea_aidat[index].b[0x3A] == 0) {
        return 1;
    }
    return 0;
}
