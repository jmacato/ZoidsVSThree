#include "zoid3.h"

s32 addPolyList(s32 count, void *poly, void **list)
{
    s32 i;

    if (poly == (void *)0) {
        return count;
    }
    if (count >= 100) {
        return count;
    }
    for (i = 0; i < count; i++) {
        if (list[i] == poly) {
            break;
        }
    }
    if (i != count) {
        return count;
    }
    list[count++] = poly;
    return count;
}
