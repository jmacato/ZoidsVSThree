#pragma readonly_strings on
#include "zoid3.h"
#include "game_camera.h"
#include "model_archive.h"
#include "ground_collision.h"

#define NULL 0

typedef struct CameraState3 {
    u8 reserved_000[0x1C4];
    ZoidState *zoid;
} CameraState3;

extern ModelArchive *dspWarn;
extern s32 pause;
extern s32 gameStartF;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);
extern void sMakeMatrix(HSD_JObj *joint);
extern void HiddenPartsAll(HSD_JObj *joint, s32 hidden);
extern s32 jobjAnim(HSD_JObj *joint);
extern void jobjDispAll(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *expr);

static inline f32 HSD_JObjGetScaleY(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 911, "jobj");
    return jobj->scale.y;
}

void sDispArea(CameraState3 *camera, HSD_JObj *joint)
{
    register s32 GetChild_first;

    GroundMask *mask;

    u16 polygon;
    s32 material;
    register HSD_JObj *area;
    HSD_JObj *GetChild_joint;
    ZoidState *zoid;
    HSD_JObj *source;

    if (camera == (void *)0)
        return;
    zoid = camera->zoid;
    if (zoid == (void *)0)
        return;
    if (zoid->joint == (void *)0)
        return;
    {
        GetChild_joint = joint;
        {
            GetChild_first = 0;
            source = GetChild(GetChild_joint, GetChild_first, 11, -1, -1, -1);
        }
    }
    if (dspWarn == (void *)0)
        return;
    if (gameStartF != 0)
        return;
    area = dspWarn->models[6];
    jobjCopyPos(source, area);
    sMakeMatrix(area);
    HiddenPartsAll(GetChild(area, 0, 1, -1, -1, -1), 1);
    HiddenPartsAll(GetChild(area, 0, 2, -1, -1, -1), 1);
    HiddenPartsAll(GetChild(area, 0, 0, -1, -1, -1), 0);
    polygon = zoid->ground_polygon;
    if (polygon == GROUND_POLYGON_NONE)
        return;
    material = grdcPolygon[polygon].material;
    mask = &grdcMat[material];
    if ((mask->bits[0] & 6) == 0)
        return;
    if (pause == 0 && jobjAnim(area) != 0)
        SetAnimArc2(dspWarn, 6, 1);
    sMakeMatrix(area);
    if (0.0f != HSD_JObjGetScaleY(area))
        jobjDispAll(area);
}
