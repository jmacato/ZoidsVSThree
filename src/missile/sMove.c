#pragma readonly_strings on
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
#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40
extern void sGlobal2Local(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *expr);
#pragma auto_inline off
static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & JOBJ_USER_DEF_MTX) && (jobj->flags & JOBJ_MTX_DIRTY);
}
#define HSD_JObjSetMtxDirty(jobj) \
    do { \
        if ((jobj) != NULL && !HSD_JObjMtxIsDirty(jobj)) \
            HSD_JObjSetMtxDirtySub(jobj); \
    } while (0)

static inline void HSD_JObjSetTranslateX(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 952, "jobj");
    jobj->translation.x = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}
static inline void HSD_JObjSetTranslateY(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 966, "jobj");
    jobj->translation.y = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}
static inline void HSD_JObjSetTranslateZ(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 980, "jobj");
    jobj->translation.z = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}
extern s32 TEA_VidChk(s32 id);
extern s32 sAObjAnimeAll(HSD_JObj *joint);
extern u32 PSMTXInverse(f32 src[3][4], f32 inv[3][4]);
extern void misProc(Missile3 *missile);
extern void HSD_LObjSetPosition(void *lobj, Vec3 *position);

extern void sMissileSetAnim(Missile3 *missile, s32 anim);
extern void msFlyTrace(Missile3 *missile);

void sMove(Missile3 *missile)
{
    f32 step[3];
    Vec3 position;
    s32 k;
    s32 i;
    s32 j;
    register s32 m;

    if (missile == (void *)0)
        return;
    missile->update_count++;
    if (missile->purge_timer != 0)
        return;
    if (missile->hit != 0)
        return;
    if (missile->se) {
        (void)0;
    }
    for (k = 0; k < 3; k++) {
        for (j = 0; j < 4; j++) {
            missile->previous[k][j] = missile->matrix[k][j];
        }
    }
    if (sAObjAnimeAll(missile->joint) != 0) {
        if (missile->animation == 0) {
            sMissileSetAnim(missile, 1);
            missile->hit = 1;
        } else {
            missile->purge_timer = 1;
            sMissileSetAnim(missile, 2);
        }
    }
    if (missile->kind != 4 && missile->hit_ground != 0)
        missile->speed = 0.0f;
    if (missile->kind != 5) {
        for (k = 0; k < 3; k++) {
            step[k] = missile->matrix[k][0] * missile->speed;
            missile->matrix[k][3] += step[k];
        }
    }
    if (missile->proc != 7 && missile->kind != 4) {
        missile->speed += missile->accel;
        if (missile->speed > missile->max_speed)
            missile->speed = missile->max_speed;
    }
    PSMTXInverse(missile->matrix, missile->inverse);
    if (missile->proc_delay < missile->update_count)
        misProc(missile);
    HSD_JObjSetTranslateX(missile->joint, missile->matrix[0][3]);
    HSD_JObjSetTranslateY(missile->joint, missile->matrix[1][3]);
    HSD_JObjSetTranslateZ(missile->joint, missile->matrix[2][3]);
    sMakeMatrix(missile->joint);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            missile->joint->matrix[i][j] = missile->matrix[i][j];
        }
    }
    sGlobal2Local(missile->joint);
    if (missile->beam_joints[0] != 0) {
        for (m = 0; m < 3; m++) {
            missile->beam_positions[0][m] = missile->matrix[m][3];
        }
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 4; j++) {
                missile->beam_joints[0]->matrix[i][j] = missile->joint->matrix[i][j];
            }
        }
        sGlobal2Local(missile->beam_joints[0]);
        msFlyTrace(missile);
        for (k = 1; k < 7; k++) {
            if (missile->beam_joints[k] == (void *)0)
                break;
        }
    }
    if (missile->light != 0) {
        position.x = missile->matrix[0][3];
        position.y = missile->matrix[1][3];
        position.z = missile->matrix[2][3];
        HSD_LObjSetPosition(missile->light, &position);
    }
}
