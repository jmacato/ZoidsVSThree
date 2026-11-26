#include "zoid3.h"
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
extern void misProcStraight(Missile3 *missile);
extern void misProcParabola(Missile3 *missile);
extern void misProcFloat(Missile3 *missile);
extern void misProcGround(Missile3 *missile);
extern void misProc00(Missile3 *missile, Vec3 *target_position);
extern void misProc01(Missile3 *missile, Vec3 *target_position);
extern void misProc02(Missile3 *missile, Vec3 *target_position);
extern void misProc03(Missile3 *missile, Vec3 *target_position);
extern void misProcAT50(Missile3 *missile, Vec3 *target_position);
extern void misProcAT20(Missile3 *missile, Vec3 *target_position);

extern HSD_JObj *grdObjGetJObj(void *object);
extern void misProcHB(Missile3 *missile, Vec3 *target);

void misProc(Missile3 *missile)
{
    struct ZoidState *zoid;
    Missile3 *target_missile;
    HSD_JObj *jobj;
    f32 (*mtx)[4];
    Vec3 target_position;
    s32 i;

    switch (missile->proc) {
    case 6:
        misProcStraight(missile);
        break;
    case 7:
        misProcParabola(missile);
        break;
    case 8:
        misProcFloat(missile);
        break;
    case 9:
        misProcGround(missile);
        break;
    default:
        zoid = missile->target_zoid;
        jobj = 0;
        if (zoid != 0) {
            jobj = (HSD_JObj *)zoid->camera_joint;
        } else {
            target_missile = missile->target_missile;
            if (target_missile != 0) {
                jobj = target_missile->joint;
            }
        }
        if (jobj == 0) {
            jobj = grdObjGetJObj(missile->field_30);
        }
        if (jobj == 0) {
            mtx = 0;
        } else {
            mtx = jobj->matrix;
        }
        if (mtx != 0) {
            for (i = 0; i < 3; i++) {
                (&target_position.x)[i] = mtx[i][3];
            }
        } else {
            for (i = 0; i < 3; i++) {
                (&target_position.x)[i] = missile->matrix[i][0] * 10.0f;
            }
        }
        if (missile->proc == 10) {
            misProcHB(missile, &target_position);
        }
        if (mtx != 0) {
            switch (missile->proc) {
            case 0:
                misProc00(missile, &target_position);
                break;
            case 1:
                misProc01(missile, &target_position);
                break;
            case 2:
                misProc02(missile, &target_position);
                break;
            case 3:
                misProc03(missile, &target_position);
                break;
            case 5:
                misProcAT50(missile, &target_position);
                break;
            case 4:
                misProcAT20(missile, &target_position);
                break;
            }
        }
        break;
    }
}
