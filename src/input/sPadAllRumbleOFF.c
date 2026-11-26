#include "types.h"

typedef struct PadState3 {
    s8 connected;
    s8 previous_connected;
    u8 reserved_02[2];
    u32 buttons;
    s32 field_08;
    s32 reset_hold_frames;
    u8 reserved_10[0x74];
    s8 rumble;
    s8 previous_rumble;
    u8 reserved_86[2];
} PadState3;

extern PadState3 sPad[4];
extern void HSD_PadRumbleOffN(u8 channel);

void sPadAllRumbleOFF(void)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        sPad[i].rumble = 0;
        sPad[i].previous_rumble = 0;
        HSD_PadRumbleOffN((u8)i);
    }
}
