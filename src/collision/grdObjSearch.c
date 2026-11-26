#include "types.h"
#include "joint.h"

typedef struct GroundObjMapInfo3 {
    u8 pad_00[0x18];
    s8 field_18;
} GroundObjMapInfo3;

typedef struct GroundObject3 {
    u8 pad_00[0xE0];
    GroundObjMapInfo3 *map_info;
} GroundObject3;

extern GroundObject3 obj[50];
extern s32 grdObjAliveN(s32 index);

s32 grdObjSearch(s32 index)
{
    GroundObject3 *object;
    GroundObjMapInfo3 *info;

    if (index < 0)
        return 0;
    if (index >= 50)
        return 0;
    object = &obj[index];
    if (grdObjAliveN(index) == 0)
        return 0;
    info = object->map_info;
    if (info->field_18 == 0)
        return 0;
    return 1;
}
