extern "C" {
#pragma readonly_strings on
#pragma dont_inline on
#pragma bool off
#include "types.h"
#include "zoid3.h"

typedef struct GameModeState3 {
    u8 reserved_00[4];
    s32 game_type;
    u8 reserved_08[0x18];
} GameModeState3;
extern GameModeState3 GameMode;
extern void ZoidSetAnim(ZoidState *zoid, s32 anim);
extern void zdVoiceScG(ZoidState *zoid, s32 voice);
extern void zdChgNormal(ZoidState *zoid);
extern void sLinear1D(f32 *value, f32 target, f32 rate);
extern void ZoidSusumuStepVF(ZoidState *zoid, s32 flag);
extern void __assert(const char *file, s32 line, const char *expr);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void zdFace(ZoidState *zoid);
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40
#define JOBJ_USE_QUATERNION 0x20000
#pragma auto_inline off
static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & JOBJ_USER_DEF_MTX) && (jobj->flags & JOBJ_MTX_DIRTY);
}
#define HSD_JObjSetMtxDirty(jobj) \
    do { \
        if ((jobj) != 0 && !HSD_JObjMtxIsDirty(jobj)) \
            HSD_JObjSetMtxDirtySub(jobj); \
    } while (0)
static inline void HSD_JObjSetRotationX(HSD_JObj *jobj, f32 x)
{
    jobj ? (void)0 : __assert("jobj.h", 676, "jobj");
    !(jobj->flags & JOBJ_USE_QUATERNION) ? (void)0 : __assert("jobj.h", 677, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    jobj->rotation[0] = x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}
static inline void HSD_JObjSetRotationY(HSD_JObj *jobj, f32 y)
{
    jobj ? (void)0 : __assert("jobj.h", 696, "jobj");
    !(jobj->flags & JOBJ_USE_QUATERNION) ? (void)0 : __assert("jobj.h", 697, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    jobj->rotation[1] = y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}
extern void ZoidSusumuStepV(ZoidState *zoid);
extern void stepMove(ZoidState *zoid);
extern void zdLinierTm(ZoidState *zoid, s32 frames);
extern s32 zdCol(ZoidState *zoid, f32 *vec, f32 distance);
extern f32 zdColPosY(f32 *point, s32 flag);
typedef struct GroundMask {
    u8 bits[4];
} GroundMask;
typedef struct ZoidDat3 {
    u8 reserved_000[0x6C6];
    s16 attack_range[24];
    u8 reserved_6F6[0x106];
} ZoidDat3;
extern ZoidDat3 Tea_zoiddat[];
extern void OSReport(const char *fmt, ...);
extern f32 beSide(f32 value, f32 target, f32 step);
extern s32 ZoidSisei(ZoidState *zoid);
extern s32 zdAtkSub(ZoidState *zoid);
extern void zdAtkSubFor(ZoidState *zoid, s32 attack);
extern void zdAtkSubForPull(ZoidState *zoid, s32 attack);
extern void chkNav(ZoidState *zoid);
extern s32 zdFaceAtk(ZoidState *zoid, f32 distance, f32 offset);
extern f32 zdGoYA(ZoidState *zoid, f32 a, f32 b);
extern f32 sColPtJobj(u8 *a, u8 *b, GroundMask *mask);
extern void coBakAtk(ZoidState *zoid);
extern void zdAtackSetEffect(ZoidState *zoid, s32 effect);
extern void zdSetXYZ(ZoidState *zoid);
extern void sMakeMatrix(HSD_JObj *joint);
extern void setAnimRate(HSD_JObj *joint, f32 rate);
extern void ZoidInertiaAtk(ZoidState *zoid);
extern s32 zdAtkSubLakka(ZoidState *zoid);
typedef struct GrdPoly3 {
    u8 reserved_00[4];
    u16 normal_index;
    u8 reserved_06[26];
} GrdPoly3;
extern GrdPoly3 *grdcPolygon;
extern Vec3 *grdcNormal;
extern void sEffectSet(s32 type, s32 mode, f32 *position, HSD_JObj *source, struct ZoidState *zoid);
extern void dummyFunc(const char *str);
extern s32 sprintf(char *buf, const char *fmt, ...);
extern f64 sin(f64 x);
extern f64 cos(f64 x);
extern void zdVaSet(ZoidState *zoid);
extern void zdJumpMove(ZoidState *zoid);
extern void ZoidWalkJ(ZoidState *zoid);
extern void ZoidWalkJ3(ZoidState *zoid);
extern void ZoidWalk(ZoidState *zoid);
typedef struct AtkTbl5 {
    s32 v[5];
} AtkTbl5;

void ZoidSiseiFace(ZoidState *zoid);
void ZoidJump(ZoidState *zoid);
void ZoidActStep(ZoidState *zoid);
void ZoidActStepF(ZoidState *zoid);
void ZoidActAtack(ZoidState *zoid);
static const u32 lit_371[3] = { 0x00000000, 0x00000000, 0x00000000 };
#pragma dont_inline off
void ZoidSiseiFace(ZoidState *zoid)
{
    f32 saveA = zoid->face_yaw;
    f32 saveB = zoid->face_pitch;
    f32 yawA;
    f32 yawB;

    zdFace(zoid);
    yawA = zoid->face_yaw;
    if (zoid->buckle_joint != 0)
        HSD_JObjSetRotationY(zoid->buckle_joint, 8.0 * yawA / 53.0);
    if (zoid->field_1AD8 != 0)
        HSD_JObjSetRotationY(zoid->field_1AD8, 20.0 * yawA / 53.0);
    if (zoid->field_1ADC != 0)
        HSD_JObjSetRotationY(zoid->field_1ADC, 25.0 * yawA / 53.0);
    yawB = zoid->face_pitch;
    if (zoid->buckle_joint != 0)
        HSD_JObjSetRotationX(zoid->buckle_joint, 8.0 * yawB / 53.0);
    if (zoid->field_1AD8 != 0)
        HSD_JObjSetRotationX(zoid->field_1AD8, 20.0 * yawB / 53.0);
    if (zoid->field_1ADC != 0)
        HSD_JObjSetRotationX(zoid->field_1ADC, 25.0 * yawB / 53.0);
}
#pragma dont_inline on

static const char lit_960[9] __attribute__((aligned(4))) = "WkSuSpd>";
#define DEG(x) (2.0 * (3.1415926 * (x)) / 360.0)

void ZoidJump(ZoidState *zoid)
{
    static char aaa[256];
    f32 vy;
    void *cam;
    f32 power[46] = {
        0.0f, 0.3f, 0.34f, 0.4f, 0.47f, 0.5f, 0.57f, 0.6f, 0.66f, 0.69f, 0.7f, 0.76f, 0.79f, 0.8f,
        0.831f, 0.865f, 0.9f, 0.93f, 0.96f, 0.985f, 1.0f, 1.03f, 1.06f, 1.08f, 1.1f, 1.12f, 1.14f,
        1.16f, 1.18f, 1.2f, 1.22f, 1.24f, 1.26f, 1.28f, 1.3f, 1.32f, 1.34f, 1.36f, 1.38f, 1.4f, 1.5f,
        1.5f, 1.6f, 1.6f, 1.7f, 0.0f,
    };
    s32 state;
    ZoidControlData *control;
    s32 anim;
    s32 mode;
    f32 turn;
    f32 dx;
    f32 push;
    f32 dz;
    Vec3 *normal;
    HSD_JObj *effect_joint;

    zoid->slide_frames = 0;
    cam = zoid->camera;
    zoid->field_1C34 = 0;
    if (zoid->requested_action == 1 || zoid->requested_action == 2) {
        zoid->requested_action = 0;
    }
    state = zoid->jump_phase;
    vy = zoid->velocity[1];
    control = (ZoidControlData *)zoid->anim_data;
    turn = zoid->field_1C90[0];
    if (state == 0x11 || (state == 0x21 && zoid->grounded == 0)) {
        if (zoid->requested_action == 0xd && zoid->field_1DB0 < 8) {
            zoid->requested_action = 0;
        }
        if (zoid->jump_attack_phase == 0 && zoid->requested_action == 0xd) {
            ZoidSetAnim(zoid, 0x41);
            zdAtackSetEffect(zoid, 5);
            zdVoiceScG(zoid, 0x12);
            zoid->requested_action = 0;
            zoid->jump_attack_phase = 1;
        }
        zoid->requested_action = 0;
    }
    if (zoid->jump_attack_phase == 1 && (state == 0x21 || state == 0x11) && zoid->animation_stopped != 0) {
        ZoidSetAnim(zoid, 0x42);
        zoid->requested_action = 0;
        zoid->jump_attack_phase = 2;
    }
    if (zoid->jump_attack_phase != 0) {
        zoid->field_1DA0 = 5;
    }
    dummyFunc("s");
    sprintf(aaa, "-%02X-", state);
    dummyFunc(aaa);
    switch (state) {
    case 1:
    case 2:
        dummyFunc("j1");
        if ((u32)zoid->camera_joint != 0) {
            zoid->field_1CF0 = ((HSD_JObj *)zoid->camera_joint)->matrix[1][3];
        }
        if (control->field_00F8 != 1) {
            effect_joint = zoid->f_base_joint;
            if (effect_joint == 0) {
                effect_joint = zoid->joint;
            }
            sEffectSet(0x3c, 1, 0, effect_joint, 0);
        }
        dummyFunc(".a.");
        zoid->jump_attack_phase = 0;
        zoid->velocity[0] = 0.0f;
        zoid->velocity[2] = 0.0f;
        zoid->velocity[1] = power[*(s32 *)((u8 *)control + ((state - 1) << 2) + 0xa0)];
        if (control->field_00F8 != -1 && zoid->ground_polygon != 0xffff) {
            normal = &grdcNormal[grdcPolygon[zoid->ground_polygon].normal_index];
            zoid->velocity[0] = 0.01 * normal->x;
            zoid->velocity[2] = 0.01 * normal->z;
            zoid->velocity[1] *= normal->y;
        }
        dummyFunc("b.");
        if (zoid->field_1ACC != 0) {
            push = 0.02 * zoid->senter_roll;
            dx = push * sin(DEG(90) + zoid->heading);
            dz = push * cos(DEG(90) + zoid->heading);
            zoid->velocity[0] += dx;
            zoid->velocity[2] += dz;
        }
        dummyFunc("c.");
        anim = 13;
        if (turn > 0.0f) {
            anim = 17;
        } else if (turn < 0.0f) {
            anim = 21;
        }
        ZoidSetAnim(zoid, anim);
        zoid->jump_phase = 3;
        break;
    case 3:
        dummyFunc("j3");
        if (zoid->animation_stopped != 0 || zoid->animation_looped != 0) {
            anim = 14;
            if (turn > 0.0f) {
                anim = 18;
            } else if (turn < 0.0f) {
                anim = 22;
            }
            zoid->jump_phase = 16;
            ZoidSetAnim(zoid, anim);
            zoid->jump_attack_phase = 0;
        }
        break;
    case 16:
        dummyFunc("j4");
        anim = 14;
        if (turn > 0.0f) {
            anim = 18;
        } else if (turn < 0.0f) {
            anim = 22;
        }
        if (zoid->current_animation != anim) {
            ZoidSetAnim(zoid, anim);
            zdLinierTm(zoid, 30);
        }
        zoid->jump_phase = 17;
        zoid->gene_frames = 0;
        break;
    case 17:
        zoid->gene_frames++;
        dummyFunc("e1");
        zdJumpMove(zoid);
        if (zoid->velocity[1] < 0.0f) {
            zoid->jump_phase = 32;
        }
        if (zoid->velocity[1] < 0.5) {
            zoid->jump_phase = 18;
        }
        break;
    case 18:
        dummyFunc("e2");
        zdJumpMove(zoid);
        if (zoid->velocity[1] < 0.0f) {
            zoid->jump_phase = 32;
        }
        if (zoid->jump_attack_phase == 0) {
            anim = 15;
            if (turn > 0.0f) {
                anim = 19;
            } else if (turn < 0.0f) {
                anim = 23;
            }
            if (zoid->current_animation != anim) {
                ZoidSetAnim(zoid, anim);
                zdLinierTm(zoid, 240);
            }
        }
        break;
    case 32:
        if (zoid->jump_attack_phase == 0) {
            anim = 15;
            if (turn > 0.0f) {
                anim = 19;
            } else if (turn < 0.0f) {
                anim = 23;
            }
            if (zoid->current_animation != anim) {
                ZoidSetAnim(zoid, anim);
                zdLinierTm(zoid, 240);
            }
        }
        zoid->jump_phase = 33;
    case 33:
        dummyFunc("t1");
        zdVaSet(zoid);
        zdJumpMove(zoid);
        mode = 0;
        if (control->field_00F4 != 0) {
            if (zoid->feet[0].joint != 0 && (zoid->feet[0].flags & 1)) {
                mode = 1;
            }
            if (zoid->feet[1].joint != 0 && (zoid->feet[1].flags & 1)) {
                mode = 1;
            }
            if (zoid->feet[2].joint != 0 && (zoid->feet[2].flags & 1)) {
                mode = 1;
            }
            if (zoid->feet[3].joint != 0 && (zoid->feet[3].flags & 1)) {
                mode = 1;
            }
            if (*(u32 *)(zoid->r_leg2_coobj + 0) != 0 && (*(u32 *)(zoid->r_leg2_coobj + 0x14) != 0 || *(u32 *)(zoid->r_leg2_coobj + 0x18) != 0)) {
                mode = 1;
            }
            if (*(u32 *)(zoid->r_leg1_coobj + 0) != 0 && (*(u32 *)(zoid->r_leg1_coobj + 0x14) != 0 || *(u32 *)(zoid->r_leg1_coobj + 0x18) != 0)) {
                mode = 1;
            }
            if (*(u32 *)(zoid->l_leg2_coobj + 0) != 0 && (*(u32 *)(zoid->l_leg2_coobj + 0x14) != 0 || *(u32 *)(zoid->l_leg2_coobj + 0x18) != 0)) {
                mode = 1;
            }
            if (*(u32 *)(zoid->l_leg1_coobj + 0) != 0 && (*(u32 *)(zoid->l_leg1_coobj + 0x14) != 0 || *(u32 *)(zoid->l_leg1_coobj + 0x18) != 0)) {
                mode = 1;
            }
        } else if (zoid->foot_contacts != 0 || zoid->grounded != 0) {
            mode = 1;
        }
        if (zoid->displacement[1] > 0.0f) {
            mode = 1;
        }
        if (*(u32 *)(zoid->bust_coobj + 0x18) != 0) {
            mode = 1;
        }
        if (control->field_00F8 == 1) {
            if (zoid->field_1CF0 >= ((HSD_JObj *)zoid->camera_joint)->matrix[1][3]) {
                mode = 1;
            }
            if (zoid->position[1] <= zoid->ground_height) {
                mode = 1;
            }
        }
        if (mode != 0) {
            zoid->jump_phase = 48;
            zoid->field_1DD4 = 60;
        }
        break;
    case 48:
        dummyFunc("j5");
        zoid->jump_attack_phase = 0;
        if (zoid->velocity[1] > -1.2) {
            zoid->action = 0;
            zoid->jump_phase = 0;
            if (zoid->velocity[1] < -0.4 && control->field_00F8 != 1) {
                effect_joint = zoid->f_base_joint;
                if (effect_joint == 0) {
                    effect_joint = zoid->joint;
                }
                if (effect_joint != 0) {
                    sEffectSet(0x3c, 1, 0, effect_joint, 0);
                }
            }
            ZoidSetAnim(zoid, 1);
        } else {
            anim = 16;
            if (turn > 0.0f) {
                anim = 20;
            } else if (turn < 0.0f) {
                anim = 24;
            }
            if (control->field_00F8 != -1) {
                effect_joint = zoid->f_base_joint;
                if (effect_joint == 0) {
                    effect_joint = zoid->joint;
                }
                sEffectSet(0x3c, 1, 0, effect_joint, 0);
            }
            ZoidSetAnim(zoid, anim);
            zoid->jump_phase = 49;
        }
        break;
    case 49:
        zoid->field_1BFC = 0;
        if (zoid->jump_attack_phase != 0) {
            zoid->feet[0].no_contact_frames = 0;
            zoid->feet[1].no_contact_frames = 0;
        }
        zoid->jump_attack_phase = 0;
        if (zoid->animation_stopped != 0 || zoid->animation_looped != 0) {
            zoid->jump_phase = 0;
            zoid->action = 0;
            ZoidSetAnim(zoid, 1);
        }
        break;
    }
    mode = 2;
    if (zoid->jump_phase == 1) {
        mode = 1;
    }
    if (zoid->jump_phase == 48) {
        mode = 0;
    }
    if (zoid->jump_phase == 49) {
        mode = 0;
    }
    if (zoid->field_0170 != 0) {
        mode = 3;
    }
    dummyFunc("k");
    if (mode == 3) {
        ZoidWalkJ3(zoid);
    }
    if (mode == 2) {
        ZoidWalkJ(zoid);
    }
    if (mode == 1) {
        ZoidWalk(zoid);
    }
}

static const AtkTbl5 lit_2318 = { { 67, 69, 71, 73, 75 } };
static const AtkTbl5 lit_2319 = { { 68, 70, 72, 74, 76 } };
static const char lit_2558[14] = "float cancel\n";
void ZoidActStep(ZoidState *zoid)
{
    s32 busy;
    u8 *slider;
    s32 voice;
    s32 below;
    s32 tblA[4] = { 25, 29, 33, 37 };
    s32 tblB[4] = { 26, 30, 34, 38 };
    s32 tblC[4] = { 27, 31, 35, 39 };
    s32 tblD[4] = { 28, 32, 36, 40 };
    ZoidControlData *control;

    busy = 0;
    slider = (u8 *)zoid->slider_info;
    control = (ZoidControlData *)zoid->anim_data;
    zoid->field_1CA0 = 0;
    if (slider != 0) {
        if (zoid->requested_action == 0x17)
            busy = 1;
        if (zoid->requested_action == 0x18)
            busy = 1;
        if (zoid->requested_action == 0x19)
            busy = 1;
        if (zoid->requested_action == 0x1a)
            busy = 1;
        if (zoid->requested_action == 0x2d)
            busy = 1;
        if (zoid->requested_action == 0x2e)
            busy = 1;
        if (zoid->requested_action == 0x2f)
            busy = 1;
        if (zoid->requested_action == 0x30)
            busy = 1;
        if (busy != 0)
            zoid->requested_action = 0;
        if (zoid->action_phase >= 0x10 && zoid->action_phase < 0x30)
            ZoidSusumuStepV(zoid);
        switch (zoid->action_phase) {
        case 0:
            busy = 0;
            zoid->field_1DBC |= 1;
            zoid->field_1CF0 = ((HSD_JObj *)zoid->camera_joint)->matrix[1][3];
            if (slider[0x70c] == 0) {
                if (control->field_00F8 == 1) {
                    if (zdCol(zoid, zoid->launch_velocity, 10.0f) != 0)
                        busy = 1;
                }
            } else {
                if (zdCol(zoid, zoid->launch_velocity, (f32)slider[0x70c]) != 0)
                    busy = 1;
            }
            if (busy != 0) {
                zoid->action_phase = 0x99;
                break;
            }
            ZoidSetAnim(zoid, tblA[zoid->action - 0x17]);
            zoid->action_phase = 1;
            voice = 1;
            if (GameMode.game_type == 1 || GameMode.game_type == 4) {
                if (zoid->slot != Zoid[0].slot)
                    voice = 0;
                if (zoid == &Zoid[2])
                    voice = 0;
            }
            if (voice != 0)
                zdVoiceScG(zoid, 0x1c);
            break;
        case 1:
            if (zoid->animation_stopped == 0 && zoid->animation_looped == 0)
                break;
        case 0x10:
            ZoidSetAnim(zoid, tblB[zoid->action - 0x17]);
            zoid->action_phase = 0x11;
            break;
        case 0x11:
            stepMove(zoid);
            if (*(void **)(zoid->bust_coobj + 0x18) != 0)
                zoid->launch_velocity[1] = 0.0f;
            if (*(void **)(zoid->hip_coobj + 0x18) != 0)
                zoid->launch_velocity[1] = 0.0f;
            if (*(void **)(zoid->neck_coobj + 0x18) != 0)
                zoid->launch_velocity[1] = 0.0f;
            if (zoid->launch_velocity[1] > 0.0f)
                break;
        case 0x20:
            ZoidSetAnim(zoid, tblC[zoid->action - 0x17]);
            zdLinierTm(zoid, 0x3c);
            zoid->action_phase = 0x21;
            break;
        case 0x21:
            if (zoid->action == 0x18) {
                zoid->field_1C90[2] = 0.0f;
                zoid->field_1C90[1] = 0.0f;
                zoid->field_1C90[0] = 0.0f;
            }
            stepMove(zoid);
            if (control->field_00F8 == 1) {
                below = 0;
                if (zoid->field_1CF0 >= ((HSD_JObj *)zoid->camera_joint)->matrix[1][3])
                    below = 1;
                if (zoid->position[1] <= zdColPosY(zoid->position, 0))
                    below = 1;
                if (below != 0)
                    zoid->action_phase = 0x30;
                break;
            }
            if (zoid->ground_normal_count == 0 && zoid->grounded == 0)
                break;
            zoid->grounded_frames = 0;
            zoid->action_phase = 0x30;
        case 0x22:
            zoid->grounded_frames = zoid->grounded_frames + 1;
        case 0x30:
            ZoidSetAnim(zoid, tblD[zoid->action - 0x17]);
            zoid->field_1DD8 = 0x3c;
            zoid->action_phase = 0x31;
            if (zoid->field_1C90[1] >= 15.0)
                zoid->action_phase = 0x99;
            break;
        case 0x31:
            if (zoid->animation_stopped == 0 && zoid->animation_looped == 0)
                break;
        default:
            zdChgNormal(zoid);
            break;
        }
        zoid->field_1C74 = 0.0f;
    }
}

void ZoidActStepF(ZoidState *zoid)
{
    s32 busy;
    s32 voice;
    s32 tblA[4] = { 25, 29, 33, 37 };
    s32 tblB[4] = { 26, 30, 34, 38 };
    s32 tblC[4] = { 27, 31, 35, 39 };
    s32 tblD[4] = { 28, 32, 36, 40 };
    u16 *slider;
    void *anim;

    busy = 0;
    slider = zoid->slider_info;
    anim = zoid->anim_data;
    if (slider != 0) {
        if (zoid->requested_action == 0x17)
            busy = 1;
        if (zoid->requested_action == 0x18)
            busy = 1;
        if (zoid->requested_action == 0x19)
            busy = 1;
        if (zoid->requested_action == 0x1a)
            busy = 1;
        if (zoid->requested_action == 0x2d)
            busy = 1;
        if (zoid->requested_action == 0x2e)
            busy = 1;
        if (zoid->requested_action == 0x2f)
            busy = 1;
        if (zoid->requested_action == 0x30)
            busy = 1;
        if (busy != 0)
            zoid->requested_action = 0;
        if (zoid->action_phase >= 0x10 && zoid->action_phase <= 0x30)
            ZoidSusumuStepVF(zoid, zoid->action_phase == 0x30);
        sLinear1D(&zoid->high_angle, 0.0f, 0.0174532924f);
        switch (zoid->action_phase) {
        case 0:
            zoid->field_1DBC |= 1;
            ZoidSetAnim(zoid, tblA[zoid->action - 0x17]);
            zoid->action_phase = 0x10;
            voice = 1;
            if (GameMode.game_type == 1 || GameMode.game_type == 4) {
                if (zoid->slot != Zoid[0].slot)
                    voice = 0;
                if (zoid == &Zoid[2])
                    voice = 0;
            }
            if (voice != 0)
                zdVoiceScG(zoid, 0x1c);
            break;
        case 0x10:
            if (zoid->animation_stopped != 0 || zoid->animation_looped != 0) {
                ZoidSetAnim(zoid, tblB[zoid->action - 0x17]);
                zoid->action_phase = 0x30;
            }
            break;
        case 0x30:
            if (zoid->animation_stopped == 0 && zoid->animation_looped == 0)
                break;
        default:
            zdChgNormal(zoid);
            break;
        }
        zoid->field_1C74 = 0.0f;
    }
}

void ZoidActAtack(ZoidState *zoid)
{
    AtkTbl5 tblA = lit_2318;
    AtkTbl5 tblB = lit_2319;
    f32 saved[3];
    GroundMask mask;
    f32 lift;
    f32 dist;
    f32 range;
    s32 i;
    s32 ok;
    ZoidControlData *control;
    u8 *camera;
    s32 attack;
    u8 *slider;
    s32 busy;
    s32 flags;
    s32 voice;
    s32 grounded;
    s32 turn;

    if (zoid == (void *)0)
        return;
    control = (ZoidControlData *)zoid->anim_data;
    if (control == (void *)0)
        return;
    slider = (u8 *)zoid->slider_info;
    if (slider == 0)
        return;
    camera = (u8 *)zoid->camera;
    if (zoid->requested_action == 2)
        zoid->requested_action = 0;
    if (zoid->requested_action == 1)
        zoid->requested_action = 0;
    busy = 0;
    if (zoid->requested_action == 0x1b)
        busy = 1;
    if (zoid->requested_action == 0x22)
        busy = 1;
    if (busy != 0)
        zoid->action_phase = 0x99;
    turn = zoid->ground_turn;
    attack = zoid->action - 0xd;
    turn = turn;
    turn = turn;
    zoid->face_yaw = beSide(zoid->face_yaw, 0.0f, 0.0872664600f);
    zoid->face_pitch = beSide(zoid->face_pitch, 0.0f, 0.0872664600f);
    zoid->senter_roll = beSide(zoid->senter_roll, 0.0f, 0.0872664600f);
    zoid->f_base_ry = beSide(zoid->f_base_ry, 0.0f, 0.0872664600f);
    ZoidSisei(zoid);
    if (zoid->action_phase == 0)
        zoid->attack_target = -1;
    zdAtkSub(zoid);
    zdAtkSubFor(zoid, attack);
    zoid->jump_attack_phase = 0;
    zdAtkSubForPull(zoid, attack);
    range = (f32)Tea_zoiddat[zoid->type].attack_range[attack];
    chkNav(zoid);
    zoid->gene_frames = zoid->gene_frames + 1;
    switch (zoid->action_phase) {
    case 0:
        lift = zoid->height_offset;
        if (lift > 0.0f) {
            zoid->position[1] = zoid->position[1] + lift;
            zoid->height_offset = zoid->height_offset - lift;
            zoid->field_1C24[1] = zoid->field_1C24[1] + lift;
        }
        if (camera != 0)
            *(s32 *)(camera + 0x34) = 600;
        if (zoid->action == 0xd) {
            zoid->gene_frames = 0;
        } else if (zoid->field_1EB0 == 0 && zoid->field_1EAE == 0xffff && zoid->field_0170 == 0) {
            zoid->ground_turn = 0;
        }
        ok = 1;
        dist = 5.0f;
        if (slider[0x70b] & 2) {
            dist = range;
            if (dist < 5.0f)
                dist = 5.0f;
        }
        if (zdFaceAtk(zoid, dist, 0.0f) != 0)
            ok = 0;
        if (zdGoYA(zoid, 0.0f, 0.5f) > 1.0f)
            ok = 0;
        if (zdGoYA(zoid, 0.0f, 1.0f) > 1.0f)
            ok = 0;
        if (zdGoYA(zoid, 0.0f, 2.0f) > 1.0f)
            ok = 0;
        if (zdGoYA(zoid, 0.0f, 5.0f) > 1.0f)
            ok = 0;
        if (zoid->action != 0xd && zoid->attack_target != -1) {
            if (sColPtJobj((u8 *)zoid->camera_joint, (u8 *)Zoid[zoid->attack_target].camera_joint, (mask = (GroundMask){{3, 0, 0, 0}}, &mask)) == 10000.0f)
                ok = 1;
        }
        if (ok == 0) {
            zoid->action_phase = 0x99;
            for (i = 0; i < 3; i++)
                saved[i] = zoid->joint->child->matrix[i][3];
            ZoidSetAnim(zoid, 1);
            for (i = 0; i < 3; i++)
                zoid->position[i] = saved[i];
            zdSetXYZ(zoid);
            sMakeMatrix(zoid->joint);
            return;
        }
        ok = 1;
        if (control->field_00F4 == 4 && control->field_00F8 == 0) {
            if (zoid->grounded == 0 && zoid->field_1EB0 == 0)
                ok = 0;
            if (zoid->ground_normal_count != 0)
                ok = 1;
        }
        if (control->field_00F8 == 1)
            ok = 1;
        if (ok == 0 && zoid->action != 0xd && zoid->gene_frames < 0x1e)
            ok = 1;
        if (ok == 0) {
            coBakAtk(zoid);
            zoid->action_phase = 0x99;
            zoid->requested_action = 0;
            OSReport(lit_2558);
            return;
        }
        zoid->gene_frames = 0;
        ZoidSetAnim(zoid, tblA.v[zoid->action - 0xd]);
        if (zoid->field_1EB0 != 0)
            zoid->ground_turn = 0xf;
        zdAtackSetEffect(zoid, attack);
        zoid->action_phase = 1;
        zdAtkSub(zoid);
        if (zoid->action == 0xd) {
            voice = 1;
            if (GameMode.game_type == 1 && zoid == &Zoid[2] && zoid->slot == Zoid[0].slot)
                voice = 0;
            if (voice != 0)
                zdVoiceScG(zoid, zoid->action + 5);
        }
        zoid->field_1C90[0] = 0.0f;
        zoid->field_1C90[1] = 0.0f;
        zoid->field_1C90[2] = 0.0f;
        for (i = 0; i < 3; i++) {
            zoid->displacement[i] = 0.0f;
            zoid->field_1C24[i] = zoid->position[i];
        }
        break;
    case 0x11:
        setAnimRate(zoid->joint, 0.0f);
        if (zoid->ground_turn != 0)
            zoid->ground_turn = 0xf;
        if (zoid->field_1EAE != 0xffff || zoid->field_1EB0 != 0 || *(u32 *)(zoid->r_leg2_coobj + 0x1c) != 0 || *(u32 *)(zoid->l_leg2_coobj + 0x1c) != 0) {
            zoid->ground_turn = 0xf;
            zoid->action_phase = 0x13;
            zoid->grounded_frames = 0;
            for (i = 0; i < 3; i++)
                zoid->displacement[i] = 0.0f;
            break;
        }
        if (zoid->grounded != 0) {
            zoid->action_phase = 0x12;
            zoid->grounded_frames = 0;
            zoid->ground_turn = 0xf;
            if (control->field_00F8 == 2) {
                zoid->action_phase = 0x13;
                zoid->grounded_frames = 0;
                for (i = 0; i < 3; i++)
                    zoid->displacement[i] = 0.0f;
            }
        }
        ZoidInertiaAtk(zoid);
        zoid->field_1BFC = 0;
        break;
    case 0x12:
        setAnimRate(zoid->joint, 0.0f);
        if (zoid->field_1EAE != 0xffff || zoid->field_1EB0 != 0) {
            zoid->ground_turn = 0xf;
            zoid->action_phase = 0x13;
            zoid->grounded_frames = 0;
            for (i = 0; i < 3; i++)
                zoid->displacement[i] = 0.0f;
            break;
        }
        zoid->grounded_frames = zoid->grounded_frames + 1;
        ok = 0;
        if (control->field_00F4 != 0) {
            if (*(u32 *)(zoid->r_leg2_coobj + 0) != 0 && (*(u32 *)(zoid->r_leg2_coobj + 0x14) != 0 || *(u32 *)(zoid->r_leg2_coobj + 0x18) != 0))
                ok = 1;
            if (*(u32 *)(zoid->l_leg2_coobj + 0) != 0 && (*(u32 *)(zoid->l_leg2_coobj + 0x14) != 0 || *(u32 *)(zoid->l_leg2_coobj + 0x18) != 0))
                ok = 1;
            if (*(u32 *)(zoid->head_coobj + 0) != 0 && (*(u32 *)(zoid->head_coobj + 0x14) != 0 || *(u32 *)(zoid->head_coobj + 0x18) != 0))
                ok = 1;
            if ((zoid->feet[2].flags & 1) || (zoid->feet[3].flags & 1))
                ok = 1;
        }
        if (zoid->grounded_frames > 6)
            ok = 1;
        if (zoid->grounded != 0)
            ok = 1;
        if (ok != 0) {
            zoid->displacement[0] = 0.0f;
            zoid->displacement[2] = 0.0f;
            if (zoid->displacement[1] > 0.0f)
                zoid->displacement[1] = 0.9f;
            zoid->displacement[1] = 0.9f;
            zoid->action_phase = 0x13;
        } else {
            ZoidInertiaAtk(zoid);
            zoid->field_1BFC = 0;
        }
        break;
    case 1:
        if (camera != 0)
            *(s32 *)(camera + 0x34) = 600;
        if (range > 2.0f) {
            grounded = 1;
            flags = slider[0x70e];
            if (zoid->grounded == 0)
                grounded = 0;
            if (grounded != 0) {
                if ((flags & 1) && *(u16 *)(zoid->head_coobj + 0x28) != 0xffff)
                    zoid->ground_turn = 1;
                if ((flags & 2) && *(u16 *)(zoid->neck_coobj + 0x28) != 0xffff)
                    zoid->ground_turn = 1;
                if ((flags & 4) && *(u16 *)(zoid->bust_coobj + 0x28) != 0xffff)
                    zoid->ground_turn = 1;
            }
        }
        if (zoid->ground_turn != 0)
            zoid->ground_turn = 0xf;
        ok = 0;
        if (zdAtkSubLakka(zoid) != 0) {
            zoid->action_phase = 0x11;
            setAnimRate(zoid->joint, 0.0f);
            break;
        }
        if (zoid->animation_stopped == 0 && zoid->animation_looped == 0)
            ok = 1;
        if (ok != 0)
            break;
    case 0x13:
        zoid->gene_frames = 0;
        if (zoid->requested_action == 0xd && attack + 1 < control->attack_chain_length) {
            zoid->action++;
            zoid->action_phase = 0;
            zoid->requested_action = 0;
            zoid->gene_frames = 0;
            break;
        }
        zoid->action_phase = 2;
    case 2:
        if (zoid->field_1EAE != 0xffff || zoid->field_1EB0 != 0)
            turn = 0xf;
        zoid->attack_target = -2;
        ZoidSetAnim(zoid, tblB.v[zoid->action - 0xd]);
        if (turn != 0 || zoid->field_1A74 != 0)
            zoid->ground_turn = 0xf;
        zoid->field_1A74 = 0;
        zoid->displacement[0] = 0.0f;
        zoid->displacement[1] = 0.0f;
        zoid->displacement[2] = 0.0f;
        zoid->action_phase = 3;
        zoid->gene_frames = 0;
        break;
    case 3:
        zoid->ground_height = zdColPosY(zoid->position, 0);
        lift = zoid->position[1] - zoid->ground_height;
        if (lift < 0.0f) {
            lift = -1.0f;
            zoid->height_offset = zoid->height_offset + lift;
            zoid->position[1] = zoid->position[1] - lift;
        }
        if (zoid->height_offset < -2.0f)
            zoid->height_offset = beSide(zoid->height_offset, -2.0f, 0.2f);
        zoid->attack_target = -2;
        zoid->gene_frames = zoid->gene_frames + 1;
        zoid->displacement[0] = 0.0f;
        zoid->displacement[1] = 0.0f;
        zoid->displacement[2] = 0.0f;
        if (zdAtkSubLakka(zoid) != 0) {
            zoid->action_phase = 0x31;
            zoid->gene_frames = 0;
            setAnimRate(zoid->joint, 0.0f);
            break;
        }
        if (zoid->gene_frames > 0x12c) {
            zoid->action_phase = 0x99;
            break;
        }
        if (zoid->animation_stopped == 0 && zoid->animation_looped == 0)
            break;
    default:
        zoid->action = 0;
        if (zoid->requested_action == 0x1b) {
            zdChgNormal(zoid);
            zoid->requested_action = 0x1b;
        } else if (zoid->requested_action == 0x22) {
            zdChgNormal(zoid);
            zoid->requested_action = 0x22;
        } else {
            zoid->requested_action = 0;
            zdChgNormal(zoid);
            if (turn != 0)
                zoid->ground_turn = 0xf;
            zoid->field_1A74 = 0;
            if (zoid->field_1EAE == 0xffff && turn != 0) {
                for (i = 0; i < 3; i++) {
                    zoid->displacement[i] = 0.0f;
                    zoid->launch_velocity[i] = 0.0f;
                }
            }
            if (camera != 0)
                *(s32 *)(camera + 0x34) = 600;
            zoid->field_1DA0 = -1;
        }
        break;
    case 0x31:
        if (zoid->displacement[1] > 0.0f)
            zoid->displacement[1] = 0.0f;
        if (zoid->launch_velocity[1] > 0.0f)
            zoid->launch_velocity[1] = 0.0f;
        if (zoid->grounded != 0) {
            zoid->action_phase = 3;
            zoid->grounded_frames = 0;
            setAnimRate(zoid->joint, 0.5f);
        }
        if (zoid->gene_frames > 0x12c)
            zoid->action_phase = 0x99;
        ZoidInertiaAtk(zoid);
        zoid->field_1BFC = 0;
        break;
    }
}

static const u32 lit_2735[6] = { 0x0000002C, 0x0000002D, 0x0000002E, 0x0000002F, 0x00000030, 0x00000031 };
static const u32 lit_2764[6] = { 0x00000032, 0x00000033, 0x00000034, 0x00000035, 0x00000037, 0x00000036 };
static const char lit_2978[20] = "geneX=%d geneZ=%d \n";
static const char lit_2997[9] = "mot-Win\n";
static const char lit_3863[9] = "\n[Z%02d]";
static const char lit_3877[24] = "ZM.pt-----------------\n";
}
