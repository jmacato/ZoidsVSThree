#include "types.h"

typedef struct CameraState3 {
    u8 pad_000[0x244];
    void *cobj;
    u8 pad_248[0x264 - 0x248];
    f32 projection[7];
    f32 viewport[6];
    f32 view[3][4];
    f32 inverse_view[3][4];
} CameraState3;

extern CameraState3 *camTmp;
extern void GXGetProjectionv(f32 *projection);
extern void GXGetViewportv(f32 *viewport);
extern void HSD_CObjGetViewingMtx(void *cobj, f32 matrix[3][4]);
extern f32 (*HSD_CObjGetInvViewingMtxPtr(void *cobj))[4];
extern void PSMTXCopy(f32 src[3][4], f32 dst[3][4]);

void sCameraMatrix(CameraState3 *camera)
{
    f32 (*inverse)[4];

    GXGetProjectionv(camera->projection);
    GXGetViewportv(camera->viewport);
    HSD_CObjGetViewingMtx(camTmp->cobj, camera->view);
    inverse = HSD_CObjGetInvViewingMtxPtr(camTmp->cobj);
    PSMTXCopy(inverse, camera->inverse_view);
}
