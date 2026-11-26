#include "zoid3.h"

typedef struct CameraState3 {
    s32 mode;
    s32 half;
    struct HSD_LObj *lights;
    struct HSD_Shadow *shadow;
    u8 reserved_010[0x1C];
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
    Vec3 eye;
    Vec3 interest;
    Vec3 saved_eye;
    Vec3 saved_interest;
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

extern s32 searchCamBetterOnAtk(CameraState3 *camera, ZoidState *zoid, s32 slot);
extern s32 searchCamBetterOnAtkObj(CameraState3 *camera, ZoidState *zoid, s32 slot);

extern s32 searchCamBetterOnAtk(CameraState3 *camera, ZoidState *zoid, s32 slot);
extern s32 searchCamBetterOnAtkObj(CameraState3 *camera, ZoidState *zoid, s32 slot);

void searchCamBetterOn(CameraState3 *camera)
{
    s32 dead;
    s32 slot;
    s32 i;
    s32 j;
    ZoidState *zoid;

    i = 20;
    dead = 0;
    j = i;
    dead = 0;
    slot = -1000;
    zoid = camera->zoid;
    if (zoid != 0) {
        if (zoid->target_pending != 0) {
            slot = zoid->target_slot;
            j = searchCamBetterOnAtk(camera, zoid, slot);
        }
        if (zoid->lock_active != 0) {
            slot = zoid->lock_obj;
            j = searchCamBetterOnAtkObj(camera, zoid, slot);
        }
    }
    if (j != 20)
        i = j;
    if (i == 20) {
        for (i = 0, j = 10; i < 20; i++, j++) {
            if (j >= 20)
                j = 0;
            if (camera->mount_times[j] >= 60 && !camera->mount_blocked[j] && !camera->mount_hidden[j])
                break;
        }
    }
    if (i == 20) {
        for (i = 0, j = 10; i < 20; i++, j++) {
            if (j >= 20)
                j = 0;
            if (camera->mount_times[j] >= 60 && !camera->mount_blocked[j])
                break;
        }
    }
    if (i == 20) {
        for (i = 0, j = 10; i < 20; i++, j++) {
            if (j >= 20)
                j = 0;
            if (camera->mount_times[j] >= 60 && !camera->mount_hidden[j])
                break;
        }
    }
    if (i == 20) {
        for (i = 0, j = 10; i < 20; i++, j++) {
            if (j >= 20)
                j = 0;
            if (!camera->mount_blocked[j])
                break;
        }
    }
    if (i == 20)
        j = 10;
    if (camera->mount_index != j) {
        camera->mount_index = j;
        camera->field_1E4 = 0;
        camera->mount_timer = 0;
        camera->focus_distance = 45.0F;
        if (slot != -1) {
            if (camera->zoid_distance[slot] > 200.0F)
                camera->focus_distance = 10.0F;
        }
        camera->field_1BC = 60;
    }
}
