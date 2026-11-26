#include "zoid3.h"

extern void zdWp1SliderN(ZoidState *zoid, s32 index, s32 value);

s32 zdWp1Slider(ZoidState *zoid, s32 index, s32 flag)
{
    s32 value;
    s32 count;

    if (zoid == 0) {
        return 0;
    }
    if (zoid->joint == 0) {
        return 0;
    }
    if (zoid->slider_info == 0) {
        return 0;
    }
    count = zoid->slider_info[0];
    if (count == 0) {
        return 0;
    }
    value = zoid->slider_positions[index];
    if (flag != 0) {
        if (value == count) {
            return 0;
        }
        value += 1;
        if (value > count) {
            value = count;
        }
    } else {
        if (value == 0) {
            return 0;
        }
        value -= 1;
        if (value < 0) {
            value = 0;
        }
    }
    zdWp1SliderN(zoid, index, value);
    return 1;
}
