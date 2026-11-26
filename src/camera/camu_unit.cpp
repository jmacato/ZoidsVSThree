extern "C" {
#pragma readonly_strings on
#pragma dont_inline on
#pragma bool off
#include "types.h"
#include "object.h"
#include "zoid3.h"
#include "ground_collision.h"

typedef struct PadT {
    u8 b[0x88];
} PadT;
extern PadT sPad[4];
extern s32 nowShadow;
extern void *camTmp;
extern void shadowRendering(void *shadow, s32 index);
extern void *HSD_CObjLoadDesc(void *desc);
extern void ZeroMemory(void *p, u32 n);
typedef struct CamS {
    u8 pad0[0x4];
    s32 a4;
    void * lights;
    void * shadow;
    f32 a10;
    u8 pad1[0x4];
    f32 a18;
    f32 a1c;
    u8 pad2[4];
    f32 a24;
    u8 pad3[0x4];
    f32 a2c;
    u8 pad4[0x184];
    s32 a1b4;
    u8 pad5[8];
    s32 field_1C0;
    s32 field_1C4;
    s32 target_index;
    u8 pad6[0x1c];
    void * pad;
    u8 pad7[0x58];
    void * cobj;
    u8 pad8[0x1c];
    u8 b264[0x1c];
    u8 b280[0x18];
    u8 b298[0x10];
    u8 pad9[0x2F9 - 0x2A8];
    u8 field_2F9;
    u8 field_2FA;
    u8 field_2FB;
    u8 reserved_2FC[0x590 - 0x2FC];
} CamS;
s32 sctblLen = 20;
s32 sCamMuteki;
extern void sReadPre(void);
extern void HSD_AudioStreamVolume(s32 a);
extern void HSD_AudioStreamStop(s32 a);
extern s32 DVDConvertPathToEntrynum(char *path);
extern s32 DVDFastOpen(s32 entry, void *info);
extern s32 DVDReadAsyncPrio(void *info, void *buf, s32 len, s32 off, void *cb, s32 prio);
extern s32 DVDClose(void *info);
extern char *strcpy(char *d, const char *s);
extern s32 StrCmp(char *a, char *b);
extern s16 TEA_VOICEVOL;
extern void TEA_VoiceFilePlay(char *name, u8 vol, s32 flag);
extern void camVoiceSeekCB(s32 a, void *b);
extern s32 camVoiceSeekFile(char *name);
typedef struct IntSeE {
    f32 distance;
    s16 se;
    f32 x;
    f32 z;
    s32 handle;
    s32 timer;
    s32 delay;
} IntSeE;
extern s32 vsyncN;
extern s32 TEA_SeOnF(u16 se, f32 x, f32 z);
extern s32 HSD_AudioSFXCheck(s32 handle);
extern void camVoiceSeekInt(void);
typedef struct JObjM {
    u8 pad[0x44];
    f32 mtx[3][4];
} JObjM;
extern void GXProject(f32 x, f32 y, f32 z, void *mtx, void *proj, void *vp, f32 *sx, f32 *sy, f32 *sz);
typedef struct CamMine {
    s32 mode;
    s32 half;
    u8 reserved_08[8];
    f32 focus_heading;
    u8 reserved_14[0x38];
    s8 mount_blocked[20];
    s8 mount_hidden[20];
    f32 mount_positions[20][3];
    s32 mount_times[20];
} CamMine;

typedef struct CamMount {
    s32 slot;
    s32 angle;
    s32 distance;
    s32 height;
} CamMount;

extern void angLimit(f32 *angle);
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern f32 sColPosAndY(Vec3 *point, u16 *selector, GroundMask *mask);
extern f32 sColPtAll(f32 *first, f32 *second, GroundMask *mask);
extern HSD_JObj *grdObjGetJObj(s32 index);
extern f32 sLenJobj(HSD_JObj *joint, HSD_JObj *target);

extern s32 sLightEfct;
extern s32 sprintf(char *buf, const char *fmt, ...);
extern s32 camVoiceSeek(char *name);

void sCameraInit(void);
s32 sCameraIn2(CamS *cam, JObjM *jobj);
void camInMine(CamMine *camera, ZoidState *zoid);
void sCameraShadowAll(void);
s32 camVoiceSeekFile(char *name);
void camVoiceSeekInt(void);
void camVoiceOn(s32 a, s32 b);
void camVoiceNow(s32 a, s32 b);
void IntSeClear(void);
s32 IntSeSetTm(s16 se, f32 distance, f32 x, f32 z, s32 delay);
#pragma force_active on
CamS sCamera[4];
static IntSeE IntSe[32];
static char vcSeekStr[200];
static char vcSeekNow[200];
static u8 vcSeekIfo[60];
static u8 rrrbuf[512] __attribute__((aligned(32))) ;
static u32 camNormal_pos_wobjdesc[5] = { 0x00000000, 0x41A00000, 0x41A00000, 0x41A00000, 0x00000000 };
static u32 camNormal_interest_wobjdesc[5] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
u32 cameraNormal[14] = {
    0x00000000, 0x00000001, 0x00000280, 0x000001E0, 0x00000280, 0x000001E0, 0x801434C8, 0x801434DC,
    0x00000000, 0x00000000, 0x3F8CCCCD, 0x465AC000, 0x42700000, 0x3FAA3D71
};
static s32 vcSeekMode2;
s32 vcSeekMode;
s32 sCamNS;
s32 sCamNN2;
s32 sCamNN;
void *sCamNormal;
#pragma force_active off
void sCameraInit(void)
{
    s32 i;

    sCamNormal = HSD_CObjLoadDesc(&cameraNormal);
    for (i = 0; i < 4; i++) {
        ZeroMemory(&sCamera[i], sizeof(CamS));
        sCamera[i].pad = &sPad[i];
        sCamera[i].a1b4 = 3;
        sCamera[i].a10 = 0.0f;
        sCamera[i].a18 = 0.2617994f;
        sCamera[i].a24 = 0.0f;
        sCamera[i].a2c = 0.0f;
    }
}

s32 sctblMin1a[4] = {50, 590, 30, 400};
s32 sctblMin2a[4] = {50, 590, 25, 190};
s32 sctblMin2b[4] = {50, 590, 265, 440};
s32 sctblMin3a[4] = {5, 315, 50, 400};
s32 sctblMin3b[4] = {325, 635, 50, 400};
s32 sctblMax1a[4] = {130, 400, 100, 360};
s32 sctblMax2a[4] = {130, 400, 50, 170};
s32 sctblMax2b[4] = {130, 400, 290, 420};
s32 sctblMax3a[4] = {25, 305, 100, 360};
s32 sctblMax3b[4] = {335, 625, 100, 360};
s32 sCameraIn2(CamS *cam, JObjM *jobj)
{
    f32 pp[3];
    s32 sc[2];
    s32 dead;
    s32 outcode;
    s32 *min;
    s32 *max;

    if (jobj == (void *)0)
        return 0;
    GXProject(jobj->mtx[0][3], jobj->mtx[1][3], jobj->mtx[2][3], cam->b298, cam->b264, cam->b280, &pp[0], &pp[1], &pp[2]);
    sc[0] = (s32)pp[0];
    sc[1] = (s32)pp[1];
    if (pp[2] >= 1.0)
        return 0xf;
    min = sctblMin1a;
    max = sctblMax1a;
    if (sCamNN == 2) {
        if (sCamNS == 0) {
            if (cam->a4 == 0) {
                min = sctblMin2a;
                max = sctblMax2a;
            } else {
                min = sctblMin2b;
                max = sctblMax2b;
            }
        } else {
            if (cam->a4 == 0) {
                min = sctblMin3a;
                max = sctblMax3a;
            } else {
                min = sctblMin3b;
                max = sctblMax3b;
            }
        }
    }
    dead = 0;
    /* MWCC binds outcode before folding these constant returns. */
    if (sc[0] < min[0]) {
        outcode = 2;
        return outcode;
    }
    if (sc[0] > min[1]) {
        outcode = 8;
        return outcode;
    }
    if (sc[1] < min[2])
        return 1;
    if (sc[1] > min[3])
        return 4;
    if (sc[0] > max[0] && sc[0] < max[1] && sc[1] > max[2] && sc[1] < max[3])
        return 0x10;
    return 0;
}

static const u32 lit_462[8] = { 0x00000140, 0x000000F0, 0x01400280, 0x000000F0, 0x00000140, 0x00F001E0, 0x01400280, 0x00F001E0 };
static const u32 lit_463[8] = { 0x00000140, 0x000000F0, 0x01400280, 0x000000F0, 0x00000140, 0x00F001E0, 0x01400280, 0x00F001E0 };
static const char lit_746[21] = "01234567890123456789";
static const u32 lit_1587[4] = { 0x0000000A, 0x00000276, 0x0000000A, 0x000001B8 };
static const u32 lit_1588[4] = { 0x0000000A, 0x00000276, 0x0000000A, 0x000000E6 };
static const u32 lit_1589[4] = { 0x0000000A, 0x00000276, 0x000000FA, 0x000001D6 };
static const u32 lit_1590[4] = { 0x00000082, 0x00000190, 0x00000064, 0x00000168 };
static const u32 lit_1591[4] = { 0x00000082, 0x00000190, 0x0000003C, 0x000000B4 };
static const u32 lit_1592[4] = { 0x00000082, 0x00000190, 0x0000012C, 0x000001A4 };
static char *str00 = lit_746;
s32 sLightEfct = 1;

#pragma dont_inline off
/* MWCC binds these inline arguments before removing their moves. */
static inline f32 cameraSin(f32 angle)
{
    return sinf(angle);
}

static inline f32 cameraCos(f32 angle)
{
    return cosf(angle);
}

void camInMine(CamMine *camera, ZoidState *zoid)
{
    s32 k;
    s32 i;
    HSD_JObj *joint;
    CamMount *mount;
    HSD_JObj *target_joint;
    ZoidState *target;
    s32 slot;
    CamMount *control;
    CamMount *mounts;
    f32 distance;
    f32 height;
    f32 range;
    f32 offset;
    f32 fraction;
    f32 y;
    f32 mine[3];
    f32 pos[3];
    f32 angle;
    void *anim;

    if (zoid == (void *)0)
        return;
    mounts = (CamMount *)zoid->field_2090;
    control = mounts;
    anim = zoid->anim_data;
    for (i = 0; i < 20; i++) {
        mount = &control[i];
        if (mount->slot == -1)
            joint = zoid->field_1ACC;
        else
            joint = zoid->weapon_slots[mount->slot].joint;
        if (joint == (void *)0) {
            camera->mount_blocked[i] = 1;
            continue;
        }
        if (zoid->target_pending != 0 || zoid->lock_active != 0)
            angle = camera->focus_heading + (f32)mount->angle * 3.1415926 * 2.0 / 360.0;
        else
            angle = zoid->heading + (f32)mount->angle * 3.1415926 * 2.0 / 360.0;
        angLimit(&angle);
        for (k = 0; k < 3; k++) {
            camera->mount_positions[i][k] = joint->matrix[k][3];
            mine[k] = joint->matrix[k][3];
        }
        distance = (f32)mount->distance;
        height = (f32)mount->height;
        if (distance <= 5.0f && height < 50.0f)
            height = 50.0f;
        camera->mount_positions[i][0] += distance * cameraSin(angle);
        camera->mount_positions[i][2] += distance * cameraCos(angle);
        camera->mount_positions[i][1] += height - 30.0;
        target_joint = 0;
        if (zoid->target_pending != 0) {
            target = &Zoid[slot = zoid->target_slot];
            target_joint = *(HSD_JObj **)&target->camera_joint;
            range = zoid->distances[slot];
        }
        if (zoid->lock_active != 0) {
            target_joint = grdObjGetJObj(zoid->lock_obj);
            range = sLenJobj(target_joint, joint);
        }
        if ((zoid->target_pending != 0 || zoid->lock_active != 0) && range && mount->distance != 0
            && target_joint != 0 && *(HSD_JObj **)&zoid->camera_joint != 0) {
            offset = (f32)mount->distance * ((target_joint->matrix[1][3] - ((HSD_JObj *)zoid->camera_joint)->matrix[1][3]) / range);
            if (offset < -15.0f)
                offset = -15.0f;
            camera->mount_positions[i][1] -= offset;
            {
                GroundMask copy;
                GroundMask mask = {{0, 255, 0, 0}};

                copy = mask;
                y = 1.0f + sColPosAndY((Vec3 *)camera->mount_positions[i], 0, &copy);
                if (y > camera->mount_positions[i][1])
                    camera->mount_positions[i][1] = y;
            }
        }
        for (k = 0; k < 3; k++)
            pos[k] = camera->mount_positions[i][k];
        {
            GroundMask copy2;
            GroundMask mask2 = {{0, 255, 0, 0}};

            copy2 = mask2;
            fraction = sColPtAll(mine, camera->mount_positions[i], &copy2);
        }
        camera->mount_blocked[i] = 10000.0f != fraction;
        if (10000.0f == fraction)
            camera->mount_blocked[i] = 0;
        else
            camera->mount_blocked[i] = 1;
        str00[i] = camera->mount_blocked[i] ? 'x' : '0' + i % 10;
        if (camera->mount_blocked[i]) {
            (void)0;
        }
    }
    for (i = 0; i < 20; i++) {
        if (camera->mount_blocked[i])
            camera->mount_times[i] = 0;
    }
}
#pragma dont_inline on

void sCameraShadowAll(void)
{
    s32 i;
    void *shadow;

    if (nowShadow == 0) {
        for (i = 0; i < 4; i++) {
            camTmp = &sCamera[i];
            if (sCamera[i].cobj != (void *)0 && sCamera[i].lights != (void *)0) {
                shadow = sCamera[i].shadow;
                if (shadow != 0)
                    shadowRendering(shadow, sCamera[i].target_index);
            }
        }
    }
}

s32 camVoiceSeekFile(char *name)
{
    s32 entry;

    sReadPre();
    HSD_AudioStreamVolume(0);
    HSD_AudioStreamStop(0);
    vcSeekNow[0] = 0;
    entry = DVDConvertPathToEntrynum(name);
    if (entry == -1)
        return 0;
    if (DVDFastOpen(entry, vcSeekIfo) == 0)
        return 0;
    vcSeekMode = 1;
    if (DVDReadAsyncPrio(vcSeekIfo, rrrbuf, 0x100, 0, camVoiceSeekCB, 0) == 0) {
        DVDClose(vcSeekIfo);
        vcSeekMode = 0;
        return 0;
    }
    strcpy(vcSeekNow, name);
    return 1;
}

void camVoiceSeekInt(void)
{
    switch (vcSeekMode) {
    case 0:
        if (vcSeekStr[0] != 0)
            camVoiceSeekFile(vcSeekStr);
        break;
    case 1:
        break;
    case 2:
        DVDClose(vcSeekIfo);
        if (StrCmp(vcSeekStr, vcSeekNow) != 0) {
            sReadPre();
            TEA_VoiceFilePlay(vcSeekNow, TEA_VOICEVOL, 0);
            vcSeekStr[0] = 0;
        }
        vcSeekNow[0] = 0;
        vcSeekMode = 3;
        vcSeekMode2 = 15;
        break;
    case 3:
        if (vcSeekMode2 != 0)
            vcSeekMode2--;
        else
            vcSeekMode = 0;
        break;
    default:
        vcSeekMode = 0;
        break;
    }
}

void camVoiceOn(s32 a, s32 b)
{
    char buf[256];

    sprintf(buf, "voice/%03d/%03d_%02d.adp", a, a, b);
    camVoiceSeek(buf);
}

void camVoiceNow(s32 a, s32 b)
{
    char buf[256];

    sprintf(buf, "voice/%03d/%03d_%02d.adp", a, a, b);
    sReadPre();
    TEA_VoiceFilePlay(buf, TEA_VOICEVOL, 0);
}

extern void HSD_ShadowRemove(void *shadow);

#pragma dont_inline off
static inline s32 camera_reference_decrement(void *object)
{
    s32 result;

    result = (u64)(((HSD_Obj *)object)->reference_count == (u16)0xFFFF);
    if (result) {
        return result;
    }
    result = (((HSD_Obj *)object)->reference_count == (u16)0);
    ((HSD_Obj *)object)->reference_count--;
    return result;
}

static inline void camera_unreference(void *object)
{
    if (object != 0 && camera_reference_decrement(object)) {
        if (object != 0) {
            ((HSD_Class *)object)->class_info->release((HSD_Class *)object);
            ((HSD_Class *)object)->class_info->destroy((HSD_Class *)object);
        }
    }
}

void sCameraReset(CamS *camera)
{
    register void *camera_unreference_object;

    u32 i;

    if (camera != (void *)0) {
        if (camera->shadow != 0) {
            HSD_ShadowRemove(camera->shadow);
            camera->shadow = 0;
        }
        if (camera->cobj != 0) {
            {
                camera_unreference_object = camera->cobj;
                camera_unreference(camera_unreference_object);
            }
            camera->cobj = 0;
        }
        camera->field_1C4 = 0;
        camera->field_1C0 = 0;
        camera->a2c = 0.0f;
        camera->a1c = 0.0f;
        camera->a10 = 0.0f;
        camera->a18 = 2 * (3.1415926 * 10.0f) / 360.0;
        camera->field_2F9 = 0;
        camera->field_2FA = 0;
        camera->field_2FB = 0;
        /* The original shift condition skips this loop when i starts at zero. */
        for (i = 0; (i << 20) != 0; i++) {
            *(s32 *)((u8 *)camera + 0x164 + 4 * i) = 120;
        }
    }
}
#pragma dont_inline on

extern void camVoiceClose(void);

void IntSePrologue(void)
{
    s32 i;

    for (i = 0; i < 32; i++) {
        IntSe[i].se = 0;
    }
    vcSeekStr[0] = 0;
    vcSeekNow[0] = 0;
    vcSeekMode = 0;
    ZeroMemory(vcSeekIfo, 60);
}

void IntSeClose(void)
{
    s32 i;

    for (i = 0; i < 32; i++) {
        if (IntSe[i].se != 0 && IntSe[i].delay != -1) {
            IntSe[i].delay = -1;
            IntSe[i].timer = 0;
            IntSe[i].se = 0;
        }
    }
    camVoiceClose();
}

void IntSeClear(void)
{
    s32 i;
    s32 flag;
    u32 handle;

    flag = 0;
    camVoiceSeekInt();
    if (vsyncN & 1)
        flag = 1;
    for (i = 0; i < 32; i++) {
        if (IntSe[i].se != 0 && IntSe[i].delay != -1) {
            if (IntSe[i].delay == 0) {
                if (flag == 0) {
                    IntSe[i].delay = -1;
                    handle = TEA_SeOnF((u16)IntSe[i].se, IntSe[i].x, IntSe[i].z);
                    IntSe[i].handle = handle;
                    flag = 1;
                }
            } else {
                IntSe[i].delay--;
            }
        }
    }
    for (i = 0; i < 32; i++) {
        if (IntSe[i].se != 0 && IntSe[i].delay == -1) {
            if (IntSe[i].timer != 0)
                IntSe[i].timer--;
            if (IntSe[i].timer == 0 && (vsyncN & 3) == 0) {
                handle = HSD_AudioSFXCheck(IntSe[i].handle);
                if (handle == -1) {
                    IntSe[i].timer = 0;
                    IntSe[i].se = 0;
                }
            }
        }
    }
}

s32 IntSeSetTm(s16 se, f32 distance, f32 x, f32 z, s32 delay)
{
    s32 i;
    s32 dead;

    if (delay == -1)
        delay = 0;
    for (i = 0; i < 32; i++) {
        if (IntSe[i].se != 0 && se == IntSe[i].se && delay == IntSe[i].delay && IntSe[i].distance <= 1.3 * distance)
            return 0;
    }
    for (i = 0; i < 32; i++) {
        if (IntSe[i].se == 0) {
            IntSe[i].distance = distance;
            IntSe[i].se = se;
            IntSe[i].x = x;
            IntSe[i].z = z;
            IntSe[i].timer = 15;
            IntSe[i].delay = delay;
            IntSe[i].handle = -1;
            dead = -1;
            return dead;
        }
    }
    dead = dead;
    return 0;
}

static u32 mnStage_1885[16] = {
    0x80136BAC, 0x00000004, 0x803889D0, 0x00000000, 0x80136BB8, 0x00000004, 0x803882E0, 0x00000000,
    0x8038A6F8, 0x00000001, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
};
static const char lit_1886[9] = "\x92" "e\x83\x89\x83" "C\x83g";
static const char lit_1887[11] = "\x83G\x83t\x83" "F\x83N\x83g";
}
