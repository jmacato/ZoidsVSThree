extern "C" {
#pragma readonly_strings on
#pragma dont_inline on
#pragma bool off
#include "types.h"

typedef struct StgT {
    s16 a;
    s16 b;
    s16 c;
    s16 d;
    u8 pad[8];
    s8 clip;
    u8 pad2[0x4F];
} StgT;
extern s32 sprintf(char *buffer, const char *format, ...);
extern void OSReport(const char *format, ...);
extern void TEA_USBFileLenPtr(char *name, void *dst, s32 a, s32 b);
extern void sReadLenPtr(char *name, void *dst, s32 a, s32 b);
extern void sColPrologue(char *name, s32 usb);
extern void PurgeStageData(void);
extern void LoadStageData2(s32 stage);
extern void LoadStageDataUSB2(s32 stage);
extern s32 nowStage;
typedef struct JObjT {
    u8 pad0[0x10];
    struct JObjT *child;
    u32 flags;
    u8 pad1[4];
    f32 rot_x;
    f32 rot_y;
    f32 rot_z;
    u8 pad1b[4];
    f32 scale_x;
    f32 scale_y;
    f32 scale_z;
    u8 pad2[0xc];
    f32 mtx[3][4];
} JObjT;
typedef struct InfoT {
    u8 pad0[6];
    u16 h6;
    u8 pad1[9];
    s8 b11;
    u8 pad2;
    s8 b13;
    u8 pad3[7];
    s8 flag;
    u8 pad4[0x14];
    u16 h30;
    u16 h32;
    u8 pad5[2];
    u16 h36;
    u8 pad6[0x48];
} InfoT;
typedef struct GObj3 {
    JObjT *source;
    f32 pos[3];
    f32 mtx[3][4];
    f32 inv[3][4];
    s32 slot;
    JObjT *joint;
    s32 anim;
    s32 w7c;
    s32 w80;
    s32 w84;
    s32 w88;
    s32 w8c;
    f32 rotY;
    u8 pad_c[0xa0 - 0x94];
    s32 wa0;
    u8 pad_e[0xe0 - 0xa4];
    InfoT *info;
} GObj3;
typedef struct FogT {
    u8 pad[0x18];
    s32 vi;
} FogT;
typedef struct ArcT {
    u8 pad[0x34];
    FogT *fog;
    u8 pad2[4];
    JObjT *jobj;
} ArcT;
typedef ArcT SkyT;
typedef struct VIT {
    u8 pad[0x48];
    s32 v;
} VIT;
extern VIT HSD_VIData;
SkyT *Sky;
extern s32 usbForce;
extern void jobjUnrefAll(JObjT *joint);
extern void ZeroMemory(void *address, u32 size);
extern void PurgeArc2(void *arc);
extern void free(void *p);
extern void *LoadArcU(void *dst, char *name, s32 usb);
extern ArcT *LoadArc2(char *name);
extern ArcT *LoadArc2USB(char *name);
extern void StgLoad(s32 stage, s32 usb);
extern void setModelShadow2(JObjT *jobj);
extern void getSkyAmbient(void);
extern void jobjAmbient(JObjT *jobj, s32 *amb);
extern void GroundObjLoad(s32 stage, s32 usb);
typedef struct GroundT {
    u8 pad[0x3c];
    JObjT *shadow;
} GroundT;
extern s32 jobjAnim(JObjT *j);
extern void grdObjSetAnim(GObj3 *o, s32 anim);
extern void HSD_JObjSetMtxDirtySub(JObjT *j);
extern void __assert(const char *file, s32 line, const char *expr);
extern void sMakeMatrix(JObjT *j);
extern void PSMTXInverse(f32 *a, f32 *b);
#pragma dont_inline off
#pragma auto_inline off
static inline s32 HSD_JObjMtxIsDirty(JObjT *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & 0x00800000) && (jobj->flags & 0x40);
}
static inline void HSD_JObjSetRotY(JObjT *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 696, "jobj");
    !(jobj->flags & 0x20000) ? (void)0 : __assert("jobj.h", 697, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    jobj->rot_y = value;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj))
            HSD_JObjSetMtxDirtySub(jobj);
    }
}
static inline void HSD_JObjSetScaleX(JObjT *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 805, "jobj");
    jobj->scale_x = value;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj))
            HSD_JObjSetMtxDirtySub(jobj);
    }
}
static inline void HSD_JObjSetScaleZ(JObjT *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 833, "jobj");
    jobj->scale_z = value;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj))
            HSD_JObjSetMtxDirtySub(jobj);
    }
}
static inline void HSD_JObjSetScaleY(JObjT *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 819, "jobj");
    jobj->scale_y = value;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj))
            HSD_JObjSetMtxDirtySub(jobj);
    }
}
extern s32 fileLen(char *name);
extern JObjT *CopyJoint2(ArcT *arc, s32 model);
extern void sGlobal2Local(JObjT *j);
extern void setModelShadow(JObjT *j);
extern f32 sColPosY(f32 *pos, s32 flag);

void GroundObjLoadSub2(JObjT *joint, s32 stage, s32 usb);
void GroundObjLoadMapInfo(s32 type, s32 x, s32 z, s32 rot, s32 usb);
void GroundObjPurge(void);
void StgLoad(s32 stage, s32 usb);
s32 LoadStageData2__(s32 stage, s32 usb);
void grdObjAnim(void);
void ssLoadStageNow(s32 stage, s32 mode);
#pragma force_active on
static ArcT *GroundObj[30];
static GObj3 obj[50];
GroundT Ground;
StgT Stg;
s32 sPad[306];
static InfoT *MapObjDef;
static s32 MapObjDefN;
static s32 objNow;
static s32 objSize;
s32 nowShadow;
s32 offShadow;
s32 SkyAmbient;
FogT *fogG;
s32 sPadRep __attribute__((aligned(8)));
s32 sPadResetSTOP;
static s32 sDispClipOnOff = 1;
s32 sPad1 = -2145955528;
s32 sPad2 = -2145955392;
s32 sPad3 = -2145955256;
s32 sPad4 = -2145955120;
s32 padBy = 202;
#pragma force_active off
extern void HSD_JObjDispAll(JObjT *joint, void *matrix, u32 flags, u32 render_mode);
extern void grdDispSub(JObjT *joint);
extern void grdDispSubXLU(JObjT *joint);

void grdDisp(void)
{
    JObjT *joint = Ground.shadow;

    if (obj != 0) {
        if (sDispClipOnOff != 3) {
            if (sDispClipOnOff == 0) {
                HSD_JObjDispAll(Ground.shadow, 0, 1, 0);
            } else {
                grdDispSub(Ground.shadow->child);
            }
        }
    }
}

void grdDispXLU(void)
{
    if (sDispClipOnOff != 3) {
        if (sDispClipOnOff == 0) {
            HSD_JObjDispAll(Ground.shadow, 0, 2, 0);
            HSD_JObjDispAll(Ground.shadow, 0, 4, 0);
        } else {
            grdDispSubXLU(Ground.shadow->child);
        }
    }
}

void GroundObjLoadSub2(JObjT *joint, s32 stage, s32 usb)
{
    char name[256];
    s32 color;
    s32 j;
    s32 i;
    s32 type;
    JObjT *copy;
    InfoT *map;
    f32 sy;

    if (usbForce != 0)
        usb = 1;
    if (joint == (void *)0)
        return;
    if (objNow >= 50)
        return;
    if (stage < 0)
        return;
    joint ? (void)0 : __assert("jobj.h", 911, "jobj");
    sy = joint->scale_y;
    type = (s32)sy - 1;
    if (type == 0)
        return;
    if (type >= 30)
        return;
    if (GroundObj[type] == (void *)0) {
        sprintf(name, "stage/map_obj/map_obj%02d.dat", type);
        if (usb != 0)
            GroundObj[type] = LoadArc2USB(name);
        else
            GroundObj[type] = LoadArc2(name);
        if (GroundObj[type] != 0) {
            jobjAmbient(GroundObj[type]->jobj, (color = SkyAmbient, &color));
            objSize += fileLen(name);
        }
    }
    if (GroundObj[type] == (void *)0)
        return;
    obj[objNow].source = joint;
    sMakeMatrix(joint);
    for (i = 0; i < 3; i++)
        obj[objNow].pos[i] = joint->mtx[i][3];
    obj[objNow].slot = type;
    copy = CopyJoint2(GroundObj[type], 0);
    obj[objNow].joint = copy;
    obj[objNow].anim = 0;
    obj[objNow].w7c = 4000;
    obj[objNow].w80 = 0;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++)
            copy->mtx[i][j] = joint->mtx[i][j];
        obj[objNow].pos[i] = joint->mtx[i][j];
    }
    sGlobal2Local(copy);
    HSD_JObjSetScaleX(copy, 1.0f);
    HSD_JObjSetScaleY(copy, 1.0f);
    HSD_JObjSetScaleZ(copy, 1.0f);
    sMakeMatrix(copy);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++)
            obj[objNow].mtx[i][j] = copy->mtx[i][j];
    }
    PSMTXInverse(&obj[objNow].mtx[0][0], &obj[objNow].inv[0][0]);
    grdObjSetAnim(&obj[objNow], 0);
    obj[objNow].wa0 = -1;
    obj[objNow].w84 = 0;
    obj[objNow].info = 0;
    if (MapObjDef != 0 && type < MapObjDefN) {
        map = &MapObjDef[type];
        obj[objNow].info = map;
        obj[objNow].w7c = map->h6;
        obj[objNow].w80 = map->h36;
        if (map->b11 != 0)
            setModelShadow(GroundObj[type]->jobj);
        obj[objNow].w84 = map->h32;
        obj[objNow].w8c = map->b13;
        obj[objNow].w88 = map->h30;
    }
    objNow++;
}

void GroundObjLoadMapInfo(s32 type, s32 x, s32 z, s32 rot, s32 usb)
{
    InfoT *map;
    JObjT *copy;
    char name[256];
    s32 color;

    if (usbForce != 0)
        usb = 1;
    if (objNow >= 50)
        return;
    if (type < 0)
        return;
    if (type >= 30)
        return;
    if (GroundObj[type] == (void *)0) {
        sprintf(name, "stage/map_obj/map_obj%02d.dat", type);
        if (usb != 0)
            GroundObj[type] = LoadArc2USB(name);
        else
            GroundObj[type] = LoadArc2(name);
        if (GroundObj[type] != 0) {
            jobjAmbient(GroundObj[type]->jobj, (color = SkyAmbient, &color));
            objSize += fileLen(name);
        }
    }
    if (GroundObj[type] == (void *)0)
        return;
    obj[objNow].source = 0;
    obj[objNow].pos[0] = (f32)x;
    obj[objNow].pos[1] = 0.0f;
    obj[objNow].pos[2] = (f32)z;
    obj[objNow].pos[1] = sColPosY(&obj[objNow].pos[0], 0);
    obj[objNow].slot = type;
    copy = CopyJoint2(GroundObj[type], 0);
    obj[objNow].joint = copy;
    obj[objNow].anim = 0;
    obj[objNow].w7c = 4000;
    obj[objNow].w80 = 0;
    obj[objNow].rotY = 2.0 * (3.1415926 * (f32)rot) / 360.0;
    HSD_JObjSetRotY(copy, (f32)rot);
    HSD_JObjSetScaleX(copy, 1.0f);
    HSD_JObjSetScaleY(copy, 1.0f);
    HSD_JObjSetScaleZ(copy, 1.0f);
    sMakeMatrix(copy);
    for (x = 0; x < 3; x++) {
        for (z = 0; z < 4; z++)
            obj[objNow].mtx[x][z] = copy->mtx[x][z];
    }
    PSMTXInverse(&obj[objNow].mtx[0][0], &obj[objNow].inv[0][0]);
    grdObjSetAnim(&obj[objNow], 0);
    obj[objNow].wa0 = -1;
    obj[objNow].w84 = 0;
    obj[objNow].info = 0;
    if (MapObjDef != 0 && type < MapObjDefN) {
        map = &MapObjDef[type];
        obj[objNow].info = map;
        obj[objNow].w7c = map->h6;
        obj[objNow].w80 = map->h36;
        if (map->b11 != 0)
            setModelShadow(GroundObj[type]->jobj);
        obj[objNow].w84 = map->h32;
        obj[objNow].w88 = map->h30;
    }
    OSReport("obj %d from mapInfo\n", type);
    copy = copy;
    objNow++;
}

void GroundObjPurge(void)
{
    s32 i;
    GObj3 *o;
    for (i = 0; i < 50; i++) {
        o = &obj[i];
        if (o->joint != 0)
            jobjUnrefAll(o->joint);
        o->joint = 0;
        ZeroMemory(o, sizeof(GObj3));
    }
    for (i = 0; i < 30; i++) {
        if (GroundObj[i] != 0) {
            PurgeArc2(GroundObj[i]);
            GroundObj[i] = 0;
        }
    }
    objNow = 0;
    if (MapObjDef != 0)
        free(MapObjDef);
    MapObjDef = 0;
    MapObjDefN = 0;
}

static const char lit_613[22] = "stage/map_obj/def.bin";
static const char lit_614[41] = "ground stage=%d , obj=%d   objSize=%d  \n";
void StgLoad(s32 stage, s32 usb)
{
    char name[256];

    Stg.a = 0;
    Stg.b = 800;
    Stg.c = 0;
    Stg.d = 3000;
    ((u8 *)&Stg)[0x10] = 1;
    sprintf(name, "stage/st%02d.i", stage);
    if (usb != 0)
        TEA_USBFileLenPtr(name, &Stg, 0, 0x60);
    else
        sReadLenPtr(name, &Stg, 0, 0x60);
}

s32 LoadStageData2__(s32 stage, s32 usb)
{
    char sky[40];
    char name[256];
    s32 tmp[1];
    s32 amb;

    if (usbForce != 0)
        usb = 1;
    sprintf(name, "stage/st%02d.dat", stage);
    LoadArcU(&Ground, name, usb);
    StgLoad(stage, usb);
    setModelShadow2(Ground.shadow);
    sprintf(sky, "stage/skymap%02d.dat", stage);
    if (usb != 0)
        Sky = LoadArc2USB(sky);
    else
        Sky = LoadArc2(sky);
    fogG = 0;
    if (Sky != 0)
        fogG = Sky->fog;
    if (fogG != 0) {
        tmp[0] = fogG->vi;
        HSD_VIData.v = tmp[0];
    }
    getSkyAmbient();
    jobjAmbient(Ground.shadow, (amb = SkyAmbient, &amb));
    GroundObjLoad(stage, usb);
    return 1;
}

void grdObjAnim(void)
{
    GObj3 *p;
    InfoT *info;
    s32 j;
    s32 i;

    for (i = 0; i < 50; i++) {
        p = &obj[i];
        if (p->joint != (void *)0) {
            info = p->info;
            for (j = 0; j < 3; j++)
                p->pos[j] = p->joint->mtx[j][3];
            if (p->anim == 0) {
                jobjAnim(p->joint);
            } else if (p->anim != 2) {
                if (jobjAnim(p->joint) != 0 && p->anim == 1) {
                    grdObjSetAnim(p, 2);
                    jobjAnim(p->joint);
                }
                HSD_JObjSetScaleY(p->joint, 1.0f);
                if (info != 0 && info->flag != 0 && p->joint->child != 0)
                    PSMTXInverse(&p->joint->child->mtx[0][0], &p->inv[0][0]);
            }
        }
    }
    jobjAnim(Ground.shadow);
    sMakeMatrix(Ground.shadow);
    jobjAnim(Sky->jobj);
}

void ssLoadStageNow(s32 stage, s32 mode)
{
    char dat_name[40];
    char xb_name[40];

    if (stage >= 0) {
        OSReport("load stage %d   \n", stage);
        if (nowStage != -1)
            PurgeStageData();
        sprintf(dat_name, "st%02d.dat", stage);
        sprintf(xb_name, "st%02d.xb", stage);
        sColPrologue(xb_name, mode);
        if (mode != 0)
            LoadStageDataUSB2(stage);
        else
            LoadStageData2(stage);
        nowStage = stage;
        sDispClipOnOff = Stg.clip;
    }
}

static const char lit_977[43] = "MapObjDef\x82\xaa\x91\xab\x82\xe8\x82\xdc\x82\xb9\x82\xf1\x81" "A\x92\xe8\x8b`\x82\xb5\x82\xc4\x82\xad\x82\xbe\x82\xb3\x82\xa2\x81" "B\n";
static const char lit_1042[19] = "fire ========NULL\n";
}
