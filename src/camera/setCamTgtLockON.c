#include "zoid3.h"

typedef struct CameraState3 {
    u8 pad_000[0x2C];
    f32 focus_distance;
    s32 mount_index;
    u8 pad_034[0x190];
    ZoidState *zoid;
    u8 pad_1C8[0x34];
    f32 focus[3];
} CameraState3;

extern HSD_JObj *grdObjGetJObj(u8 id);
extern f32 sLenJobj(HSD_JObj *a, HSD_JObj *b);

void setCamTgtLockON(CameraState3 *camera)
{
    ZoidState *zoid;
    ZoidState *enemy;
    HSD_JObj *joint;
    HSD_JObj *enemy_joint;
    u8 *control;
    void *anim;
    s32 *mount;
    f32 ratio;
    f32 length;
    f32 weight;
    f32 joint_weight;
    s32 i;

    if (camera != (void *)0 && (zoid = camera->zoid) != (void *)0 && zoid->joint != (void *)0) {
        control = zoid->field_2090;
        anim = zoid->anim_data;
        mount = (s32 *)(control + camera->mount_index * 16);
        if (*mount == -1)
            joint = zoid->field_1ACC;
        else
            joint = zoid->weapon_slots[*mount].joint;
        if (joint == (void *)0)
            joint = *(HSD_JObj **)zoid->body_coobj;
        if (joint == (void *)0)
            joint = zoid->joint;
        if (joint == (void *)0)
            return;
        if (zoid->target_pending != 0) {
            enemy = &Zoid[zoid->target_slot];
            if (enemy == (void *)0) {
                zoid->target_pending = 0;
                return;
            }
            enemy_joint = (HSD_JObj *)enemy->camera_joint;
        }
        if (zoid->lock_active != 0) {
            enemy_joint = grdObjGetJObj(zoid->lock_obj);
            if (enemy_joint == 0) {
                zoid->lock_active = 0;
                return;
            }
        }
        if (enemy_joint == 0)
            return;
        ratio = camera->focus_distance / 200.0f;
        length = sLenJobj(enemy_joint, joint);
        if (length * ratio < 10.0f) {
            if (length > 1.0f)
                ratio = (f32)(10.0 / length);
        }
        weight = ratio;
        joint_weight = 1.0f - weight;
        for (i = 0; i < 3; i++)
            (&camera->focus[0])[i] = enemy_joint->matrix[i][3] * weight + joint->matrix[i][3] * joint_weight;
    }
}
