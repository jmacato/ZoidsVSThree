#include "zoid3.h"

typedef struct ZoidDataV3 {
    u8 reserved_0000[0x66];
    s16 field_0066;
    u8 reserved_0068[0x7FC - 0x68];
} ZoidDataV3;

extern ZoidDataV3 Tea_zoiddat[];
extern void resetCoDmg(ZoidState *zoid);
extern void zdCalcCoDmg(ZoidState *zoid);

void ZoidInitParam(ZoidState *zoid)
{
    s32 type;

    if (zoid == 0) {
        return;
    }
    if (zoid->joint == 0) {
        return;
    }
    type = zoid->type;
    zoid->health = Tea_zoiddat[type].field_0066;
    zoid->field_0150 = zoid->health;
    zoid->max_health = zoid->health;
    zoid->field_1E54 = 0x384;
    zoid->field_1CB8 = 0;
    zoid->field_1A74 = 0;
    resetCoDmg(zoid);
    zdCalcCoDmg(zoid);
    zoid->requested_action = 0;
    zoid->action = 0;
    zoid->jump_phase = 0;
    zoid->death_pending = 0;
    zoid->death_started = 0;
    zoid->field_1E5C = 0;
    zoid->field_1E74 = 0;
    zoid->field_0148 = 0;
    zoid->field_014C = 0;
}
