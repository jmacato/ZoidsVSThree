#include "zoid3.h"

typedef struct GameZoidEntry3 {
    s16 type;
    s16 weapons[28];
    s8 color;
    u8 weapon_colors[0x1D];
    s16 person;
    u8 pad_5A[4];
    s16 option;
    u8 pad_60[8];
} GameZoidEntry3;

typedef struct TeaZoidData3 {
    u8 pad_0000[0x7BE];
    s16 mount_parts[10];
    u8 pad_07D2[0x2A];
} TeaZoidData3;

extern GameZoidEntry3 GameZoid[16];
extern TeaZoidData3 Tea_zoiddat[];

extern void sWeaponMount(s32 weapon, ZoidState *zoid, s32 slot, s32 mount);
extern s32 zdWeaponColor(ZoidState *zoid, s32 slot, s32 color);
extern void zdLoadSuperAtackWp(ZoidState *zoid);
extern void zdLoadOption(ZoidState *zoid, s32 option);
extern void OSReport(char *fmt, ...);

void zdSetGameZoidMount(s32 index, ZoidState *zoid)
{
    s32 type;
    s32 i;
    s32 weapon;
    s32 color;
    s32 mount;

    if (zoid == 0) {
        return;
    }
    type = zoid->type;
    for (i = 0; i < 0x1C; i++) {
        if (zoid->weapon_slots[i].joint != 0) {
            weapon = GameZoid[index].weapons[i];
            if (weapon >= 0) {
                color = (s8)GameZoid[index].weapon_colors[i];
                for (mount = 0; mount < 10; mount++) {
                    if (Tea_zoiddat[type].mount_parts[mount] == weapon) {
                        break;
                    }
                }
                if (mount == 10) {
                    mount = 9;
                }
                sWeaponMount(weapon, zoid, i, mount);
                zdWeaponColor(zoid, i, color);
                OSReport("GameZoid %d WpColor=%d\n", type, color);
            }
        }
    }
    zdLoadSuperAtackWp(zoid);
    zdLoadOption(zoid, GameZoid[index].option);
}
