#include "zoid3.h"

extern f32 sLenJobj(HSD_JObj *first, HSD_JObj *second);
extern f32 ZoidCalcAngle(ZoidState *zoid, Vec3 *point);
extern void angLimit(f32 *angle);

void zdAtkSubFor(ZoidState *zoid, ZoidState *other)
{
    ZoidState *target;
    f32 angle;
    f32 limit;

    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        if (zoid->attack_target != -1 && zoid->attack_target != -2 && zoid->action_phase != 3) {
            limit = 0.0261799383f;
            if (zoid->action_phase == 0) {
                limit = 0.5235987756f;
            }
            target = &Zoid[zoid->attack_target];
            if (target->joint != (void *)0 &&
                (zoid->action_phase == 0 || !(sLenJobj(zoid->joint->child, target->joint->child) < 15.0f))) {
                angle = ZoidCalcAngle(zoid, (Vec3 *)target->position);
                if (angle > limit) {
                    angle = limit;
                }
                if (angle < -limit) {
                    angle = -limit;
                }
                zoid->heading += angle;
                angLimit(&zoid->heading);
            }
        }
    }
    other = other;
}
