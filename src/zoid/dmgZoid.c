#include "zoid3.h"

void dmgZoid(ZoidState *zoid)
{
    void *control;

    if (zoid != 0 && zoid->joint != 0) {
        control = zoid->anim_data;
        if (zoid->requested_action >= 0x22 && zoid->requested_action <= 0x28 && zoid->action != 0) {
            zoid->jump_phase = 0;
            switch (zoid->action) {
            case 0x1:
            case 0x2:
            case 0xC:
            case 0xD:
            case 0xE:
            case 0xF:
            case 0x10:
            case 0x11:
            case 0x12:
            case 0x13:
            case 0x14:
            case 0x15:
            case 0x16:
            case 0x17:
            case 0x18:
            case 0x19:
            case 0x1A:
            case 0x29:
            case 0x2C:
            case 0x2D:
            case 0x2E:
            case 0x2F:
            case 0x30:
            case 0x34:
                zoid->action = 0;
                break;
            }
        }
    }
}
