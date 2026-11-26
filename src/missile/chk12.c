#include "types.h"
#include "jobj.h"

typedef struct CoObj3 {
    HSD_JObj *joint;
    u8 pad_04[4];
    f32 minimum_scale;
} CoObj3;

extern f32 sLenJobj(HSD_JObj *joint, HSD_JObj *target);

s32 chk12(CoObj3 *object, HSD_JObj *target, f32 range)
{
    HSD_JObj *joint;
    f32 length;
    if (object == 0)
        return 0;
    joint = object->joint;
    if (joint == 0)
        return 0;
    if (target == 0)
        return 0;
    length = sLenJobj(joint, target);
    if (length > range + object->minimum_scale)
        return 0;
    return 1;
}
