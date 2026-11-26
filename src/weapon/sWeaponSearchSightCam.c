#include "types.h"
#include "zoid3.h"

typedef struct WeaponMarker3 {
    f32 position[3];
    s32 locked;
    s32 field_10;
    ZoidState *target;
    struct Missile3 *source;
    HSD_JObj *joint;
    s32 object_index;
} WeaponMarker3;

typedef struct WeaponState3 {
    u8 reserved_00[0x400];
    s32 marker_count;
    u8 reserved_404[0x40C - 0x404];
    WeaponMarker3 markers[20];
} WeaponState3;

typedef struct Missile3 {
    u8 reserved_00[0x24];
    HSD_JObj *joint;
    u8 reserved_28[0xF4 - 0x28];
    s32 purge_timer;
    u8 reserved_F8[0x1A4 - 0xF8];
} Missile3;

extern s32 vsyncN;
extern Missile3 missileStart[200];
extern s32 grdObjAliveN(s32 index);
extern s32 grdObjGetMax(void);
extern HSD_JObj *grdObjGetJObj(s32 index);
extern s32 sCameraPt2d(void *camera, Vec3 *position, s32 *screen_point);
extern s32 sCameraJobjPt2d(void *camera, HSD_JObj *joint, s32 *screen_point);
extern s32 sWpSearchSight1z(WeaponState3 *weapon, ZoidState *zoid, ZoidState *target);
extern s32 sWpSearchSight1g(WeaponState3 *weapon, ZoidState *zoid, s32 index);

void sWeaponSearchSightCam(WeaponState3 *weapon, ZoidState *zoid)
{
    s32 index;
    s32 i;
    s32 slot;
    s32 max;
    s32 pt[2];
    WeaponMarker3 *marker;
    ZoidState *target;
    Missile3 *missile;
    HSD_JObj *joint;

    for (i = 0; i < 20; i++) {
        marker = &weapon->markers[i];
        if (marker->joint == 0)
            continue;
        target = marker->target;
        missile = marker->source;
        if (marker->locked != 0) {
            if (target != 0 && target->death_started == 0) {
                /* Widening preserves MWCC's temporary-register selection. */
                if (((s32)(s64)vsyncN & 0x1E0) != 0)
                    continue;
                if (zoid->camera != 0 &&
                    sCameraPt2d(zoid->camera, (Vec3 *)target->position, pt) != 0)
                    continue;
                marker->joint = 0;
                continue;
            }
            if (marker->object_index != 0 && grdObjAliveN(marker->object_index) != 0) {
                if (((s32)(s64)vsyncN & 0x1E0) != 0)
                    continue;
                if (zoid->camera != 0) {
                    joint = grdObjGetJObj(marker->object_index);
                    if (sCameraJobjPt2d(zoid->camera, joint, pt) != 0)
                        continue;
                }
                marker->joint = 0;
                continue;
            }
            if (missile != 0 && missile->purge_timer == 0)
                continue;
            marker->joint = 0;
        } else {
            if (((s32)(s64)vsyncN & 0x3E0) != 0)
                continue;
            marker->joint = 0;
        }
    }
    slot = zoid->slot;
    index = 0;
    if (zoid->target_pending != 0)
        index = zoid->target_slot;
    for (i = 0; i < 16; i++, index++) {
        if (index < 0)
            index = 0;
        if (index >= 16)
            index = 0;
        target = &Zoid[index];
        if (target != zoid && target->joint != (void *)0 &&
            target->death_started == 0 && slot != target->slot) {
            if (sWpSearchSight1z(weapon, zoid, target) != 0)
                return;
        }
    }
    max = grdObjGetMax();
    index = 0;
    if (zoid->lock_active != 0)
        index = zoid->lock_obj;
    for (i = 0; i < max; i++, index++) {
        if (index >= max)
            index = 0;
        if (sWpSearchSight1g(weapon, zoid, index) != 0)
            return;
    }
    missile = missileStart;
    for (i = 0; i < 200; i++, missile++) {
        if (missile == (void *)0)
            break;
        if (missile->purge_timer == 0) {
            /* The release code evaluates this check without acting on it. */
            if (missile->joint != (void *)0) {
                (void)0;
            }
        }
    }
}
