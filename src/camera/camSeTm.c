#include "game_mode.h"
#include "types.h"

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

extern void sCameraRela(CameraState3 *camera, Vec3 *position, Vec3 *relative);
extern s32 SE_TableList[];
extern s32 IntSeSetTm(s16 id, f32 distance, f32 x, f32 z, s32 volume);

s32 camSeTm(CameraState3 *camera, s16 sound, Vec3 *point, s32 volume)
{
    Vec3 relative;
    f32 distance;
    s16 id;

    if (sound <= 0)
        return 0;
    if (GameMode.game_type != 2) {
        sCameraRela(camera, point, &relative);
        distance = relative.x * relative.x + relative.z * relative.z;
        if (distance > 90000.0F)
            return 0;
    } else {
        relative.x = 0.0F;
        relative.z = 100.0F;
        distance = 100.0F;
    }
    id = SE_TableList[sound];
    if (id < 0)
        return 0;
    return IntSeSetTm(id, distance, relative.x, -relative.z, volume);
}
