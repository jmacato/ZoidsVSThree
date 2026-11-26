#include "model_archive.h"
#include "angle.h"
#include "matrix.h"
#include "joint_matrix.h"
#include "math_support.h"

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
extern f32 sLenPoint3dR(Vec3 *point);
extern f32 atan2f(f32 y, f32 x);
static inline f32 sqrt4(f32 x, volatile f32 *y)
{
    f64 guess;
    if (x > 0.0f) {
        guess = __frsqrte(x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        *y = x * guess;
        return *y;
    }
    return x;
}

void misProcParabola(Missile3 *missile)
{
    Mtx rot;
    Vec3 velocity;
    volatile f32 root;
    f32 angle;
    f32 previous;
    f32 current;
    f32 length;
    f32 offset;
    s32 i;

    if (missile->matrix[1][1] < 0.0f) {
        PSMTXRotRad(rot, 'X', 3.1415925f);
        PSMTXConcat(missile->matrix, rot, missile->matrix);
    } else if (missile->matrix[1][2] != 0.0f) {
        angle = DEG2RAD_F(30.0f);
        if (missile->matrix[1][2] < 0.0f)
            angle = -angle;
        while (angle && missile->matrix[1][2]) {
            if (missile->matrix[1][2] < 0.0f) {
                while (missile->matrix[1][2] < 0.0f) {
                    PSMTXRotRad(rot, 'X', angle);
                    PSMTXConcat(missile->matrix, rot, missile->matrix);
                }
                if (missile->matrix[1][2] > 0.0f)
                    angle = -(angle / 2.0f);
            } else if (missile->matrix[1][2] > 0.0f) {
                while (missile->matrix[1][2] > 0.0f) {
                    PSMTXRotRad(rot, 'X', angle);
                    PSMTXConcat(missile->matrix, rot, missile->matrix);
                }
                if (missile->matrix[1][2] < 0.0f)
                    angle = -(angle / 2.0f);
            }
        }
    }
    for (i = 0; i < 3; i++) {
        (&velocity.x)[i] = missile->matrix[i][0] * missile->speed;
    }
    previous = velocity.y;
    velocity.y = previous - 0.025;
    current = velocity.y;
    missile->speed = sLenPoint3dR(&velocity);
    if (missile->speed > 0.1) {
        length = sqrt4(velocity.x * velocity.x + velocity.z * velocity.z, &root);
        if (length > 0.1) {
            offset = atan2f(length, current);
            angle = atan2f(length, previous) - offset;
            if (angle) {
                PSMTXRotRad(rot, 'Z', angle);
                PSMTXConcat(missile->matrix, rot, missile->matrix);
            } else {
                PSMTXRotRad(rot, 'Z', DEG2RAD_F(-2.0f));
                PSMTXConcat(missile->matrix, rot, missile->matrix);
            }
        } else {
            PSMTXRotRad(rot, 'Z', DEG2RAD_F(-2.0f));
            PSMTXConcat(missile->matrix, rot, missile->matrix);
        }
    } else {
        PSMTXRotRad(rot, 'Z', DEG2RAD_F(-2.0f));
        PSMTXConcat(missile->matrix, rot, missile->matrix);
    }
}
