#include "model_archive.h"
#include "angle.h"
#include "matrix.h"
#include "joint_matrix.h"
#include "random.h"

typedef struct Missile3 {
    s32 flags;
    s32 bullet;
    s32 kind;
    s32 zoid_hit;
    s32 hit_ground;
    u8 pad_14[0x1C - 0x14];
    s32 animation;
    ModelArchive *archive;
    HSD_JObj *joint;
    struct ZoidState *owner;
    s32 owner_weapon_mount;
    struct ZoidState *target_zoid;
    struct Missile3 *target_missile;
    void *field_30;
    u8 pad_3C[0x50 - 0x3C];
    f32 speed;
    f32 turn_rate;
    f32 matrix[3][4];
    f32 previous[3][4];
    f32 step_length;
    f32 inverse[3][4];
    s32 update_count;
    s32 damage;
    s32 purge_timer;
    s32 hit;
    f32 max_speed;
    f32 accel;
    u8 pad_104[0x108 - 0x104];
    s32 proc;
    s32 proc_delay;
    HSD_JObj *beam_joints[7];
    f32 beam_positions[7][3];
    HSD_JObj *a1_joint;
    struct HSD_LObj *light;
    u8 hit_zoids[16];
    s32 se;
    s32 se_playing;
    u32 se_voice;
} Missile3;
extern void PSMTXRotRad(Mtx m, char axis, f32 rad);
static inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

void misProc03(Missile3 *missile, Vec3 *target)
{
    Vec3 local;
    Mtx rot;
    f32 angle;
    s32 elapsed = missile->update_count - missile->proc_delay;

    PSMTXMultVec(missile->inverse, target, &local);
    if (elapsed < 60) {
        if (elapsed % 15 == 0 && local.x < 0.0f) {
            PSMTXRotRad(rot, 'Z', DEG2RAD_F(20.0f));
            PSMTXConcat(missile->matrix, rot, missile->matrix);
        }
    } else {
        if (elapsed % 15 == 0) {
            angle = 0.0f;
            if (local.z > 0.0f) {
                angle = -DEG2RAD_F(20.0f);
            }
            if (local.z < 0.0f) {
                angle = DEG2RAD_F(10.0f);
            }
            if (local.x > 100.0f && absf(angle) < 0.0017453292482296542) {
                angle = 2.0 * (3.1415926 * (f32)(HSD_Randi(10) - 5)) / 360.0;
            }
            if (angle != 0.0f) {
                PSMTXRotRad(rot, 'Y', angle);
                PSMTXConcat(missile->matrix, rot, missile->matrix);
            }
        }
        if (elapsed % 15 == 10) {
            angle = 0.0f;
            if (local.y > 0.0f) {
                angle = DEG2RAD_F(20.0f);
            }
            if (local.y < 0.0f) {
                angle = -DEG2RAD_F(10.0f);
            }
            if (angle != 0.0f) {
                PSMTXRotRad(rot, 'Z', angle);
                PSMTXConcat(missile->matrix, rot, missile->matrix);
            }
        }
        PSMTXRotRad(rot, 'X', DEG2RAD_F(10.0f));
        PSMTXConcat(missile->matrix, rot, missile->matrix);
    }
}
