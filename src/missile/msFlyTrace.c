#include "model_archive.h"
#include "angle.h"

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

typedef struct BulletDat3 {
    char name[8];
    s32 damage;
    s16 speed;
    u8 pad_0E[0x12 - 0x0E];
    s16 kind;
    u8 pad_14[0x16 - 0x14];
    s16 trace_rate;
    u8 pad_18[0x1A - 0x18];
    s16 zoid_hit;
    s16 hit_effect;
    s16 fire_effect;
    s16 se;
    u8 pad_22[0x28 - 0x22];
    s16 turn_angle;
    u8 pad_2A[0x4C - 0x2A];
} BulletDat3;

extern BulletDat3 Tea_bulletdat[131];
extern f32 sLiner(f32 target, f32 current, f32 fraction);
extern void sGlobal2Local(HSD_JObj *joint);

void msFlyTrace(Missile3 *missile)
{
    s32 bullet;
    f32 rate;
    s32 i;
    s32 k;
    s32 n;
    s32 j;

    if (missile == (void *)0)
        return;
    if (missile->purge_timer != 0)
        return;
    if (missile->beam_joints[0] == 0)
        return;
    bullet = missile->bullet;
    rate = (f32)Tea_bulletdat[bullet].trace_rate * 0.01;
    for (i = 6; i > 0; i--) {
        if (missile->beam_joints[i] != (void *)0 && missile->beam_joints[i - 1] != (void *)0) {
            for (k = 0; k < 3; k++) {
                missile->beam_positions[i][k] = sLiner(missile->beam_positions[i - 1][k], missile->beam_positions[i][k], rate);
                missile->beam_joints[i]->matrix[k][3] = missile->beam_positions[i][k];
            }
            for (n = 0; n < 3; n++) {
                for (j = 0; j < 3; j++)
                    missile->beam_joints[i]->matrix[n][j] = missile->beam_joints[i - 1]->matrix[n][j];
            }
            sGlobal2Local(missile->beam_joints[i]);
        }
    }
}
