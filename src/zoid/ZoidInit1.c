#include "zoid3.h"

typedef struct PadState3 {
    s8 connected;
    u8 pad_01[0x2F];
    s8 held_up;
    s8 held_down;
    s8 held_left;
    s8 held_right;
    u8 pad_34[0x11];
    s8 field_45;
    u8 pad_46[0x42];
} PadState3;

typedef struct GameZoidEntry3 {
    s16 type;
    s16 weapons[28];
    s8 color;
    s8 weapon_colors[0x1D];
    s16 person;
    u8 pad_5A[4];
    s16 option;
    s16 additional_parts[3];
    u8 pad_66[2];
} GameZoidEntry3;

typedef struct TeaZoidData3 {
    u8 pad_0000[0x7BE];
    s16 mount_parts[10];
    u8 pad_07D2[0x2A];
} TeaZoidData3;

extern GameZoidEntry3 GameZoid[16];
extern TeaZoidData3 Tea_zoiddat[];
extern PadState3 sPad[4];
extern s32 sCamNN;

extern s32 ZoidInit(ZoidState *zoid, s32 type);
extern s32 ZoidColor(ZoidState *zoid, s32 color, s32 flags);
extern void sWeaponMount(s32 weapon, ZoidState *zoid, s32 slot, s32 mount);
extern s32 zdWeaponColor(ZoidState *zoid, s32 slot, s32 color);
extern void zdLoadSuperAtackWp(ZoidState *zoid);
extern void zdLoadOption(ZoidState *zoid, s32 option);
extern void OSReport(char *fmt, ...);

void ZoidInit1(ZoidState *zoid, s32 index, s32 slot)
{
    s32 i;
    s32 type;
    s32 mount;
    s32 color;
    s32 part;
    PadState3 *pad;

    if (zoid == 0)
        return;
    type = GameZoid[index].type;
    if (type == -1)
        return;
    ZoidInit(zoid, type);
    zoid->slot = slot;
    zoid->person = GameZoid[index].person;
    color = GameZoid[index].color;
    if (sCamNN >= 2) {
        pad = &sPad[zoid->index];
        if (index < 4 && pad->connected != 0 && pad->field_45 != 0) {
            color = 1;
            if (pad->held_left != 0)
                color = 2;
            if (pad->held_right != 0)
                color = 3;
            if (pad->held_up != 0)
                color = 4;
            if (pad->held_down != 0)
                color = 5;
        }
    }
    if (color != 0)
        ZoidColor(zoid, color, 0);
    for (i = 0; i < 28; i++) {
        if (zoid->weapon_slots[i].joint != 0) {
            part = GameZoid[index].weapons[i];
            if (part >= 0) {
                color = GameZoid[index].weapon_colors[i];
                for (mount = 0; mount < 10; mount++) {
                    if (part == Tea_zoiddat[type].mount_parts[mount])
                        break;
                }
                if (mount == 10)
                    mount = 9;
                sWeaponMount(part, zoid, i, mount);
                zdWeaponColor(zoid, i, color);
                OSReport("GameZoid %d WpColor=%d\n", type, color);
            }
        }
    }
    zdLoadSuperAtackWp(zoid);
    zdLoadOption(zoid, GameZoid[index].option);
    for (i = 0; i < 3; i++)
        zoid->additional_parts[i] = GameZoid[index].additional_parts[i];
}
