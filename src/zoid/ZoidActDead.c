#include "zoid3.h"
#include "missile.h"

extern s32 sCamNN;
extern void PartnerFace(s32 face, s32 duration);

void ZoidActDead(ZoidState *zoid)
{
    HSD_JObj *joint;

    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        zoid->lock_frames = 0;
        zoid->death_pending = 1;
        if (zoid->death_started == 0) {
            zoid->death_started = 1;
            joint = zoid->buckle_joint;
            if (joint == 0) {
                joint = zoid->bust_base_joint;
            }
            if (joint == 0) {
                joint = zoid->joint;
            }
            sEffectSet(105, 2, 0, joint, zoid);
            sEffectSet(47, 3, 0, joint, zoid);
            if (zoid == &Zoid[2] && sCamNN == 1 && Zoid[2].joint != 0 &&
                Zoid[0].slot == Zoid[2].slot) {
                PartnerFace(7, 120);
            }
        }
        zoid->action = 0x2B;
    }
}
