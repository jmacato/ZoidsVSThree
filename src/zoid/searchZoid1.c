#include "zoid3.h"

extern ZoidState Zoid[];

s32 searchZoid1(ZoidState *zoid, s32 index)
{
    ZoidState *other;
    s32 group;

    if (zoid == 0) {
        return 0;
    }
    group = zoid->slot;
    other = &Zoid[index];
    if (other == (void *)0) {
        return 0;
    }
    if (other->joint == (void *)0) {
        return 0;
    }
    if (group == other->slot) {
        return 0;
    }
    if (other->death_started != 0) {
        return 0;
    }
    if (other->stel_state == 2) {
        return 0;
    }
    if (zoid->target_visibility[index] == 0) {
        return 0;
    }
    if (zoid->search_range < zoid->distances[index]) {
        return 0;
    }
    return 1;
}
