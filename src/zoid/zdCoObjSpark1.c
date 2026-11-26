#include "zoid3.h"

extern u32 vsyncN;
extern void sEffectSet(s32 type, s32 mode, f32 *position, HSD_JObj *source, ZoidState *zoid);

typedef struct SparkCoObj {
    HSD_JObj *source;
    u8 pad_0004[0x68];
    s32 count;
    s32 period;
} SparkCoObj;

void zdCoObjSpark1(ZoidState *zoid, SparkCoObj *obj, s32 phase)
{
    s32 count;
    s32 pct;
    s32 rem;
    s32 period;

    rem = vsyncN % 20;
    if (rem == phase) {
        period = obj->period;
        count = obj->count;
        if (period != 0) {
            pct = count * 100 / period;
            if (pct <= 50) {
                if (obj->source != 0) {
                    sEffectSet(0x28, 2, 0, obj->source, zoid);
                }
            }
        }
    }
}
