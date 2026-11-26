#include "zoid3.h"

typedef struct CoObjV3 {
    HSD_JObj *joint;
} CoObjV3;

typedef struct GrdPolyV3 {
    u8 reserved_0000[4];
    u16 normal_index;
    u8 reserved_0006[0x1A];
} GrdPolyV3;

typedef struct F1 {
    f32 v;
} F1;

typedef struct VecV3 {
    f32 x;
    f32 y;
    f32 z;
} VecV3;

extern f32 sColPosAndY(f32 *position, u16 *polygon, F1 *y);
extern void HSD_JObjSetFlags(HSD_JObj *joint, u32 flags);
extern void HSD_JObjClearFlags(HSD_JObj *joint, u32 flags);
extern void HSD_ShadowAddObject(void *shadow, HSD_JObj *joint);
extern GrdPolyV3 *grdcPolygon;
extern VecV3 *grdcNormal;

void zdShadowLoChk(void *shadow, CoObjV3 *co)
{
    u16 polygon;
    f32 position[3];
    F1 ground_y;
    GrdPolyV3 *poly;
    VecV3 *normal;
    s32 index;
    s32 ok;
    f32 ground;

    if (shadow != 0 && co != 0 && co->joint != 0) {
        for (index = 0; index < 3; index++) {
            position[index] = co->joint->matrix[index][3];
        }
        ground_y = (F1){ 1.05879118e-22f };
        ground = sColPosAndY(position, &polygon, &ground_y);
        ok = 1;
        if (ground > position[1]) {
            ok = 0;
        }
        if (polygon != 0xFFFF) {
            poly = &grdcPolygon[polygon];
            normal = &grdcNormal[poly->normal_index];
            if (normal->y < 0.5) {
                ok = 0;
            }
        }
        if (ok == 0) {
            HSD_JObjSetFlags(co->joint, 0x10);
        } else {
            HSD_JObjClearFlags(co->joint, 0x10);
            HSD_ShadowAddObject(shadow, co->joint);
        }
    }
}
