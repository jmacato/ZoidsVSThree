#include "zoid3.h"

extern f32 zdCoCoMinR0(u8 *a, u8 *b, Vec3 *direction, void *c, void *d);
extern f32 sLenPoint3dR(Vec3 *point);
extern f32 zdColPosY(f32 *position, u16 *selector);

f32 zdCoCoMinR(ZoidState *a, ZoidState *b)
{
    f32 distance[6][6];
    u8 *parts_a[9];
    u8 *parts_b[9];
    Vec3 direction;
    Vec3 push;
    u16 sel_a;
    u16 sel_b;
    u8 *part_a;
    u8 *part_b;
    u8 *info_a;
    u8 *info_b;
    u8 *ctrl_a;
    u8 *ctrl_b;
    void *vec_a;
    void *vec_b;
    s32 flag_a;
    s32 flag_b;
    s32 i;
    s32 j;
    s32 k;
    f32 d;
    f32 max;
    f32 d2;
    f32 plus;
    f32 minus;
    f32 mass_a;
    f32 mass_b;
    f32 total;

    part_a = 0;
    part_b = 0;
    info_a = (u8 *)a->slider_info;
    ctrl_a = a->field_2090;
    ctrl_b = b->field_2090;
    vec_a = *(void **)(ctrl_a + 0x150);
    vec_b = *(void **)(ctrl_b + 0x150);
    info_b = (u8 *)b->slider_info;
    if (info_a != 0) {
        if (info_a[0x70D] == 0)
            part_a = a->hip_coobj;
        if (info_a[0x70D] == 2)
            part_a = a->bust_coobj;
    }
    if (info_b != 0) {
        if (info_b[0x70D] == 0)
            part_b = b->hip_coobj;
        if (info_b[0x70D] == 2)
            part_b = b->bust_coobj;
    }
    flag_a = 0;
    if (part_a != 0 && *(u32 *)(part_a + 0x18) != 0)
        flag_a = 1;
    flag_b = 0;
    if (part_b != 0 && *(u32 *)(part_b + 0x18) != 0)
        flag_b = 1;
    parts_a[0] = a->hip_coobj;
    parts_b[0] = b->hip_coobj;
    parts_a[1] = a->bust_coobj;
    parts_b[1] = b->bust_coobj;
    parts_a[2] = a->neck_coobj;
    parts_b[2] = b->neck_coobj;
    parts_a[3] = a->r_leg1_coobj;
    parts_b[3] = b->r_leg1_coobj;
    parts_a[4] = a->l_leg1_coobj;
    parts_b[4] = b->l_leg1_coobj;
    parts_a[5] = a->head_coobj;
    parts_b[5] = b->head_coobj;
    for (k = 0; k < 3; k++)
        (&push.x)[k] = 0.0f;
    max = -1.0f;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 6; j++) {
            d = zdCoCoMinR0(parts_a[i], parts_b[j], &direction, vec_a, vec_b);
            distance[i][j] = d;
            if (0.0f != d && (-1.0f == max || max < d)) {
                max = d;
                for (k = 0; k < 3; k++)
                    (&push.x)[k] = (&direction.x)[k];
            }
        }
    }
    if (flag_a != 0 && flag_b != 0)
        return 0.0f;
    if (max <= 0.0f)
        return 0.0f;
    d = sLenPoint3dR(&push);
    if (d <= 0.01)
        return 0.0f;
    if (max > 1.0) {
        max = 1.0f;
        for (k = 0; k < 3; k++)
            (&push.x)[k] *= max / d;
    }
    mass_a = a->field_20C0;
    mass_b = b->field_20C0;
    if (a->death_started != 0)
        mass_a *= 10.0f;
    if (b->death_started != 0)
        mass_b *= 10.0f;
    total = mass_a + mass_b;
    if (total <= 0.1) {
        mass_a = 1.0f;
        mass_b = 1.0f;
        total = 2.0f;
    }
    if (flag_a != 0) {
        mass_a = 0.0f;
        mass_b = 1.0f;
        total = 1.0f;
    }
    if (flag_b != 0) {
        mass_a = 1.0f;
        mass_b = 0.0f;
        total = 1.0f;
    }
    mass_a = mass_a / total;
    mass_b = mass_b / total;
    for (k = 0; k < 3; k++) {
        d2 = (&push.x)[k];
        plus = d2;
        minus = d2;
        a->position[k] += plus * mass_b;
        b->position[k] -= minus * mass_a;
    }
    plus = zdColPosY(a->position, &sel_a);
    if (a->position[1] < plus)
        a->position[1] = plus;
    minus = zdColPosY(b->position, &sel_b);
    if (b->position[1] < minus)
        b->position[1] = minus;
    return max;
}
