#include "types.h"

typedef struct TeaPart {
    u8 b[0x124];
} TeaPart;

typedef struct TeaBullet {
    u8 b[0x4C];
} TeaBullet;

typedef struct AiData3 {
    u8 b[0xF0];
} AiData3;

extern TeaPart Tea_partsdat[];
extern TeaBullet Tea_bulletdat[];
extern AiData3 aiDat[];

extern s32 zdAI_WeaponSlotGetID(s32 index, s32 slot);
extern s32 zdAI_WeaponSlotBullet(s32 index, s32 slot);
extern s32 aiNextWeapon(s32 index);

s32 aiWepSearchSlot(s32 index, s32 type_a, s32 type_b)
{
    s32 i = 0;
    s32 id = 0;
    s32 bullet = 0;
    s32 bullet_type = 0;
    s32 count = 0;

    for (i = 0; i < 0x1C; i++) {
        if (i == *(s16 *)&aiDat[index].b[0xAE]) {
            continue;
        }
        id = zdAI_WeaponSlotGetID(index, i);
        if (id < 0) {
            continue;
        }
        bullet = *(s32 *)&Tea_partsdat[id].b[0x5C];
        if (bullet < 0) {
            continue;
        }
        bullet_type = *(s16 *)&Tea_bulletdat[bullet].b[0x12];
        count = zdAI_WeaponSlotBullet(index, i);
        if (count <= 0) {
            continue;
        }
        if (bullet_type == type_a) {
            return i;
        }
        if (bullet_type == type_b) {
            return i;
        }
    }
    for (i = 0; i < 0x1C; i++) {
        id = zdAI_WeaponSlotGetID(index, i);
        if (id < 0) {
            continue;
        }
        bullet = *(s32 *)&Tea_partsdat[id].b[0x5C];
        if (bullet < 0) {
            continue;
        }
        bullet_type = *(s16 *)&Tea_bulletdat[bullet].b[0x12];
        if (bullet_type == type_a) {
            return i;
        }
        if (bullet_type == type_b) {
            return i;
        }
    }
    aiNextWeapon(index);
    return 0;
}
