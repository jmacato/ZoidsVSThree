#include "zoid3.h"
#include "ground_collision.h"
#include "math_support.h"
#pragma readonly_strings on

#define DEG(x) (2.0 * (3.1415926 * (x)) / 360.0)

extern void dummyFunc(const char *);
extern void flyZoid(ZoidState *zoid);
extern void dmgZoid(ZoidState *zoid);
extern f32 sLenPoint3dR(f32 *point);
extern void ZoidToFly(ZoidState *zoid);
extern void ZoidSiseiFace(ZoidState *zoid);
extern f32 zdColPosY(f32 *point, u16 *selector);
extern void zdChgNormal(ZoidState *zoid);
extern void zdLinierTm(ZoidState *zoid, s32 frames);
extern void ZoidWalk(ZoidState *zoid);
extern void ZoidSuberi(ZoidState *zoid);
extern void zdZuri(ZoidState *zoid);
extern void ZoidJump(ZoidState *zoid);
extern void ZoidActFlyB(ZoidState *zoid);
extern void zdModeGene(ZoidState *zoid);
extern void ZoidTurnR(ZoidState *zoid, s32 mode);
extern void ZoidTurnL(ZoidState *zoid, s32 mode);
extern void ZoidStop1(ZoidState *zoid);
extern void ZoidDash1(ZoidState *zoid);
extern void ZoidActAtack(ZoidState *zoid);
extern void ZoidActStepF(ZoidState *zoid);
extern void ZoidActStep(ZoidState *zoid);
extern void ZoidActDmg2(ZoidState *zoid);
extern void ZoidActDmg3(ZoidState *zoid);
extern void ZoidActDeadly(ZoidState *zoid);
extern void ZoidActDead(ZoidState *zoid);
extern void ZoidActDeath(ZoidState *zoid);
extern void ZoidActMotion(ZoidState *zoid);
extern void ZoidActWin(ZoidState *zoid);
extern void angLimit(f32 *angle);
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern f32 atan2f(f32 y, f32 x);

static inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

static inline f32 vector_heading(f32 x, f32 z)
{
    return atan2f(x, z);
}

void ZoidMove(ZoidState *zoid)
{
    s32 damage_level;
    u8 *control;
    u8 *slider;
    u8 *table;
    u8 *mountp;
    s32 flag;
    s32 i;
    s32 j;
    f32 magnitude;
    f32 step;
    f32 relative;
    f32 relative2;
    f32 relative3;
    f32 knockback_length;
    f32 magnitude2;
    f32 magnitude3;
    f32 length;
    f32 sum;
    f32 v;
    Vec3 *normal;
    s32 index;

    knockback_length = 0.0f;
    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        if (zoid->action != zoid->field_1DAC) {
            zoid->field_1DAC = zoid->action;
            zoid->field_1DB0 = 0;
        } else {
            zoid->field_1DB0++;
        }
        if (zoid->death_started == 0) {
            zoid->lock_frames = 0;
        }
        flyZoid(zoid);
        zoid->field_1DA0 = -1;
        mountp = 0;
        slider = (u8 *)zoid->slider_info;
        control = (u8 *)zoid->anim_data;
        table = (u8 *)zoid->field_2090;
        if (slider != 0) {
            if (zoid->weapon_mount == 0x13) {
                mountp = slider + 2;
            } else {
                mountp = (u8 *)((zoid->weapon_mount + 1) * 16 + 2);
                mountp = (u8 *)((u32)slider + (u32)mountp);
            }
        }
        damage_level = 0;
        if (zoid->field_1E5C != 0) {
            for (i = 0; i < 3; i++) {
                zoid->knockback[i] = zoid->field_1D20[i];
                zoid->field_1D20[i] = 0.0f;
            }
            if (zoid->field_1E5C & 2) {
                damage_level = 1;
            }
            if (zoid->field_1E5C & 4) {
                damage_level = 2;
            }
            if (zoid->health == 0) {
                damage_level = 2;
            }
        } else {
            knockback_length = sLenPoint3dR(zoid->knockback);
            if (knockback_length >= 1.0 && zoid->field_1D2C < 1.0f) {
                damage_level = 1;
            }
            if (knockback_length > 1.6666666f) {
                damage_level = 2;
            }
            if (knockback_length && zoid->health == 0 && zoid->action != 0x2A && zoid->action != 0x2B
                && zoid->death_started == 0) {
                damage_level = 2;
            }
            zoid->field_1D2C = knockback_length;
        }
        if (damage_level == 1 && zoid->jump_phase != 0) {
            if (zoid->field_1EB0 == 0 || zoid->field_1EB2 == 0) {
                damage_level = 2;
            }
        }
        dummyFunc("f");
        ZoidToFly(zoid);
        for (i = 0; i < 3; i++) {
            zoid->field_1A9C[i] = zoid->joint->child->matrix[i][3];
            zoid->field_1C24[i] = zoid->position[i];
            if (zoid->field_1A7C != 0) {
                zoid->field_1A80[i] = zoid->field_1A7C->matrix[i][3];
            }
        }
        if (zoid->health <= 0) {
            zoid->health = 0;
        }
        if (zoid->health == 0) {
            if (zoid->field_1E54 != 0) {
                zoid->field_1E54--;
            }
            if (zoid->field_1E54 == 0) {
                if (zoid->action != 0x2A && zoid->action != 0x2B && zoid->death_started == 0) {
                    zoid->launch_velocity[1] = 0.0f;
                    zoid->action = 0x2A;
                    zoid->requested_action = 0x2A;
                    zoid->action_phase = 0;
                }
            }
        }
        if (*(s32 *)(control + 0x100) != 0) {
            if (damage_level == 1 && zoid->attack_index != -1) {
                zoid->field_1E50 = 0x78;
                damage_level = 0;
            }
            if (zoid->health == 0) {
                zoid->field_1BE4 = 1;
            }
            if (zoid->health > 0 && damage_level == 2) {
                damage_level = 1;
            }
            if (damage_level != 0) {
                for (i = 0; i < 3; i++) {
                    zoid->knockback[i] = 0.0f;
                    zoid->field_1D20[i] = 0.0f;
                    zoid->field_1E5C = 0;
                }
            }
            if (zoid->action == 0x2A || zoid->action == 0x2B) {
                damage_level = 0;
                knockback_length = 0.0f;
                if (zoid->requested_action == 0x1B) {
                    zoid->requested_action = 0;
                }
                if (zoid->requested_action == 0x22) {
                    zoid->requested_action = 0;
                }
            }
        }
        if (zoid->health == 0) {
            damage_level = 2;
        }
        if (damage_level != 0) {
            zoid->requested_action = 0x1B;
            if (damage_level == 2) {
                zoid->requested_action = 0x22;
                switch (zoid->action) {
                case 0x22: case 0x23: case 0x24: case 0x25: case 0x26:
                case 0x27: case 0x28: case 0x29: case 0x2A: case 0x2B:
                    break;
                default:
                    zoid->action = 0;
                    zoid->action_phase = 0;
                    zoid->gene_frames = 0;
                    zdChgNormal(zoid);
                    zdLinierTm(zoid, 0x3C);
                    zoid->death_pending = 0;
                    zoid->field_1C34 = 0;
                    zoid->requested_action = 0x22;
                    break;
                }
            }
            if (damage_level == 1) {
                if (zoid->action >= 0x1B && zoid->action <= 0x21) {
                    zoid->action = 0;
                    zoid->action_phase = 0;
                }
            }
        }
        if (knockback_length > 0.0f && zoid->health <= 0) {
            zoid->requested_action = 0x22;
            zoid->health = 0;
            if (zoid->action >= 0xD && zoid->action <= 0x16) {
                zoid->action = 0;
            }
            if (zoid->action >= 0x2C && zoid->action <= 0x30) {
                zoid->action = 0;
            }
        }
        dmgZoid(zoid);
        dummyFunc("n");
        if (zoid->field_1374 != 0) {
            zoid->field_1C34 = 1;
            if ((s32)mountp[6] == 1) {
                zoid->field_1C34 = 0;
                if (zoid->position[1] < zoid->ground_height || zoid->grounded != 0) {
                    /* MWCC needs this form to preserve temporary register allocation. */
                    zoid->field_1BFC *= 0;
                }
                zoid->field_1C90[0] = 0.0f;
                zoid->field_1C90[1] = 0.0f;
                zoid->field_1C90[2] = 0.0f;
            }
            if (zoid->face_lock != 0) {
                ZoidSiseiFace(zoid);
            }
            return;
        }
        dummyFunc("b");
        zoid->death_pending = 0;
        switch (zoid->action) {
        case 0:
            zoid->field_1C34 = 0;
            dummyFunc("W");
            ZoidWalk(zoid);
            ZoidSuberi(zoid);
            zdZuri(zoid);
            zoid->jump_phase = 0;
            break;
        case 1:
        case 2:
            flag = 0;
            if (*(s32 *)(control + 0xA4) == 0) {
                flag = 1;
            }
            if (zoid->field_0170 != 0) {
                flag = 1;
            }
            if (flag != 0) {
                zoid->requested_action = 0;
                zoid->action = 0;
                zoid->jump_phase = 0;
                break;
            }
            dummyFunc("J");
            ZoidJump(zoid);
            break;
        case 0x34:
            zoid->field_1C34 = 0;
            ZoidActFlyB(zoid);
            break;
        case 0x33:
            zoid->field_1C34 = 0;
            zdModeGene(zoid);
            break;
        case 3:
            zoid->field_1C34 = 0;
            zoid->action = 0;
            break;
        case 4:
            zoid->field_1C34 = 0;
            ZoidTurnR(zoid, 0);
            break;
        case 8:
            zoid->field_1C34 = 0;
            ZoidTurnR(zoid, 1);
            break;
        case 10:
            zoid->field_1C34 = 0;
            ZoidTurnR(zoid, 2);
            break;
        case 6:
            zoid->field_1C34 = 0;
            ZoidTurnR(zoid, 3);
            break;
        case 5:
            zoid->field_1C34 = 0;
            ZoidTurnL(zoid, 0);
            break;
        case 9:
            zoid->field_1C34 = 0;
            ZoidTurnL(zoid, 1);
            break;
        case 11:
            zoid->field_1C34 = 0;
            ZoidTurnL(zoid, 2);
            break;
        case 7:
            zoid->field_1C34 = 0;
            ZoidTurnL(zoid, 3);
            break;
        case 12:
            zoid->field_1C34 = 0;
            ZoidStop1(zoid);
            break;
        case 0x2C:
            zoid->field_1C34 = 0;
            ZoidDash1(zoid);
            break;
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
            zoid->field_1DA0 = zoid->action - 13;
            zoid->field_1C34 = 1;
            zoid->field_1DD4 = 0;
            zoid->field_1DD8 = 0;
            ZoidActAtack(zoid);
            break;
        case 23:
        case 24:
        case 25:
        case 26:
            zoid->field_1C34 = 1;
            if (zoid->field_0170 != 0) {
                ZoidActStepF(zoid);
                zoid->field_1DFC = *(s32 *)(control + 0x314);
            } else {
                ZoidActStep(zoid);
                if (zoid->action_phase < 0x30) {
                    zoid->field_1DFC = *(s32 *)(control + 0x314);
                }
            }
            break;
        case 27:
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
        case 33:
            zoid->field_1C34 = 0;
            ZoidActDmg2(zoid);
            break;
        case 34:
        case 35:
        case 36:
        case 37:
        case 38:
        case 39:
        case 40:
            zoid->field_1C34 = 1;
            ZoidActDmg3(zoid);
            break;
        case 41:
            if (zoid->health == 0) {
                zoid->action = 0;
                zoid->requested_action = 0x22;
            }
            zoid->field_1C34 = 1;
            ZoidActDeadly(zoid);
            break;
        case 42:
            zoid->field_1C34 = 1;
            ZoidActDead(zoid);
            if (zoid->health == 0) {
                return;
            }
            break;
        case 43:
            zoid->field_1C34 = 1;
            ZoidActDeath(zoid);
            if (zoid->health == 0) {
                return;
            }
            break;
        case 49:
            zoid->field_1C34 = 1;
            ZoidActMotion(zoid);
            break;
        case 50:
            zoid->field_1C34 = 1;
            ZoidActWin(zoid);
            break;
        default:
            zoid->field_1C34 = 0;
            break;
        }
        dummyFunc("m");
        if (zoid->action != 0) {
            return;
        }
        switch (zoid->requested_action) {
        case 0:
            break;
        case 1:
        case 2:
            zoid->jump_phase = zoid->requested_action;
            if (*(s32 *)(control + 0xA4) == 0) {
                zoid->jump_phase = 0;
            }
            if (zoid->jump_phase != 0 && *(s32 *)(control + 0xF4) != 0
                && zoid->ground_height < zoid->position[1] - 0.5) {
                if (zoid->feet[2].joint != 0 && !(zoid->feet[2].flags & 1)) {
                    zoid->jump_phase = 0;
                }
                if (zoid->feet[3].joint != 0 && !(zoid->feet[3].flags & 1)) {
                    zoid->jump_phase = 0;
                }
            }
            if (zoid->position[1] > (f32) * (s32 *)(control + 0xA4) + zdColPosY(zoid->position, 0)) {
                if (*(s32 *)(control + 0xF8) == 0) {
                    zoid->jump_phase = 0;
                } else if (zoid->grounded != 0 || zoid->field_1EAE != 0xFFFF) {
                    zoid->jump_phase = 0;
                }
            }
            if (zoid->jump_phase == 0) {
                zoid->requested_action = 0;
                break;
            }
            zoid->action_phase = 0;
            zoid->action = zoid->requested_action;
            zoid->requested_action = 0;
            break;
        case 0x33:
            zoid->action = zoid->requested_action;
            zoid->action_phase = 0;
            zoid->requested_action = 0;
            break;
        case 0x34:
            zoid->action = zoid->requested_action;
            if (zoid->field_0170 == 0) {
                zoid->action = 0;
            }
            zoid->action_phase = 0;
            zoid->requested_action = 0;
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            zoid->action = zoid->requested_action;
            zoid->action_phase = 0;
            zoid->requested_action = 0;
            break;
        case 12:
            zoid->action = zoid->requested_action;
            zoid->action_phase = 0;
            zoid->requested_action = 0;
            if (zoid->field_0170 == 0 && zoid->position[1] - zoid->ground_height > 0.5) {
                zoid->action = 0;
            }
            break;
        case 13:
            if (slider[0x710] != 0 && 1.0f + zoid->ground_height < zoid->joint->child->matrix[1][3]
                && 1.0f + zoid->ground_height < zoid->position[1]) {
                break;
            }
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
            if (zoid->field_016C != 0) {
                zoid->requested_action = 0;
                break;
            }
            if (zoid->field_1DD4 > 0x1E) {
                break;
            }
            if (zoid->field_0170 == 0 && 0.0f != zoid->high_angle) {
                break;
            }
            if (*(s32 *)(control + 0xF4) == 4 && *(s32 *)(control + 0xF8) == 0 && zoid->grounded == 0) {
                break;
            }
            zoid->field_1A78 = 1.0f;
            zoid->action = zoid->requested_action;
            zoid->action_phase = 0;
            zoid->requested_action = 0;
            break;
        case 23:
        case 24:
        case 25:
        case 26:
            step = zoid->step_heading;
            relative = step - zoid->heading;
            angLimit(&relative);
            magnitude = absf(relative);
            if (magnitude < DEG(45)) {
                zoid->action = 0x17;
            } else if (magnitude > DEG(135)) {
                zoid->action = 0x18;
            } else if (relative > 0.0f) {
                zoid->action = 0x1A;
            } else {
                zoid->action = 0x19;
            }
            if (magnitude > DEG(90) && *(u16 *)(zoid->hip_coobj + 0x28) != 0xFFFF) {
                zoid->requested_action = 0;
                zoid->action = 0;
                break;
            }
            if (zoid->field_0170 == 0) {
                zoid->launch_velocity[0] = zoid->displacement[0] + sinf(step);
                zoid->launch_velocity[2] = zoid->displacement[2] + cosf(step);
            }
        case 45:
        case 46:
        case 47:
        case 48:
            if (zoid->field_1DFC != 0) {
                break;
            }
            if (zoid->requested_action == 0x2D) {
                zoid->action = 0x17;
            }
            if (zoid->requested_action == 0x2E) {
                zoid->action = 0x18;
            }
            if (zoid->requested_action == 0x2F) {
                zoid->action = 0x19;
            }
            if (zoid->requested_action == 0x30) {
                zoid->action = 0x1A;
            }
            zoid->launch_velocity[1] = 0.01 * (f32) * (s32 *)(control + 0xD0) + zoid->displacement[1];
            if (zoid->launch_velocity[1] > 1.0f) {
                zoid->launch_velocity[1] = 1.0f;
            }
            if (zoid->field_0170 == 0 && zoid->ground_polygon != GROUND_POLYGON_NONE) {
                index = grdcPolygon[zoid->ground_polygon].normal_index;
                normal = &grdcNormal[index];
                zoid->launch_velocity[0] += normal->x;
                zoid->launch_velocity[2] += normal->z;
                zoid->launch_velocity[1] *= normal->y;
            }
            zoid->action_phase = 0;
            zoid->requested_action = 0;
            if (zoid->position[1] > 1.0f + zoid->ground_height) {
                flag = 0;
                if (*(s32 *)(control + 0xF8) == 0 && zoid->field_0170 == 0) {
                    flag = 1;
                } else if (zoid->grounded != 0 || zoid->field_1EAE != 0xFFFF) {
                    flag = 1;
                }
                if (zoid->action == 0x17 && *(u16 *)(zoid->hip_coobj + 0x28) != 0xFFFF) {
                    flag = 1;
                }
                if (flag != 0) {
                    zoid->action = 0;
                }
            }
            if (zoid->field_0170 != 0 && (zoid->field_1EAC & 1)) {
                zoid->action = 0;
            }
            break;
        case 27:
            if (absf(zoid->knockback[1]) >= absf(zoid->knockback[0])
                && absf(zoid->knockback[1]) >= absf(zoid->knockback[2])) {
                if (zoid->knockback[1] > 0.0f) {
                    zoid->action = 0x21;
                } else {
                    zoid->action = 0x20;
                }
            } else {
                relative2 = vector_heading(zoid->knockback[0], zoid->knockback[2]) - zoid->heading;
                angLimit(&relative2);
                magnitude2 = absf(relative2);
                if (relative2 > 0.0f) {
                    zoid->action = 0x1E;
                } else {
                    zoid->action = 0x1D;
                }
                if (magnitude2 < DEG(45)) {
                    zoid->action = 0x1F;
                }
                if (magnitude2 > DEG(135)) {
                    zoid->action = 0x1C;
                }
            }
            zoid->knockback[0] += zoid->displacement[0];
            zoid->knockback[2] += zoid->displacement[2];
            for (i = 0; i < 3; i++) {
                zoid->launch_velocity[i] = zoid->knockback[i];
            }
            if (zoid->field_1E5C != 0) {
                zoid->field_1E5C = 0;
                for (i = 0; i < 3; i++) {
                    zoid->knockback[i] = 0.0f;
                    zoid->field_1D20[i] = 0.0f;
                }
            }
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
        case 33:
            zoid->action_phase = 0;
            zoid->requested_action = 0;
            break;
        case 34:
            length = sLenPoint3dR(zoid->knockback);
            if (length > 0.22) {
                zoid->knockback[0] = 2.0f * (zoid->knockback[0] / length);
                zoid->knockback[1] = 2.0f * (zoid->knockback[1] / length);
                zoid->knockback[2] = 2.0f * (zoid->knockback[2] / length);
            }
            zoid->knockback[1] = 0.4 * ((f32) * (s32 *)(table + 0x158) / 100.0);
            if (absf(zoid->knockback[1]) >= absf(zoid->knockback[0])
                && absf(zoid->knockback[1]) >= absf(zoid->knockback[2])) {
                zoid->knockback[1] = 0.4 * ((f32) * (s32 *)(table + 0x158) / 100.0);
                if (zoid->knockback[1] > 0.0f) {
                    zoid->action = 0x28;
                } else {
                    zoid->action = 0x27;
                }
            } else {
                relative3 = vector_heading(zoid->knockback[0], zoid->knockback[2]) - zoid->heading;
                angLimit(&relative3);
                magnitude3 = absf(relative3);
                if (relative3 > 0.0f) {
                    zoid->action = 0x25;
                } else {
                    zoid->action = 0x24;
                }
                if (magnitude3 < DEG(45)) {
                    zoid->action = 0x26;
                }
                if (magnitude3 > DEG(135)) {
                    zoid->action = 0x23;
                }
                zoid->knockback[1] = 0.4 * ((f32) * (s32 *)(table + 0x158) / 100.0);
            }
        case 35:
        case 36:
        case 37:
        case 38:
        case 39:
        case 40:
            sum = 0.0f;
            for (j = 0; j < 3; j++) {
                v = zoid->knockback[j];
                zoid->launch_velocity[j] = v;
                sum += v * v;
            }
            sum = square_root(sum);
            if (sum > 2.0f) {
                for (j = 0; j < 3; j++) {
                    v = zoid->knockback[j];
                    zoid->launch_velocity[j] = 2.0f * v / sum;
                }
            }
            v = (f32) * (s32 *)(table + 0x158) * (f32) * (s32 *)(table + 0x158) / 100.0 / 100.0;
            zoid->launch_velocity[0] *= v;
            zoid->launch_velocity[2] *= v;
            zoid->launch_velocity[1] = (f32) * (s32 *)(table + 0x158) / 100.0;
            zoid->launch_velocity[0] += zoid->displacement[0];
            zoid->launch_velocity[2] += zoid->displacement[2];
            zoid->action_phase = 0;
            zoid->requested_action = 0;
            if (zoid->field_1E5C != 0) {
                zoid->field_1E5C = 0;
                for (i = 0; i < 3; i++) {
                    zoid->knockback[i] = 0.0f;
                    zoid->field_1D20[i] = 0.0f;
                }
            }
            break;
        case 41:
        case 42:
        case 43:
            zoid->launch_velocity[1] = 0.0f;
            zoid->action = zoid->requested_action;
            zoid->action_phase = 0;
            zoid->requested_action = 0;
            break;
        case 49:
            zoid->action = zoid->requested_action;
            zoid->action_phase = 0;
            zoid->requested_action = 0;
            break;
        case 50:
            if (zoid->foot_contacts != 0 || zoid->grounded != 0) {
                zoid->action = zoid->requested_action;
                zoid->action_phase = 0;
                zoid->requested_action = 0;
            }
            break;
        }
    }
    (void)slider;
}
