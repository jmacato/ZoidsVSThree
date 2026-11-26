#include "types.h"

extern void *missBinB2;
extern void *binB2(void *pack, s32 index, s32 *size);
extern void *LoadArc2B(void *data, s32 size, char *name);

void *sMissileLoad(s32 index, char *name)
{
    void *data;
    s32 size;
    void *result;
    data = binB2(missBinB2, index, &size);
    if (data == 0) {
        return 0;
    }
    result = LoadArc2B(data, size, name);
    return result;
}
