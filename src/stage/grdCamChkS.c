#include "zoid3.h"
#include "joint.h"

typedef struct CameraState3 {
    u8 reserved_000[0x214];
    Vec3 relative_origin;
} CameraState3;

extern CameraState3 *camTmp;
extern s32 ctrlZoid;
extern f32 sPassage(Vec3 *, Vec3 *, Vec3 *);

f32 grdCamChkS(HSD_JObj *joint)
{
    Vec3 point;
    point.x = joint->matrix[0][3];
    point.y = joint->matrix[1][3];
    point.z = joint->matrix[2][3];
    return sPassage(&camTmp->relative_origin, (Vec3 *)Zoid[ctrlZoid].position, &point);
}
