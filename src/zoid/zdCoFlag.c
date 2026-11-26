#include "zoid3.h"

s32 zdCoFlag(ZoidState *zoid, u8 flags)
{
    s32 result;

    result = 0;
    if ((flags & 1) && *(void **)(zoid->head_coobj + 0x18) != 0) {
        result = 1;
    }
    if ((flags & 2) && *(void **)(zoid->neck_coobj + 0x18) != 0) {
        result = 1;
    }
    if ((flags & 4) && *(void **)(zoid->bust_coobj + 0x18) != 0) {
        result = 1;
    }
    if ((flags & 8) && *(void **)(zoid->hip_coobj + 0x18) != 0) {
        result = 1;
    }
    if ((flags & 0x80) && zoid->field_1C48 != 0 && zoid->ground_normal_count != 0) {
        result = 1;
    }
    return result;
}
