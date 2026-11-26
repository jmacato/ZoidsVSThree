#include "zoid3.h"

typedef struct GameModeState3 {
    u8 reserved_00[4];
    s32 game_type;
    u8 reserved_08[0xC];
    s32 field_14;
} GameModeState3;

extern GameModeState3 GameMode;
extern ZoidState Zoid[16];
extern u8 sCamera[];
extern s32 searchEndVs4p(void);

void motWinSet4p(void)
{
    s32 i;
    s32 slot;
    s32 winner;

    winner = searchEndVs4p();
    GameMode.field_14 = winner;
    for (i = 0; i < 4; i++) {
        ZoidState *zoid = &Zoid[i];
        if (zoid->joint != 0) {
            slot = zoid->slot;
            if (slot == winner) {
                zoid->requested_action = 0x32;
                (sCamera + i * 0x590)[0x2F9] = 1;
            }
        }
    }
}
