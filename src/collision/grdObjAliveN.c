#include "types.h"
#include "joint.h"

typedef struct GroundObjMapInfo3 {
    u8 pad_00[0x10];
    s8 field_10;
} GroundObjMapInfo3;

typedef struct GroundObject3 {
    u8 pad_00[0x74];
    HSD_JObj *joint;
    s32 animation;
    u8 pad_7C[0xE0 - 0x7C];
    GroundObjMapInfo3 *map_info;
} GroundObject3;

extern GroundObject3 obj[50];

s32 grdObjAliveN(s32 index)
{
    GroundObject3 *object;
    GroundObjMapInfo3 *info;

    if (index < 0)
        return 0;
    if (index >= 50)
        return 0;
    object = &obj[index];
    if (object->joint == (void *)0)
        return 0;
    if (object->animation == 2)
        return 0;
    info = object->map_info;
    if (info->field_10 == 0)
        return 0;
    return 1;
}
