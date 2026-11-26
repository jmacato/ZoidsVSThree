#include "types.h"
#include "joint.h"

typedef struct MapObjDef3 {
    u16 dims[3];
    u8 reserved_06[0x10 - 0x06];
    s8 valid;
} MapObjDef3;

typedef struct GroundObject3 {
    u8 reserved_00[0x04];
    f32 position[3];
    u8 reserved_10[0x40 - 0x10];
    f32 inverse[3][4];
    s32 archive_slot;
    u8 reserved_74[0x78 - 0x74];
    s32 animation;
    s32 health;
    s32 sound;
    u8 reserved_84[0xE0 - 0x84];
    MapObjDef3 *def;
} GroundObject3;

extern s32 vsyncN;
extern s32 camTmp;
extern void OSReport(const char *fmt, ...);
extern void PSMTXMultVecArray(f32 m[3][4], Vec3 *src, Vec3 *dst, u32 count);
extern s32 sColCube4Point(Vec3 *point);
extern void sMissileHitOn(void *missile);
extern void grdObjSetAnim(GroundObject3 *object, s32 animation);
extern void camSe(s32 cam, s16 id, f32 *position);

s32 grdObjIn(GroundObject3 *object, u8 *missile)
{
    MapObjDef3 *def;
    s32 hit;
    s32 i;
    s32 j;
    Vec3 spare0[2];
    Vec3 local[21];
    Vec3 spare1[2];
    Vec3 points[21];
    s32 slot;

    if (object->animation != 0)
        return 1;
    def = object->def;
    slot = object->archive_slot;
    if (def == 0) {
        if ((vsyncN & 0x10) == 0)
            OSReport("MapObjDef\202\252\221\253\202\350\202\334\202\271\202\361\201A\222\350\213`\202\265\202\304\202\255\202\276\202\263\202\242\201B\n");
        return 0;
    }
    if (def->valid == 0)
        return 0;
    for (j = 0; j < 3; j++) {
        if (def->dims[j] == 0)
            return 0;
    }
    for (i = 0; i < 21; i++) {
        for (j = 0; j < 3; j++) {
            (&points[i].x)[j] = (*(f32 *)(missile + 0x64 + j * 16) * (f32)i) / 20.0f + (*(f32 *)(missile + 0x94 + j * 16) * (f32)(20 - i)) / 20.0f;
        }
    }
    PSMTXMultVecArray(object->inverse, points, local, 21);
    for (j = 0; j < 21; j++) {
        for (i = 0; i < 3; i++)
            (&local[j].x)[i] = (&local[j].x)[i] / (f32)def->dims[i];
    }
    for (j = 0; j < 21; j++) {
        hit = sColCube4Point(&local[j]);
        if (hit != 0)
            break;
    }
    if (hit == 0)
        return 0;
    sMissileHitOn(missile);
    object->health -= *(s32 *)(missile + 0xF0);
    if (object->health < 0)
        object->health = 0;
    if (object->health > 0)
        return 1;
    if (object->animation == 0)
        grdObjSetAnim(object, 1);
    if (object->sound != 0)
        camSe(camTmp, object->sound, object->position);
    return 1;
}
