#include "types.h"

typedef struct TeaAi {
    u8 b[0x160];
} TeaAi;

typedef struct AiData3 {
    u8 b[0xF0];
} AiData3;

extern TeaAi Tea_aidat[];
extern AiData3 aiDat[];

extern void zdAI_setHigh(s32 index, s32 flag);

void aiActFlightZoidLow(s16 index)
{
    if (*(s8 *)&Tea_aidat[index].b[0xDC]) {
        if (*(s32 *)&aiDat[index].b[0xC0] != 0) {
            zdAI_setHigh(index, 2);
        }
    }
}
