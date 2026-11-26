#include "joint.h"

extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);

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

HSD_JObj *grdObjGetJObj(s32 index)
{
    register HSD_JObj *joint;
    GroundObject3 *object;

    if (index < 0)
        return 0;
    if (index >= 50)
        return 0;
    object = &obj[index];
    joint = object->joint;
    return GetChild(joint, 0, 2, -1, -1, -1);
}
