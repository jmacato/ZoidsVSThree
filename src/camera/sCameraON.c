#include "zoid3.h"
#include "ground_collision.h"

typedef struct CameraState3 {
    s32 mode;
    s32 half;
    struct HSD_LObj *lights;
    struct HSD_Shadow *shadow;
    f32 focus_heading[3];
    u8 reserved_01C[0x10];
    f32 focus_distance;
    s32 mount_index;
    s32 mount_timer;
    u8 reserved_038[0x14];
    s8 mount_blocked[20];
    s8 mount_hidden[20];
    Vec3 mount_positions[20];
    s32 mount_times[20];
    u8 reserved_1B4[0x8];
    s32 field_1BC;
    struct HSD_JObj *field_170;
    struct ZoidState *zoid;
    s32 target_index;
    u8 reserved_1CC[0x18];
    s32 field_1E4;
    u8 reserved_1E8[0x8];
    Vec3 relative_origin;
    Vec3 focus;
    Vec3 field_208;
    f32 eye[3];
    f32 interest[3];
    f32 saved_eye[3];
    f32 saved_interest[3];
    struct HSD_CObj *cobj;
    Vec3 direction;
    f32 planar[2];
    f32 planar_length;
    f32 yaw;
    f32 projection[7];
    f32 viewport[6];
    f32 view[3][4];
    f32 inverse_view[3][4];
    u8 reserved_2F8[0x4];
    f32 fov;
    struct HSD_JObj *field_300;
    f32 zoid_distance[16];
    u8 reserved_344[0x240];
    s32 range_index;
    s32 target_marker_count;
    s32 range_timer;
} CameraState3;

extern void camSameTime(CameraState3 *camera);
extern void camInMine(CameraState3 *camera, ZoidState *zoid);
extern void camInEnemy(CameraState3 *camera, ZoidState *zoid);
extern void searchCamBetterOn(CameraState3 *camera);
extern void searchCamBetterOff(CameraState3 *camera);
extern void setCamTgtLockON(CameraState3 *camera);
extern void setCamTgtLockOFF(CameraState3 *camera);
extern void sCameraCalcET(CameraState3 *camera);
extern void angLimit(f32 *angle);
extern void camPara(CameraState3 *camera);
extern void camLimit(CameraState3 *camera);
extern s32 sCamBallOut(CameraState3 *camera, f32 radius);
extern s32 linierCamLimitXZ(CameraState3 *camera, f32 limit);
extern void linierCamXZ(CameraState3 *camera, s32 mode);
extern void camCockpit(CameraState3 *camera, ZoidState *zoid);
extern f32 HSD_CObjGetFov(struct HSD_CObj *cobj);
extern void HSD_CObjSetFov(struct HSD_CObj *cobj, f32 fov);
extern void HSD_CObjSetInterest(struct HSD_CObj *cobj, Vec3 *interest);
extern void HSD_CObjSetEyePosition(struct HSD_CObj *cobj, Vec3 *position);
extern void sCameraCalc(CameraState3 *camera);
extern s32 GameMode[];

void sCameraON(CameraState3 *camera)
{
    s32 linierCamXZ_mode;

    s32 flag;
    s32 i;
    s32 special;
    void *table;
    ZoidState *zoid;
    s32 pad1;
    u8 *entry;
    s32 pad2;
    s32 mount;
    GroundMask mask = {{0, 255, 0, 0}};

    if (camera != (void *)0 && camera->cobj != (void *)0 && (zoid = camera->zoid, zoid != (void *)0)) {
        table = zoid->field_2090;
        if (table != 0)
            entry = (u8 *)table + camera->mount_index * 16;
        else
            entry = 0;
        flag = 0;
        special = 0;
        if ((GameMode[1] == 2 || GameMode[1] == 3) && GameMode[2] == 1)
            special = 1;
        for (i = 0; i < 20; i++) {
            camera->mount_times[i]++;
            if (camera->mount_times[i] > 36000)
                camera->mount_times[i] = 36000;
        }
        camSameTime(camera);
        camInMine(camera, zoid);
        camInEnemy(camera, zoid);
        camera->mount_timer++;
        mount = camera->mount_index;
        if (mount == 20)
            mount = 0;
        if (zoid->target_pending != 0) {
            if (camera->mount_blocked[mount] != 0 || camera->mount_hidden[mount] != 0)
                flag = 1;
        } else {
            if (camera->mount_blocked[mount] != 0)
                flag = 1;
        }
        if (camera->mount_timer > 120)
            flag = 1;
        if (camera->mount_timer > 60 && entry != 0 && *(s32 *)(entry + 8) <= 5)
            flag = 1;
        if (camera->mount_timer > 60 && zoid->target_pending != 0 && camera->mount_index < 10)
            flag = 1;
        if (special != 0)
            flag = 0;
        if (flag != 0) {
            if (zoid->target_pending != 0)
                searchCamBetterOn(camera);
            else
                searchCamBetterOff(camera);
        }
        if (special != 0)
            camera->mount_index = 13;
        if (zoid->target_pending != 0) {
            setCamTgtLockON(camera);
            sCameraCalcET(camera);
        } else if (zoid->lock_active != 0) {
            setCamTgtLockON(camera);
            sCameraCalcET(camera);
        } else {
            setCamTgtLockOFF(camera);
        }
        angLimit(camera->focus_heading);
        camPara(camera);
        camLimit(camera);
        if (camera->field_1BC != 0)
            camera->field_1BC--;
        pad1 = 3;
        pad2 = 3;
        sCamBallOut(camera, 10.0f);
        if (linierCamLimitXZ(camera, 5.0f) != 0)
            camera->field_1BC = 180;
        if (zoid->current_animation == 5)
            camera->field_1BC = 180;
        if (zoid->current_animation == 8)
            camera->field_1BC = 180;
        if (camera->field_1BC != 0) {
            linierCamXZ_mode = 1;
            linierCamXZ(camera, linierCamXZ_mode);
        }
        if (mount == 20)
            camCockpit(camera, camera->zoid);
        if (60.0f != HSD_CObjGetFov(camera->cobj))
            HSD_CObjSetFov(camera->cobj, 60.0f);
        HSD_CObjSetInterest(camera->cobj, (Vec3 *)camera->interest);
        HSD_CObjSetEyePosition(camera->cobj, (Vec3 *)camera->eye);
        sCameraCalc(camera);
        for (i = 0; i < 3; i++) {
            camera->saved_eye[i] = camera->eye[i];
            camera->saved_interest[i] = camera->interest[i];
        }
    }
}
