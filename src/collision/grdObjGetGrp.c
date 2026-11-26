#include "joint.h"

typedef struct GroundObject3 {
    HSD_JObj *source;
    f32 position[3];
    f32 matrix[3][4];
    f32 inverse[3][4];
    s32 archive_slot;
    HSD_JObj *joint;
    s32 animation;
    s32 health;
    u8 reserved_080[0x8C - 0x80];
    s32 group;
    u8 reserved_090[0xE4 - 0x90];
} GroundObject3;

extern GroundObject3 obj[50];
extern s32 objNow;

s32 grdObjGetGrp(s32 index)
{
    GroundObject3 *object;

    if (index < 0)
        return -1;
    if (index >= 50)
        return -1;
    object = &obj[index];
    if (object->joint == (void *)0)
        return -1;
    return object->group;
}
