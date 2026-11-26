#include "zoid3.h"

s32 zdLakkaTest2(ZoidState *zoid)
{
    if (zoid == (void *)0) {
        return 0;
    }
    if (zoid->joint == (void *)0) {
        return 0;
    }
    if ((zoid->movement_flags & 3) != 2) {
        return 0;
    }
    if (zoid->ground_normal_count != 0) {
        return 0;
    }
    if (*(void **)(zoid->r_arm2_coobj + 0x18) != 0) {
        return 0;
    }
    if (*(void **)(zoid->r_arm1_coobj + 0x18) != 0) {
        return 0;
    }
    if (*(void **)(zoid->l_arm2_coobj + 0x18) != 0) {
        return 0;
    }
    if (*(void **)(zoid->l_arm1_coobj + 0x18) != 0) {
        return 0;
    }
    if (*(void **)(zoid->r_leg2_coobj + 0x18) != 0) {
        return 0;
    }
    if (*(void **)(zoid->r_leg1_coobj + 0x18) != 0) {
        return 0;
    }
    if (*(void **)(zoid->l_leg2_coobj + 0x18) != 0) {
        return 0;
    }
    if (*(void **)(zoid->l_leg1_coobj + 0x18) != 0) {
        return 0;
    }
    return 1;
}
