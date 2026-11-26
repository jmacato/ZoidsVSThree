#include "types.h"

typedef struct AiWallState {
    u8 reserved_00[0x34];
    s16 field_34;
    u8 reserved_36[0x70 - 0x36];
    s16 field_70;
    u8 reserved_72[0xF0 - 0x72];
} AiWallState;

extern AiWallState aiDat[16];
extern s32 aiObjectWall(s16 index, s16 degrees);

s16 aiNoWallSetPar(s16 index, s16 step)
{
    s16 first = 0;
    s16 second = 0;
    s16 angle = 0;
    s32 result = 0;

    for (angle = 0; angle < 190; angle += step) {
        if (aiObjectWall(index, angle) == 0) {
            return angle;
        }
        if (aiObjectWall(index, -angle) == 0) {
            return -angle;
        }
    }
    aiDat[index].field_70 = 0;
    aiDat[index].field_34 = 0;
    return 180;
}
