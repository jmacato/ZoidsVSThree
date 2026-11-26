#include "zoid3.h"

extern void zdLimitHigh(ZoidState *zoid);

void flyZoid(ZoidState *zoid)
{
    u8 *control;

    if (zoid != 0 && zoid->joint != 0) {
        control = zoid->anim_data;
        zdLimitHigh(zoid);
        if (*(s32 *)(control + 0xF8) == 1) {
            switch (zoid->requested_action) {
            case 0xC:
            case 0x2C:
                zoid->requested_action = 0;
                break;
            }
        }
    }
}
