#include "zoid3.h"

extern Vec3 *grdObjGetPt(void *obj);
extern s32 grdObjGetGrp(void *obj);
extern s32 grdObjSearch(void *obj);
extern f32 sLenPoint3d(Vec3 *a, Vec3 *b);

s32 searchObj1(ZoidState *zoid, void *obj)
{
    s32 group;
    Vec3 *point;
    f32 dist;

    if (zoid == 0) {
        return 0;
    }
    if (zoid->joint == 0) {
        return 0;
    }
    group = zoid->slot;
    point = grdObjGetPt(obj);
    if (point == 0) {
        return 0;
    }
    if (group == grdObjGetGrp(obj)) {
        return 0;
    }
    if (grdObjSearch(obj) == 0) {
        return 0;
    }
    dist = sLenPoint3d((Vec3 *)zoid->position, point);
    if (zoid->search_range < dist) {
        return 0;
    }
    return 1;
}
