#include "zoid3.h"

typedef struct ZoidF32Span {
    u8 pad[0x1D14];
    f32 values[3];
} ZoidF32Span;

extern void ZoidSetAnim(ZoidState *zoid, s32 animation);
extern void PartnerFace(s32 face, s32 frames);
extern void zdChgNormal(ZoidState *zoid);
extern void zdLinierTm(ZoidState *zoid, s32 frames);

void ZoidActDmg2(ZoidState *zoid)
{
    s32 motions[6] = {44, 45, 46, 47, 48, 49};
    register s32 i;
    u8 *anim;

    anim = zoid->anim_data;
    if (anim != 0 && *(s32 *)(anim + 0x100) != 0) {
        zoid->field_1E50 = 60;
        for (i = 0; i < 3; i++) {
            ((ZoidF32Span *)zoid)->values[i] = 0.0f;
            zoid->field_1D20[i] = 0.0f;
        }
        zoid->field_1E5C = 0;
    }
    zoid->gene_frames += 1;
    switch (zoid->action_phase) {
    case 0:
        zoid->gene_frames = 0;
        ZoidSetAnim(zoid, motions[zoid->action - 0x1C]);
        zoid->action_phase = 1;
        if (Zoid[2].joint != 0 && zoid == &Zoid[2] && zoid->slot == 0) {
            PartnerFace(4, 60);
        }
        for (i = 0; i < 3; i++) {
            zoid->field_1D20[i] = 0.0f;
        }
        break;
    case 1:
        if (zoid->gene_frames > 120) {
            zoid->action_phase = 0x99;
        }
        if (zoid->animation_stopped == 0 && zoid->animation_looped == 0) {
            break;
        }
    default:
        zoid->action = 0;
        zoid->field_1C90[1] = 0.0f;
        zoid->field_1C90[2] = 0.0f;
        zoid->field_1C90[0] = 0.0f;
        zdChgNormal(zoid);
        zdLinierTm(zoid, 60);
        break;
    }
}
