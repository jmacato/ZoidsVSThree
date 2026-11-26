#include "zoid3.h"
#include "math_support.h"
#include "angle.h"
#pragma readonly_strings on

typedef struct PadState3 {
    u8 pad_00[0x40];
    s8 held_40;
    s8 held_41;
    s8 held_42;
    u8 pad_43[2];
    s8 held_45;
    u8 pad_46;
    s8 held_47;
    u8 pad_48[7];
    s8 pressed_4f;
    s8 pressed_50;
    s8 pressed_51;
    s8 pressed_52;
    u8 pad_53[8];
    s8 pressed_5b;
    s8 pressed_5c;
    s8 pressed_5d;
    s8 pressed_5e;
    u8 pad_5f;
    s8 pressed_60;
    s8 pressed_61;
    u8 pad_62[2];
    f32 stick_x;
    f32 stick_y;
    f32 substick_x;
    f32 substick_y;
    u8 pad_74[0x10];
    s8 rumble;
} PadState3;

typedef struct CameraState3 {
    u8 pad_000[0x1B4];
    s32 field_1B4;
    u8 pad_1B8[0xC];
    ZoidState *zoid;
    s32 target_index;
    u8 pad_1CC[0x1C];
    PadState3 *pad;
    u8 pad_1EC[0x244 - 0x1EC];
    void *cobj;
    u8 pad_248[0x260 - 0x248];
    f32 yaw;
    u8 pad_264[0x2F8 - 0x264];
    s8 substick_held;
    u8 pad_2F9[2];
    s8 scope_on;
    f32 fov;
    void *scope;
} CameraState3;

typedef struct AiState3 {
    u8 pad_00[0x40];
    s32 field_40;
    u8 pad_44[0x8C - 0x44];
    s32 previous_command;
    s32 command;
} AiState3;

typedef struct PersonData3 {
    u8 pad_00[0x38];
    s16 field_38;
    u8 pad_3A[0x68 - 0x3A];
} PersonData3;

extern s32 sCamMuteki;
extern s32 gameTime;
extern s32 padBy;
extern s32 rumble;
extern s32 nowStage;
extern u32 vsyncN;
extern s32 dspPartnerMsgTm;
extern s32 dspPartnerMsgTm2;
extern s32 dspPartnerMsgF;
extern s32 dspOrderAI;
extern s32 dspOrderTm;
extern s8 mgI[];
extern s32 GameMode[];
extern PersonData3 Tea_persondat[];

extern void dummyFunc(const char *);
extern void sCameraTargetZoid(CameraState3 *camera, ZoidState *zoid);
extern void sEffectSet(s32 type, s32 mode, f32 *position, void *source, ZoidState *zoid);
extern s32 zdSatkOk(ZoidState *zoid);
extern void zdWeaponChg(ZoidState *zoid);
extern void zdWeaponFireON(ZoidState *zoid);
extern void zdWeaponFireOFF(ZoidState *zoid);
extern void zdAtack1(ZoidState *zoid);
extern void ZoidSearchNextTargetObj(ZoidState *zoid);
extern void sLinear1D(f32 *value, f32 target, f32 step);
extern void calcPadR(CameraState3 *camera);
extern void zdStep0f(ZoidState *zoid, f32 angle);
extern void *zdWeaponScope(ZoidState *zoid, s32 mount);
extern void PartnerFaceV(s32 face, s32 frames, s32 person, s32 voice);
extern s32 HSD_Randi(s32 maximum);
extern void zdSuperAtackAng(ZoidState *zoid, CameraState3 *camera);
extern f32 atan2f(f32 y, f32 x);
extern void angLimit(f32 *angle);

static inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

void sCameraCtrl(CameraState3 *camera)
{
    s32 i;
    s32 old;
    AiState3 *ai;
    u8 *control;
    s32 command;
    ZoidState *zoid;
    s32 index;
    s32 roll;
    s32 saved;
    s8 held;
    f32 angle;
    s8 started;
    s32 mode;
    s32 old_scope;
    f32 delta;
    s32 person;
    void *scope;
    s32 mount;
    PadState3 *pad;
    ZoidState *partner;
    f32 scale;
    f32 x;
    f32 y;
    f32 length;
    f32 yaw;
    f32 previous;
    f32 magnitude;
    f32 amount;
    f32 stick;

    if (camera != (void *)0 && camera->cobj != (void *)0 && (pad = camera->pad) != (void *)0
        && (zoid = camera->zoid) != 0) {
        control = 0;
        if (zoid != 0) {
            control = zoid->anim_data;
        }
        if (control != 0) {
            dummyFunc("a/");
            if (sCamMuteki != 0) {
                zoid->health = zoid->max_health;
                gameTime = -1;
            }
            if (sCamMuteki == 2) {
                for (i = 0; i < 16; i++) {
                    if (Zoid[i].joint != (void *)0) {
                        Zoid[i].health = Zoid[i].max_health;
                    }
                }
            }
            scale = (f32)padBy / 100.0;
            if (zoid->booster_on != 0) {
                scale = 4.0 * ((f32)padBy / 100.0);
            }
            dummyFunc("b/");
            index = camera->target_index;
            saved = camera->field_1B4;
            sCameraTargetZoid(camera, &Zoid[index]);
            if (zoid != 0) {
                pad->rumble = zoid->rumble_timer != 0;
                if (zoid->ai_active != 0) {
                    pad->rumble = 0;
                }
            } else {
                pad->rumble = 0;
            }
            if (rumble == 0) {
                pad->rumble = 0;
            }
            if (zoid->ai != 0 && zoid->ai_active != 0) {
                pad->substick_x = 0.0f;
                pad->substick_y = 0.0f;
                pad->pressed_60 = 0;
                pad->pressed_61 = 0;
                pad->pressed_5d = 0;
                pad->held_42 = 0;
                pad->held_47 = 0;
                pad->pressed_5e = 0;
            }
            if (nowStage == 16 && vsyncN % 30 == 0) {
                sEffectSet(0x6A, 1, 0, zoid->joint, zoid);
            }
            dummyFunc("c/");
            camera->field_1B4 = saved;
            zoid->super_attack_input = pad->held_42 != 0 && pad->held_45 != 0;
            if ((s8)zoid->option_use_state != 0) {
                zoid->super_attack_input = 0;
            }
            if (zoid->death_started != 0) {
                zoid->super_attack_input = 0;
            }
            if (zdSatkOk(zoid) == 0) {
                zoid->super_attack_input = 0;
            }
            if (pad->pressed_5e != 0 && zoid->field_0170 == 0) {
                zoid->requested_action = 2;
            }
            if (pad->pressed_61 != 0) {
                zdWeaponChg(zoid);
            }
            if (zoid->super_attack_input == 0) {
                if (pad->held_42 != 0 && zoid->field_1DA0 == -1 && zoid->weapon_mount == zoid->selected_weapon_mount) {
                    zdWeaponFireON(zoid);
                } else {
                    zdWeaponFireOFF(zoid);
                }
                if (pad->pressed_60 != 0) {
                    if (zoid->field_0170 != 0) {
                        zoid->requested_action = 0x34;
                    } else {
                        zdAtack1(zoid);
                    }
                }
            }
            if (camera->scope_on != 0) {
                if (pad->held_40 != 0) {
                    camera->fov += 0.3;
                }
                if (pad->held_41 != 0) {
                    camera->fov -= 0.3;
                }
                zoid->target_pending = 0;
                zoid->lock_active = 0;
                zoid->requested_action = 0;
            } else {
                if (pad->pressed_5c != 0) {
                    ZoidSearchNextTargetObj(camera->zoid);
                }
                if (pad->pressed_5b != 0 && zoid != 0) {
                    zoid->target_pending = 0;
                    zoid->lock_active = 0;
                }
                if (pad->held_40 != 0 && zoid->field_0170 != 0) {
                    sLinear1D(&zoid->high_angle, 0.0f, 0.1f);
                }
            }
            if (camera->fov > 45.0f) {
                camera->fov = 45.0f;
            }
            if (camera->fov < 1.0f) {
                camera->fov = 1.0f;
            }
            zoid->option_use_state = pad->held_47;
            if (zoid->death_started != 0) {
                zoid->option_use_state = 0;
            }
            if (zoid->option_type == 0) {
                zoid->option_use_state = 0;
            }
            if (zoid->super_attack_input != 0) {
                zoid->option_use_state = 0;
            }
            if (zoid->weapon_mount == 0x13) {
                zoid->option_use_state = 0;
            }
            dummyFunc("f/");
            calcPadR(camera);
            magnitude = zoid->field_1C6C;
            amount = zoid->field_1C70;
            held = camera->substick_held;
            if (magnitude < 0.1) {
                held = 0;
            }
            if (magnitude > 0.3) {
                held = 1;
            }
            started = held != 0 && camera->substick_held == 0;
            camera->substick_held = held;
            stick = zoid->field_1C68;
            if (started != 0) {
                if (zoid->field_0170 == 0) {
                    zdStep0f(zoid, stick);
                } else if (zoid->field_016C == 0) {
                    magnitude = absf(stick);
                    if (magnitude > DEG2RAD_D(45.0) && magnitude < DEG2RAD_D(135.0)) {
                        zdStep0f(zoid, stick);
                    }
                }
            }
            if (zoid->field_0170 != 0) {
                if (magnitude > 0.1) {
                    if (absf(stick) < DEG2RAD_D(45.0)) {
                        zoid->high_angle += 0.03 * amount;
                    }
                    if (absf(stick) > DEG2RAD_D(135.0)) {
                        zoid->high_angle -= 0.03 * amount;
                    }
                }
                if (zoid->high_angle > DEG2RAD_D(60.0)) {
                    zoid->high_angle = DEG2RAD_D(60.0);
                }
                if (zoid->high_angle < -DEG2RAD_D(60.0)) {
                    zoid->high_angle = -DEG2RAD_D(60.0);
                }
            }
            dummyFunc("j/");
            if (zoid != 0 && zoid->index == 0 && Zoid[2].joint != 0 && zoid->slot == Zoid[2].slot
                && GameMode[1] != 5) {
                partner = &Zoid[2];
                ai = (AiState3 *)partner->ai;
                if (partner->death_started != 0) {
                    ai = 0;
                }
                if (ai != 0 && mgI[0x3218] == 0) {
                    old = ai->previous_command;
                    dspPartnerMsgTm2++;
                    if (dspPartnerMsgF == 0) {
                        ai->previous_command = 0;
                    }
                    if (dspPartnerMsgTm == 0) {
                        ai->command = 0;
                        command = -1;
                        if (pad->pressed_51 != 0) {
                            command = 3;
                        }
                        if (pad->pressed_52 != 0) {
                            command = 4;
                        }
                        if (pad->pressed_51 != 0) {
                            ai->command = 3;
                        }
                        if (pad->pressed_52 != 0) {
                            ai->command = 4;
                        }
                        if (pad->pressed_4f != 0) {
                            if (zoid->target_pending != 0) {
                                command = 1;
                            }
                            if (zoid->target_pending != 0) {
                                ai->command = 1;
                            }
                        }
                        if (ai->command == 1 && zoid->target_pending == 0) {
                            command = 0;
                        }
                        if (ai->command == 1 && zoid->target_pending == 0) {
                            ai->command = 0;
                        }
                        if (pad->pressed_50 != 0) {
                            command = 2;
                        }
                        if (pad->pressed_50 != 0) {
                            ai->command = 2;
                        }
                        if (zoid->death_started != 0) {
                            ai->command = old;
                        }
                        if (old != ai->command && ai->command != 0) {
                            person = partner->person;
                            if (dspPartnerMsgF == 0) {
                                roll = HSD_Randi(0x65);
                                if (roll <= Tea_persondat[person].field_38) {
                                    dspPartnerMsgTm2 = 0;
                                    PartnerFaceV(5, 60, person, 11);
                                } else {
                                    ai->command = old;
                                    PartnerFaceV(4, 60, person, 10);
                                }
                                dspPartnerMsgF = 0x258;
                            } else {
                                ai->command = old;
                                PartnerFaceV(4, 60, person, 10);
                            }
                        }
                        if (ai->command != 0) {
                            ai->previous_command = ai->command;
                        }
                        if (command != -1) {
                            dspOrderAI = command;
                            dspOrderTm = 0x78;
                        }
                        if (dspPartnerMsgTm2 > 0x258 && ai->command == 0 && dspOrderAI > 0) {
                            dspPartnerMsgTm2 = 0;
                            ai->command = dspOrderAI;
                            if (ai->command == 1 && zoid->target_pending == 0) {
                                ai->command = 0;
                            }
                        }
                    }
                }
            }
            dummyFunc("o/");
            if (control != 0) {
                mount = zoid->weapon_mount;
                old_scope = camera->scope_on;
                mode = *(s32 *)(control + 0x140 + mount * 4);
                camera->scope_on = zoid->animation_frame == 2;
                scope = zdWeaponScope(zoid, mount);
                if (scope == 0) {
                    scope = zoid->field_1BEC;
                }
                if (scope == 0) {
                    camera->scope_on = 0;
                }
                if (zoid->field_1364 != 0) {
                    camera->scope_on = 0;
                }
                if (mount != zoid->selected_weapon_mount) {
                    camera->scope_on = 0;
                } else if (((WeaponMount *)&zoid->weapon_mounts[mount])->state <= 1) {
                    camera->scope_on = 0;
                }
                (void)((u32)zoid->health & (u32)gameTime);
                camera->scope = scope;
                if (camera->scope_on != 0 && old_scope == 0) {
                    camera->fov = 45.0f;
                }
            }
            dummyFunc("s/");
            y = pad->stick_y * scale;
            x = pad->stick_x * scale;
            length = square_root(x * x + y * y);
            if (length < 0.16) {
                zdSuperAtackAng(zoid, camera);
                if (zoid->ai != 0
                    && ((void)(Zoid[0].health), zoid->ai_active != 0)
                    && ((void)((u32)camera / (u32)zoid),
                        ((AiState3 *)zoid->ai)->field_40 != 0)) {
                    return;
                }
                zoid->field_1C54 = 0.0f;
                zoid->field_1C74 = 0.0f;
                zoid->field_1C78 = 0.0f;
                return;
            }
            zoid->field_1C54 = length;
            angle = atan2f(-x, y);
            previous = zoid->stick_angle;
            angLimit(&angle);
            yaw = camera->yaw;
            zoid->step_heading = angle + yaw;
            zoid->stick_angle = angle;
            zoid->field_1C74 = x;
            zoid->field_1C78 = y;
            angLimit(&zoid->step_heading);
            dummyFunc("v/");
            delta = angle - previous;
            angLimit(&delta);
            if (0.0f == length) {
                zoid->stick_frames = 0.0f;
            } else {
                zoid->stick_frames += 1.0f;
            }
            (void)(Zoid[0].health);

            if (0.0f == length) {
                zoid->stick_steady_frames = 0.0f;
            } else if (absf(delta) > DEG2RAD_D(10.0)) {
                zoid->stick_steady_frames = 0.0f;
            } else {
                zoid->stick_steady_frames += 1.0f;
            }
            zdSuperAtackAng(zoid, camera);
        }
    }
}
