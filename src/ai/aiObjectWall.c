#include "types.h"

typedef struct TeaAi {
    u8 b[0x160];
} TeaAi;

extern TeaAi Tea_aidat[];

extern f32 zdAI_goY(s32 index, s32 degrees, f32 distance);
extern s32 zdAI_goWall(s32 index, s32 distance, s32 degrees);

s32 aiObjectWall(s16 index, s16 degrees)
{
    s32 angle;

    angle = (s32)zdAI_goY(index, degrees, (f32)*(s16 *)&Tea_aidat[index].b[0x48]);
    if (angle < -*(s16 *)&Tea_aidat[index].b[0xD0]) {
        return 1;
    }
    if (angle > *(s16 *)&Tea_aidat[index].b[0xD0]) {
        return 1;
    }
    if (zdAI_goWall(index, *(s16 *)&Tea_aidat[index].b[0x48], degrees) == 1) {
        return 1;
    }
    return 0;
}
