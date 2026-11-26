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

s32 linierCamLimitXZ(CameraState3 *camera, f32 radius)
{
    Vec3 *interest = &camera->interest;
    Vec3 *focus = &camera->focus;
    Vec3 *eye = &camera->eye;
    Vec3 *origin = &camera->relative_origin;
    f32 limit = radius * radius;
    f32 dist;
    f32 x, y, z;
    z = origin->z - eye->z;
    x = origin->x - eye->x;
    y = origin->y - eye->y;
    dist = x * x + z * z + y * y;
    if (dist > limit)
        return 1;
    z = focus->z - interest->z;
    x = focus->x - interest->x;
    y = focus->y - interest->y;
    dist = x * x + z * z + y * y;
    if (dist > limit / 2.0F / 2.0F)
        return 1;
    return 0;
}
