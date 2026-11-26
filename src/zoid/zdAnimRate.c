#include "zoid3.h"

extern void setAnimRate(HSD_JObj *joint, f32 rate);

void zdAnimRate(ZoidState *zoid, f32 rate)
{
    HSD_JObj *joint;
    if (zoid != 0) {
        joint = zoid->joint;
        if (joint != 0) {
            zoid->anim_rate = rate;
            setAnimRate(joint, rate);
        }
    }
}
