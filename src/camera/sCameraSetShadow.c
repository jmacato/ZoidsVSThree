#include "zoid3.h"
#include "lobj.h"
#include "game_mode.h"

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

extern struct HSD_Shadow *makeShadow(HSD_LObj *light);
extern void HSD_ShadowAddObject(struct HSD_Shadow *shadow, HSD_JObj *jobj);
extern void HSD_ShadowSetActive(struct HSD_Shadow *shadow, int active);

void sCameraSetShadow(CameraState3 *camera)
{
    HSD_LObj *light;
    HSD_LObj *next;

    if (camera != (void *)0 && camera->cobj != (void *)0 && GameMode.game_type != 5) {
        light = camera->lights;
        while (light != 0) {
            if ((light->flags & LOBJ_TYPE_MASK) != LOBJ_AMBIENT) {
                camera->shadow = makeShadow(light);
                HSD_ShadowAddObject(camera->shadow, camera->zoid->joint);
                HSD_ShadowSetActive(camera->shadow, 0);
                break;
            }
            if (light == (void *)0)
                next = 0;
            else
                next = light->next;
            light = next;
        }
    }
}
