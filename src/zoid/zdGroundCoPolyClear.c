#include "zoid3.h"
#include "ground_collision.h"

typedef struct CoObjPoly {
    HSD_JObj *joint;
    u8 reserved_04[0x10];
    s32 ground_contact;
    s32 object_contact;
    s32 field_1C;
    s32 field_20;
    u8 reserved_24[4];
    u16 ground_polygon_index;
} CoObjPoly;

void zdGroundCoPolyClear(ZoidState *zoid, CoObjPoly *poly)
{
    if (zoid == (void *)0)
        return;
    if (poly->joint == (void *)0)
        return;
    poly->ground_polygon_index = GROUND_POLYGON_NONE;
    poly->field_1C = poly->object_contact;
    poly->object_contact = 0;
    poly->ground_contact = 0;
    if (poly->field_20 != 0)
        poly->field_20--;
}
