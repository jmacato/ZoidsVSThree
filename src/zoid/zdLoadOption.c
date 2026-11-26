#pragma readonly_strings on
#include "zoid3.h"
#include "game_part_data.h"

extern void OSReport(const char *format, ...);
extern void zdLoadOption1(ZoidState *zoid, s32 part);
extern void zdLoadOption2(ZoidState *zoid, s32 part);
extern void zdLoadOption3(ZoidState *zoid);
extern void zdLoadOption4(ZoidState *zoid);
extern void zdLoadOption5(ZoidState *zoid);
extern void zdLoadOption6(ZoidState *zoid, s32 part);

void zdLoadOption(ZoidState *zoid, s32 part)
{
    u32 flags;
    s32 type;

    if (part >= 1 && zoid != (void *)0 && zoid->joint != (void *)0) {
        zoid->field_1EA0 = part;
        flags = Tea_partsdat[part].flags;
        zoid->booster_on = 0;
        zoid->field_016C = 0;
        type = ZOID_OPTION_NONE;
        if (flags & PART_FLAG_CAMOUFLAGE)
            type = ZOID_OPTION_CAMOUFLAGE;
        if (flags & PART_FLAG_BOOSTER)
            type = ZOID_OPTION_BOOSTER;
        if (flags & PART_FLAG_SHIELD)
            type = ZOID_OPTION_SHIELD;
        if (flags & PART_FLAG_MINE)
            type = ZOID_OPTION_MINE;
        if (flags & PART_FLAG_SMOKE)
            type = ZOID_OPTION_SMOKE;
        if (flags & 0x200)
            type = 6;
        zoid->option_type = type;
        if (zoid->option_type == ZOID_OPTION_SHIELD)
            zdLoadOption1(zoid, part);
        if (zoid->option_type == ZOID_OPTION_BOOSTER)
            zdLoadOption2(zoid, part);
        if (zoid->option_type == ZOID_OPTION_CAMOUFLAGE)
            zdLoadOption3(zoid);
        if (zoid->option_type == ZOID_OPTION_SMOKE)
            zdLoadOption4(zoid);
        if (zoid->option_type == ZOID_OPTION_MINE)
            zdLoadOption5(zoid);
        if (zoid->option_type == 6)
            zdLoadOption6(zoid, part);
        OSReport("option set!-%d----- [no.%d] ----zN=%d-----\n", part, type, zoid->index);
    }
}
