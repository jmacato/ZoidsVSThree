extern "C" {
#pragma readonly_strings on
#pragma dont_inline on
#pragma bool off
#include "types.h"
#include "joint.h"
#include "model_archive.h"
#include "object.h"

typedef struct BulletDat {
    u8 pad_00[8];
    s32 damage;
    s16 speed;
    u8 pad_0E[4];
    s16 kind;
    u8 pad_14[2];
    s16 trace_rate;
    u8 pad_18[2];
    s16 zoid_hit;
    s16 hit_effect;
    s16 fire_effect;
    s16 se;
    u8 pad_22[6];
    s16 turn_angle;
    u8 pad_2A[0x22];
} BulletDat;
extern s32 usbForce;
extern void *missBinB2;
extern BulletDat Tea_bulletdat[];
extern void *sReadFileU(char *name, s32 mode);
extern void ZeroMemory(void *ptr, u32 size);
extern ModelArchive *sMissileLoad(s32 index, BulletDat *dat);
typedef f32 MisMtx[3][4];
typedef struct MisAi3 {
    u8 pad_00[0x84];
    s32 missile_hit;
} MisAi3;
typedef struct MisZoid3 {
    u8 pad_0000[0x1368];
    s32 weapon_mount;
    u8 pad_136C[0x2098 - 0x136C];
    MisAi3 *ai;
} MisZoid3;
typedef struct Missile3 {
    s32 flags;
    s32 bullet;
    s32 kind;
    s32 zoid_hit;
    s32 hit_ground;
    u16 hit_polygon;
    u8 pad_16[2];
    s32 homing;
    u8 pad_1C[4];
    ModelArchive *archive;
    HSD_JObj *joint;
    MisZoid3 *owner;
    s32 owner_weapon_mount;
    MisZoid3 *target_zoid;
    struct Missile3 *target_missile;
    s32 lock;
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
    u8 pad_104[4];
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
extern s32 nowMJ;
extern s32 misALL;
extern s32 sLightMis;
extern s32 SE_TableList[];
extern ModelArchive *sEfctLight;
extern HSD_JObj *CopyJoint2(void *archive, s32 model);
extern HSD_JObj *searchJobjJoint(void *archive, HSD_JObj *joint, char *name);
extern void PSMTXRotRad(MisMtx m, char axis, f32 rad);
extern void PSMTXConcat(MisMtx a, MisMtx b, MisMtx ab);
extern void sGlobal2Local(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);
extern struct HSD_LObj *LoadArc2Light(void *archive, s32 index);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *expr);
extern f32 HSD_Randf(void);
extern void sMissileSetAnim(Missile3 *missile, s32 animation);
extern void sEffectSet(s32 type, s32 mode, f32 *position, HSD_JObj *source, void *zoid);

void sMissilePrologueU(s32 usb);
void sMissileSet(MisZoid3 *owner, MisZoid3 *target_zoid, Missile3 *target_missile, s32 lock, MisMtx mtx, s32 bullet, s32 extra_damage);
#pragma force_active on
static ModelArchive *missileFile[130];
Missile3 missileStart[200];
#pragma force_active off
#define HSD_OBJECT_METHOD(o) (((HSD_Class *)(o))->class_info)

extern void setAnimRate(HSD_JObj *joint, f32 rate);
extern void jobjUnrefAll(HSD_JObj *joint);
extern void HSD_JObjRemoveAnimAll(HSD_JObj *joint);

#pragma dont_inline off
static inline s32 ref_DEC(HSD_Obj *obj)
{
    s32 ret = (u64)(obj->reference_count == (u16)0xFFFF);

    if (ret) {
        return ret;
    }
    ret = (obj->reference_count == (u16)0);
    obj->reference_count--;
    return ret;
}

void sMissilePurge(Missile3 *missile)
{
    HSD_Obj *obj;

    if (missile != (void *)0 && missile->flags != 0) {
        misALL--;
        if (missile->joint != 0) {
            setAnimRate(missile->joint, 0.0f);
            HSD_JObjRemoveAnimAll(missile->joint);
            jobjUnrefAll(missile->joint);
            missile->joint = 0;
        }
        if (missile->se_playing != 0) {
            missile->se_playing = 0;
        }
        if (missile->light != 0) {
            obj = (HSD_Obj *)missile->light;
            if (obj != 0) {
                if (ref_DEC(obj)) {
                    if (obj != 0) {
                        HSD_OBJECT_METHOD(obj)->release((HSD_Class *)obj);
                        HSD_OBJECT_METHOD(obj)->destroy((HSD_Class *)obj);
                    }
                }
            }
        }
        missile->light = 0;
        missile->flags = 0;
    }
}

#pragma dont_inline on

extern void free(void *ptr);

void sMissileEpilogue(void)
{
    s32 i;

    for (i = 0; i < 130; i++) {
        if (missileFile[i] != 0) {
            PurgeArc2(missileFile[i]);
        }
        missileFile[i] = 0;
    }
    if (missBinB2 != 0) {
        free(missBinB2);
    }
    missBinB2 = 0;
}

void sMissilePrologueU(s32 usb)
{
    s32 i;

    if (usbForce != 0) {
        usb = 1;
    }
    missBinB2 = sReadFileU("missile/am.b", usb);
    if (missBinB2 != 0) {
        ZeroMemory(missileStart, 84000);
        ZeroMemory(missileFile, 0x208);
        for (i = 0; i < 130; i++) {
            missileFile[i] = sMissileLoad(i, &Tea_bulletdat[i]);
        }
    }
}

#pragma dont_inline off
#pragma auto_inline off
static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & 0x800000) && (jobj->flags & 0x40);
}
#define HSD_JObjSetMtxDirty(jobj) \
    do { \
        if ((jobj) != 0 && !HSD_JObjMtxIsDirty(jobj)) \
            HSD_JObjSetMtxDirtySub(jobj); \
    } while (0)
static inline void HSD_JObjSetScaleX(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 805, "jobj");
    jobj->scale.x = value;
    if (!(jobj->flags & 0x02000000))
        HSD_JObjSetMtxDirty(jobj);
}
static inline void HSD_JObjSetTranslateX(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 952, "jobj");
    jobj->translation.x = value;
    if (!(jobj->flags & 0x02000000))
        HSD_JObjSetMtxDirty(jobj);
}
static inline void HSD_JObjSetTranslateY(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 966, "jobj");
    jobj->translation.y = value;
    if (!(jobj->flags & 0x02000000))
        HSD_JObjSetMtxDirty(jobj);
}
static inline void HSD_JObjSetTranslateZ(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 980, "jobj");
    jobj->translation.z = value;
    if (!(jobj->flags & 0x02000000))
        HSD_JObjSetMtxDirty(jobj);
}
void sMissileSet(MisZoid3 *owner, MisZoid3 *target_zoid, Missile3 *target_missile, s32 lock, MisMtx mtx, s32 bullet, s32 extra_damage)
{
    static s32 cc;
    Missile3 *missile;
    ModelArchive *archive;
    s32 i;
    s32 j;
    s32 k;
    s32 l;
    s32 m;
    s32 se;
    MisMtx rot;

    if (bullet <= 0)
        return;
    if (bullet >= 130)
        return;
    archive = missileFile[bullet];
    if (archive == (void *)0)
        return;
    if (archive->model_data == (void *)0)
        return;
    if (archive->models == (void *)0)
        return;
    nowMJ++;
    for (i = 0; i < 200; i++) {
        if (nowMJ >= 200)
            nowMJ = 0;
        missile = &missileStart[nowMJ];
        if (!(missile->flags & 1))
            break;
        nowMJ++;
    }
    if (i == 200)
        return;
    if (missile->flags & 1)
        return;
    misALL++;
    ZeroMemory(missile, sizeof(Missile3));
    missile->light = 0;
    missile->hit_ground = 0;
    missile->hit_polygon = 0xFFFF;
    missile->bullet = bullet;
    missile->kind = Tea_bulletdat[bullet].kind;
    if (missile->kind == 1)
        missile->homing = 1;
    if (missile->kind == 6)
        missile->homing = 1;
    missile->zoid_hit = Tea_bulletdat[bullet].zoid_hit;
    missile->archive = archive;
    missile->joint = CopyJoint2(archive, 0);
    missile->beam_joints[0] = searchJobjJoint(archive, missile->joint, "beem_joint");
    if (missile->beam_joints[0] != 0) {
        missile->beam_joints[1] = searchJobjJoint(archive, missile->joint, "to_beem_joint");
        missile->beam_joints[2] = searchJobjJoint(archive, missile->joint, "to_to_beem_joint");
        missile->beam_joints[3] = searchJobjJoint(archive, missile->joint, "to_to_to_beem_joint");
        missile->beam_joints[4] = searchJobjJoint(archive, missile->joint, "to_to_to_to_beem_joint");
        missile->beam_joints[5] = searchJobjJoint(archive, missile->joint, "to_to_to_to_to_beem_joint");
        missile->beam_joints[6] = searchJobjJoint(archive, missile->joint, "to_to_to_to_to_to_beem_joint");
    }
    missile->a1_joint = searchJobjJoint(archive, missile->joint, "a_1_joint");
    missile->owner = owner;
    if (owner != 0)
        missile->owner_weapon_mount = owner->weapon_mount;
    missile->target_zoid = target_zoid;
    missile->target_missile = target_missile;
    missile->lock = lock;
    missile->speed = 0.0f;
    missile->update_count = 0;
    missile->purge_timer = 0;
    missile->hit = 0;
    missile->flags = 1;
    for (j = 0; j < 3; j++) {
        for (k = 0; k < 4; k++)
            missile->matrix[j][k] = mtx[j][k];
    }
    if (missile->kind != 5) {
        PSMTXRotRad(rot, 'X', 3.1415926 * (2.0f * HSD_Randf()));
        PSMTXConcat(missile->matrix, rot, missile->matrix);
    }
    for (l = 0; l < 3; l++) {
        for (m = 0; m < 4; m++)
            missile->joint->matrix[l][m] = missile->matrix[l][m];
    }
    sGlobal2Local(missile->joint);
    HSD_JObjSetTranslateX(missile->joint, mtx[0][3]);
    HSD_JObjSetTranslateY(missile->joint, mtx[1][3]);
    HSD_JObjSetTranslateZ(missile->joint, mtx[2][3]);
    sMakeMatrix(missile->joint);
    for (i = 0; i < 7; i++) {
        if (missile->beam_joints[i] != 0) {
            for (j = 0; j < 3; j++) {
                for (k = 0; k < 3; k++)
                    missile->beam_joints[i]->matrix[j][k] = mtx[j][k];
                missile->beam_joints[i]->matrix[j][3] = 0.1 * i + mtx[j][3];
                missile->beam_positions[i][j] = 0.1 * i + mtx[j][3];
            }
        }
    }
    for (i = 0; i < 7; i++) {
        if (missile->beam_joints[i] != 0) {
            HSD_JObjSetScaleX(missile->beam_joints[i], 1.0f);
            sGlobal2Local(missile->beam_joints[i]);
        }
    }
    sMakeMatrix(missile->joint);
    missile->accel = 1.0f;
    missile->turn_rate = (f32)((f32)Tea_bulletdat[bullet].turn_angle / 60.0) * 3.1415926 * 2.0 / 360.0;
    missile->max_speed = 0.1 * Tea_bulletdat[bullet].speed;
    {
        s32 procs[8] = { 6, 4, 7, 8, 9, 10, 4, 4 };
        missile->proc = procs[Tea_bulletdat[bullet].kind];
    }
    missile->proc_delay = 60;
    if (missile->proc == 7) {
        missile->speed = missile->max_speed;
        missile->proc_delay = 0;
    }
    if (missile->kind == 4) {
        missile->speed = missile->max_speed;
        missile->proc_delay = 0;
        if (missile->speed < 1.0f)
            missile->speed = 1.0f;
    }
    if (owner != 0 && owner->ai != 0)
        owner->ai->missile_hit = 0;
    missile->damage = extra_damage + Tea_bulletdat[bullet].damage;
    sMissileSetAnim(missile, 0);
    sEffectSet(Tea_bulletdat[missile->bullet].fire_effect, 1, 0, missile->joint, 0);
    {
        s32 se_index = Tea_bulletdat[bullet].se;
        se = -1;
        if (se_index >= 0)
            se = SE_TableList[se_index];
    }
    missile->se = se;
    if (sLightMis != 0) {
        missile->light = LoadArc2Light(sEfctLight, cc + 1);
        cc++;
        if (cc >= 3)
            cc = 0;
    }
}
#pragma dont_inline on

#pragma force_active on
s32 misMAX;
s32 nowMX;
#pragma force_active off
}
