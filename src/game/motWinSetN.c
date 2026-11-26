#include "zoid3.h"
#include "game_mode.h"

extern s32 winF;
extern s32 sCamNN;
extern u8 *mgP;
extern ZoidState Zoid[16];
extern u8 sCamera[];

void motWinSetN(void)
{
    s32 i;

    if (winF == 1) {
        Zoid[0].requested_action = 0x32;
        sCamera[0x2F9] = 1;
    }
    if (sCamNN == 1 && mgP != 0 && winF == 3) {
        if (((s8 *)mgP)[0x3093] != 0) {
            sCamera[0x2FA] = 1;
        }
    }
    if (winF == 3 && GameMode.game_type == 2) {
        Zoid[1].requested_action = 0x32;
        sCamera[0x889] = 1;
    }
    if (winF == 1 && GameMode.game_type == 5) {
        for (i = 0; i < 4; i++) {
            ZoidState *zoid = &Zoid[i];
            if (zoid->death_started == 0) {
                zoid->requested_action = 0x32;
                (sCamera + i * 0x590)[0x2F9] = 1;
            }
        }
    }
}
