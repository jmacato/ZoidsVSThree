#pragma readonly_strings on
#include "jobj.h"
#include "model_archive.h"
#include "video.h"
#include "fog.h"
#include "gx_pixel.h"
#include "game_mode.h"

typedef struct Vec3F {
    f32 x;
    f32 y;
    f32 z;
} Vec3F;

typedef struct CameraState3 {
    u8 reserved_00[0x08];
    void *lights;
    struct HSD_Shadow *shadow;
    u8 reserved_10[0x1F0 - 0x10];
    Vec3F relative_origin;
    u8 reserved_1FC[0x244 - 0x1FC];
    struct HSD_CObj *cobj;
} CameraState3;

extern CameraState3 *camTmp;
extern ModelArchive *Sky;
extern s32 nowShadow;
extern HSD_Fog *fogG;
extern s32 normLineDEBUG;
extern void sCameraLenZoid(CameraState3 *camera);
extern void sCameraMatrix(CameraState3 *camera);
extern void HSD_SetZSortMode(s32 a, s32 b);
extern void HSD_ShadowSetActive(struct HSD_Shadow *shadow, s32 active);
extern s32 HSD_CObjSetCurrent(struct HSD_CObj *cobj);
extern void HSD_CObjEndCurrent(void);
extern void HSD_LObjSetCurrentAll(void *lobj);
extern void HSD_LObjSetupInit(struct HSD_CObj *cobj);
extern void HSD_LObjDeleteCurrentAll(void *lobj);
extern void HSD_FogSet(HSD_Fog *fog);
extern void sMissileLight(void);
extern void sEffectLight(void);
extern void grdDisp(void);
extern void sdZoidAll(void);
extern void ZoidTransMode(void);
extern void ZoidAllDisp3(void);
extern void ZoidAllDisp(void);
extern void grdObjDispOpa(void);
extern void psDispParticles(s32 mask, s32 pass);
extern void sLsrDisp(void);
extern void grdDispXLU(void);
extern void grdObjDispXLU(void);
extern void ZoidAllDispXLU(void);
extern void ZoidAllDBG(void);
extern void sWeaponDispAll(void);
extern void sMissileDisp(void);
extern void sEffectDispAll(void);
extern void sDisp(CameraState3 *camera);
extern void putErrInt(void);
extern void putvNow(void);
extern void sPutFontAllN(void);
extern void dummyFunc(const char *tag);

#pragma auto_inline off
static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & 0x00800000) && (jobj->flags & 0x40);
}
#pragma auto_inline on

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

void draw1(s32 first_camera)
{
    s32 flag;

    if (camTmp->cobj == (void *)0) {
        return;
    }
    sCameraLenZoid(camTmp);
    HSD_SetZSortMode(1, 1);
    if (nowShadow == 0 && camTmp->shadow != 0) {
        HSD_ShadowSetActive(camTmp->shadow, 1);
    }
    if (fogG) {
        HSD_FogSet(fogG);
    }
    if (fogG) {
        volatile s32 tmp = *(s32 *)((u8 *)fogG + 0x18);
        *(s32 *)((u8 *)&HSD_VIData + 0x48) = tmp;
    }
    HSD_StartRender(first_camera ? 3 : 0);
    if (HSD_CObjSetCurrent(camTmp->cobj)) {
        flag = 1;
        HSD_LObjSetCurrentAll(camTmp->lights);
        HSD_LObjSetupInit(camTmp->cobj);
        sCameraMatrix(camTmp);
        HSD_FogSet((void *)0);
        HSD_JObjSetTranslateX(Sky->models[0], camTmp->relative_origin.x);
        HSD_JObjSetTranslateY(Sky->models[0], camTmp->relative_origin.y);
        HSD_JObjSetTranslateZ(Sky->models[0], camTmp->relative_origin.z);
        HSD_JObjDispAll(Sky->models[0], 0, HSD_TRSP_ALL, 0);
        if (fogG) {
            HSD_FogSet(fogG);
        }
        if (flag != 0 && GameMode.win == 0) {
            HSD_LObjDeleteCurrentAll(camTmp->lights);
            HSD_LObjSetCurrentAll(camTmp->lights);
            sMissileLight();
            sEffectLight();
            HSD_LObjSetupInit(camTmp->cobj);
        }
        grdDisp();
        sdZoidAll();
        ZoidTransMode();
        if (fogG) {
            HSD_FogSet((void *)0);
        }
        ZoidAllDisp3();
        if (fogG) {
            HSD_FogSet(fogG);
        }
        ZoidAllDisp();
        grdObjDispOpa();
        psDispParticles(0xFFFF, 0);
        if (fogG) {
            HSD_FogSet((void *)0);
        }
        if (fogG) {
            HSD_FogSet(fogG);
        }
        sLsrDisp();
        if (fogG) {
            HSD_FogSet((void *)0);
        }
        if (fogG) {
            HSD_FogSet(fogG);
        }
        if (fogG) {
            HSD_FogSet(fogG);
        }
        grdDispXLU();
        ZoidAllDispXLU();
        grdObjDispXLU();
        if (fogG) {
            HSD_FogSet((void *)0);
        }
        if (fogG) {
            HSD_FogSet((void *)0);
        }
        if (normLineDEBUG) {
            ZoidAllDBG();
        }
        if (fogG) {
            HSD_FogSet(fogG);
        }
        HSD_CObjEndCurrent();
        if (fogG) {
            HSD_FogSet((void *)0);
        }
        HSD_LObjDeleteCurrentAll(camTmp->lights);
        if (fogG) {
            HSD_FogSet((void *)0);
        }
    }
    HSD_SetZSortMode(0, 0);
    if (fogG) {
        HSD_FogSet((void *)0);
    }
    if (HSD_CObjSetCurrent(camTmp->cobj)) {
        HSD_LObjSetCurrentAll(camTmp->lights);
        HSD_LObjSetupInit(camTmp->cobj);
        if (fogG) {
            HSD_FogSet(fogG);
        }
        sWeaponDispAll();
        if (fogG) {
            HSD_FogSet((void *)0);
        }
        HSD_CObjEndCurrent();
        HSD_LObjDeleteCurrentAll(camTmp->lights);
    }
    HSD_SetZSortMode(1, 1);
    if (fogG) {
        HSD_FogSet((void *)0);
    }
    if (HSD_CObjSetCurrent(camTmp->cobj)) {
        HSD_LObjSetCurrentAll(camTmp->lights);
        HSD_LObjSetupInit(camTmp->cobj);
        if (fogG) {
            HSD_FogSet((void *)0);
        }
        sMissileDisp();
        sEffectDispAll();
        psDispParticles(0xFFFF, 1);
        psDispParticles(0xFFFF, 2);
        HSD_CObjEndCurrent();
    }
    if (fogG) {
        HSD_FogSet((void *)0);
    }
    HSD_EndRender();
    dummyFunc("c");
    HSD_StateInvalidate(-1);
    HSD_StartRender(first_camera ? 3 : 0);
    if (fogG) {
        HSD_FogSet((void *)0);
    }
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
    sDisp(camTmp);
    HSD_StateInvalidate(-1);
    if (fogG) {
        HSD_FogSet((void *)0);
    }
    dummyFunc("d");
    putErrInt();
    putvNow();
    sPutFontAllN();
    HSD_StateInvalidate(-1);
    HSD_EndRender();
    if (nowShadow == 0 && camTmp->shadow != 0) {
        HSD_ShadowSetActive(camTmp->shadow, 0);
    }
    dummyFunc("9");
}
