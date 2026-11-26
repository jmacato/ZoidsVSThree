#include "zoid3.h"
#include "types.h"
#include "joint.h"

typedef struct GroundObjMapInfo3 {
    u8 pad_00[0x08];
    u16 field_08;
    u8 pad_0A[0x15 - 0x0A];
    s8 field_15;
    u8 pad_16[0x32 - 0x16];
    u16 field_32;
    u8 pad_34[0x38 - 0x34];
    s16 field_38;
} GroundObjMapInfo3;

typedef struct GroundObject3 {
    u8 pad_00[0x74];
    HSD_JObj *joint;
    s32 animation;
    u8 pad_7C[0x84 - 0x7C];
    s32 field_84;
    s32 field_88;
    u8 pad_8C[0x94 - 0x8C];
    f32 field_94;
    u8 pad_98[0x9C - 0x98];
    f32 field_9C;
    s32 zoid_index;
    u8 pad_A4[0xE0 - 0xA4];
    GroundObjMapInfo3 *map_info;
} GroundObject3;

extern s32 gameStartF;
extern void OSReport(const char *format, ...);
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void sMissileSet(s32 owner, ZoidState *target_zoid, s32 target_missile, s32 index, f32 mtx[3][4], u16 bullet, s16 extra);

static inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

void grdObjFire(GroundObject3 *object)
{
    f32 matrix[3][4];
    GroundObjMapInfo3 *info;
    ZoidState *zoid;
    HSD_JObj *child;
    s32 index;
    s32 extra;
    s32 k;
    s32 i;
    s32 j;

    info = object->map_info;
    child = GetChild(object->joint, 0, 0, 0, 0, -1);
    if (child == 0)
        OSReport("fire ========NULL\n");
    if (child == 0)
        return;
    if (info == 0)
        return;
    if (gameStartF != 0)
        return;
    if (object->animation != 0)
        return;
    if (object->field_84 != 0)
        object->field_84--;
    if (object->field_84 != 0)
        return;
    if (object->field_88 == 0)
        return;
    index = object->zoid_index;
    if (index == -1)
        return;
    zoid = &Zoid[index];
    if (zoid->joint == 0)
        return;
    if (zoid->death_started != 0)
        return;
    if (absf(object->field_94) > 0.08726646111111111)
        return;
    if (info->field_15 != 0) {
        if (absf(object->field_9C) > 0.08726646111111111)
            return;
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++)
            matrix[i][j] = child->matrix[i][j];
    }
    extra = info->field_38;
    sMissileSet(0, zoid, 0, -1, matrix, info->field_08, extra);
    object->field_88--;
    object->field_84 = info->field_32;
    for (k = 0; k < 20; k++) {
        if (object->field_88 == 0)
            return;
        child = GetChild(object->joint, 0, 0, 0, 0, k);
        if (child == 0)
            return;
        object->field_88--;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 4; j++)
                matrix[i][j] = child->matrix[i][j];
        }
        sMissileSet(0, zoid, 0, -1, matrix, info->field_08, extra);
    }
}
