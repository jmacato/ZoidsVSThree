#include "types.h"
#include "zoid3.h"
#include "joint.h"

typedef struct GroundObject3 {
    u8 pad_00[0x74];
    HSD_JObj *joint;
    u8 pad_78[0xE0 - 0x78];
    struct GroundObjMapInfo3 *map_info;
} GroundObject3;

typedef struct GroundObjMapInfo3 {
    u8 pad_00[0x10];
    s8 field_10;
    u8 pad_11;
    s8 field_12;
    u8 pad_13;
    s8 field_14;
} GroundObjMapInfo3;

typedef struct Missile3 {
    u8 pad_00[0x1C];
    s32 field_1C;
    u8 pad_20[0x24 - 0x20];
    HSD_JObj *joint;
    struct ZoidState *owner;
    u8 pad_2C[0x1A4 - 0x2C];
} Missile3;

extern GroundObject3 obj[50];
extern s32 objNow;
extern Missile3 missileStart[200];
extern void grdObjIn(GroundObject3 *object, Missile3 *missile);
extern void grdObjRot(GroundObject3 *object);
extern void grdObjFire(GroundObject3 *object);

void grdObjTest(void)
{
    GroundObject3 *object;
    GroundObjMapInfo3 *info;
    Missile3 *missile;
    s32 i;
    s32 j;

    for (i = 0; i < objNow; i++) {
        object = &obj[i];
        info = object->map_info;
        if (object->joint != (void *)0 && info != 0) {
            if (info->field_10 != 0) {
                for (j = 0, missile = missileStart; j < 200; j++, missile++) {
                    if (missile->joint != (void *)0 && missile->owner != (void *)0 && missile->owner->ai_active == 0 && missile->field_1C == 0)
                        grdObjIn(object, missile);
                }
            }
            if (info->field_14 != 0)
                grdObjRot(object);
            if (info->field_12 != 0)
                grdObjFire(object);
        }
    }
}
