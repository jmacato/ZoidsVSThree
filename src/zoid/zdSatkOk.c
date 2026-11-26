#include "zoid3.h"

s32 zdSatkOk(ZoidState *zoid)
{
    s32 anim;
    s32 mode;

    if (zoid == 0)
        return 0;
    if (zoid->joint == 0)
        return 0;
    if (zoid->weapon_mount == 0x13 && *(s32 *)((u8 *)zoid + 0x17A4) == 2)
        return 1;
    mode = zoid->action;
    switch (mode) {
    case 1:
    case 2:
    case 23:
    case 24:
    case 25:
    case 26:
    case 52:
        return 0;
    }
    anim = zoid->current_animation;
    switch (anim) {
    case 4:
    case 5:
    case 8:
        return 0;
    }
    if (zoid->field_1C90[2] > 0.1 || zoid->field_1C90[0] > 0.1)
        return 0;
    if (zoid->action != 0)
        return 0;
    if (zoid->field_1DAC != 0)
        return 0;
    if (zoid->field_1DB0 <= 0xF)
        return 0;
    if (zoid->field_1DD4 != 0)
        return 0;
    return 1;
}
