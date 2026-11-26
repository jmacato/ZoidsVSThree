#include "ground_collision.h"
#include "model_archive.h"
#include "angle.h"
#include "matrix.h"
#include "joint_matrix.h"

extern double sin(double);

typedef struct Missile3 {
    s32 flags;
    s32 bullet;
    s32 kind;
    s32 zoid_hit;
    s32 hit_ground;
    u16 ground_polygon;
    u8 pad_16[0x1C - 0x16];
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
extern void misProcParabola(Missile3 *missile);

void misProcGround(Missile3 *missile)
{
    Vec3 position;
    Vec3 local;
    u16 polygon_index;
    s32 normal_index;
    Mtx rot;
    s32 i;
    Vec3 *normal;
    f32 angle;

    if (missile->hit_ground == 0) {
        misProcParabola(missile);
        return;
    }
    missile->speed = 0.0f;
    for (i = 0; i < 3; i++) {
        (&position.x)[i] = missile->matrix[i][3];
    }
    polygon_index = missile->ground_polygon;
    if (polygon_index == GROUND_POLYGON_NONE) {
        sColPosY(&position, &polygon_index);
    }
    if (polygon_index == GROUND_POLYGON_NONE)
        return;
    normal_index = grdcPolygon[polygon_index].normal_index;
    normal = &grdcNormal[normal_index];
    if (normal == 0)
        return;
    for (i = 0; i < 3; i++) {
        (&position.x)[i] -= (&normal->x)[i];
    }

    PSMTXMultVec(missile->inverse, &position, &local);
    angle = 0.0f;
    if (local.z > sin(DEG2RAD_D(10.0))) {
        angle = -DEG2RAD_F(10.0f);
    }
    if (local.z < -sin(DEG2RAD_D(10.0))) {
        angle = DEG2RAD_F(10.0f);
    }
    if (angle) {
        PSMTXRotRad(rot, 'Y', angle);
        PSMTXConcat(missile->matrix, rot, missile->matrix);
    }
    angle = 0.0f;
    if (local.y > sin(DEG2RAD_D(10.0))) {
        angle = DEG2RAD_F(10.0f);
    }
    if (local.y < -sin(DEG2RAD_D(10.0))) {
        angle = -DEG2RAD_F(10.0f);
    }
    if (angle) {
        PSMTXRotRad(rot, 'Z', angle);
        PSMTXConcat(missile->matrix, rot, missile->matrix);
    }
}
