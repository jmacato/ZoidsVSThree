#include "zoid3.h"

extern u8 Tea_zoiddat[];

s32 zdAtkZdZdDmgHp(ZoidState *zoid)
{
    s32 idx;
    s32 dmg;
    s32 type;

    dmg = 5;
    idx = zoid->attack_index;
    type = zoid->type;
    if (idx >= 0 && idx <= 11) {
        dmg = *(s16 *)(Tea_zoiddat + type * 0x7fc + idx * 2 + 0x756);
    } else {
        dmg = 10;
    }
    return dmg;
}
