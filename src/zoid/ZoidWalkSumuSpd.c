#include "zoid3.h"
#pragma readonly_strings on
extern u32 zdsMotTBL[];
extern void dummyFunc(const char *);
extern void ZoidWalkSpeed(ZoidState *zoid);
extern s32 zdFaceAtk(ZoidState *zoid, f32 distance, f32 degrees);

void ZoidWalkSumuSpd(ZoidState *zoid)
{
    u8 *control;
    f32 maximum;
    s32 locked;
    u8 *slider;
    s32 reached;

    dummyFunc("WkSuSpd>");
    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        control = zoid->anim_data;
        if (control == (void *)0) {
            return;
        }
        slider = (u8 *)zoid->slider_info;
        if (slider == 0) {
            return;
        }
        zoid->field_1F04 = *(s32 *)(control + 0xBC) + zoid->speed_bonus;
        maximum = (f64) * (s32 *)(control + 0x9C) / 100.0;
        if (zoid->booster_on == 0 && zoid->field_016C == 0) {
            maximum = (f64)zoid->field_1F04 / 100.0;
        }
        if (zoid->field_1C90[0] > maximum) {
            zoid->field_1C90[0] = maximum;
        }
        if (zoid->field_1C90[0] < (f64) - *(s32 *)(control + 0xAC) / 100.0) {
            zoid->field_1C90[0] = (f64) - *(s32 *)(control + 0xAC) / 100.0;
        }
        if (zoid->field_1C90[1] != zoid->field_1C90[0]) {
            if (zoid->field_1C90[1] > zoid->field_1C90[0]) {
                zoid->field_1C90[1] -= (f32) * (s32 *)(control + 0xD8) / 10000.0;
                if (zoid->field_1C90[1] < zoid->field_1C90[0]) {
                    zoid->field_1C90[1] = zoid->field_1C90[0];
                }
            }
            if (zoid->field_1C90[1] < zoid->field_1C90[0]) {
                zoid->field_1C90[1] += (f32) * (s32 *)(control + 0xD4) / 10000.0;
                if (zoid->field_1C90[1] > zoid->field_1C90[0]) {
                    zoid->field_1C90[1] = zoid->field_1C90[0];
                }
            }
        }
        locked = 0;
        if ((zdsMotTBL[zoid->current_animation] & 1) != 0) {
            locked = 1;
        }
        if (locked != 0) {
            if (zoid->animation_stopped != 0) {
                locked = 0;
            }
            if (zoid->current_animation == 0x42) {
                locked = 0;
            }
            if (zoid->current_animation == 0x41) {
                locked = 0;
            }
        }
        reached = 0;
        if (slider[0x70A] < 1) {
            slider[0x70A] = 1;
        }
        if (slider[0x70A] != 0) {
            if (zdFaceAtk(zoid, (f32)(s32)slider[0x70A], 0.0f) != 0) {
                reached = 1;
            }
        }
        if ((slider[0x70B] & 1) != 0 && *(u16 *)((u8 *)zoid + 0x534) != 0xFFFF) {
            reached = 1;
        }
        if (reached != 0) {
            zoid->field_1C90[1] *= 0.5;
        }
        if (locked == 0) {
            ZoidWalkSpeed(zoid);
        }
    }
}
