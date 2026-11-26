#include "zoid3.h"
#include "zoid_ai.h"

typedef struct AiState3 {
    u8 reserved_00[0x48];
    s32 target_index;
    u8 reserved_4C[0x4C];
    s32 field_98;
    f32 field_9C;
    u8 reserved_A0[0xC];
    s32 field_AC;
} AiState3;

typedef struct MgState3 {
    u8 reserved_000[0x3250];
    s32 field_3250;
    s32 field_3254;
} MgState3;

extern MgState3 *mgP;
extern int sprintf(char *s, const char *format, ...);
extern void aiReport(s32 level, const char *msg);
extern f32 HSD_Randf(void);

inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

void calcHigh(ZoidState *zoid, AiState3 *ai)
{
    char buf[0x100];
    ZoidState *other;
    s32 target;
    f32 t;
    f32 y;
    f32 oy;

    if (zoid->field_0170 == 0) {
        return;
    }
    if (ai->field_98 < 1 || ai->field_98 > 2) {
        ai->field_98 = 0;
        ai->field_AC = -1;
        ai->field_98 = 1;
        return;
    }
    sprintf(buf, "calcHigh : setY=%f NH=%d NL=%d\n", ai->field_9C, mgP->field_3250, mgP->field_3254);
    aiReport(0, buf);
    y = zoid->position[1];
    if (ai->field_98 == 1) {
        if (mgP == 0) {
            ai->field_98 = 1;
            ai->field_AC = -1;
            return;
        }
        if ((f32)mgP->field_3250 < y || (f32)mgP->field_3254 > y) {
            t = (f32)(mgP->field_3250 - mgP->field_3254);
            oy = t * HSD_Randf() + (f32)mgP->field_3254;
            ai->field_9C = oy;
            ai->field_AC = 0;
        } else {
            ai->field_AC = 1;
        }
        return;
    }
    other = 0;
    target = ai->target_index;
    if (target >= 0 && target < 16) {
        other = &Zoid[target];
    }
    if (other != 0 && other->slot == zoid->slot) {
        other = 0;
    }
    if (other != 0 && other->joint == 0) {
        other = 0;
    }
    if (other == 0) {
        target = zoid->target_slot;
        if (target >= 0 && target < 16) {
            other = &Zoid[target];
        }
        if (other != 0 && other->slot == zoid->slot) {
            other = 0;
        }
        if (other != 0 && other->joint == 0) {
            other = 0;
        }
    }
    if (other == 0) {
        ai->field_98 = 2;
        ai->field_AC = -1;
        return;
    }
    oy = other->position[1];
    ai->field_9C = oy + 5.0f;
    if (oy + 1.0f < y || oy - 1.0f > y) {
        ai->field_AC = 0;
    } else {
        ai->field_AC = 2;
    }
}
