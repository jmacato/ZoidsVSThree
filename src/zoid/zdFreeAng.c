#include "zoid3.h"

extern void angLimit(f32 *angle);
extern f32 zdFreeLen(ZoidState *zoid, f32 length, f32 angle);

f32 zdFreeAng(ZoidState *zoid, f32 length)
{
    s32 count;
    s32 index;
    s32 i;
    f32 best_value;
    f32 angle;

    if (zoid == 0) {
        return 0.0f;
    }
    if (zoid->joint == 0) {
        return 0.0f;
    }
    count = zoid->field_2060;
    if (count <= 0) {
        for (i = 0; i < 24; i++) {
            zoid->field_1FF8[i] = 0.0f;
        }
        zoid->field_2060 = 1;
        return 100.0f;
    } else {
        index = count - 1;
        angle = 2.0 * (3.1415926 * (f32)(15.0 * (f32)index)) / 360.0;
        zoid->field_1FF8[index] = zdFreeLen(zoid, length, angle);
        if (count != 24) {
            zoid->field_2060 = zoid->field_2060 + 1;
            return 100.0f;
        } else {
            zoid->field_2060 = -1;
            index = 0;
            best_value = 0.0f;
            for (i = 0; i < 24; i++) {
                if (best_value >= zoid->field_1FF8[i]) {
                } else {
                    best_value = zoid->field_1FF8[i];
                    index = i;
                }
            }
            angle = 2.0 * (3.1415926 * (f32)(15.0 * (f32)index)) / 360.0;
            zoid->field_2058 = angle;
            zoid->field_205C = zoid->heading + angle;
            angLimit(&zoid->field_205C);
            return angle;
        }
    }
}
