#include "zoid3.h"

typedef struct ZdLinearPose {
    struct ZdLinearPose *next;
    struct ZdLinearPose *child;
    u8 reserved_08[4];
    f32 rotation[3];
    u8 reserved_18[4];
    f32 scale[3];
    f32 translation[3];
    f32 matrix[3][4];
} ZdLinearPose;

extern void sGlobal2Local(HSD_JObj *joint);

void zdLinearAnimAllBak1(HSD_JObj *dst, ZdLinearPose *src)
{
    s32 i;
    s32 j;

    if (dst == (void *)0)
        return;
    if (src == (void *)0)
        return;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++)
            dst->matrix[i][j] = src->matrix[i][j];
    }
    dst->translation.x = src->translation[0];
    dst->translation.y = src->translation[1];
    dst->translation.z = src->translation[2];
    dst->scale.x = src->scale[0];
    dst->scale.y = src->scale[1];
    dst->scale.z = src->scale[2];
    dst->rotation[0] = src->rotation[0];
    dst->rotation[1] = src->rotation[1];
    dst->rotation[2] = src->rotation[2];
    sGlobal2Local(dst);
    dst->translation.x = src->translation[0];
    dst->translation.y = src->translation[1];
    dst->translation.z = src->translation[2];
    dst->rotation[0] = src->rotation[0];
    dst->rotation[1] = src->rotation[1];
    dst->rotation[2] = src->rotation[2];
    dst->scale.x = src->scale[0];
    dst->scale.y = src->scale[1];
    dst->scale.z = src->scale[2];
    dst = dst->child;
    src = src->child;
    while (dst != 0) {
        if (dst == (void *)0 || src == (void *)0)
            return;
        zdLinearAnimAllBak1(dst, src);
        dst = dst->next;
        src = src->next;
    }
}
