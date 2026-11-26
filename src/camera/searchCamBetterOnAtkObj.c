#include "zoid3.h"

typedef struct CameraState3 {
    u8 pad_000[0x30];
    s32 mount_index;
    u8 pad_034[0x18];
    s8 mount_blocked[20];
    s8 mount_hidden[20];
} CameraState3;

extern f32 *grdObjGetPt(s32 id);

s32 searchCamBetterOnAtkObj(CameraState3 *camera, ZoidState *zoid, s32 slot)
{
    s32 mount;
    f32 *point;
    f32 zero;
    s32 flag;
    s32 index;

    mount = camera->mount_index;
    flag = 0;
    if (mount == 0x12 || mount == 0x13)
        flag = 1;
    if (zoid == 0)
        return 0x14;
    if (zoid->joint == 0)
        return 0x14;
    if (zoid->field_1DA0 == -1)
        return 0x14;
    if (zoid->field_1DA0 == 5)
        return 0x14;
    if (zoid->jump_phase != 0)
        return 0x14;
    if (zoid->action == 0)
        return 0x14;
    if (zoid->field_1DD4 != 0)
        return 0x14;
    if (slot == -1000)
        return 0x14;
    if (camera->mount_blocked[mount] != 0)
        return 0x14;
    if (flag != 0)
        return mount;
    point = grdObjGetPt(slot);
    zero = 0.0f;
    index = (zero >= 0.0f) ? 0x12 : 0x13;
    if (camera->mount_blocked[index] != 0 || camera->mount_hidden[index] != 0)
        return 0x14;
    camera->mount_index = 0;
    return index;
}
