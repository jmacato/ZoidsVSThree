#pragma readonly_strings on
#include "zoid3.h"
#include "aobj.h"

extern u32 zdsMotTBL[];
extern void __assert(const char *file, u32 line, const char *condition);
extern void OSReport(const char *format, ...);
extern void zdAnimEffect(ZoidState *zoid, s32 animation);
extern void zdClearAtkTouch(ZoidState *zoid);
extern void zdAddAnimRy(ZoidState *zoid);
extern void sAddAnimAllXor2ANIM(ZoidState *zoid, s32 animation);
extern HSD_AObj *getAnimAobj(HSD_JObj *joint);
extern void HSD_JObjReqAnimAll(HSD_JObj *joint, f32 frame);
extern void setAnimRate(HSD_JObj *joint, f32 rate);
extern void ZoidAnim(ZoidState *zoid);

static inline f32 HSD_AObjGetEndFrame(HSD_AObj *aobj)
{
    aobj ? (void)0 : __assert("aobj.h", 171, "aobj");
    return aobj->end_frame;
}

#pragma push
#pragma opt_common_subs off
void ZoidSetAnim(ZoidState *zoid, s32 animation)
{
    void *data;
    s32 current;
    ModelAnimationTable *animations;
    HSD_AObj *aobj;
    s32 i;

    if (zoid == (void *)0)
        return;
    if (zoid->joint == (void *)0)
        return;
    if (animation < 0) {
        OSReport("zoid anim setAnim=(%d)error \n", animation);
        return;
    }
    switch (animation) {
    case 1:
    case 2:
    case 10:
    case 11:
    case 12:
        break;
    default:
        zoid->field_2060 = 0;
    }
    zoid->field_1C48 = 0;
    if (animation == 0x67)
        animation = 0x40;
    if (animation > 0x65)
        animation = 0;
    switch (animation) {
    case 0x43:
    case 0x44:
        zoid->attack_index = 0;
        break;
    case 0x45:
    case 0x46:
        zoid->attack_index = 1;
        break;
    case 0x47:
    case 0x48:
        zoid->attack_index = 2;
        break;
    case 0x49:
    case 0x4A:
        zoid->attack_index = 3;
        break;
    case 0x4B:
    case 0x4C:
        zoid->attack_index = 4;
        break;
    case 0x41:
        zoid->attack_index = 5;
        break;
    case 0x42:
        zoid->attack_index = 5;
        break;
    case 0x3E:
        zoid->attack_index = 7;
        break;
    default:
        zoid->attack_index = -1;
        break;
    }
    zoid->field_1DF4 = 0;
    switch (animation) {
    case 0x43: case 0x44: case 0x45: case 0x46: case 0x47: case 0x48: case 0x49: case 0x4A:
    case 0x4B: case 0x4C: case 0x4D: case 0x4E: case 0x4F: case 0x50: case 0x51:
        zoid->field_1DF4 = 1;
    }
    zdAnimEffect(zoid, animation);
    data = zoid->anim_data;
    zdClearAtkTouch(zoid);
    current = zoid->current_animation;
    if (zdsMotTBL[current] & 8)
        zdAddAnimRy(zoid);
    zoid->interpolation_remaining = 15;
    zoid->interpolation_duration = 15;
    zoid->field_1C40 = 0;
    zoid->current_animation = animation;
    zoid->field_1DE4 = animation;
    animations = zoid->animations;
    if (animations->models != (void *)0 && animations->models[0]->joint_animations != (void *)0) {
        sAddAnimAllXor2ANIM(zoid, animation);
        zoid->aobj = getAnimAobj(zoid->joint->child);
        if (zoid->aobj == 0) {
            zoid->animation_end_frame = 0.0f;
        } else {
            aobj = zoid->aobj;
            zoid->animation_end_frame = HSD_AObjGetEndFrame(aobj);
        }
        zoid->animation_stopped = 0;
        HSD_JObjReqAnimAll(zoid->joint, 0.0f);
        for (i = 0; i < 3; i++) {
            zoid->field_1A40[i] = 0.0f;
            zoid->previous_child_translation[i] = 0.0f;
            zoid->child_translation[i] = 0.0f;
        }
        setAnimRate(zoid->joint->child, 1.0f);
        zoid->anim_rate = 1.0f;
        ZoidAnim(zoid);
    }
}
#pragma pop
