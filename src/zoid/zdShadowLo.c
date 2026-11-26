#include "zoid3.h"
#include "ground_collision.h"

#define JOBJ_HIDDEN 0x10

typedef struct CoObjVS3 {
    HSD_JObj *joint;
    u8 pad_0004[0x24];
    u16 ground_polygon_index;
} CoObjVS3;

extern void HSD_JObjClearFlags(HSD_JObj *jobj, u32 flags);
extern void HSD_JObjSetFlags(HSD_JObj *jobj, u32 flags);
extern void HSD_ShadowAddObject(void *shadow, HSD_JObj *jobj);

s32 zdShadowLo(void *shadow, CoObjVS3 *co)
{
    s32 visible;
    u16 polygon_index;
    GroundPolygon *polygon;
    Vec3 *normal;

    if (co == (void *)0) {
        return 1;
    }
    if (co->joint == (void *)0) {
        return 1;
    }
    if (shadow == 0) {
        return 1;
    }
    visible = 1;
    polygon_index = co->ground_polygon_index;
    if (polygon_index != GROUND_POLYGON_NONE) {
        polygon = &grdcPolygon[polygon_index];
        normal = &grdcNormal[((u16 *)polygon)[2]];
        if (normal->y < 0.5) {
            visible = 0;
        }
    }
    if (visible == 0) {
        HSD_JObjSetFlags(co->joint, JOBJ_HIDDEN);
        return 0;
    }
    HSD_JObjClearFlags(co->joint, JOBJ_HIDDEN);
    HSD_ShadowAddObject(shadow, co->joint);
    return 1;
}
