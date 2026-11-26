#include "types.h"
#include "cobj.h"

typedef struct CameraState3 {
    u8 pad_000[0x214];
    f32 eye[3];
    f32 interest[3];
    u8 pad_22C[0x244 - 0x22C];
    HSD_CObj *cobj;
} CameraState3;

typedef struct WinEntry {
    s32 index;
    s32 field_04;
    s32 radius;
    s32 height;
} WinEntry;

extern u32 vsyncN;
extern void angLimit(f32 *value);
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern f32 HSD_CObjGetFov(HSD_CObj *cobj);
extern void sCameraCalc(CameraState3 *camera);

void camOnWin00(CameraState3 *camera, u8 *zoid)
{
    s32 idx;
    u8 *joint;
    WinEntry *table;
    WinEntry *entry;
    void *table2;
    s32 height;
    s32 index;
    s32 radius;
    f32 (*m)[4];
    f32 angle;
    f32 sine_angle;
    f32 cosine_angle;
    s32 i;

    idx = 0;
    if (camera != 0 && camera->cobj != 0 && zoid != 0 && *(void **)(zoid + 0x40) != 0
        && (table = *(WinEntry **)(zoid + 0x2090), table != 0)
        && (table2 = *(void **)(zoid + 0x2094), table2 != 0)) {
        entry = &table[idx];
        index = entry->index;
        radius = entry->radius;
        height = entry->height - 30;
        if (index == -1)
            joint = *(u8 **)(zoid + 0x1ACC);
        else
            joint = *(u8 **)(zoid + 0x18D0 + index * 12);
        if (joint == (void *)0)
            joint = *(u8 **)(zoid + 0x40);
        m = (f32 (*)[4])(joint + 0x44);
        angle = (f32)(f64) * (f32 *)(zoid + 0x1C7C);
        angle = angle + 2.0 * (3.1415926 * (f32)(360.0 * vsyncN / 300.0)) / 360.0;
        angLimit(&angle);
        for (i = 0; i < 3; i++) {
            camera->eye[i] = m[i][3];
            camera->interest[i] = m[i][3];
        }
        sine_angle = angle;
        camera->eye[0] += radius * sinf(sine_angle);
        cosine_angle = angle;
        camera->eye[2] += radius * cosf(cosine_angle);
        camera->eye[1] += height;
        if (60.0f != HSD_CObjGetFov(camera->cobj))
            HSD_CObjSetFov(camera->cobj, 60.0f);
        HSD_CObjSetInterest(camera->cobj, (Vec3 *)camera->interest);
        HSD_CObjSetEyePosition(camera->cobj, (Vec3 *)camera->eye);
        sCameraCalc(camera);
            }
}
