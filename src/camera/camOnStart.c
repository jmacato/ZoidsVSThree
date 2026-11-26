#include "zoid3.h"
#include "cobj.h"
#include "ground_collision.h"

typedef struct CameraState3 {
    u8 pad_000[0x1C4];
    ZoidState *zoid;
    u8 pad_1C8[0x214 - 0x1C8];
    f32 eye[3];
    f32 interest[3];
    u8 pad_22C[0x244 - 0x22C];
    HSD_CObj *cobj;
} CameraState3;

typedef struct StartEntry {
    s32 index;
    s32 field_04;
    s32 radius;
    s32 height;
} StartEntry;

extern s32 gameStartTm;
extern void angLimit(f32 *value);
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern f32 HSD_CObjGetFov(HSD_CObj *cobj);
extern void sCameraCalc(CameraState3 *camera);

static inline GroundMask startMaskA(void)
{
    return (GroundMask){{3, 0, 0, 0}};
}

static inline GroundMask startMaskB(void)
{
    return (GroundMask){{0, 255, 0, 0}};
}

static inline f32 startPt(f32 *eye, f32 *interest)
{
    GroundMask maskB;
    maskB = startMaskB();
    return sColPt((Vec3 *)eye, (Vec3 *)interest, &maskB);
}

void camOnStart(CameraState3 *camera)
{
    s32 idx;
    s32 i;
    s32 moved;
    HSD_JObj *joint;
    StartEntry *entry;
    StartEntry *table;
    void *data;
    s32 index;
    s32 radius;
    s32 height;
    f32 (*m)[4];
    f32 angle;
    f32 floor_y;
    GroundMask maskA;
    f32 sine_angle;
    f32 cosine_angle;
    ZoidState *zoid;

    idx = 0;
    if (camera != 0 && camera->cobj != 0 && (zoid = camera->zoid, zoid != 0) && zoid->joint != 0
        && (data = zoid->anim_data, data != 0) && (table = zoid->field_2090, table != 0)) {
        if (zoid->action != 50) {
            zoid->requested_action = 50;
            zoid->action = 50;
        }
        entry = &table[idx];
        index = entry->index;
        radius = entry->radius;
        height = entry->height - 30;
        if (index != -1)
            joint = zoid->weapon_slots[index].joint;
        else
            joint = zoid->field_1ACC;
        if (joint == (void *)0)
            joint = zoid->joint;
        m = (f32 (*)[4])((u8 *)joint + 0x44);
        angle = 3.1415926 + zoid->heading;
        angle += 2.0 * (3.1415926 * (f32)(360.0 * gameStartTm / 300.0)) / 360.0;
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
        maskA = startMaskA();
        floor_y = 5.0f + sColPosAndY((Vec3 *)camera->eye, 0, &maskA);
        if (camera->eye[1] < floor_y)
            camera->eye[1] = floor_y;
        moved = 0;
        i = 0;
        while (10000.0f != startPt(camera->eye, camera->interest)) {
            camera->eye[1] += 1.0f;
            i++;
            moved = 1;
            if (i > 10)
                break;
        }
        if (moved != 0)
            camera->eye[1] += 0.2;
        if (60.0f != HSD_CObjGetFov(camera->cobj))
            HSD_CObjSetFov(camera->cobj, 60.0f);
        HSD_CObjSetInterest(camera->cobj, (Vec3 *)camera->interest);
        HSD_CObjSetEyePosition(camera->cobj, (Vec3 *)camera->eye);
        sCameraCalc(camera);
            }
}
