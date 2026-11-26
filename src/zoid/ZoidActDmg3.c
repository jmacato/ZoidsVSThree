#include "zoid3.h"

typedef struct ZoidCtl3 {
    u8 pad[0x158];
    s32 f158;
    s32 f15c;
    s32 f160;
} ZoidCtl3;

typedef struct ZoidAnim3 {
    u8 pad[0xF8];
    s32 f0f8;
} ZoidAnim3;

extern void ZoidSetAnim(ZoidState *zoid, s32 animation);
extern void ZoidSusumuV(ZoidState *zoid);
extern void zdSetXYZ(ZoidState *zoid);
extern void zdAtackSetEffect(ZoidState *zoid, s32 effect);
extern void zdVoiceScG(ZoidState *zoid, s32 voice);
extern void zdLinearAnimAllBak(ZoidState *zoid);
extern void zdChgNormal(ZoidState *zoid);

void ZoidActDmg3(ZoidState *zoid)
{
    s32 hit[6] = {50, 51, 52, 53, 55, 54};
    s32 i;
    s32 j;
    s32 k;
    u32 *c;
    ZoidCtl3 *control;
    ZoidAnim3 *anim;
    u8 *slider;

    control = zoid->field_2090;
    anim = zoid->anim_data;
    slider = (u8 *)zoid->slider_info;
    if (control == 0) {
        return;
    }
    if (slider == 0) {
        return;
    }
    c = (u32 *)zoid->bust_coobj;
    if (*c == 0) {
        c = (u32 *)zoid->neck_coobj;
    }
    if (*c == 0) {
        c = (u32 *)zoid->hip_coobj;
    }
    if (*c) {
        (void)0;
    }
    zoid->displacement[0] = 0.0f;
    zoid->displacement[1] = 0.0f;
    zoid->displacement[2] = 0.0f;
    if (zoid->requested_action == 27) {
        zoid->requested_action = 0;
    }
    if (zoid->requested_action == 34) {
        zoid->requested_action = 0;
    }
    zoid->death_pending = 0;
    if (zoid->action_phase > 0 && zoid->action_phase <= 48) {
        ZoidSusumuV(zoid);
        zoid->field_1BFC = 0;
    }
    if (zoid->field_1E50 < 2) {
        zoid->field_1E50 = 2;
    }
    switch (zoid->action_phase) {
    case 0:
        ZoidSetAnim(zoid, hit[zoid->action - 35]);
        zoid->interpolation_remaining = 6;
        zoid->interpolation_duration = 6;
        if (zoid->field_0170) {
            zoid->interpolation_remaining = 60;
            zoid->interpolation_duration = 60;
        }
        zoid->action_phase = 1;
        zoid->field_1E50 = 30;
        for (i = 0; i < 3; i++) {
            zoid->knockback[i] = 0.0f;
            zoid->field_1D20[i] = 0.0f;
        }
        zoid->gene_frames = 0;
    case 1:
        if (slider[0x70b] & 4) {
            zoid->height_offset = 0.0f;
        }
        if (anim->f0f8 == 3) {
            zoid->height_offset = 0.0f;
        }
        zoid->death_pending = 0;
        zoid->field_1C34 = 0;
        if (zoid->animation_looped == 0 && zoid->animation_stopped == 0) {
            break;
        }
    case 16:
        ZoidSetAnim(zoid, 56);
        zoid->interpolation_remaining = 60;
        zoid->interpolation_duration = 60;
        zoid->action_phase = 17;
        zoid->position[1] = zoid->position[1] + 10.0 * (0.4 * ((f32)control->f158 / 100.0));
        zoid->grounded = 0;
        if (control->f158 == 0) {
            zoid->action_phase = 32;
        }
        zdSetXYZ(zoid);
        break;
    case 17:
        zoid->gene_frames++;
        if (zoid->gene_frames > 600) {
            zoid->action_phase = 32;
        }
        if (zoid->grounded == 0) {
            break;
        }
    case 32:
        for (j = 0; j < 3; j++) {
            zoid->launch_velocity[j] *= 0.7;
        }
        zoid->gene_frames = 0;
        zoid->launch_velocity[1] *= 0.3;
        zoid->action_phase = 33;
    case 33:
        zoid->launch_velocity[1] *= 0.3;
        zoid->field_1C34 = 0;
        for (k = 0; k < 3; k++) {
            zoid->launch_velocity[k] *= 0.9;
        }
        if (zoid->animation_stopped == 0 && zoid->animation_looped == 0) {
            break;
        }
        zoid->launch_velocity[1] *= 0.3;
    case 48:
        zoid->field_1C34 = 0;
        zoid->action_phase = 49;
        zoid->field_1DBC = 0;
        zoid->launch_velocity[1] *= 0.3;
    case 49:
        zoid->death_pending = 1;
        if (zoid->health <= 0) {
            zoid->health = 0;
            zoid->launch_velocity[1] = 0.0f;
            zoid->action = 42;
            zoid->action_phase = 0;
            zoid->requested_action = 42;
            break;
        }
        if ((s32)zoid->field_1DBC >= control->f15c) {
            if (zoid->field_0170 && zoid->requested_action == 13) {
                zoid->action = 0;
            }
            if (zoid->field_0170 && zoid->requested_action == 2) {
                zoid->action = 0;
            }
            if (zoid->requested_action == 13) {
                zdAtackSetEffect(zoid, 7);
                zoid->action_phase = 80;
                zdVoiceScG(zoid, 5);
                break;
            } else if (zoid->requested_action == 2) {
                if (zoid->field_1E50 < 90) {
                    zoid->field_1E50 = 90;
                }
                zoid->action_phase = 96;
                break;
            }
        }
        zoid->field_1DBC++;
        if ((s32)zoid->field_1DBC > control->f160) {
            zoid->action_phase = 64;
        }
        break;
    case 64:
        zoid->field_1C34 = 0;
        ZoidSetAnim(zoid, 57);
        zdLinearAnimAllBak(zoid);
        zoid->action_phase = 65;
    case 65:
        zoid->field_1C34 = 0;
        if (zoid->field_1E50 < 60) {
            zoid->field_1E50 = 60;
        }
        if (zoid->animation_stopped == 0 && zoid->animation_looped == 0) {
            break;
        }
    default:
    case 153:
        zoid->field_1C90[0] = 0.0f;
        zoid->field_1C90[2] = 0.0f;
        zoid->field_1C90[1] = 0.0f;
        zoid->launch_velocity[0] = 0.0f;
        zoid->launch_velocity[1] = 0.0f;
        zoid->launch_velocity[2] = 0.0f;
        zoid->displacement[0] = 0.0f;
        zoid->displacement[1] = 0.0f;
        zoid->displacement[2] = 0.0f;
        zoid->knockback[0] = 0.0f;
        zoid->knockback[1] = 0.0f;
        zoid->knockback[2] = 0.0f;
        zoid->field_1D20[0] = 0.0f;
        zoid->field_1D20[1] = 0.0f;
        zoid->field_1D20[2] = 0.0f;
        zoid->action = 0;
        zoid->requested_action = 0;
        zdChgNormal(zoid);
        break;
    case 80:
        zoid->requested_action = 0;
        ZoidSetAnim(zoid, 62);
        zoid->action_phase = 81;
    case 81:
        if (zoid->animation_stopped == 0 && zoid->animation_looped == 0) {
            break;
        }
        zoid->action_phase = 153;
        break;
    case 96:
        zoid->requested_action = 0;
        ZoidSetAnim(zoid, 58);
        zoid->action_phase = 97;
    case 97:
        if (zoid->animation_stopped == 0 && zoid->animation_looped == 0) {
            break;
        }
        ZoidSetAnim(zoid, 59);
        zoid->launch_velocity[1] = 0.55f;
        zoid->launch_velocity[0] = 0.0f;
        zoid->launch_velocity[2] = 0.0f;
        if (zoid->ground_normal) {
            zoid->launch_velocity[0] = zoid->ground_normal->x;
            zoid->launch_velocity[2] = zoid->ground_normal->z;
        }
        zoid->action_phase = 98;
        zoid->gene_frames = 0;
    case 98:
        ZoidSusumuV(zoid);
        if (zoid->launch_velocity[1] > 0.0f) {
            break;
        }
        ZoidSetAnim(zoid, 60);
        zoid->action_phase = 99;
    case 99:
        zoid->gene_frames++;
        if (zoid->gene_frames > 300) {
            zoid->action_phase = 100;
        }
        if (anim->f0f8 == 1 && zoid->ground_height >= zoid->position[1]) {
            zoid->action_phase = 100;
            break;
        }
        ZoidSusumuV(zoid);
        if (zoid->grounded == 0 && zoid->ground_normal_count == 0) {
            break;
        }
    case 100:
        zoid->launch_velocity[0] = 0.0f;
        zoid->launch_velocity[1] = 0.0f;
        zoid->launch_velocity[2] = 0.0f;
        zoid->displacement[0] = 0.0f;
        zoid->displacement[1] = 0.0f;
        zoid->displacement[2] = 0.0f;
        ZoidSetAnim(zoid, 61);
        zoid->action_phase = 101;
    case 101:
        zoid->launch_velocity[0] = 0.0f;
        zoid->launch_velocity[1] = 0.0f;
        zoid->launch_velocity[2] = 0.0f;
        zoid->displacement[0] = 0.0f;
        zoid->displacement[1] = 0.0f;
        zoid->displacement[2] = 0.0f;
        if (zoid->animation_stopped != 0 || zoid->animation_looped != 0) {
            zoid->action_phase = 153;
        }
        break;
    }
}
