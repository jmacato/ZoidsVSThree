#include "zoid3.h"
#include "ground_collision.h"

extern GroundMask GXColorZoid;
extern f32 sColPosLessAndY(Vec3 *point, u16 *selector, GroundMask *mask, f32 limit);
extern void ZoidSetAnim(ZoidState *zoid, s32 animation);
extern void HSD_JObjAnimAll(HSD_JObj *joint);
extern void zdGetBodyPt(ZoidState *zoid, Vec3 *point);
extern void zdLinierTm(ZoidState *zoid, s32 frames);
extern void zdSetXYZ(ZoidState *zoid);
extern void zdSetXYZ2(ZoidState *zoid);
extern void zdLinearAnimAllBak(ZoidState *zoid);
extern void sMakeMatrix(HSD_JObj *joint);
extern void ik3dOn(ZoidState *zoid, FootJoint *foot);
extern void zdLinierReset(ZoidState *zoid, HSD_JObj *joint);

typedef struct ZoidAnimData3 {
    u8 pad[0xF4];
    s32 field_F4;
} ZoidAnimData3;

void zdChgNormal(ZoidState *zoid)
{
    ZoidAnimData3 *control;
    u8 *slider;
    Vec3 body;
    Vec3 body2;
    GroundMask mask;
    f32 ground;
    f32 depth;

    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        zoid->field_1C14 = 1;
        control = zoid->anim_data;
        slider = (u8 *)zoid->slider_info;
        zdSetXYZ(zoid);
        sMakeMatrix(zoid->joint);
        zdGetBodyPt(zoid, &body);
        ZoidSetAnim(zoid, 1);
        zdLinierTm(zoid, 30);
        zoid->height_offset_speed = 0.0f;
        zoid->displacement[1] = 0.0f;
        mask = GXColorZoid;
        ground = sColPosLessAndY((Vec3 *)zoid->position, 0, &mask, zoid->field_1AA8);
        depth = ground - zoid->position[1];
        if (depth > 0.0f) {
            zoid->field_1C24[1] = ground;
            zoid->position[1] = ground;
            zoid->height_offset -= depth;
        }
        zoid->height_offset = 0.0f;
        zdSetXYZ(zoid);
        HSD_JObjAnimAll(zoid->joint);
        sMakeMatrix(zoid->joint);
        zdGetBodyPt(zoid, &body2);
        depth = body2.y - body.y;
        if (zoid->field_0170 != 0 || zoid->ai_active == 0) {
            zoid->height_offset -= depth;
        } else if (depth > 0.0f) {
            zoid->height_offset -= depth;
        }
        zdSetXYZ2(zoid);
        zdLinearAnimAllBak(zoid);
        sMakeMatrix(zoid->joint);
        ik3dOn(zoid, &zoid->feet[2]);
        ik3dOn(zoid, &zoid->feet[3]);
        if (control->field_F4 != 2 && !(slider[0x70B] & 8)) {
            ik3dOn(zoid, &zoid->feet[0]);
            ik3dOn(zoid, &zoid->feet[1]);
        }
        zdLinierReset(zoid, zoid->feet[2].joint);
        zdLinierReset(zoid, zoid->feet[3].joint);
        if (control->field_F4 != 2 && !(slider[0x70B] & 8)) {
            zdLinierReset(zoid, zoid->feet[0].joint);
            zdLinierReset(zoid, zoid->feet[1].joint);
        }
        zoid->action = 0;
        zoid->requested_action = 0;
        zoid->displacement[0] = 0.0f;
        zoid->displacement[2] = 0.0f;
    }
}
