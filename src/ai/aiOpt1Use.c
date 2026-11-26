#include "types.h"

typedef struct TeaAi {
    u8 b[0x160];
} TeaAi;

extern TeaAi Tea_aidat[];

extern void zdAI_UseOption(s32 index);

void aiOpt1Use(s16 index)
{
    if ((s32)Tea_aidat[index].b[0xCB] == 1) {
        zdAI_UseOption(index);
    }
}
