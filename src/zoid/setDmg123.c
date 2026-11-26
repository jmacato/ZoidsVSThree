#include "zoid3.h"

void setDmg123(ZoidState *src, ZoidState *dst, s32 index, s32 mode)
{
    s32 kind;
    u8 *p;
    s32 a;
    s32 b;
    u16 *slider;
    s32 flag;
    s32 type;
    s32 prev_type;

    if (src == 0)
        return;
    if (dst == 0)
        return;
    if (src->joint == 0)
        return;
    if (dst->joint == 0)
        return;
    if (index < 0)
        return;
    if (index > 11)
        return;
    slider = src->slider_info;
    if (slider == 0)
        return;
    a = src->field_20C0;
    b = dst->field_20C0;
    type = src->type;
    p = (u8 *)slider + index * 6 + 0x6ba;
    prev_type = dst->type;
    if (a * 2 < b) {
        if (mode != 0)
            kind = (s8)p[2];
        else
            kind = (s8)p[5];
    } else if (a / 2 > b) {
        if (mode != 0)
            kind = (s8)p[0];
        else
            kind = (s8)p[3];
    } else {
        if (mode != 0)
            kind = (s8)p[1];
        else
            kind = (s8)p[4];
    }
    if (kind == 0)
        return;
    dst->field_1E64 = type;
    dst->field_1E68 = src->person;
    flag = 1;
    if (!(dst->field_1E5C & 4) && kind == 1)
        flag = 0;
    if (dst->health == 0)
        dst->field_1E5C |= 4;
    if (kind == 1)
        dst->field_1E5C |= 2;
    if (kind == 2)
        dst->field_1E5C |= 4;
    if (flag != 0)
        dst->field_1E60 = src->index;
}
