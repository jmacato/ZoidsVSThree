#include "zoid3.h"

typedef struct CameraState3 {
    u8 pad_000[0x30];
    s32 mount_index;
    u8 pad_034[0x190];
    ZoidState *zoid;
} CameraState3;

extern s32 sCameraIn2(CameraState3 *camera, HSD_JObj *joint);

s32 camZdLimit2(CameraState3 *camera, ZoidState *zoid)
{
    s32 result;
    s32 index;
    u8 *control;
    s32 *mount;
    HSD_JObj *joint;
    s32 hit;

    if (zoid == (void *)0)
        return 0;
    if (zoid->joint == (void *)0)
        return 0;
    if (camera == (void *)0)
        return 0;
    index = camera->mount_index;
    control = zoid->field_2090;
    mount = (s32 *)(control + index * 16);
    if (*mount == -1)
        joint = zoid->field_1ACC;
    else
        joint = zoid->weapon_slots[*mount].joint;
    if (joint == 0)
        joint = *(HSD_JObj **)zoid->body_coobj;
    if (joint == 0)
        joint = zoid->joint;
    if (camera->zoid == zoid && joint != 0 && mount[2] < 10)
        return sCameraIn2(camera, joint);
    result = 0;
    hit = sCameraIn2(camera, zoid->joint);
    result |= hit;
    hit = sCameraIn2(camera, zoid->head_base_joint);
    result |= hit;
    hit = sCameraIn2(camera, zoid->hip_base_joint);
    result |= hit;
    hit = sCameraIn2(camera, zoid->feet[2].joint);
    result |= hit;
    hit = sCameraIn2(camera, *(HSD_JObj **)zoid->tail_coobjs[0]);
    result |= hit;
    return result;
}
