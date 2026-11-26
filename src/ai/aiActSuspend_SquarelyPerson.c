#include "types.h"

typedef struct TeaAi {
    u8 b[0x160];
} TeaAi;

typedef struct AiData3 {
    u8 b[0xF0];
} AiData3;

extern TeaAi Tea_aidat[];
extern AiData3 aiDat[];

extern s64 OSGetTime(void);
extern u32 __OSBusClock : 0x800000F8;
extern s32 aiDontMove(s32 index);
extern void aiWepAtck(s16 index);

s32 aiActSuspend_SquarelyPerson(s16 index, s16 param)
{
    s32 result = 0;
    s16 rnd;
    s16 copy;

    rnd = (s16)(((OSGetTime() * 8) / ((__OSBusClock / 4) / 125000)) % 360);
    copy = param;
    if (*(s32 *)&aiDat[index].b[0xC0] == 0) {
        return 0;
    }
    if (*(s32 *)&aiDat[index].b[0x54] == 0) {
        return 0;
    }
    if (*(s8 *)&Tea_aidat[index].b[0x0C]) {
        aiWepAtck(index);
    }
    if (aiDontMove(index)) {
        return 0;
    }
    return result;
}
