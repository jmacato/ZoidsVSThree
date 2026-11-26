#include "types.h"

typedef struct CameraState3 {
    s32 mode;
    s32 half;
    u8 pad_008[0x1C0 - 0x08];
    void *field_1C0;
    void *zoid;
    u8 pad_1C8[0x244 - 0x1C8];
    void *cobj;
} CameraState3;

extern void camOnWin00(void *camera, void *zoid);

void camOnWin(CameraState3 *camera)
{
    void *zoid;
    if (camera != 0 && camera->cobj != 0) {
        zoid = camera->zoid;
        if (zoid != 0)
            camOnWin00(camera, zoid);
    }
}
