#pragma readonly_strings on
#include "zoid3.h"

typedef struct CoObj3 {
    HSD_JObj *joint;
    HSD_JObj *base_joint;
    f32 minimum_scale;
    f32 maximum_scale;
    f32 radius;
    u8 pad_14[0x58];
    s32 health;
    s32 maximum_health;
} CoObj3;

extern f64 __frsqrte(f64);
extern HSD_JObj *searchJoint(ZoidState *zoid, const char *part);
extern void __assert(const char *file, s32 line, const char *message);

static inline f32 sqrtf(f32 x)
{
    static const f64 _half = 0.5;
    static const f64 _three = 3.0;
    volatile f32 y;

    if (x > 0.0f) {
        f64 guess = __frsqrte((f64)x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        y = (f32)(x * guess);
        return y;
    }
    return x;
}

static inline f32 HSD_JObjGetScaleX(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 899, "jobj");
    return jobj->scale.x;
}
static inline f32 HSD_JObjGetScaleY(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 911, "jobj");
    return jobj->scale.y;
}
static inline f32 HSD_JObjGetScaleZ(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 923, "jobj");
    return jobj->scale.z;
}

#pragma auto_inline off
void searchJointCoObj(ZoidState *zoid, CoObj3 *object, const char *part, HSD_JObj *base_joint)
{
    HSD_JObj *joint;
    f32 y;
    f32 z;
    f32 x;
    f32 minimum;
    f32 maximum;
    object->health = 0;
    object->maximum_health = 0;
    joint = searchJoint(zoid, part);
    object->joint = joint;
    if (joint != (void *)0) {
        object->maximum_health = 100;
        object->health = 100;
        x = HSD_JObjGetScaleX(joint);
        y = HSD_JObjGetScaleY(joint);
        z = HSD_JObjGetScaleZ(joint);
        minimum = x;
        maximum = x;
        if (maximum < y)
            maximum = y;
        if (maximum < z)
            maximum = z;
        if (minimum > y)
            minimum = y;
        if (minimum > z)
            minimum = z;
        object->minimum_scale = minimum;
        object->maximum_scale = maximum;
        object->radius = sqrtf(x * x + y * y + z * z) / 2.0f;
        object->base_joint = base_joint;
    }
}
