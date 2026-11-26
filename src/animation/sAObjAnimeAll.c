#pragma readonly_strings on
#include "joint.h"
#include "aobj.h"

#define NULL ((void *)0)

extern void __assert(const char *file, u32 line, const char *condition);
extern HSD_AObj *getAnimAobj(HSD_JObj *joint);
extern void HSD_JObjAnimAll(HSD_JObj *joint);
extern u32 HSD_AObjGetFlags(HSD_AObj *aobj);
extern void setAnimFrame(HSD_JObj *joint, f32 frame);
extern void setAnimRate(HSD_JObj *joint, f32 rate);

static inline f32 HSD_AObjGetCurrFrame(HSD_AObj *aobj)
{
    aobj ? (void)0 : __assert("aobj.h", 149, "aobj");
    return aobj->current_frame;
}

s32 sAObjAnimeAll(HSD_JObj *joint)
{
    HSD_AObj *aobj;
    f32 frame;
    u32 flags;

    if (joint == NULL)
        return 0;
    aobj = getAnimAobj(joint);
    if (aobj == NULL)
        return 0;
    frame = HSD_AObjGetCurrFrame(aobj);
    HSD_JObjAnimAll(joint);
    flags = HSD_AObjGetFlags(aobj);
    if (!(flags & AOBJ_REWINDED))
        return 0;
    setAnimFrame(joint, frame);
    setAnimRate(joint, 0.0f);
    return 1;
}
