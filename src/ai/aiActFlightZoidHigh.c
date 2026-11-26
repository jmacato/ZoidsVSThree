#include "types.h"

typedef struct TeaAi {
    u8 b[0x160];
} TeaAi;

extern TeaAi Tea_aidat[];

extern void zdAI_setHigh(s32 index, s32 flag);

void aiActFlightZoidHigh(s16 index)
{
    if (*(s8 *)&Tea_aidat[index].b[0xDC]) {
        zdAI_setHigh(index, 1);
    }
}
