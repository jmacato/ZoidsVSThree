#include "types.h"

typedef struct TeaPart {
    u8 b[0x124];
} TeaPart;

typedef struct AiData3 {
    u8 b[0xF0];
} AiData3;

extern TeaPart Tea_partsdat[];
extern AiData3 aiDat[];

extern s32 zdAI_WeaponSlotGetID(s32 index, s32 slot);
extern s32 zdAI_WeaponSlotBullet(s32 index, s32 slot);
extern void zdAI_WeaponChgSlot(s32 index, s32 slot);

s16 aiNextWeaponScan(s32 index)
{
    s32 i = 0;
    s32 id = 0;
    s32 bullet = 0;
    s32 dead = 0;

    for (i = 0; i < 0x1C; i++) {
        id = zdAI_WeaponSlotGetID(index, i);
        if (id < 0) {
            continue;
        }
        bullet = *(s32 *)&Tea_partsdat[id].b[0x5C];
        if (bullet < 0) {
            continue;
        }
        dead = 1;
        if (zdAI_WeaponSlotBullet(index, i) > 0) {
            zdAI_WeaponChgSlot(index, i);
            *(s16 *)&aiDat[index].b[0x78] = 0xB4;
            return (s16)i;
        }
    }
    *(s32 *)&aiDat[index].b[0x8C] = 0;
    return -1;
}
