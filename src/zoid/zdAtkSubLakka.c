#include "zoid3.h"

extern s32 zdLakkaTest2(ZoidState *zoid);
extern void setAnimRate(HSD_JObj *joint, f32 rate);
extern void ZoidInertiaAtk(ZoidState *zoid);

s32 zdAtkSubLakka(ZoidState *zoid)
{
    s32 i;
    s32 kind;
    s32 attack_index;
    ZoidControlData *control;
    u8 *slider;
    f32 lift;
    f32 scale;

    control = (ZoidControlData *)zoid->anim_data;
    slider = (u8 *)zoid->slider_info;
    attack_index = zoid->attack_index;
    if (slider == 0) {
        return 0;
    }
    if (control->field_00F8 == 1) {
        return 0;
    }
    if (control->field_00F8 == 3) {
        return 0;
    }
    if (zoid->field_0170 != 0) {
        return 0;
    }
    kind = (slider + 0x714)[attack_index];
    if (kind == 1) {
        if (zoid->grounded == 0) {
            zoid->displacement[1] -= 0.025;
            zoid->position[1] += zoid->displacement[1];
        }
        return 0;
    }
    if (zoid->ground_turn != 0 || zoid->field_1A74 != 0) {
        for (i = 0; i < 3; i++) {
            zoid->displacement[i] = 0.0f;
        }
    }
    if (kind == 2) {
        if ((zoid->movement_flags & 3) == 2) {
            setAnimRate(zoid->joint, 0.0f);
            for (i = 0; i < 3; i++) {
                zoid->displacement[i] = *(f32 *)((u8 *)zoid + 0x4F8 + i * 4);
            }
            ZoidInertiaAtk(zoid);
            lift = zoid->height_offset;
            zoid->position[1] += lift;
            zoid->height_offset -= lift;
            zoid->field_1C24[1] += lift;
            zoid->field_1BFC = 0;
            return 1;
        }
        return 0;
    }
    if ((zoid->movement_flags & 1) == 0 && zoid->grounded == 0 && kind != 2) {
        zoid->displacement[1] -= 0.025;
        zoid->position[1] += zoid->displacement[1];
    }
    if (zdLakkaTest2(zoid) == 0) {
        if (zoid->action_phase == 1) {
            return 0;
        }
        scale = 0.0f;
        if (zoid->action_phase == 3) {
            scale = 0.0075f;
            if (zoid->ground_normal_count) {
                (void)0;
            }
        }
        if (kind == 2) {
            scale = 0.0f;
        }
        if (scale) {
            zoid->displacement[1] -= scale;
            zoid->position[1] += zoid->displacement[1];
        }
        return 0;
    } else {
        setAnimRate(zoid->joint, 0.0f);
        for (i = 0; i < 3; i++) {
            zoid->displacement[i] = *(f32 *)((u8 *)zoid + 0x4F8 + i * 4);
        }
        ZoidInertiaAtk(zoid);
        lift = zoid->height_offset;
        zoid->position[1] += lift;
        zoid->height_offset -= lift;
        zoid->field_1C24[1] += lift;
        zoid->field_1BFC = 0;
        return 1;
    }
}
