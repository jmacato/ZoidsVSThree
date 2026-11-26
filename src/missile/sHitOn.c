#include "types.h"
#include "jobj.h"

#define NULL ((void *)0)

typedef struct Missile3 {
    s32 flags;
    u8 pad_04[0x18];
    s32 animation;
    u8 pad_20[4];
    HSD_JObj *joint;
    u8 pad_28[0xEC - 0x28];
    s32 update_count;
    s32 damage;
    s32 purge_timer;
    s32 hit_timer;
    u8 pad_FC[0x19C - 0xFC];
    s32 se_playing;
    u8 pad_1A0[0x1A4 - 0x1A0];
} Missile3;

extern s32 sAObjAnimeAll(HSD_JObj *joint);
extern void sMissileSetAnim(Missile3 *missile, s32 animation);
extern void msFlyTrace(Missile3 *missile);

void sHitOn(Missile3 *missile)
{
    s32 animation;

    if (missile != NULL) {
        missile->update_count++;
        if (missile->purge_timer == 0 && missile->hit_timer != 0) {
            missile->hit_timer++;
            if (sAObjAnimeAll(missile->joint)) {
                missile->purge_timer = 1;
                animation = missile->animation;
                if (animation == 0) {
                    sMissileSetAnim(missile, 1);
                }
                if (animation == 1) {
                    sMissileSetAnim(missile, 2);
                }
                if (animation == 2) {
                    sMissileSetAnim(missile, 2);
                }
            }
            if (missile->se_playing != 0) {
                missile->se_playing = 0;
            }
            msFlyTrace(missile);
        }
    }
}
