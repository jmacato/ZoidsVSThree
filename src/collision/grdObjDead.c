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

s32 grdObjDead(s32 type)
{
    s32 count;
    s32 i;
    GroundObject3 *object;

    i = 0;
    count = 0;
    for (; i < 50; i++) {
        object = &obj[i];
        if (object->joint != (void *)0 && object->archive_slot == type && object->animation == 2)
            count++;
    }
    return count;
}
