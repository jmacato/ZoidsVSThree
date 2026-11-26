#include "zoid3.h"
#include "zoid_ai.h"

typedef struct AiState3 {
    u8 reserved_00[0x98];
    s32 field_98;
    u8 reserved_9C[0x10];
    s32 field_AC;
} AiState3;

typedef struct MgState3 {
    u8 reserved_000[0x3250];
    s32 field_3250;
    s32 field_3254;
} MgState3;

extern MgState3 *mgP;
extern void aiCmdReport(const char *msg);

s32 zdAI_setHigh(s32 index, s32 mode)
{
    AiState3 *ai;
    ZoidState *zoid;
    f32 y;

    aiCmdReport("aiCmd-setHigh \n");
    if (index < 0) {
        return 1;
    }
    if (index >= 16) {
        return 1;
    }
    zoid = &Zoid[index];
    if (zoid->joint == 0) {
        return 1;
    }
    ai = (AiState3 *)zoid->ai;
    if (ai == 0) {
        return 1;
    }
    if (mode < 1) {
        return 0;
    }
    if (mode > 2) {
        return 0;
    }
    ai->field_98 = mode;
    ai->field_AC = 0;
    if (mode == 1) {
        y = zoid->position[1];
        if ((f32)mgP->field_3250 < y) {
            return 1;
        }
        if ((f32)mgP->field_3254 > y) {
            return 1;
        }
        ai->field_AC = 1;
        return 1;
    }
    return 1;
}
