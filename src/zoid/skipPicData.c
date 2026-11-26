#include "zoid3.h"

#define NULL 0

u8 *skipPicData(u8 *data)
{
    s32 alpha;
    u8 chained;
    s32 run;
    s32 i;
    s32 x;
    u16 width;
    u32 magic;
    u16 height;
    s32 y;

    magic = *(u32 *)data;
    data += 4;
    if (magic != 0x5380F634) {
        return NULL;
    }
    width = *(u16 *)(data + 88);
    height = *(u16 *)(data + 90);
    data += 100;
    alpha = 0;
    do {
        chained = data[0];
        alpha |= data[3];
        data += 4;
    } while (chained != 0);
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x += run) {
            run = *data++;
            if (run == 128) {
                run = *(u16 *)data;
                data += 5;
            } else if (run > 127) {
                run -= 127;
                data += 3;
            } else {
                run++;
                for (i = 0; i < run; i++) {
                    data += 3;
                }
            }
        }
        if (alpha & 0x10) {
            for (x = 0; x < width; x += run) {
                run = *data++;
                if (run == 128) {
                    run = *(u16 *)data;
                    data += 3;
                } else if (run > 127) {
                    run -= 127;
                    data += 1;
                } else {
                    run++;
                    for (i = 0; i < run; i++) {
                        data += 1;
                    }
                }
            }
        }
    }
    return data;
}
