#include "zoid3.h"
#include "game_mode.h"

extern void zdVoiceScG(ZoidState *zoid, s32 id);

void zdWeaponFireVoice(ZoidState *zoid)
{
    if (zoid != 0 && zoid->joint != 0 && zoid->field_1C4C == 0) {
        if (GameMode.game_type == 9) {
            return;
        }
        if (GameMode.game_type == 1 || GameMode.game_type == 4) {
            if (zoid != &Zoid[0]) {
                return;
            }
        }
        zoid->field_1C4C = 300;
        zdVoiceScG(zoid, 3);
    }
}
