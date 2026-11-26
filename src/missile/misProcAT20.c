#include "model_archive.h"
#include "angle.h"
#include "matrix.h"
#include "joint_matrix.h"

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

void misProcAT20(Missile3 *missile, Vec3 *target)
{
    Vec3 local;
    Mtx rot;
    f32 angle;

    PSMTXMultVec(missile->inverse, target, &local);
    angle = 0.0f;
    if (local.z > 0.0f) {
        angle = -missile->turn_rate;
    }
    if (angle != 0.0f) {
        PSMTXRotRad(rot, 'Y', angle);
        PSMTXConcat(missile->matrix, rot, missile->matrix);
    }
    angle = 0.0f;
    if (local.y > 0.0f) {
        angle = -DEG2RAD_F(10.0f);
    }
    if (local.y < 0.0f) {
        angle = DEG2RAD_F(10.0f);
    }
    if (angle != 0.0f) {
        while (angle) {
            PSMTXRotRad(rot, 'X', angle);
            PSMTXConcat(missile->matrix, rot, missile->matrix);
            PSMTXMultVec(missile->inverse, target, &local);
            angle *= 0.5f;
            if (local.y == 0.0f) {
                break;
            }
            if (local.y > 0.0f && angle > 0.0f) {
                angle = -angle;
            }
            if (local.y < 0.0f && angle < 0.0f) {
                angle = -angle;
            }
        }
    }
}
