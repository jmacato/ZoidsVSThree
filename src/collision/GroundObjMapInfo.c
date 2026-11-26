#include "types.h"

typedef struct MapObjRec3 {
    u8 pad_00[0x20];
    s32 field_20;
    u8 pad_24[0xB2 - 0x24];
    s16 field_B2;
    u8 pad_B4[0xB6 - 0xB4];
    s16 field_B6;
    u8 pad_B8[0xBA - 0xB8];
    s16 field_BA;
    u8 pad_BC[0xBD - 0xBC];
    s8 field_BD;
    u8 pad_BE[0x24C - 0xBE];
} MapObjRec3;

extern u8 *mgP;
extern void GroundObjLoadMapInfo(s32 kind, s16 b2, s16 ba, s16 b6, s32 usb);

void GroundObjMapInfo(s32 usb)
{
    MapObjRec3 *rec;
    s32 i;

    if (mgP != 0) {
        for (i = 0; i < 0x11; i++) {
            rec = (MapObjRec3 *)((u8 *)mgP + (i * 0x24C) + 0x12C);
            if (rec->field_20 == 2 && rec->field_BD != 0)
                GroundObjLoadMapInfo(rec->field_BD, rec->field_B2, rec->field_BA, rec->field_B6, usb);
        }
    }
}
