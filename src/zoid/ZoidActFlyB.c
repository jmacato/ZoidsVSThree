#include "zoid3.h"
#include "game_mode.h"

extern void zdActFlyB_susumu(ZoidState *zoid);
extern void limitHigh(f32 *position);
extern void limitHighAng(ZoidState *zoid);
extern void zdChgNormal(ZoidState *zoid);
extern void ZoidSetAnim(ZoidState *zoid, s32 animation);
extern void zdVoiceScG(ZoidState *zoid, s32 voice);
extern void zdAtackSetEffect(ZoidState *zoid, s32 effect);

typedef struct ZoidFlyAnim {
    u8 pad[0x338];
    s32 value_338;
    s32 value_33c;
} ZoidFlyAnim;

void ZoidActFlyB(ZoidState *zoid)
{
    s32 flag;
    ZoidFlyAnim *anim;
    s32 dead;
    u16 *slider;

    dead = 0;
    slider = zoid->slider_info;
    anim = (ZoidFlyAnim *)zoid->anim_data;
    if (slider != 0) {
        if (zoid->action_phase > 0 && zoid->action_phase < 0x30) {
            zdActFlyB_susumu(zoid);
        }
        limitHigh(zoid->position);
        limitHighAng(zoid);
        switch (zoid->action_phase) {
        case 0:
            ZoidSetAnim(zoid, 0x41);
            zoid->action_phase = 0x10;
            flag = 1;
            if (GameMode.game_type == 1 || GameMode.game_type == 4) {
                if (zoid->slot != Zoid[0].slot) {
                    flag = 0;
                }
                if (zoid == &Zoid[2]) {
                    flag = 0;
                }
            }
            if (flag != 0) {
                zdVoiceScG(zoid, 0x1C);
            }
            zdAtackSetEffect(zoid, 5);
            zoid->field_1D60 = zoid->field_1C90[2] + (f32)anim->value_338;
            zoid->field_1D5C = zoid->heading;
            zoid->field_1D58 = zoid->high_angle;
            break;
        case 0x10:
            if (zoid->field_1D60) {
                zoid->field_1D60 = zoid->field_1D60 - 0.005 * (f32)anim->value_33c;
                if (zoid->field_1D60 < 0.0f) {
                    zoid->field_1D60 = 0.0f;
                }
            }
            if (zoid->field_1C90[2] < 0.0f) {
                zoid->field_1C90[2] = 0.0f;
            }
            if (!(zoid->field_1D60 > zoid->field_1C90[2])) {
                zoid->action_phase = 0x30;
            }
            break;
        case 0x30:
        default:
            zdChgNormal(zoid);
            break;
        }
        zoid->field_1C74 = 0.0f;
        dead = 1;
    }
}
