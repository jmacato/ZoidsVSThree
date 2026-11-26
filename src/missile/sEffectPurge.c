#include "jobj.h"
#include "object.h"

typedef struct Effect3 {
    HSD_JObj *root;
    u8 pad_04[0x41C - 4];
    s32 se_playing;
    u32 se_voice;
    HSD_Obj *light;
} Effect3;

extern void jobjUnrefAll(HSD_JObj *joint);

static inline s32 ref_DEC(HSD_Obj *o)
{
    s32 ret;

    ret = (u64)(o->reference_count == (u16)0xFFFF);
    if (ret != 0) {
        return ret;
    }
    ret = (o->reference_count == (u16)0);
    o->reference_count--;
    return ret;
}

void sEffectPurge(Effect3 *effect)
{
    HSD_Obj *obj;

    if (effect != (void *)0 && effect->root != (void *)0) {
        if (effect->se_playing != 0) {
            effect->se_playing = 0;
        }
        if (effect->light != 0) {
            obj = effect->light;
            if (obj != 0) {
                if (ref_DEC(obj) != 0) {
                    if (obj != 0) {
                        ((HSD_Class *)obj)->class_info->release((HSD_Class *)obj);
                        ((HSD_Class *)obj)->class_info->destroy((HSD_Class *)obj);
                    }
                }
            }
            effect->light = 0;
        }
        jobjUnrefAll(effect->root);
        effect->root = 0;
    }
}
