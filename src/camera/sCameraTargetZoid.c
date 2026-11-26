#include "zoid3.h"

typedef struct CameraState3 {
    u8 pad_000[0x1C0];
    HSD_JObj *field_1C0;
    ZoidState *zoid;
    s32 target_index;
} CameraState3;

void sCameraTargetZoid(CameraState3 *camera, ZoidState *zoid)
{
    HSD_JObj *joint;
    if (camera != (void *)0 && zoid != (void *)0) {
        camera->zoid = zoid;
        joint = 0;
        camera->target_index = zoid->index;
        zoid->camera = camera;
        if (*(HSD_JObj **)zoid->body_coobj != 0)
            joint = *(HSD_JObj **)zoid->body_coobj;
        else if (*(HSD_JObj **)zoid->head_coobj != 0)
            joint = *(HSD_JObj **)zoid->head_coobj;
        else if (*(HSD_JObj **)zoid->neck_coobj != 0)
            joint = *(HSD_JObj **)zoid->neck_coobj;
        else if (*(HSD_JObj **)zoid->hip_coobj != 0)
            joint = *(HSD_JObj **)zoid->hip_coobj;
        else if (*(HSD_JObj **)zoid->tail_coobjs[0] != 0)
            joint = *(HSD_JObj **)zoid->tail_coobjs[0];
        camera->field_1C0 = joint;
    }
}
