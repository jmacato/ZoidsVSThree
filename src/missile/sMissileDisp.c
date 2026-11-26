#include "types.h"
#include "jobj.h"

typedef struct Missile3 {
    s32 flags;
    u8 pad_04[0x20];
    HSD_JObj *joint;
    u8 pad_28[0xEC - 0x28];
    s32 update_count;
    s32 field_F0;
    s32 purge_timer;
    s32 hit_timer;
    u8 pad_FC[0x19C - 0xFC];
    s32 field_19C;
    u8 pad_1A0[0x1A4 - 0x1A0];
} Missile3;

extern Missile3 missileStart[200];
extern s32 nowMX;
extern s32 misMAX;

void sMissileDisp(void)
{
    Missile3 *missile;
    s32 i;

    nowMX = 0;
    missile = missileStart;
    for (i = 0; i < 200; i++, missile++) {
        if ((missile->flags & 1) && missile->purge_timer == 0 && missile->joint != (void *)0) {
            nowMX++;
            HSD_JObjDispAll(missile->joint, 0, 7, 0);
        }
    }
    if (nowMX > misMAX) {
        misMAX = nowMX;
    }
}
