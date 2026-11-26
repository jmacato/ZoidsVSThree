#include "zoid3.h"

extern s32 GetVsBpLimit(void);
extern s32 zdCalcFarm(ZoidState *zoid, s32 index, s32 a, s32 b);

s32 chkMapBP(s32 index)
{
    s32 limit;
    ZoidState *zoid;
    limit = GetVsBpLimit();
    if (limit == 0)
        return 0;
    zoid = &Zoid[index];
    if (zoid->joint == (void *)0)
        zoid->joint = (void *)1;
    zdCalcFarm(zoid, index, -1, -2);
    if (zoid->joint == (void *)1)
        zoid->joint = (void *)0;
    if (zoid->field_20F8 > limit)
        return 1;
    return 0;
}
