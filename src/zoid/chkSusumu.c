#include "zoid3.h"
#include "ground_collision.h"

extern GroundMask GXColorZoid;
extern f32 sLenPoint3dR(Vec3 *point);
extern f32 sColPt(Vec3 *start, Vec3 *end, GroundMask *mask);

s32 chkSusumu(ZoidState *zoid, Vec3 *point)
{
    Vec3 end;
    Vec3 start;
    GroundMask mask;
    s32 i;
    f32 length;

    if (zoid == 0) {
        return 0;
    }
    for (i = 0; i < 3; i++) {
        length = ((f32 *)point)[i];
        ((f32 *)&end)[i] = 5.0f * length + *(f32 *)((u8 *)zoid + 0x50 + i * 16);
        ((f32 *)&start)[i] = *(f32 *)((u8 *)zoid + 0x50 + i * 16) - 2.0f * length;
    }
    length = sLenPoint3dR(point);
    mask = GXColorZoid;
    end.y += 5.0f * length;
    return 10000.0f != sColPt(&start, &end, &mask);
}
