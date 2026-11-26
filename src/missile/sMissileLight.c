#include "lobj.h"
#include "jobj.h"

typedef struct Missile3 {
    u8 reserved_00[0x08];
    s32 kind;
    u8 reserved_0C[0x18];
    HSD_JObj *joint;
    u8 reserved_28[0xCC];
    s32 purge_timer;
    s32 hit;
    u8 reserved_FC[0x88];
    HSD_LObj *light;
    u8 reserved_188[0x1C];
} Missile3;

extern Missile3 missileStart[200];

void sMissileLight(void)
{
    s32 hidden = 0;
    s32 i;
    s32 count;
    Missile3 *missile = missileStart;
    s32 show;

    i = 0;
    count = 0;
    for (; i < 200; missile++, i++) {
        if (missile == (void *)0) {
            return;
        }
        if (missile->purge_timer == 0 && missile->joint != (void *)0) {
            show = 1;
            if (missile->kind == 4 && missile->hit == 0) {
                show = 0;
            }
            if (missile->kind == 3) {
                show = 0;
            }
            if (hidden != 0) {
                show = 0;
            } else {
                count++;
            }
            if (count >= 3) {
                show = 0;
            }
            if (show != 0 && missile->light != 0) {
                HSD_LObjAddCurrent(missile->light);
            }
        }
    }
}
