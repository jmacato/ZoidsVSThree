extern "C" {
#pragma readonly_strings on
#pragma dont_inline on
#pragma bool off
#include "zoid3.h"
#include "game_mode.h"
#include "aobj.h"
#include "archive.h"
#include "game_zoid_entry.h"
#include "types.h"

extern void dummyFunc(const char *s);
typedef struct PicHeader {
    u8 reserved_00[0x10];
    s32 format;
    u8 reserved_14[4];
    s32 width;
    s32 height;
    u8 reserved_20[0x2C];
    u16 colors;
} PicHeader;
extern PicHeader *skipPicData(u8 *data);
extern u32 calc_doltexture_size(s32 format, s32 width, s32 height);
extern void putErr(const char *message);
extern void OSReport(const char *format, ...);
extern void MemCpy(u8 *source, u8 *destination, s32 size);
extern void DCFlushRange(void *memory, u32 size);
extern void GXInvalidateTexAll(void);
typedef struct CamVS3 {
    u8 pad_0000[0x244];
    void *cobj;
    u8 pad_0248[0x2FB - 0x248];
    s8 lod_flag;
    u8 pad_02FC[0x304 - 0x2FC];
    f32 zoid_distance[16];
} CamVS3;
extern s32 sCamNN;
extern f32 (*HSD_CObjGetViewingMtxPtr(void *cobj))[4];
extern s32 zdClip(s32 flag, f32 matrix[3][4], ZoidState *zoid, Vec3 *out);
extern void ZoidCoObjOFF(ZoidState *zoid);
extern void ZoidSmallDisp(ZoidState *zoid);
extern void HSD_JObjDispAll(HSD_JObj *jobj, f32 (*vmtx)[4], u32 flags, u32 rendermode);
extern void angLimit(f32 *angle);
extern void limitHigh(f32 *position);
extern void limitHigh2(f32 *position);
extern void limitHighAng(ZoidState *zoid);
extern void zdDispCursor(void);
extern s32 HSD_Randi(s32 maximum);
typedef struct VoiceEntry {
    u8 flags;
    s8 kind;
    u16 value;
    s8 choices[4];
} VoiceEntry;
extern void zdSetXYZ(ZoidState *zoid);
extern void *binB(void *pack, s32 index);
extern void camVoiceOn(s32 person, s32 voice);
typedef struct ColorImageDesc {
    u8 *image;
    u16 width;
    u16 height;
    s32 format;
} ColorImageDesc;
typedef struct ColorTObj {
    u8 reserved_00[0x58];
    ColorImageDesc *imagedesc;
} ColorTObj;
extern ColorTObj *searchTObj(HSD_JObj *joint);
extern u8 *sReadFileU(char *name, s32 mode);
extern s32 sprintf(char *buffer, const char *format, ...);
extern s32 SetTex2(u8 *texture, u8 *image, s32 size);
extern void free(void *ptr);
extern s32 zdSetTex(u8 *data, u8 *texture, u32 size);
extern f64 __frsqrte(f64 value);
#pragma dont_inline off
static inline f32 sqrtf_vol(f32 x, volatile f32 *y)
{
    static const f64 _half = 0.5;
    static const f64 _three = 3.0;

    if (x > 0.0f) {
        f64 guess = __frsqrte((f64)x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        *y = (f32)(x * guess);
        return *y;
    }
    return x;
}
#pragma dont_inline on
extern void HSD_JObjAnimAll(HSD_JObj *joint);
extern u32 HSD_AObjGetFlags(HSD_AObj *aobj);
extern void zdAnimEffect(ZoidState *zoid, s32 animation);
extern void zdClearAtkTouch(ZoidState *zoid);
extern void zdAnimRate(ZoidState *zoid, f32 rate);
extern void setAnimFrame(HSD_JObj *joint, f32 frame);
extern void setAnimStop(HSD_JObj *joint);
extern void setAnimRate(HSD_JObj *joint, f32 rate);
extern void zdChildAnmBak(ZoidState *zoid);
extern void zdChildAnmDif(ZoidState *zoid);
extern void zdAtkTransOFF(ZoidState *zoid);
extern void zdClearAnimRy(HSD_JObj *joint, u32 flags);
extern void __assert(const char *file, s32 line, const char *expr);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern f32 zdGetBasePoly(ZoidState *zoid, f32 *point);
extern void sMakeMatrix(HSD_JObj *joint);
extern void ik3d(ZoidState *zoid, FootJoint *foot);
typedef struct SliderEntry {
    u16 range;
    u8 joint;
    u8 type;
    s16 min;
    s16 max;
    u8 pad[8];
} SliderEntry;
extern void sLinear1D(f32 *value, f32 target, f32 rate);
extern void sSetRxRzF(ZoidState *zoid, FootJoint *front, FootJoint *back, f32 *rx, f32 *rz);
typedef struct MapUnit3 {
    u8 pad_00[0x20];
    s32 kind;
    u8 pad_24[0xB0 - 0x24];
    s16 gene_y;
    s16 x;
    u8 pad_B4[2];
    s16 heading;
    u8 pad_B8[2];
    s16 z;
    s8 enabled;
    u8 pad_BD;
    s8 fixed_y;
    u8 pad_BF;
    s32 info;
    u8 pad_C4[0x10C - 0xC4];
    u8 f10C;
    u8 pad_10D;
    u8 f10E;
    u8 pad_10F[2];
    u8 field_111;
    u8 pad_112[0x1FA - 0x112];
    s8 f1FA;
    s8 f1FB;
    u8 pad_1FC[0x24C - 0x1FC];
} MapUnit3;
typedef struct MapInfo3 {
    u8 pad_00[0x12C];
    MapUnit3 units[17];
} MapInfo3;
extern MapInfo3 mgI;
extern void ZoidInit1(ZoidState *zoid, s32 index, s32 team);
extern s32 infoLoadZoid0(ZoidState *zoid, void *info);
extern s32 infoLoadZoid1(ZoidState *zoid, void *info);
extern f32 zdColPosY(f32 *point, u16 *selector);
typedef struct ZoidDat3 {
    u8 pad_0000[0x48];
    char model_name[0x786 - 0x48];
    s16 attack_hit_effects[12];
    u8 pad_079E[6];
    s16 search_range;
    u8 pad_07A6[0x7FC - 0x7A6];
} ZoidDat3;
typedef struct PartDat3 {
    u8 pad_0000[0x78];
    s16 hit_a;
    u8 pad_007A[0xE0 - 0x7A];
    s16 hit_b;
    u8 pad_00E2[0x124 - 0xE2];
} PartDat3;
typedef struct WpInv3 {
    HSD_JObj *joint;
    f32 inverse[3][4];
    u8 pad_34[4];
} WpInv3;
typedef struct Weapon3 {
    s32 active;
    u8 pad_04[8];
    s32 type;
    u8 pad_10[0x3C - 0x10];
    ZoidState *owner;
    u8 pad_40[0x148 - 0x40];
    WpInv3 inverses[12];
    u8 pad_3E8[0x6DC - (0x148 + 12 * 0x38)];
} Weapon3;
extern ZoidDat3 Tea_zoiddat[];
extern PartDat3 Tea_partsdat[];
extern Weapon3 sWeapon[100];
extern s32 gameStartF;
extern s32 gametime;
extern s32 bitTBL[];
extern s32 zdAtkZdZdDmgHp(ZoidState *zoid);
extern s32 ZoidZdCoAtack(void *attack, ZoidState *zoid, s32 effect, s32 damage);
extern void ZoidCoAtackDmg(ZoidState *zoid, void *attack, ZoidState *target, s32 hit);
extern s32 ZoidWpCoAtk(void *attack, ZoidState *zoid, s32 a, s32 b);
extern void ZoidCoWpAtackDmg(Weapon3 *weapon, void *inverse, ZoidState *zoid);
extern s32 ZoidZdCoObj(ZoidState *zoid, ZoidState *other);
extern void zdCoCoMinR(ZoidState *zoid, ZoidState *other);
extern void ZoidCopyAnim(ZoidState *zoid);
extern Vec3 *grdObjGetPt(s32 index);
extern f32 sLenPoint3d(Vec3 *a, Vec3 *b);
extern s32 zdWpSlider(ZoidState *zoid, s32 mount);
extern s32 zdWeaponWpForceOFF(ZoidState *zoid, WeaponMount *mount);
extern s32 zdWeaponWpOFF(ZoidState *zoid, WeaponMount *mount);
extern s32 zdWeaponWpON(ZoidState *zoid, WeaponMount *mount);
extern void zdWeaponFireOFF(ZoidState *zoid);
extern void zdWeaponFire1(ZoidState *zoid);
extern void zdSearchSight(ZoidState *zoid, s32 index);
extern s32 zdCoFlag(ZoidState *zoid, s32 flag);
extern void zdChgNormal(ZoidState *zoid);
extern void zdChgAction(ZoidState *zoid);
extern void ZoidSetAnim(ZoidState *zoid, s32 animation);
extern s32 zdGetAnimNum(ZoidState *zoid, HSD_JObj *joint);
extern void zdVoiceScG(ZoidState *zoid, s32 voice);
extern s32 usbForce;
extern s32 fexistU(char *name, s32 usb);
extern HSD_Archive *TEA_USBFileArchiveLoad(char *name, void **data);
extern HSD_Archive *sLoad(char *name, void **data);
extern void *LoadArc2USB(char *name);
extern void Str2Lows(char *name);
extern HSD_JObj *HSD_JObjLoadJoint(HSD_JObjDesc *description);
extern s32 jobjAnim(HSD_JObj *joint);
extern JointPose *makeJobj(void);
extern void stCopyObj(HSD_JObj *joint, JointPose *pose);
extern void stCopyMatMobj(HSD_JObj *joint, JointPose *pose);
extern HSD_JObj *searchJoint(ZoidState *zoid, const char *name);
extern void searchJointFoot(ZoidState *zoid, FootJoint *foot, const char *name);
extern void searchJointCoObj(ZoidState *zoid, void *part, const char *name, HSD_JObj *joint);
extern void zdCalcCoDmg(ZoidState *zoid);
extern void HiddenParts(HSD_JObj *joint, s32 hidden);
extern void *getAnimAobj(HSD_JObj *joint);
extern void ZoidInitParam(ZoidState *zoid);
extern void *malloc2(u32 size);
extern void ZeroMemory(void *data, u32 size);
extern u8 *sReadFileLenU(char *name, s32 usb, s32 *length);
extern void paramInit(void *control);
extern char *strcpy(char *dst, const char *src);
extern void ZoidPurge(ZoidState *zoid);
extern void HSD_JObjAddAnimAll(HSD_JObj *joint, void *a, void *b, void *c);

s32 ZoidInit_(ZoidState *zoid, s32 type, s32 usb);
void ZoidInitAll(void);
s32 zdVoiceScriptCalc(VoiceEntry *entry, ZoidState *zoid, s32 a, s32 b);
void zdVoiceSc(ZoidState *zoid, s32 id);
void zdSetXYZ(ZoidState *zoid);
void ZoidAnim(ZoidState *zoid);
void calcBaseF(ZoidState *zoid);
void calcBaseB(ZoidState *zoid);
void ZoidPutJumpingXZ(ZoidState *zoid);
void ZoidAllPutXZ(void);
void ZoidAllDisp3(void);
void ZoidAllDisp(void);
void ZoidAllDispXLU(void);
void zdLen(s32 a, s32 b);
void ZoidLen(void);
void ZoidZdCoObjBodyAll(void);
void ZoidZdAll(void);
s32 zdWp1SliderN(ZoidState *zoid, s32 index, s32 value);
void zdWeaponActLoop(ZoidState *zoid);
s32 zdSetTex(u8 *data, u8 *texture, u32 size);
s32 ZoidColor(ZoidState *zoid, s32 color, s32 mode);
#pragma force_active on
ZoidState Zoid[16];
static s32 prmTblParam[1872];
static s32 sdTest;
static s32 dbgZoidColi;
s32 sZoidEx;
s32 steFile;
s32 steMobj;
static s32 csrDispON;
static s32 csrFile;
static s32 prmTblN;
static s32 csrNum = -1;
CamVS3 *camTmp = (CamVS3 *)-2144874336;
s32 sCamNS2 = 1;
#pragma force_active off
u32 zdsMotTBL[1338] = {
    0x00000000, 0x00000000, 0x00000002, 0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000002, 0x00000002, 0x00000096, 0x00000096, 0x00000096, 0x00000096, 0x00000094, 0x00000094,
    0x00000003, 0x00000096, 0x00000094, 0x00000094, 0x00000003, 0x00000096, 0x00000094, 0x00000094,
    0x00000003, 0x000000F2, 0x000000F0, 0x000000F0, 0x000000F3, 0x000000F2, 0x000000F0, 0x000000F0,
    0x000000F3, 0x000000F2, 0x000000F0, 0x000000F0, 0x000000F3, 0x000000F2, 0x000000F0, 0x000000F0,
    0x000000F3, 0x000000F3, 0x000000F3, 0x000000F3, 0x0000000B, 0x0000000B, 0x0000000B, 0x0000000B,
    0x0000000B, 0x0000000B, 0x000000F3, 0x000000F3, 0x000000F3, 0x000000F3, 0x000000F3, 0x000000F3,
    0x000000F9, 0x000000E3, 0x000000E2, 0x000000F0, 0x000000F0, 0x000000F2, 0x000000F2, 0x0000000A,
    0x00000008, 0x000000FA, 0x000000FA, 0x0000000A, 0x000000FA, 0x0000000A, 0x000000FA, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x00000008, 0x0000000A,
    0x000000FA, 0x000000F0, 0x0000000A, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008,
    0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008,
    0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008,
    0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008,
    0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008,
    0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008,
    0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x00000008, 0x00000008, 0x00000008, 0x00000008,
    0x00000008, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A,
    0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A, 0x00000000,
    0x00000000, 0x00000000
};
static const char lit_387[19] = "zoid/stels_mat.dat";
static const char lit_388[13] = "debug/c_.dat";
static const char lit_424[19] = "zoid purge! [%s] \n";
static const char lit_464[32] = "joint error [%s] \n ============";
static const char lit_611[12] = "zoid/%s.dat";
static const char lit_688[12] = "mtp_0_joint";
static const char lit_689[12] = "mtp_1_joint";
static const char lit_690[12] = "mtp_2_joint";
static const char lit_691[12] = "mtp_3_joint";
static const char lit_692[12] = "mtp_4_joint";
static const char lit_693[12] = "mtp_5_joint";
static const char lit_694[12] = "mtp_6_joint";
static const char lit_695[12] = "mtp_7_joint";
static const char lit_696[12] = "mtp_8_joint";
static const char lit_697[12] = "mtp_9_joint";
static const char lit_698[12] = "BUST1_joint";
static const char lit_699[11] = "HIP1_joint";
static const char lit_700[13] = "L_ARM1_joint";
static const char lit_701[13] = "R_ARM1_joint";
static const char lit_702[13] = "L_ARM2_joint";
static const char lit_703[13] = "R_ARM2_joint";
static const char lit_704[13] = "L_HAND_joint";
static const char lit_705[13] = "R_HAND_joint";
static const char lit_706[12] = "NECK1_joint";
static const char lit_707[12] = "HEAD1_joint";
static const char lit_708[13] = "L_LEG1_joint";
static const char lit_709[13] = "L_LEG2_joint";
static const char lit_710[13] = "R_LEG1_joint";
static const char lit_711[13] = "R_LEG2_joint";
static const char lit_712[13] = "L_FOOT_joint";
static const char lit_713[13] = "R_FOOT_joint";
static const char lit_714[12] = "TEAL1_joint";
static const char *const lit_715[28] = { lit_688, lit_689, lit_690, lit_691, lit_692, lit_693, lit_694, lit_695, lit_696, lit_697, lit_698, lit_699, lit_700, lit_701, lit_702, lit_703, lit_704, lit_705, lit_706, lit_707, lit_708, lit_709, lit_710, lit_711, lit_712, lit_713, lit_714, 0 };
static const char lit_747[13] = "L_spip_joint";
static const char lit_748[13] = "R_spip_joint";
static const char lit_749[13] = "L_spik_joint";
static const char lit_750[13] = "R_spik_joint";
static const char lit_751[12] = "up_WP_joint";
static const char lit_752[12] = "att_E_joint";
static const s32 lit_807[20] = { 180, 172, 171, 204, 180, 205, 153, 180, 180, 158, 214, 153, 221, 157, 221, 148, 220, 230, 140, 180 };
static const s32 lit_808[20] = { 32, 17, 14, 27, 34, 20, 15, 23, 1, 14, 32, 36, 21, 41, 68, 41, 91, 22, 25, 6 };
static const s32 lit_809[20] = { 39, 28, 27, 30, 41, 35, 30, 43, 35, 24, 38, 40, 46, 50, 65, 63, 85, 30, 30, 40 };
static char *tbl_746[6] = { (char *)lit_747, (char *)lit_748, (char *)lit_749, (char *)lit_750, (char *)lit_751, (char *)lit_752 };

typedef struct NameTable {
    const char *n[28];
} NameTable;

typedef struct ParamTable {
    s32 v[20];
} ParamTable;

#define ZS32(off) (*(s32 *)((u8 *)zoid + (off)))
#define ZJ(off) (*(HSD_JObj **)((u8 *)zoid + (off)))
#define CS32(c, off) (*(s32 *)((u8 *)(c) + (off)))

#pragma dont_inline off
static inline f32 HSD_JObjGetTranslationY(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 1021, "jobj");
    return jobj->translation.y;
}

static inline f32 HSD_JObjGetTranslationZ(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 1033, "jobj");
    return jobj->translation.z;
}

s32 ZoidInit_(ZoidState *zoid, s32 type, s32 usb)
{
    char path[120];
    u8 *ai;
    void *data;
    s32 low = 0;
    char *names[28];
    char tail[200];
    char attack[200];
    s32 length;
    u8 *data2;
    s32 length2;
    s32 angles[20];
    s32 distances[20];
    s32 heights[20];
    s32 length3;
    HSD_JObj *buckle;
    ZoidControlData *ctrl2;
    HSD_JObj *look;
    ZoidControlData *control;
    HSD_JObj *look2;
    ModelAnimationTable *scene;
    HSD_Archive *archive;
    s32 j;
    s32 i;
    CameraMountInfo *entry;
    u8 *buf2;
    u8 *cam;
    u8 *slider;

    if (usbForce != 0) {
        usb = 1;
    }
    ZoidPurge(zoid);
    zoid->field_1E9A = 0;
    ZS32(0x1EA0) = 0;
    zoid->current_animation = 0;
    data = 0;
    if (sCamNN == 4) {
        low = 1;
        sprintf(path, "zoid/low/%s.dat", Tea_zoiddat[type].model_name);
        if (!fexistU(path, usb)) {
            low = 0;
        }
    }
    if (low == 0) {
        sprintf(path, lit_611, Tea_zoiddat[type].model_name);
    }
    OSReport("%s\n", path);
    if (fexistU(path, usb) == 0) {
        return 0;
    }
    if (usb != 0) {
        archive = TEA_USBFileArchiveLoad(path, &data);
    } else {
        archive = sLoad(path, &data);
    }
    zoid->archive = archive;
    zoid->type = type;
    if (archive == (void *)0) {
        return 0;
    }
    HSD_ArchiveLoadDepends(archive, 0, 0, 0);
    HSD_ArchiveResolveReference(archive, 0);
    ZS32(0x3C) = (s32)data;
    scene = (ModelAnimationTable *)HSD_ArchiveGetPublicAddress(archive, "scene_data");
    zoid->animations = scene;
    if (scene == (void *)0) {
        ZoidPurge(zoid);
        return 0;
    }
    strcpy(zoid->name, Tea_zoiddat[type].model_name);
    Str2Lows(zoid->name);
    sprintf(path, "zoid/%s_b.dat", Tea_zoiddat[type].model_name);
    if (usb != 0) {
        zoid->field_0038 = LoadArc2USB(path);
    } else {
        zoid->field_0038 = LoadArc2(path);
    }
    if (zoid->field_0038 == 0) {
        ZoidPurge(zoid);
        return 0;
    }
    if (scene->models != 0) {
        zoid->joint = HSD_JObjLoadJoint(scene->models[0]->joint);
        HSD_JObjAddAnimAll(zoid->joint,
                           scene->models[0]->joint_animations != 0 ? scene->models[0]->joint_animations[0] : (void *)0,
                           scene->models[0]->material_animations != 0 ? scene->models[0]->material_animations[0] : (void *)0,
                           scene->models[0]->shape_animations != 0 ? scene->models[0]->shape_animations[0] : (void *)0);
    }
    jobjAnim(zoid->joint);
    sMakeMatrix(zoid->joint);
    zoid->pose = makeJobj();
    stCopyObj(zoid->joint, zoid->pose);
    stCopyMatMobj(zoid->joint, zoid->pose);
    ZoidCopyAnim(zoid);
    *(NameTable *)names = *(NameTable *)lit_715;
    for (i = 0; i < 30; i++) {
        zoid->weapon_slots[i].joint = 0;
    }
    for (i = 0; names[i] != 0; i++) {
        zoid->weapon_slots[i].joint = searchJoint(zoid, names[i]);
    }
    ZJ(0x1BEC) = searchJoint(zoid, "scope_joint");
    zoid->f_base_joint = searchJoint(zoid, "f_base_joint");
    zoid->b_base_joint = searchJoint(zoid, "b_base_joint");
    if (zoid->f_base_joint == 0) {
        zoid->f_base_joint = searchJoint(zoid, "base_joint");
    }
    if (zoid->b_base_joint == 0) {
        zoid->b_base_joint = searchJoint(zoid, "base_joint");
    }
    zoid->foot_count = 0;
    searchJointFoot(zoid, &zoid->feet[0], "R_glove_joint");
    searchJointFoot(zoid, &zoid->feet[1], "L_glove_joint");
    searchJointFoot(zoid, &zoid->feet[2], "R_shoe_joint");
    searchJointFoot(zoid, &zoid->feet[3], "L_shoe_joint");
    zoid->field_1ACC = searchJoint(zoid, "senter_joint");
    if (zoid->field_1ACC != 0) {
        zoid->senter_translation_y = HSD_JObjGetTranslationY(zoid->field_1ACC);
        zoid->senter_translation_z = HSD_JObjGetTranslationZ(zoid->field_1ACC);
    }
    ZJ(0x12CC) = searchJoint(zoid, "berut1_joint");
    ZJ(0x12D0) = searchJoint(zoid, "cap_joint");
    ZJ(0x12D4) = searchJoint(zoid, "collar_joint");
    ZJ(0x12D8) = searchJoint(zoid, "jacket_joint");
    ZJ(0x12DC) = searchJoint(zoid, "berut1_joint");
    zoid->tail_base_joints[0] = searchJoint(zoid, "fly_joint");
    for (i = 1; i < 8; i++) {
        zoid->tail_base_joints[i] = zoid->tail_base_joints[0];
    }
    ZJ(0x80) = searchJoint(zoid, "to_fly_joint");
    ZJ(0x9C) = searchJoint(zoid, "to_to_fly_joint");
    ZJ(0xB8) = searchJoint(zoid, "to_to_to_fly_joint");
    ZJ(0xD4) = searchJoint(zoid, "to_to_to_to_fly_joint");
    ZJ(0xF0) = searchJoint(zoid, "to_to_to_to_to_fly_joint");
    ZJ(0x10C) = searchJoint(zoid, "to_to_to_to_to_to_fly_joint");
    ZJ(0x128) = searchJoint(zoid, "to_to_to_to_to_to_to_fly_joint");
    ZJ(0x144) = zoid->tail_base_joints[0];
    zoid->buckle_joint = searchJoint(zoid, "buckle_joint");
    ZJ(0x1AD4) = searchJoint(zoid, "berut1_joint");
    ZJ(0x1AD8) = searchJoint(zoid, "jacket_joint");
    ZJ(0x1ADC) = searchJoint(zoid, "collar_joint");
    ZJ(0x1AE0) = searchJoint(zoid, "NAVEL_joint");
    ZJ(0x1AE4) = searchJoint(zoid, "target_joint");
    searchJointCoObj(zoid, zoid->body_coobj, "c_BODY_joint", ZJ(0x12CC));
    searchJointCoObj(zoid, zoid->head_coobj, "c_head_joint", ZJ(0x12D0));
    searchJointCoObj(zoid, zoid->neck_coobj, "c_neck_joint", ZJ(0x12D4));
    searchJointCoObj(zoid, zoid->bust_coobj, "c_bust_joint", ZJ(0x12D8));
    searchJointCoObj(zoid, zoid->hip_coobj, "c_hip_joint", ZJ(0x12DC));
    searchJointCoObj(zoid, zoid->tail_coobjs[0], "c_tail_joint", zoid->tail_base_joints[0]);
    for (i = 1; i < 8; i++) {
        sprintf(tail, "c_tail%d_joint", i);
        searchJointCoObj(zoid, zoid->tail_coobjs[i], tail, zoid->tail_base_joints[i]);
    }
    searchJointCoObj(zoid, zoid->l_arm1_coobj, "c_l_arm1_joint", zoid->feet[1].joint);
    searchJointCoObj(zoid, zoid->l_arm2_coobj, "c_l_arm2_joint", zoid->feet[1].joint);
    searchJointCoObj(zoid, zoid->r_arm1_coobj, "c_r_arm1_joint", zoid->feet[0].joint);
    searchJointCoObj(zoid, zoid->r_arm2_coobj, "c_r_arm2_joint", zoid->feet[0].joint);
    searchJointCoObj(zoid, zoid->l_leg1_coobj, "c_l_leg1_joint", zoid->feet[3].joint);
    searchJointCoObj(zoid, zoid->l_leg2_coobj, "c_l_leg2_joint", zoid->feet[3].joint);
    searchJointCoObj(zoid, zoid->r_leg1_coobj, "c_r_leg1_joint", zoid->feet[2].joint);
    searchJointCoObj(zoid, zoid->r_leg2_coobj, "c_r_leg2_joint", zoid->feet[2].joint);
    searchJointCoObj(zoid, zoid->l_foot_coobj, "c_l_foot_joint", zoid->feet[3].joint);
    searchJointCoObj(zoid, zoid->r_foot_coobj, "c_r_foot_joint", zoid->feet[2].joint);
    zdCalcCoDmg(zoid);
    for (i = 0; i < 6; i++) {
        zoid->spik_joints[i] = searchJoint(zoid, tbl_746[i]);
        OSReport("joint spik [%s] is %s \n", tbl_746[i], zoid->spik_joints[i] != 0 ? "on " : "off");
    }
    for (i = 0; i < 10; i++) {
        sprintf(attack, "a_%1d_joint", i);
        zoid->attack_objects[i].joint = searchJoint(zoid, attack);
        HiddenParts(zoid->attack_objects[i].joint, 1);
    }
    OSReport("atack... read ! ok \n");
    if (zoid->joint != 0) {
        zoid->aobj = (HSD_AObj *)getAnimAobj(zoid->joint->child);
    }
    *(f32 *)((u8 *)zoid + 0x1BE8) = 1.0f + zoid->senter_translation_y;
    ZS32(0x1E9C) = 2;
    zoid->field_1EF8 = Tea_zoiddat[type].search_range;
    ZoidInitParam(zoid);

    sprintf(path, "zoid/idp/zoid_%03d.prm", type);
    buf2 = (u8 *)malloc2(0x750);
    control = (ZoidControlData *)buf2;
    zoid->anim_data = control;
    if (control != 0) {
        ZeroMemory(buf2, 0x750);
        paramInit(control);
        buf2 = sReadFileLenU(path, usb, &length);
        if (buf2 == 0) {
            sprintf(path, "zoid/%s.prm", Tea_zoiddat[type].model_name);
            buf2 = sReadFileLenU(path, usb, &length);
        }
        if (buf2 != 0) {
            MemCpy(buf2, (u8 *)control, length);
            free(buf2);
        }
        if (CS32(control, 0x190) == 0) {
            CS32(control, 0x190) = 4;
        }
        if (CS32(control, 0xD0) == 0) {
            CS32(control, 0xD0) = 40;
        }
        if (CS32(control, 0xD4) == 0) {
            CS32(control, 0xD4) = 150;
        }
        if (CS32(control, 0xD8) == 0) {
            CS32(control, 0xD8) = 150;
        }
        if (CS32(control, 0xE4) == 0) {
            CS32(control, 0xE4) = 15;
        }
        if (CS32(control, 0x308) == 0) {
            CS32(control, 0x308) = 250;
        }
        for (i = 4; i < 10; i++) {
            control->field_0140[i] = 0;
        }
        if (CS32(control, 0x310) < 2) {
            CS32(control, 0x310) = 2;
        }
        if (CS32(control, 0x33C) == 0 && CS32(control, 0x338) == 0) {
            CS32(control, 0x33C) = 50;
            CS32(control, 0x338) = 10;
        }
    }
    zoid->weapon_mount = -1;
    zoid->selected_weapon_mount = 1;
    ai = (u8 *)malloc2(0xB8);
    if (ai != 0) {
        ZeroMemory(ai, 0xB8);
        *(f32 *)(ai + 0xB0) = 1.0f;
        CS32(ai, 0xB4) = 60;
        zoid->ai = (ZoidAIState *)ai;
    }
    sprintf(path, "zoid/mdp/%s.cam", Tea_zoiddat[type].model_name);
    zoid->field_2090 = malloc2(0x164);
    if (zoid->field_2090 != 0) {
        cam = (u8 *)(s32)zoid->field_2090;
        ZeroMemory(cam, 0x164);
        if (CS32(cam, 0x158) == 0) {
            CS32(cam, 0x158) = 60;
        }
        if (CS32(cam, 0x15C) == 0) {
            CS32(cam, 0x15C) = 90;
        }
        if (CS32(cam, 0x160) == 0) {
            CS32(cam, 0x160) = 120;
        }
        data2 = sReadFileLenU(path, usb, &length2);
        if (data2 != 0) {
            MemCpy(data2, (u8 *)(s32)zoid->field_2090, length2);
            free(data2);
        }
    }
    if (zoid->field_2090 != 0) {
        for (i = 0; i < 20; i++) {
            *(ParamTable *)angles = *(ParamTable *)lit_807;
            *(ParamTable *)distances = *(ParamTable *)lit_808;
            *(ParamTable *)heights = *(ParamTable *)lit_809;
            entry = (CameraMountInfo *)((s32)zoid->field_2090 + i * 16);
            if (entry->height == 0 || (zoid->weapon_slots[entry->joint_slot].joint == 0 && entry->joint_slot != -1)) {
                entry->angle = angles[i];
                entry->height = heights[i];
                entry->distance = distances[i];
                if (*(void **)((u8 *)zoid + 0x19B4) != 0) {
                    entry->joint_slot = 19;
                } else {
                    for (j = 0; j < 27; j++) {
                        if (zoid->weapon_slots[j].joint != 0) {
                            entry->joint_slot = j;
                            break;
                        }
                    }
                }
            }
            if (entry->angle == 0) {
                entry->angle = 180;
            }
            if (entry->height == 0) {
                entry->height = 30;
            }
            if (entry->distance == 0) {
                entry->distance = 10;
            }
        }
        if (CS32((s32)zoid->field_2090, 0x154) == 0) {
            CS32((s32)zoid->field_2090, 0x154) = 90;
        }
    }
    for (i = 0; i < 20; i++) {
        zoid->slider_positions[i] = 0;
    }
    sprintf(path, "zoid/mdp/%s.p_a", Tea_zoiddat[type].model_name);
    slider = (u8 *)malloc2(0x752);
    zoid->slider_info = (u16 *)slider;
    if (slider != 0) {
        ZeroMemory(slider, 0x752);
        for (i = 0; i < 200; i++) {
            *(u16 *)((u8 *)zoid->slider_info + 0x142 + i * 2) = i;
            *((u8 *)zoid->slider_info + 0x2D2 + i) = 0;
            *((u8 *)zoid->slider_info + 0x39A + i) = 0;
            if (zdsMotTBL[i] & 0x20) {
                *((u8 *)zoid->slider_info + 0x2D2 + i) |= 8;
            }
            if (zdsMotTBL[i] & 0x10) {
                *((u8 *)zoid->slider_info + 0x2D2 + i) |= 4;
            }
            if (zdsMotTBL[i] & 0x40) {
                *((u8 *)zoid->slider_info + 0x2D2 + i) |= 2;
            }
            if (zdsMotTBL[i] & 0x4) {
                *((u8 *)zoid->slider_info + 0x2D2 + i) |= 1;
            }
            if (zdsMotTBL[i] & 0x8) {
                *((u8 *)zoid->slider_info + 0x2D2 + i) |= 0xF0;
            }
            if (zdsMotTBL[i] & 0x1) {
                *((u8 *)zoid->slider_info + 0x39A + i) |= 2;
            }
            if (zdsMotTBL[i] & 0x2) {
                *((u8 *)zoid->slider_info + 0x39A + i) |= 1;
            }
        }
        if (*(u16 *)((u8 *)zoid->slider_info + 0x702) == 0) {
            *(u16 *)((u8 *)zoid->slider_info + 0x702) = 18;
        }
        if (*(u16 *)((u8 *)zoid->slider_info + 0x706) == 0) {
            *(u16 *)((u8 *)zoid->slider_info + 0x706) = 18;
        }
        if (*(u16 *)((u8 *)zoid->slider_info + 0x704) == 0) {
            *(u16 *)((u8 *)zoid->slider_info + 0x704) = 30;
        }
        if (*(u16 *)((u8 *)zoid->slider_info + 0x708) == 0) {
            *(u16 *)((u8 *)zoid->slider_info + 0x708) = 30;
        }
    }
    if (zoid->slider_info != 0) {
        slider = sReadFileLenU(path, usb, &length3);
        if (slider != 0) {
            MemCpy(slider, (u8 *)zoid->slider_info, length3);
            free(slider);
        }
    }
    if (CS32(zoid->anim_data, 0xF4) != 2) {
        ZS32(0x1BDC) = zoid->foot_count;
    } else {
        ZS32(0x1BDC) = 2;
    }
    for (i = 0; i < 30; i++) {
        zoid->weapon_slots[i].weapon = -1;
    }
    for (i = 0; i < 20; i++) {
        zoid->weapon_mounts[i].active = 0;
        for (j = 0; j < 4; j++) {
            zoid->weapon_mounts[i].entries[j].slot = -1;
            zoid->weapon_mounts[i].entries[j].active = 0;
        }
        zoid->mount_extra[i].slot = -1;
        zoid->mount_extra[i].active = 0;
    }
    for (i = 0; i < 3; i++) {
        zoid->additional_parts[i] = -1;
    }
    buckle = zoid->buckle_joint;
    sMakeMatrix(zoid->joint);
    if (buckle != 0) {
        *(f32 *)((u8 *)zoid + 0x1BF8) = buckle->matrix[1][3] - zoid->joint->matrix[1][3];
    }
    look = 0;
    if (look == 0) look = *(HSD_JObj **)zoid->bust_coobj;
    if (look == 0) look = *(HSD_JObj **)zoid->hip_coobj;
    if (look == 0) look = *(HSD_JObj **)zoid->neck_coobj;
    if (look == 0) look = *(HSD_JObj **)zoid->head_coobj;
    if (look == 0) look = ZJ(0x1AD4);
    if (look == 0) look = ZJ(0x1AD8);
    if (look == 0) look = ZJ(0x1ADC);
    if (look == 0) look = ZJ(0x1AD0);
    if (look == 0) look = ZJ(0x1AD8);
    if (look == 0) look = *(HSD_JObj **)zoid->body_coobj;
    if (look == 0) OSReport("jobjLook error \n");
    if (look == 0) look = zoid->joint;
    ZJ(0x1A30) = look;
    ctrl2 = (ZoidControlData *)zoid->anim_data;
    switch (CS32(ctrl2, 0xFC)) {
    case 0:
        look2 = ZJ(0x1AE0);
        break;
    case 1:
        look2 = 0;
        break;
    case 2:
        look2 = ZJ(0x1ADC);
        break;
    case 3:
        look2 = ZJ(0x1AD8);
        break;
    case 4:
        look2 = ZJ(0x1AD4);
        break;
    case 5:
        look2 = ZJ(0x1AD0);
        break;
    default:
        look2 = 0;
        break;
    }
    if (look2 == 0) look2 = ZJ(0x1ACC);
    if (look2 == 0) look2 = ZJ(0x1AD0);
    if (look2 == 0) look2 = ZJ(0x1AD4);
    if (look2 == 0) look2 = ZJ(0x1AD8);
    if (look2 == 0) look2 = ZJ(0x1ADC);
    if (look2 == 0) look2 = ZJ(0x1AE0);
    if (look2 == 0 && zoid->joint != 0) look2 = zoid->joint->child;
    ZJ(0x1A7C) = look2;
    ZS32(0x1DAC) = -1;
    ZS32(0x1DB0) = 0;
    OSReport("===================zoid OK============\n");
    return 1;
}
#pragma dont_inline on

static const char lit_1010[15] = "zd color =%d \n";
static const char lit_1016[15] = "mount [%s] -- ";
static const char lit_1066[44] = "option set!-%d----- [no.%d] ----zN=%d-----\n";
static const char lit_1170[24] = "GameZoid %d WpColor=%d\n";
void ZoidInitAll(void)
{
    ZoidState *zoid;
    ZoidState *zoid2;
    s32 cnt;
    ZoidControlData *control;
    s32 slots[17];
    s32 start;
    s32 n;
    s32 team;
    MapUnit3 *unit2;
    s32 type;
    s32 human;
    MapUnit3 *unit;
    s32 result;
    s32 i;

    cnt = 0;
    for (i = 0; i < 16; i++) {
        OSReport("zd=%d group=%d\n", i, *(s16 *)((u8 *)&GameZoid[i] + 0x5A));
    }
    if (GameMode.game_type == 9) {
        for (i = 0; i < 16; i++) {
            GameZoid[i].type = -1;
        }
    }
    for (i = 0; i < 16; i++) {
        type = GameZoid[i].type;
        if (type == -1) {
            continue;
        }
        if (i < 5) {
            team = 0;
        } else {
            team = 1;
        }
        if (team == 1 && (GameMode.game_type == 1 || GameMode.game_type == 4)) {
            continue;
        }
        n = (i % 5) * 2 + team;
        if (GameMode.game_type == 5) {
            team = *(s16 *)((u8 *)&GameZoid[i] + 0x5A);
            n = i;
        }
        ZoidInit1(&Zoid[n], i, team);
        if (GameMode.game_type == 5) {
            Zoid[n].slot = team;
            OSReport("group=%d\n", team);
        }
    }
    for (i = 0; i < 17; i++) {
        unit = &mgI.units[i];
        switch (unit->kind) {
        case 0:
        case 2:
            break;
        case 1:
        case 3:
        case 4:
            zoid = 0;
            if (unit->kind == 1) {
                zoid = 0;
                if (unit->enabled != 0) {
                    human = (s8)unit->field_111;
                    start = human + 1;
                    if (GameMode.game_type == 9) {
                        start &= 1;
                    }
                    for (n = start; n < 16; n += 2) {
                        if (Zoid[n].joint == (void *)0) {
                            break;
                        }
                    }
                    if (n >= 16) {
                        continue;
                    }
                    if (Zoid[n].joint != 0) {
                        continue;
                    }
                    zoid = &Zoid[n];
                    result = infoLoadZoid0(zoid, &unit->info);
                    zoid->field_20A0 = unit->f10E + unit->f10C * 256;
                    if (result == 0) {
                        slots[i] = -1;
                        zoid = 0;
                    } else {
                        slots[i] = n;
                    }
                    zoid->slot = (human + 1) & 1;
                    zoid->gene_x = unit->x;
                    zoid->gene_z = unit->z;
                    zoid->gene_y = unit->gene_y;
                    zoid->gene_y_fixed = unit->fixed_y;
                    zoid->field_20BC = unit->f1FA;
                    zoid->field_20B4 = unit->f1FB * 60;
                    zoid->field_20B8 = zoid->field_20B4;
                    OSReport("zd=%d grp=%d %s\n", n, zoid->slot, zoid->field_20BC != 0 ? "gene" : "    ");
                }
            }
            if (unit->kind == 3) {
                zoid = &Zoid[cnt];
                cnt++;
            }
            if (unit->kind == 4) {
                zoid = &Zoid[2];
                zoid->field_20A0 = unit->f10E + unit->f10C * 256;
            }
            if (zoid != 0) {
                zoid->position[0] = unit->x;
                zoid->position[2] = unit->z;
                if (unit->fixed_y != 0) {
                    zoid->position[1] = unit->gene_y;
                } else {
                    zoid->position[1] = 100.0f;
                    zoid->position[1] = 1.0f + zdColPosY(zoid->position, 0);
                    zoid->position[1] = 100.0f + zdColPosY(zoid->position, 0);
                    zoid->position[1] = 1.0f + zdColPosY(zoid->position, 0);
                }
                zoid->heading = 2 * (3.1415926 * (f32)unit->heading) / 360.0;
            }
            break;
        }
    }
    for (i = 0; i < 17; i++) {
        unit2 = &mgI.units[i];
        switch (unit2->kind) {
        case 0:
            break;
        case 1:
            if (unit2->kind == 1 && unit2->enabled != 0) {
                n = slots[i];
                if (n != -1 && Zoid[n].joint != 0) {
                    zoid2 = &Zoid[n];
                    infoLoadZoid1(zoid2, &unit2->info);
                }
            }
            break;
        case 2:
            break;
        }
    }
    if (GameMode.game_type == 3) {
        if (GameMode.win == 0) {
            Zoid[1].field_20A0 = Zoid[1].person + 120;
            control = (ZoidControlData *)Zoid[1].anim_data;
            if (control != 0 && control->field_00F8 == 3) {
                Zoid[1].field_20A0 = Zoid[1].person + 500;
            }
        } else {
            Zoid[1].field_20A0 = Zoid[1].person + 260;
            control = (ZoidControlData *)Zoid[1].anim_data;
            if (control != 0 && control->field_00F8 == 3) {
                Zoid[1].field_20A0 = Zoid[1].person + 500;
            }
        }
    }
    if (GameMode.game_type == 5) {
        for (i = 0; i < 4; i++) {
            if (GameZoid[i].option != 0) {
                Zoid[i].field_20A0 = Zoid[i].person + 120;
            }
        }
    }
    if (GameMode.game_type == 1) {
        if (Zoid[2].joint != 0) {
            control = (ZoidControlData *)Zoid[2].anim_data;
            if (control != 0 && control->field_00F8 == 3) {
                Zoid[2].field_20A0 = Zoid[2].person + 500;
            }
        }
    }
    zoid2 = zoid2;
    zoid2 = zoid2;
    zoid2 = zoid2;
    zoid2 = zoid2;
    zoid2 = zoid2;
}

s32 zdVoiceScriptCalc(VoiceEntry *entry, ZoidState *zoid, s32 a, s32 b)
{
    s32 i;
    s32 type;
    s32 typeA;
    s32 typeB;
    s32 person;
    s32 personA;
    s32 personB;
    s32 f68;
    s32 f64;
    s8 *choices;
    s8 result;

    if (entry == 0) {
        return -1;
    }
    type = zoid->type;
    person = zoid->person;
    f68 = zoid->field_1E68;
    f64 = zoid->field_1E64;
    typeA = Zoid[a].type;
    typeB = Zoid[b].type;
    personA = Zoid[a].person;
    personB = Zoid[b].person;
    for (i = 0; i < 20; i++, entry++) {
        choices = entry->choices;
        switch (entry->kind) {
        case 0:
            return -1;
        case 1:
            break;
        case 2:
            if (entry->value == person) break;
            continue;
        case 3:
            if (entry->value == type) break;
            continue;
        case 4:
            if (entry->value == personA) break;
            continue;
        case 5:
            if (entry->value == typeA) break;
            continue;
        case 6:
            if (entry->value == personB) break;
            continue;
        case 7:
            if (entry->value == typeB) break;
            continue;
        case 8:
            if (entry->value != f68) continue;
            zoid->field_1E68 = -1;
            break;
        case 9:
            if (entry->value != f64) continue;
            zoid->field_1E64 = -1;
            break;
        default:
            continue;
        }
        if (entry->flags & 1) {
            result = choices[HSD_Randi(4)];
        } else {
            result = choices[0];
        }
        return result;
    }
    return -1;
}

void zdVoiceScript(ZoidState *zoid)
{
    char path[100];
    if (zoid->joint != 0) {
        sprintf(path, "chara/v_sc/man%03d.sc", zoid->person);
        zoid->field_0028 = sReadFileU(path, 0);
        OSReport("voice script [%s] %s \n", path, zoid->field_0028 != 0 ? "OK" : "GGG not dound");
    }
}

void zdVoiceSc(ZoidState *zoid, s32 id)
{
    void *pack;
    VoiceEntry *script;
    VoiceEntry *entries;
    s32 flag;
    s32 team;
    s32 index;
    s32 i;
    ZoidState *other;
    s32 target;
    s32 voice;

    if (zoid == 0) {
        return;
    }
    if (zoid->joint == 0) {
        return;
    }
    pack = zoid->field_0028;
    if (pack == 0) {
        return;
    }
    script = (VoiceEntry *)binB(pack, id);
    if (script == 0) {
        OSReport("no script ---------[%d] \n", id);
    }
    if (script == 0) {
        return;
    }
    entries = script;
    flag = 0;
    if (GameMode.game_type == 2) {
        flag = 1;
    }
    if (GameMode.game_type == 3) {
        flag = 1;
    }
    if (flag == 0) {
        if (zoid == &Zoid[0]) {
            flag = 1;
        }
        if (zoid == &Zoid[2]) {
            flag = 1;
        }
    }
    if (flag == 0) {
        if (camTmp == 0) {
            return;
        }
        if (camTmp->zoid_distance[zoid->index] > 500.0f) {
            return;
        }
    }
    team = zoid->slot;
    index = -1;
    for (i = 0; i < 16; i++) {
        other = &Zoid[i];
        if (other != zoid && other->joint != 0 && team == other->slot) {
            index = i;
            break;
        }
    }
    target = zoid->target_slot;
    if (zoid->target_pending == 0) {
        target = -1;
    }
    if (target != -1 && Zoid[target].joint != 0) {
        target = -1;
    }
    voice = zdVoiceScriptCalc(entries, zoid, index, target);
    OSReport("voice man[%d] script[%d] set %d voice \n", zoid->person, id, voice);
    if (voice != -1) {
        camVoiceOn(zoid->person, voice);
    }
}

static const char lit_1506[38] = "add power z%d \x92" "e=%d , \x8ai\x93\xac=%d bp=%d \n";
#pragma dont_inline off
static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & 0x00800000) && (jobj->flags & 0x40);
}

static inline void HSD_JObjSetTranslateX(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 952, "jobj");
    jobj->translation.x = value;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj)) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

static inline void HSD_JObjSetTranslateY(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 966, "jobj");
    jobj->translation.y = value;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj)) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

static inline void HSD_JObjSetTranslateZ(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 980, "jobj");
    jobj->translation.z = value;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj)) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

static inline void HSD_JObjSetRotationX(HSD_JObj *jobj, f32 x)
{
    jobj ? (void)0 : __assert("jobj.h", 676, "jobj");
    !(jobj->flags & 0x20000) ? (void)0 : __assert("jobj.h", 677, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    jobj->rotation[0] = x;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj)) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

static inline void HSD_JObjSetRotationY(HSD_JObj *jobj, f32 y)
{
    jobj ? (void)0 : __assert("jobj.h", 696, "jobj");
    !(jobj->flags & 0x20000) ? (void)0 : __assert("jobj.h", 697, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    jobj->rotation[1] = y;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj)) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

static inline void HSD_JObjSetRotationZ(HSD_JObj *jobj, f32 z)
{
    jobj ? (void)0 : __assert("jobj.h", 716, "jobj");
    !(jobj->flags & 0x20000) ? (void)0 : __assert("jobj.h", 717, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    jobj->rotation[2] = z;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj)) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

static inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

void zdSetXYZ(ZoidState *zoid)
{
    ZoidControlData *control = (ZoidControlData *)zoid->anim_data;
    s32 mode = control->field_00F8;
    f32 other_rx = 0.0f;
    f32 rx = zoid->high_angle;
    f32 heading;

    HSD_JObjSetTranslateX(zoid->joint, zoid->position[0]);
    HSD_JObjSetTranslateY(zoid->joint, zoid->position[1] + zoid->height_offset);
    HSD_JObjSetTranslateZ(zoid->joint, zoid->position[2]);
    heading = zoid->heading;
    if (absf(heading) < (3.1415926 / 180.0)) {
        if (heading >= 0.0f) {
            heading = (f32)(3.1415926 / 180.0);
        } else {
            heading = -(f32)(3.1415926 / 180.0);
        }
    }
    HSD_JObjSetRotationY(zoid->joint, heading);
    if (control->field_00F8 == 3) {
        other_rx = rx;
        rx = 0.0f;
        if (absf(other_rx) >= (20 * 3.1415926 / 180.0)) {
            if (other_rx > 0.0f) {
                rx = other_rx - (20 * 3.1415926 / 180.0);
                other_rx = (f32)(20 * 3.1415926 / 180.0);
            } else {
                rx = (20 * 3.1415926 / 180.0) + other_rx;
                other_rx = -(f32)(20 * 3.1415926 / 180.0);
            }
        }
    }
    HSD_JObjSetRotationX(zoid->joint, rx);
    if (control->field_00F8 == 3) {
        HSD_JObjSetRotationX(zoid->buckle_joint, other_rx);
    }
}
#pragma dont_inline on

#pragma dont_inline off
static inline f32 HSD_AObjGetCurrentFrame(HSD_AObj *aobj)
{
    aobj ? (void)0 : __assert("aobj.h", 149, "aobj");
    return aobj->current_frame;
}

void ZoidAnim(ZoidState *zoid)
{
    HSD_JObj *HSD_JObjAnimAll_joint;

    u32 *motion = zdsMotTBL;
    s32 loop;
    f32 frame;

    if (zoid != (void *)0 && zoid->joint != (void *)0 && zoid->animation_stopped == 0 && zoid->death_pending == 0) {
        if (zoid->aobj == 0) {
            frame = 0.0f;
        } else {
            frame = HSD_AObjGetCurrentFrame(zoid->aobj);
        }
        {
            HSD_JObjAnimAll_joint = zoid->joint;
            HSD_JObjAnimAll(HSD_JObjAnimAll_joint);
        }
        zoid->animation_stopped = 0;
        if (zoid->aobj == 0) {
            zoid->anim_current_frame = 0.0f;
        } else {
            zoid->anim_current_frame = HSD_AObjGetCurrentFrame(zoid->aobj);
        }
        zoid->animation_looped = 0;
        loop = 0;
        if (HSD_AObjGetFlags(zoid->aobj) & AOBJ_REWINDED) {
            if (zoid->current_animation == 5 || zoid->current_animation == 4) {
                zdClearAtkTouch(zoid);
            }
            zoid->animation_looped = 1;
            loop = 1;
            if (!(motion[zoid->current_animation] & 2)) {
                zdAnimEffect(zoid, zoid->current_animation);
            }
        }
        if (loop != 0 && (motion[zoid->current_animation] & 2)) {
            zdAnimRate(zoid, 1.0f);
            setAnimFrame(zoid->joint, frame);
            setAnimStop(zoid->joint);
            setAnimRate(zoid->joint, 0.0f);
            zoid->anim_rate = 0.0f;
            HSD_JObjAnimAll(zoid->joint);
            zoid->animation_stopped = 1;
        }
        zdChildAnmBak(zoid);
        zoid->child_translation_y = HSD_JObjGetTranslationY(zoid->joint->child);
        zdChildAnmDif(zoid);
        zdAtkTransOFF(zoid);
        if (zoid->ground_normal_count != 0) {
            zoid->field_1C40 = 0;
        } else {
            zoid->field_1C40++;
        }
        if (zoid->child_translation_y > 0.3) {
            zoid->movement_flags = (zoid->movement_flags << 1) | 1;
            zoid->field_1C48 = 1;
        }
        if (zoid->child_translation_y < 0.01) {
            zoid->movement_flags = zoid->movement_flags << 1;
        }
        zoid->movement_flags = (u8)zoid->movement_flags;
        if (motion[zoid->current_animation] & 0x80) {
            zdClearAnimRy(zoid->joint, motion[zoid->current_animation]);
        }
        zdSetXYZ(zoid);
    }
}
#pragma dont_inline on

#pragma dont_inline off
void calcBaseF(ZoidState *zoid)
{
    ZoidControlData *control;
    u8 *info;
    f32 rx;
    f32 rz;
    f32 step;
    f32 limit;

    if (zoid && zoid->joint != 0 && zoid->f_base_joint != 0) {
        info = (u8 *)zoid->slider_info;
        control = (ZoidControlData *)zoid->anim_data;
        if (info != 0) {
            step = 2 * (3.1415926 * ((f32) * (u16 *)(info + 0x702) / 60.0f)) / 360.0;
            limit = 2 * (3.1415926 * (f32) * (u16 *)(info + 0x704)) / 360.0;
            if (control->field_00F8 == 1) {
                HSD_JObjSetRotationX(zoid->f_base_joint, zoid->ground_rx);
                HSD_JObjSetRotationZ(zoid->f_base_joint, zoid->ground_rz);
            } else {
                if (control->field_00F4 != 2) {
                    sSetRxRzF(zoid, &zoid->feet[1], &zoid->feet[0], &rx, &rz);
                    if (rx > limit) {
                        rx = limit;
                    }
                    if (rz > limit) {
                        rz = limit;
                    }
                    if (rx < -limit) {
                        rx = -limit;
                    }
                    if (rz < -limit) {
                        rz = -limit;
                    }
                    sLinear1D(&zoid->f_base_rx, rx, step);
                    sLinear1D(&zoid->f_base_rz, rz, step);
                    HSD_JObjSetRotationX(zoid->f_base_joint, zoid->f_base_rx);
                    HSD_JObjSetRotationZ(zoid->f_base_joint, zoid->f_base_rz);
                } else {
                    HSD_JObjSetRotationX(zoid->f_base_joint, zoid->ground_rx);
                    HSD_JObjSetRotationZ(zoid->f_base_joint, zoid->ground_rz);
                }
            }
        }
    }
}
#pragma dont_inline on

#pragma dont_inline off
void calcBaseB(ZoidState *zoid)
{
    ZoidControlData *control;
    u16 *slider;

    if (zoid && zoid->joint != 0 && (control = (ZoidControlData *)zoid->anim_data) != 0 && (slider = zoid->slider_info) != 0 && zoid->b_base_joint != 0) {
        if (control->field_00F8 == 1) {
            HSD_JObjSetRotationX(zoid->b_base_joint, zoid->ground_rx);
            HSD_JObjSetRotationZ(zoid->b_base_joint, zoid->ground_rz);
        } else if (control->field_00F4 != 0) {
            HSD_JObjSetRotationX(zoid->b_base_joint, zoid->ground_rx);
            HSD_JObjSetRotationZ(zoid->b_base_joint, zoid->ground_rz);
        }
    }
    slider = slider;
}
#pragma dont_inline on

#pragma dont_inline off
void ZoidPutJumpingXZ(ZoidState *zoid)
{
    ZoidControlData *control;
    HSD_JObj *joint;
    s32 i;

    if (zoid == (void *)0) {
        return;
    }
    if (zoid->joint == (void *)0) {
        return;
    }
    control = (ZoidControlData *)zoid->anim_data;
    zdGetBasePoly(zoid, zoid->position);
    if (zoid->height_offset < 0.0f) {
        zoid->height_offset += 0.02;
    }
    if (zoid->height_offset > 0.0f) {
        zoid->height_offset -= 0.02;
    }
    joint = zoid->joint;
    zdSetXYZ(zoid);
    if (zoid->f_base_joint != (void *)0 && control->field_00F4 == 4) {
        if (zoid->f_base_rx > 0.0f) {
            zoid->f_base_rx -= 5 * 3.1415926 / 180.0;
        }
        if (zoid->f_base_rx < 0.0f) {
            zoid->f_base_rx += 5 * 3.1415926 / 180.0;
        }
        if (zoid->f_base_rz > 0.0f) {
            zoid->f_base_rz -= 5 * 3.1415926 / 180.0;
        }
        if (zoid->f_base_rz < 0.0f) {
            zoid->f_base_rz += 5 * 3.1415926 / 180.0;
        }
        HSD_JObjSetRotationX(zoid->f_base_joint, zoid->f_base_rx);
        HSD_JObjSetRotationZ(zoid->f_base_joint, zoid->f_base_rz);
    }
    if (zoid->b_base_joint != (void *)0 && control->field_00F4 != 0) {
        if (zoid->ground_rx > 0.0f) {
            zoid->ground_rx -= 5 * 3.1415926 / 180.0;
        }
        if (zoid->ground_rx < 0.0f) {
            zoid->ground_rx += 5 * 3.1415926 / 180.0;
        }
        if (zoid->ground_rz > 0.0f) {
            zoid->ground_rz -= 5 * 3.1415926 / 180.0;
        }
        if (zoid->ground_rz < 0.0f) {
            zoid->ground_rz += 5 * 3.1415926 / 180.0;
        }
        HSD_JObjSetRotationX(zoid->b_base_joint, zoid->ground_rx);
        HSD_JObjSetRotationZ(zoid->b_base_joint, zoid->ground_rz);
    }
    zdSetXYZ(zoid);
    sMakeMatrix(zoid->joint);
    zoid->ground_normal_count = 0;
    for (i = 0; i < 3; ) {
        zoid->ground_normal_sum[i++] = 0.0f;
    }
    if (control->field_00F4 != 2) {
        ik3d(zoid, &zoid->feet[0]);
        ik3d(zoid, &zoid->feet[1]);
    }
    ik3d(zoid, &zoid->feet[2]);
    ik3d(zoid, &zoid->feet[3]);
}
#pragma dont_inline on

extern void ZoidPutXZ(ZoidState *zoid);
extern void ZoidPutJumpingXZ(ZoidState *zoid);
extern void ZoidPutLandingXZ(ZoidState *zoid);

void ZoidAllAnim(void)
{
    s32 i;

    for (i = 0; i < 16; i++) {
        if (Zoid[i].joint != (void *)0) {
            angLimit(&Zoid[i].heading);
            ZoidCopyAnim(&Zoid[i]);
            ZoidAnim(&Zoid[i]);
        }
    }
}

void ZoidAllMat(void)
{
    s32 i;

    for (i = 0; i < 16; i++) {
        if (Zoid[i].joint != (void *)0) {
            zdSetXYZ(&Zoid[i]);
            sMakeMatrix(Zoid[i].joint);
        }
    }
}

extern void zdLockOnOff(ZoidState *zoid);
extern s32 zdWeaponNow(ZoidState *zoid);
extern void zdOptionLoop(ZoidState *zoid);
extern void zdSmokeRecv(ZoidState *zoid);

void ZoidWeaponActLoop(void)
{
    s32 i;
    ZoidState *zoid;
    ZoidControlData *control;
    s32 weapon_available;

    for (i = 0; i < 16; i++) {
        zoid = &Zoid[i];
        if (zoid->joint != 0) {
            control = (ZoidControlData *)zoid->anim_data;
            dummyFunc("1");
            zdLockOnOff(zoid);
            dummyFunc("2");
            zdWeaponNow(zoid);
            dummyFunc("3");
            zdWeaponActLoop(zoid);
            dummyFunc("4");
            zdOptionLoop(zoid);
            dummyFunc("5");
            zdSmokeRecv(zoid);
            dummyFunc("6");
            if (zoid->weapon_mount != -1) {
                weapon_available = 1;
            }
            if (zoid->field_016C != 0 || (control != 0 && control->field_00F8 == 3)) {
                zoid->field_0170 = 1;
            } else {
                zoid->field_0170 = 0;
            }
            dummyFunc("e");
        }
    }
    dummyFunc("E.");
}

void ZoidAllPutXZ(void)
{
    s32 i;
    ZoidState *zoid;
    ZoidControlData *control;
    s32 state;
    s32 group;

    for (i = 0; i < 16; i++) {
        zoid = &Zoid[i];
        if (zoid->joint != (void *)0) {
            control = (ZoidControlData *)zoid->anim_data;
            if (control != 0 && control->field_00F8 != 3 && zoid->field_0170 == 0) {
                dummyFunc("p.");
                state = zoid->jump_phase;
                group = state & 0xF0;
                if (state == 0) {
                    dummyFunc("0");
                    ZoidPutXZ(&Zoid[i]);
                } else if (state <= 3 && zoid->field_1C90[2]) {
                    ZoidPutJumpingXZ(&Zoid[i]);
                } else if (group == 16) {
                    ZoidPutJumpingXZ(&Zoid[i]);
                } else if (group == 32) {
                    ZoidPutLandingXZ(&Zoid[i]);
                } else if (group == 48) {
                    ZoidPutLandingXZ(&Zoid[i]);
                } else {
                    ZoidPutLandingXZ(&Zoid[i]);
                }
            }
        }
    }
}

void ZoidAllDisp3(void)
{
    s32 i;
    f32 (*view)[4];
    Vec3 point;
    s32 lod;
    ZoidState *zoid;
    ZoidControlData *control;
    s32 flag;
    s32 stealth;

    view = HSD_CObjGetViewingMtxPtr(camTmp->cobj);
    for (i = 0; i < 16; i++) {
        stealth = 0;
        if ((zoid = &Zoid[i])->joint != (void *)0) {
            lod = camTmp->lod_flag;
            control = (ZoidControlData *)zoid->anim_data;
            if (zoid->stel_state == 2) {
                stealth = 1;
            }
            if (stealth == 0) {
                continue;
            }
            if (zdClip(lod, view, &Zoid[i], &point) != 0) {
                continue;
            }
            angLimit(&Zoid[i].heading);
            zdSetXYZ(zoid);
            flag = camTmp->zoid_distance[i] < (f32)control->detail_distance;
            if (sCamNN == 4) {
                flag = camTmp->zoid_distance[i] < 200.0f;
            }
            if (flag) {
                flag = !dbgZoidColi;
            }
            if (lod != 0) {
                flag = 1;
            }
            if (flag) {
                ZoidCoObjOFF(zoid);
                HSD_JObjDispAll(Zoid[i].joint, 0, 7, 0);
            } else {
                ZoidSmallDisp(&Zoid[i]);
            }
            zoid = zoid;
            stealth = stealth;
        }
    }
}

void ZoidAllDisp(void)
{
    s32 i;
    f32 (*view)[4];
    Vec3 point;
    s32 lod;
    ZoidState *zoid;
    ZoidControlData *control;
    s32 flag;

    view = HSD_CObjGetViewingMtxPtr(camTmp->cobj);
    for (i = 0; i < 16; i++) {
        zoid = &Zoid[i];
        if (Zoid[i].joint != (void *)0) {
            lod = camTmp->lod_flag;
            control = (ZoidControlData *)zoid->anim_data;
            if (zoid->stel_state != 0) {
                continue;
            }
            if (zdClip(lod, view, &Zoid[i], &point) != 0) {
                continue;
            }
            angLimit(&Zoid[i].heading);
            flag = camTmp->zoid_distance[i] < (f32)control->detail_distance;
            if (sCamNN == 4) {
                flag = camTmp->zoid_distance[i] < 200.0f;
            }
            if (flag) {
                flag = !dbgZoidColi;
            }
            if (lod != 0) {
                flag = 1;
            }
            if (flag) {
                ZoidCoObjOFF(zoid);
                HSD_JObjDispAll(Zoid[i].joint, 0, 7, 0);
            } else {
                ZoidSmallDisp(&Zoid[i]);
            }
        }
    }
    zdDispCursor();
}

void ZoidAllDispXLU(void)
{
    s32 i;
    f32 (*view)[4];
    Vec3 point;
    s32 lod;
    ZoidState *zoid;
    ZoidControlData *control;
    s32 flag;

    view = HSD_CObjGetViewingMtxPtr(camTmp->cobj);
    for (i = 0; i < 16; i++) {
        if ((zoid = &Zoid[i])->joint != (void *)0) {
            lod = camTmp->lod_flag;
            control = (ZoidControlData *)zoid->anim_data;
            if (zoid->stel_state != 1) {
                continue;
            }
            if (zdClip(lod, view, &Zoid[i], &point) != 0) {
                continue;
            }
            flag = camTmp->zoid_distance[i] < (f32)control->detail_distance;
            if (sCamNN == 4) {
                flag = camTmp->zoid_distance[i] < 200.0f;
            }
            if (flag) {
                flag = !dbgZoidColi;
            }
            if (lod != 0) {
                flag = 1;
            }
            if (flag) {
                ZoidCoObjOFF(zoid);
                HSD_JObjDispAll(Zoid[i].joint, 0, 2, 0);
                HSD_JObjDispAll(Zoid[i].joint, 0, 4, 0);
            } else {
                ZoidSmallDisp(zoid);
            }
            zoid = zoid;
        }
    }
}

#pragma dont_inline off
void zdLen(s32 a, s32 b)
{
    s32 k;
    f32 len3 = 0.0f;
    f32 lenxz = 0.0f;
    f32 diff;
    f32 sq;
    volatile f32 rootA;
    volatile f32 rootB;

    if (a != b) {
        for (k = 0; k < 3; k++) {
            diff = Zoid[a].joint->matrix[k][3] - Zoid[b].joint->matrix[k][3];
            sq = diff * diff;
            len3 += sq;
            if (k != 1) {
                lenxz += sq;
            }
        }
        len3 = sqrtf_vol(len3, &rootA);
        lenxz = sqrtf_vol(lenxz, &rootB);
    }
    Zoid[a].distances[b] = len3;
    Zoid[b].distances[a] = len3;
    Zoid[a].field_1F48[b] = lenxz;
    Zoid[b].field_1F48[a] = lenxz;
}
#pragma dont_inline on

extern void zdLen(s32 a, s32 b);
extern void zdAtk(ZoidState *zoid);
extern f32 ZoidCalcAngle(ZoidState *zoid, f32 *pos);

void ZoidLen(void)
{
    s32 i;
    s32 j;
    ZoidState *zoid;
    ZoidState *other;
    f32 angle;

    for (i = 0; i < 16; i++) {
        if (Zoid[i].joint != (void *)0) {
            for (j = i; j < 16; j++) {
                if (Zoid[j].joint != (void *)0) {
                    zdLen(i, j);
                }
            }
        }
    }
    for (i = 0; i < 16; i++) {
        zoid = &Zoid[i];
        if (zoid->joint != (void *)0) {
            zdAtk(zoid);
            for (j = 0; j < 16; j++) {
                other = &Zoid[j];
                if (i != j && other->joint != (void *)0) {
                    angle = ZoidCalcAngle(zoid, other->position);
                    if (angle != 100.0) {
                        zoid->target_angles[j] = angle;
                    }
                }
            }
        }
    }
}

extern void ZoidCoObjMtxI(ZoidState *zoid);
extern s32 ZoidCoObjCoObj(void *a, void *b, s32 flags);

void ZoidZdCoObjBodyAll(void)
{
    s32 dead;
    s32 i;
    ZoidState *zoid;
    ZoidState *other;
    s32 j;

    for (i = 0; i < 16; i++) {
        zoid = &Zoid[i];

        if (zoid->joint != (void *)0 && *(HSD_JObj **)zoid->body_coobj != (void *)0) {
            ZoidCoObjMtxI(zoid);
        }
    }
    for (i = 0; i < 16; i++) {
        zoid = &Zoid[i];

        if (zoid->joint != (void *)0 && *(HSD_JObj **)zoid->body_coobj != (void *)0) {
            for (j = 0; j < 16; j++) {
                if (i != j && (other = &Zoid[j])->joint != (void *)0 && *(HSD_JObj **)other->body_coobj != (void *)0) {
                    dead = dead;
                    dead = 0;
                    other->contact[i] = (zoid->contact[j] = ZoidCoObjCoObj(zoid->body_coobj, other->body_coobj, 0));
                }
            }
        }
    }
}

static const char lit_2040[30] = "zoid anim setAnim=(%d)error \n";
#pragma dont_inline off
static inline f32 HSD_JObjGetScaleX(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 899, "jobj");
    return jobj->scale.x;
}

static inline f32 HSD_JObjGetScaleY(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 911, "jobj");
    return jobj->scale.y;
}

static inline f32 HSD_JObjGetScaleZ(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 923, "jobj");
    return jobj->scale.z;
}

void ZoidZdAll(void)
{
    s32 team;
    s32 attack_index;
    s32 type;
    s32 damage;
    u16 polygon;
    Vec3 *point;
    s32 attack_effect;
    s32 weapon_b;
    s32 weapon_a;
    s32 i;
    ZoidState *other2;
    HSD_JObj *ajoint;
    s32 k2;
    s32 hit;
    Weapon3 *weapon;
    ZoidState *other;
    ZoidState *zoid;
    ZoidAttackObject *attack;
    s32 j;
    HSD_JObj *jobj;
    s32 k;
    f32 ratio;
    f32 range;

    for (i = 0; i < 16; i++) {
        zoid = &Zoid[i];
        hit = 0;
        if (zoid->joint == (void *)0) {
            continue;
        }
        attack_index = -1;
        type = zoid->type;
        if (zoid->action >= 13 && zoid->action <= 22) {
            attack_index = zoid->action - 13;
        }
        if (zoid->jump_phase != 0 && zoid->jump_attack_phase != 0) {
            attack_index = 5;
        }
        if (attack_index != -1) {
            attack_effect = Tea_zoiddat[type].attack_hit_effects[attack_index];
        } else {
            attack_effect = Tea_zoiddat[type].attack_hit_effects[11];
        }
        damage = zdAtkZdZdDmgHp(zoid);
        for (j = 0; j < 16; j++) {
            if (i == j || zoid->contact[j] == 0 || (other = &Zoid[j])->joint == (void *)0 || other->field_1E50 != 0) {
                continue;
            }
            for (k = 0; k < 10; k++) {
                attack = &zoid->attack_objects[k];
                (void)hit;
                (void)hit;
                if (attack == (void *)0 || (ajoint = attack->joint) == (void *)0) {
                    continue;
                }
                if ((s8)attack->touched[j] != 0) {
                    continue;
                }
                if (ajoint->scale.x <= 0.1 || ajoint->scale.y <= 0.1 || ajoint->scale.z <= 0.1) {
                    continue;
                }
                if (gameStartF != 0) {
                    continue;
                }
                if (gametime < 15) {
                    continue;
                }
                if (other->armor < 1) {
                    other->armor = 1;
                }
                ratio = 10.0 * (f32)damage / (f32)other->armor;
                if ((hit = ZoidZdCoAtack(attack, other, attack_effect, (s32)ratio))) {
                    attack->touched[j] = 1;
                    ZoidCoAtackDmg(zoid, attack, other, hit);
                }
            }
            if (hit != 0) {
                break;
            }
        }
    }

    dummyFunc("ZdWpCo\n");
    for (i = 0; i < 16; i++) {
        zoid = &Zoid[i];
        if (zoid->joint == (void *)0) {
            continue;
        }
        hit = 0;
        for (j = 0; j < 100; j++) {
            weapon = &sWeapon[j];
            if (weapon->active == 0 || weapon->owner == zoid) {
                continue;
            }
            for (k = 0; k < 12; k++) {
                jobj = weapon->inverses[k].joint;
                weapon_a = Tea_partsdat[weapon->type].hit_b;
                weapon_b = Tea_partsdat[weapon->type].hit_a;
                if (jobj == (void *)0) {
                    continue;
                }
                if (HSD_JObjGetScaleX(jobj) < 0.1) {
                    continue;
                }
                if (HSD_JObjGetScaleY(jobj) < 0.1) {
                    continue;
                }
                if (HSD_JObjGetScaleZ(jobj) < 0.1) {
                    continue;
                }
                if (gameStartF != 0) {
                    continue;
                }
                if (gametime < 15) {
                    continue;
                }
                if ((hit = ZoidWpCoAtk(&weapon->inverses[k], zoid, weapon_a, weapon_b))) {
                    ZoidCoWpAtackDmg(weapon, &weapon->inverses[k], zoid);
                    break;
                }
            }
            if (hit != 0) {
                break;
            }
        }
    }

    dummyFunc("CoCoMinR\n");
    for (i = 0; i < 16; i++) {
        zoid = &Zoid[i];
        if (zoid->joint != (void *)0) {
            zoid->field_1EB2 = zoid->field_1EB0;
            zoid->field_1EB0 = 0;
            zoid->contact_bits = 0;
        }
    }
    for (i = 0; i < 16; i++) {
        zoid = &Zoid[i];
        if (zoid->joint == (void *)0) {
            continue;
        }
        for (j = i; j < 16; j++) {
            if (i == j || zoid->contact[j] == 0 || (other = &Zoid[j])->joint == (void *)0) {
                continue;
            }
            if (ZoidZdCoObj(zoid, other) == 0) {
                continue;
            }
            zdCoCoMinR(zoid, other);
            zoid->field_1EB0 |= bitTBL[j];
            other->field_1EB0 |= bitTBL[i];
            ZoidCopyAnim(zoid);
            ZoidCopyAnim(other);
            zoid->interpolation_remaining = 10;
            zoid->interpolation_duration = 15;
            other->interpolation_remaining = 10;
            other->interpolation_duration = 15;
        }
    }

    dummyFunc("LenR\n");
    for (i = 0; i < 16; i++) {
        zoid = &Zoid[i];
        if (zoid->joint == (void *)0) {
            continue;
        }
        type = zoid->type;
        range = zoid->field_1EF8;
        for (j = 0; j < 16; j++) {
            zoid->target_visibility[j] = 0;
            if (i == j || (other = &Zoid[j])->joint == (void *)0) {
                continue;
            }
            if (zoid->slot == other->slot) {
                zoid->target_visibility[j] = 1;
            } else if (!(range < zoid->distances[j]) && other->stel_state != 2 && zoid->enemy_smoke_timer == 0) {
                zoid->target_visibility[j] = 1;
            }
        }
    }

    for (i = 0; i < 16; i++) {
        zoid = &Zoid[i];
        if (zoid->joint == (void *)0) {
            continue;
        }
        team = zoid->slot;
        if (zoid->enemy_smoke_timer != 0) {
            continue;
        }
        for (j = 0; j < 16; j++) {
            if (i == j || zoid->target_visibility[j] == 0) {
                continue;
            }
            for (k2 = 0; k2 < 16; k2++) {
                if (i != k2 && j != k2 && team == (other2 = &Zoid[k2])->slot) {
                    other2->target_visibility[j] = 1;
                    (void)other2;
                }
            }
        }
    }

    for (i = 0; i < 16; i++) {
        zoid = &Zoid[i];
        if (zoid->joint == (void *)0) {
            continue;
        }
        if (zoid->target_pending != 0) {
            if (zoid->target_visibility[zoid->target_slot] == 0) {
                zoid->target_pending = 0;
            }
            if (zoid->distances[zoid->target_slot] > zoid->search_range) {
                zoid->target_pending = 0;
            }
        }
        if (zoid->lock_active != 0) {
            point = grdObjGetPt(zoid->lock_obj);
            range = sLenPoint3d((Vec3 *)zoid->position, point);
            zoid->field_1E8C = range;
            zoid->lock_point = point;
            if (range > zoid->search_range) {
                zoid->lock_active = 0;
            }
        }
    }

    for (i = 0; i < 16; i++) {
        zoid = &Zoid[i];
        if (zoid->joint == (void *)0) {
            continue;
        }
        zdColPosY(zoid->position, &polygon);
        if (polygon == 0xFFFF) {
            for (j = 0; j < 3; j++) {
                zoid->position[j] = zoid->previous_position[j];
            }
        }
    }
}
#pragma dont_inline on

#pragma dont_inline off
static inline void HSD_JObjSetScaleX(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 805, "jobj");
    jobj->scale.x = value;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj)) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

static inline void HSD_JObjSetScaleY(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 819, "jobj");
    jobj->scale.y = value;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj)) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

static inline void HSD_JObjSetScaleZ(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 833, "jobj");
    jobj->scale.z = value;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj)) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

s32 zdWp1SliderN(ZoidState *zoid, s32 index, s32 value)
{
    HSD_JObj *jobj;
    s32 joint_index;
    s32 type;
    s32 range;
    f32 min;
    f32 max;
    f32 result;

    if (zoid == 0) {
        return 0;
    }
    if (zoid->slider_positions[index] == value) {
        return 0;
    }
    zoid->slider_positions[index] = value;
    if (zoid->joint == 0) {
        return 0;
    }
    if (zoid->slider_info == 0) {
        return 0;
    }
    joint_index = (s8)((SliderEntry *)zoid->slider_info)[index].joint;
    type = (s8)((SliderEntry *)zoid->slider_info)[index].type;
    if (joint_index == 0) {
        return 0;
    }
    jobj = zoid->spik_joints[joint_index - 1];
    if (jobj == 0) {
        ((SliderEntry *)zoid->slider_info)[index].joint = 0;
        return 0;
    }
    if (index) {
        (void)0;
    }
    range = ((SliderEntry *)zoid->slider_info)[0].range;
    if (range == 0) {
        return 0;
    }
    range = range;
    min = ((SliderEntry *)zoid->slider_info)[index].min;
    max = ((SliderEntry *)zoid->slider_info)[index].max;
    result = min + (max - min) * (f32)value / (f32)range;
    if (type <= 2) {
        result = 2 * (3.1415926 * result) / 360.0;
    }
    switch (type) {
    case 0:
        HSD_JObjSetRotationX(jobj, result);
        break;
    case 1:
        HSD_JObjSetRotationY(jobj, result);
        break;
    case 2:
        HSD_JObjSetRotationZ(jobj, result);
        break;
    case 3:
        HSD_JObjSetScaleX(jobj, result);
        break;
    case 4:
        HSD_JObjSetScaleY(jobj, result);
        break;
    case 5:
        HSD_JObjSetScaleZ(jobj, result);
        break;
    }
    return 0;
}
#pragma dont_inline on

static u32 lit_2041[15] = {
    0x80031DC8, 0x80031DD4, 0x80031DD4, 0x80031DB0, 0x80031DBC, 0x80031D74, 0x80031D74, 0x80031D80,
    0x80031D80, 0x80031D8C, 0x80031D8C, 0x80031D98, 0x80031D98, 0x80031DA4, 0x80031DA4
};
s32 wpTbl[6][7] = {
    {0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1},
    {2, 2, 2, 2, 2, 2, 2},
    {2, 2, 1, 2, 2, 2, 0},
    {1, 1, 1, 2, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0}
};
void zdWeaponActLoop(ZoidState *zoid)
{
    ZoidControlData *control;
    u8 *slot_info;
    s32 next_index;
    s32 want;
    s32 next;
    s32 ret;
    s32 slot_kind;
    s32 anim_num;
    u8 *info;
    s32 i;
    s32 idx;
    s32 cur;
    WeaponMount *mount;
    s32 state;
    HSD_JObj *target;
    s32 type;
    s32 kind;
    s32 end;
    s32 off;
    s32 anim;
    s32 flag_arg;
    s32 mode;

    if (zoid == (void *)0) {
        return;
    }
    if (zoid->joint == (void *)0) {
        return;
    }
    next_index = zoid->weapon_mount + 1;
    info = (u8 *)zoid->slider_info;
    if (zoid->weapon_mount == -1) {
        next_index = -1;
    }
    if (zoid->weapon_mount == 19) {
        next_index = 0;
    }
    slot_info = 0;
    if (next_index != -1) {
        slot_info = (u8 *)(info + 2 + next_index * 16);
    }
    zoid->field_1360 = 0;
    zoid->field_1374 = 0;
    zoid->animation_frame = 0;
    control = (ZoidControlData *)zoid->anim_data;
    if (zoid->weapon_mount != -1) {
        zoid->field_1364 = zdWpSlider(zoid, zoid->weapon_mount);
        type = control->field_0140[zoid->weapon_mount];
        if (type == 2 && zoid->action != 0 && zoid->field_1DB0 < 15) {
            return;
        }
    } else {
        zdWpSlider(zoid, -1);
    }
    if (zoid->health == 0) {
        zoid->selected_weapon_mount = -1;
    }
    if (zoid->requested_action == 27 || zoid->requested_action == 34 || (zoid->action >= 27 && zoid->action <= 33) || (zoid->action >= 34 && zoid->action <= 40)) {
        zoid->super_attack_input = 0;
        if (zoid->selected_weapon_mount == 19) {
            zoid->selected_weapon_mount = -1;
        }
        for (i = 0; i < 11; i++) {
            idx = i;
            if (i == 10) {
                idx = 19;
            }
            zdWeaponWpForceOFF(zoid, &zoid->weapon_mounts[idx]);
            zoid->weapon_mounts[idx].state = 0;
        }
        if (zoid->selected_weapon_mount == -1) {
            return;
        }
        type = control->field_0140[zoid->selected_weapon_mount];
        state = zoid->weapon_mounts[zoid->selected_weapon_mount].state;
        kind = wpTbl[type][state];
        if (type == 2 || kind == 2) {
            zoid->selected_weapon_mount = -1;
            return;
        }
        return;
    }
    if ((zoid->requested_action >= 27 && zoid->requested_action <= 33) || (zoid->action >= 34 && zoid->action <= 40)) {
        slot_kind = zoid->weapon_slots[zoid->weapon_mount].field_04;
        zoid->selected_weapon_mount = -1;
        if (slot_kind == 6) {
            zoid->weapon_mount = -1;
            return;
        }
    }
    if (zoid->weapon_mount == 19 && zoid->selected_weapon_mount == -1) {
        zoid->super_attack_input = 0;
    }
    if (zoid->super_attack_cooldown != 0) {
        zoid->super_attack_cooldown--;
    }
    if (zoid->super_attack_input != 0 && zoid->super_attack_enabled != 0 && zoid->super_attack_cooldown == 0) {
        zoid->selected_weapon_mount = 19;
        zoid->face_lock = 1;
    }
    cur = zoid->weapon_mount;
    want = zoid->selected_weapon_mount;
    if (cur == -1) {
        cur = want;
        zoid->weapon_mount = cur;
        if (cur != -1) {
            mount = &zoid->weapon_mounts[cur];
            mount->state = 0;
        }
    }
    if (cur == -1) {
        zoid->field_1360 = 0;
        zoid->field_1374 = 0;
        return;
    }
    mount = &zoid->weapon_mounts[cur];
    if (cur >= 10) {
        mount->active = 1;
    }
    state = mount->state;
    anim = cur * 5 + 82;
    if (cur == 19) {
        anim = 77;
    }
    type = control->field_0140[cur];
    if (type == 2 || type == 3 || type == 4) {
        if (zoid->jump_phase != 0) {
            if (slot_info == 0) {
                return;
            }
            if ((s8)slot_info[6] != -1) {
                return;
            }
        }
        if (zoid->action == 26) {
            return;
        }
        if (zoid->action == 25) {
            return;
        }
        if (zoid->action == 23) {
            return;
        }
        if (zoid->action == 24) {
            return;
        }
    }
    kind = wpTbl[type][state];
    target = 0;
    target = target;
    info = info;
    zoid->animation_frame = kind;
    if (kind == 2 && state != 0) {
        zoid->field_1360 = 1;
    }
    if (kind == 2) {
        target = zoid->joint->child;
    }
    if (kind == 2) {
        if (zoid->field_1C48 == 0) {
            zoid->field_1C34 = 0;
        }
    } else {
        zoid->field_1360 = 0;
        zoid->field_1374 = 0;
    }
    if (zoid->field_1360 != 0 && zoid->weapon_mount == 19) {
        if (zdCoFlag(zoid, info[0x711])) {
            zoid->ground_turn = 15;
        }
        if (zoid->ground_turn != 0) {
            zoid->ground_turn = 15;
        }
    }
    if (cur != want) {
        if (cur < 10 && mount->active == 0) {
            mount->state = 0;
            zdWeaponFireOFF(zoid);
            zoid->weapon_mount = want;
            return;
        }
        if (target == (void *)0) {
            mount->state = 0;
        } else {
            end = 0;
            if (kind == 0) {
                end = 1;
            }
            if (kind == 2) {
                end = zoid->animation_looped | zoid->animation_stopped;
                zoid->field_1374 = 1;
            }
            if (state != 0) {
                if (state == 3) {
                    if (kind == 2) {
                        flag_arg = info[0x713];
                        if (cur == 19) {
                            flag_arg = info[0x711];
                        }
                        if (zdCoFlag(zoid, flag_arg)) {
                            zoid->ground_turn = 15;
                        }
                        if (zoid->ground_turn != 0) {
                            zoid->ground_turn = 15;
                        }
                    }
                    if (end == 0) {
                        return;
                    }
                }
                if (state == 2 || state == 3 || end != 0) {
                    next = 3;
                    if (state == 4) {
                        next = 4;
                        if (kind == 2) {
                            zdChgNormal(zoid);
                        }
                    } else if (kind == 2) {
                        ZoidSetAnim(zoid, anim + next);
                        zdChgAction(zoid);
                    }
                    if (next == 3) {
                        mount->state = 4;
                    } else {
                        mount->state = 0;
                        state = 0;
                    }
                }
            }
        }
        if (cur == 19 && zoid->mount_has_weapon[19] == 0) {
            off = 0;
            for (i = 0; i < 10; i++) {
                if (zdWeaponWpOFF(zoid, &zoid->weapon_mounts[i])) {
                    off = 1;
                }
            }
            if (off != 0) {
                return;
            }
        }
        if (zdWeaponWpOFF(zoid, mount) != 0) {
            return;
        }
        if (state != 0) {
            return;
        }
        if (cur == 19) {
            if (zoid->ground_turn != 0) {
                zoid->ground_turn = 1;
            }
            zoid->face_lock = 0;
            zoid->requested_action = 0;
        }
        zoid->weapon_mount = want;
        mount->state = 0;
        return;
    }
    zdSearchSight(zoid, zoid->weapon_mount);
    if (cur == 19 && zoid->mount_has_weapon[19] == 0) {
        for (i = 0; i < 10; i++) {
            zdSearchSight(zoid, i);
        }
    }
    if (kind == 2) {
        mode = zoid->current_animation;
        if (mode == 2) {
            mode = 1;
        }
        if (mode >= 77 && mode <= 157) {
            mode = 1;
        }
        if (state == 0) {
            if (mode != 1 || zoid->field_1C90[2] > 0.1 || zoid->field_1C90[0] > 0.1) {
                return;
            }
        }
        zoid->field_1374 = 1;
        if (zoid->requested_action == 13) {
            zoid->requested_action = 0;
        }
        if (zoid->requested_action >= 23 && zoid->requested_action <= 26) {
            zoid->requested_action = 0;
        }
        if (zoid->requested_action == 2) {
            zoid->requested_action = 0;
        }
    }
    ret = zdWeaponWpON(zoid, mount);
    if (cur == 19 && zoid->mount_has_weapon[19] == 0) {
        for (i = 0; i < 10; i++) {
            zdWeaponWpON(zoid, &zoid->weapon_mounts[i]);
        }
    }
    if (target == 0 && mount->state < 2) {
        mount->state = 2;
        return;
    }
    if (state == 2) {
        if (type == 3 || type == 4) {
            s32 off2;

            off2 = 0;
            if (zoid->jump_phase != 0) {
                off2 = 1;
            }
            if (zoid->action == 26) {
                off2 = 1;
            }
            if (zoid->action == 25) {
                off2 = 1;
            }
            if (zoid->action == 23) {
                off2 = 1;
            }
            if (zoid->action == 24) {
                off2 = 1;
            }
            if (off2 != 0) {
                return;
            }
        }
        if (cur == 19) {
            if (zoid->super_attack_input == 0) {
                if (ret != 0) {
                    return;
                }
                zoid->super_attack_cooldown = 600;
                zdWeaponFire1(zoid);
                mount->state = 3;
                zdVoiceScG(zoid, 6);
                return;
            }
            zdWeaponFireOFF(zoid);
        }
    }
    if (state == 3 || state == 5) {
        if (target != 0) {
            anim_num = zdGetAnimNum(zoid, target);
            if (kind == 2) {
                anim_num = zoid->current_animation;
            }
            if (anim_num != anim + 2) {
                if (kind == 2) {
                    ZoidSetAnim(zoid, anim + 2);
                }
                return;
            }
        }
        if (state == 3) {
            if (cur == 19) {
                zoid->selected_weapon_mount = -1;
            }
            if (kind == 2) {
                flag_arg = info[0x713];
                if (cur == 19) {
                    flag_arg = info[0x711];
                }
                if (zdCoFlag(zoid, flag_arg)) {
                    zoid->ground_turn = 15;
                }
            }
            if (zoid->ai != 0 && *(s32 *)((u8 *)zoid->ai + 0x40) != 0 && state == 3 && zoid->animation_looped != 0) {
                mount->state = 4;
            }
            return;
        }
        end = 0;
        if (kind == 2) {
            end = zoid->animation_looped;
        }
        if (end != 0) {
            mount->state = 6;
        }
    }
    if (mount->state == 6) {
        if (kind == 2) {
            ZoidSetAnim(zoid, anim + 1);
        }
        mount->state = 2;
        state = 2;
    }
    kind = wpTbl[type][state];
    if (state < 2 || state == 4) {
        end = 0;
        if (kind == 2) {
            end = zoid->animation_looped;
        }
        if (end != 0 || state == 0) {
            if (kind == 2) {
                ZoidSetAnim(zoid, anim + state);
            }
            mount->state++;
            if (state == 0) {
                mount->state = 1;
            }
            if (state == 1) {
                mount->state = 2;
            }
        }
        return;
    }
    mount->state = 2;
}

static const char lit_6660[19] = "debug/mtp_grid.dat";
#pragma push
#pragma opt_common_subs off
s32 zdSetTex(u8 *data, u8 *texture, u32 size)
{
    PicHeader *pic;
    PicHeader *hdr;
    s32 colors;
    u8 *image;
    u32 tsize;

    pic = skipPicData(data);
    hdr = pic;
    if (hdr->format != 10) {
        colors = 256;
    } else {
        colors = hdr->colors;
        if (colors > 1024) {
            putErr("tex-size  large      >1024");
            return 0;
        }
    }
    image = (u8 *)pic + 744 + (colors - 256) * 2;
    tsize = calc_doltexture_size(hdr->format, hdr->width, hdr->height);
    tsize = tsize;
    if (tsize != size) {
        putErr("tex size \201\202 file-tex-size");
        OSReport("tex size=%d(%d,%d,[%d])    != tsize=%d \n", tsize, hdr->width, hdr->height, hdr->format, size);
        if (hdr->format != 14) {
            putErr("tex size \201\202 file-tex-size    file-tex not CMPR");
            OSReport("file -tex   not CMPR\n");
        }
        return 0;
    }
    OSReport("headsize=%d    size = %d \n", 744, tsize);
    MemCpy(image, texture, tsize);
    DCFlushRange(image, tsize);
    DCFlushRange(texture, tsize);
    GXInvalidateTexAll();
    return 1;
}
#pragma pop

s32 ZoidColor(ZoidState *zoid, s32 color, s32 mode)
{
    char path[256];
    ColorImageDesc *desc;
    u8 *image;
    ColorTObj *tobj;
    u8 *data;
    HSD_JObj *joint;
    u32 tsize;

    if (color < 0)
        return 0;
    if (zoid == (void *)0)
        return 0;
    if (zoid->joint == (void *)0)
        return 0;
    if (zoid->field_1E9A == color)
        return 1;
    joint = *(HSD_JObj **)zoid->body_coobj;
    if (joint == (void *)0) {
        putErr("zoidColor : Zoid.coBody not found.");
        return 0;
    }
    tobj = searchTObj(joint);
    if (tobj == (void *)0) {
        putErr("zoidColor : tobj not found.");
        return 0;
    }
    desc = tobj->imagedesc;
    if (desc == (void *)0) {
        putErr("zoidColor : imagedesc(tobj) not found.");
        return 0;
    }
    data = data;
    data = data;
    tsize = calc_doltexture_size(desc->format, desc->width, desc->height);
    image = desc->image;
    sprintf(path, "zoid/all_tex/%s_%c.tpl", zoid, color + 'A');
    if ((data = sReadFileU(path, mode))) {
        if (SetTex2(data, image, tsize) != 0) {
            zoid->field_1E9A = color;
            free(data);
            OSReport("tex2\n");
            return 1;
        }
    } else {
        sprintf(path, "zoid/all_tex/%s_%c.pic", zoid, color + 'A');
        if ((data = sReadFileU(path, mode)) && zdSetTex(data, image, tsize) != 0) {
            zoid->field_1E9A = color;
            free(data);
            OSReport("tex\n");
            return 1;
        }
    }
    if (data == (void *)0) {
        putErr("zoidColor : file not found.");
        return 0;
    }
    OSReport("text set. error   zd-tex (%d,%d,[%d])\n", desc->width, desc->height, desc->format);
    if (desc->format != 14) {
        putErr("zoidColor : set Tex  error    zoid-tex not CMPR");
        OSReport("zoid -tex   not CMPR\n");
    }
    free(data);
    return 0;
}

static u32 prmTblZ[4] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static const char lit_6823[17] = "set ambient[%s] ";
static const u32 lit_7171[252] = {
    0x43BB8000, 0xC3BB8000, 0x00000000, 0x43BB8000, 0x433B0000, 0x00000000, 0x433B0000, 0xC33B0000,
    0x00000000, 0x00000000, 0x433B0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x433B0000, 0xC3BB8000, 0x00000000, 0x433B0000,
    0xC46A4000, 0x00000000, 0x00000000, 0xC3BB8000, 0x00000000, 0x00000000, 0xC46A4000, 0x00000000,
    0x433B0000, 0x43BB8000, 0x00000000, 0x440C8000, 0x440C8000, 0x00000000, 0x433B0000, 0x440C8000,
    0x00000000, 0x440C8000, 0x443B8000, 0x00000000, 0x43BB8000, 0xC3BB8000, 0x00000000, 0x43BB8000,
    0x433B0000, 0x00000000, 0x433B0000, 0xC33B0000, 0x00000000, 0x00000000, 0x433B0000, 0x00000000,
    0xC3BB8000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xC3BB8000, 0x433B0000,
    0x00000000, 0x00000000, 0x433B0000, 0x00000000, 0xC3BB8000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0xC3BB8000, 0x433B0000, 0x00000000, 0x00000000, 0x433B0000, 0x00000000,
    0xC33B0000, 0xC33B0000, 0x00000000, 0x433B0000, 0x433B0000, 0x00000000, 0x433B0000, 0xC33B0000,
    0x00000000, 0xC33B0000, 0x433B0000, 0x00000000, 0xC33B0000, 0xC33B0000, 0x00000000, 0x433B0000,
    0x433B0000, 0x00000000, 0x433B0000, 0xC33B0000, 0x00000000, 0xC33B0000, 0x433B0000, 0x00000000,
    0xC3BB8000, 0x00000000, 0x00000000, 0xC3BB8000, 0x43BB8000, 0x00000000, 0xC33B0000, 0x00000000,
    0x00000000, 0xC33B0000, 0x43BB8000, 0x00000000, 0xC3BB8000, 0x00000000, 0x00000000, 0xC3BB8000,
    0x43BB8000, 0x00000000, 0xC33B0000, 0x00000000, 0x00000000, 0xC33B0000, 0x43BB8000, 0x00000000,
    0xC33B0000, 0xC33B0000, 0x00000000, 0x433B0000, 0x433B0000, 0x00000000, 0x433B0000, 0xC33B0000,
    0x00000000, 0xC33B0000, 0x433B0000, 0x00000000, 0xC33B0000, 0xC33B0000, 0x00000000, 0x433B0000,
    0x433B0000, 0x00000000, 0x433B0000, 0xC33B0000, 0x00000000, 0xC33B0000, 0x433B0000, 0x00000000,
    0xC4048000, 0x43FA0000, 0x00000000, 0x443B8000, 0xC4020000, 0x00000000, 0x43340000, 0xC3EB0000,
    0x00000000, 0x41200000, 0xC3E60000, 0x00000000, 0xC4048000, 0x43FA0000, 0x00000000, 0x443B8000,
    0xC4020000, 0x00000000, 0x43340000, 0xC3EB0000, 0x00000000, 0x41200000, 0xC3E60000, 0x00000000,
    0xC4048000, 0x444A8000, 0x00000000, 0x44610000, 0xC4020000, 0x00000000, 0x43340000, 0xC3EB0000,
    0x00000000, 0x41200000, 0xC3E60000, 0x00000000, 0xC33B0000, 0xC33B0000, 0x00000000, 0x433B0000,
    0x433B0000, 0x00000000, 0x433B0000, 0xC33B0000, 0x00000000, 0xC33B0000, 0x433B0000, 0x00000000,
    0xC33B0000, 0xC33B0000, 0x00000000, 0x433B0000, 0x433B0000, 0x00000000, 0x433B0000, 0xC33B0000,
    0x00000000, 0xC33B0000, 0x433B0000, 0x00000000, 0xC33B0000, 0xC33B0000, 0x00000000, 0x433B0000,
    0x433B0000, 0x00000000, 0x433B0000, 0xC33B0000, 0x00000000, 0xC33B0000, 0x433B0000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000
};
void zdLimitHigh(ZoidState *zoid)
{
    s32 action;
    if (zoid != 0 && zoid->joint != 0) {
        void *control = zoid->anim_data;
        if (control != 0) {
            action = zoid->action;
            switch (action) {
            case 0x22: case 0x23: case 0x24: case 0x25: case 0x26:
            case 0x27: case 0x28: case 0x29: case 0x2A: case 0x2B:
            case 0x31: case 0x32: case 0x33:
                break;
            default:
                if (zoid->field_0170 == 0) {
                    limitHigh2(zoid->position);
                } else {
                    limitHigh(zoid->position);
                    limitHighAng(zoid);
                }
                break;
            }
        }
    }
}

}
