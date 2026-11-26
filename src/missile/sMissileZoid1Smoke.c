#pragma readonly_strings on
#include "zoid3.h"
#include "types.h"

#define NULL ((void *)0)

typedef struct JObj3 {
    u8 pad_00[0x2C];
    f32 scale_x;
} JObj3;

typedef struct Missile3 {
    s32 flags;
    u8 pad_04[0x20];
    void *joint;
    struct ZoidState *owner;
    u8 pad_2C[0xEC - 0x2C];
    s32 update_count;
    s32 field_F0;
    s32 purge_timer;
    s32 hit_timer;
    u8 pad_FC[0x180 - 0xFC];
    JObj3 *a1_joint;
    void *light;
    u8 pad_188[0x19C - 0x188];
    s32 se_playing;
    u8 pad_1A0[0x1A4 - 0x1A0];
} Missile3;

extern void __assert(const char *file, s32 line, const char *expr);
extern f32 sLenJobj(void *a, void *b);

void sMissileZoid1Smoke(Missile3 *missile, ZoidState *zoid)
{
    s32 slot;
    JObj3 *a1_joint;
    ZoidState *owner;
    JObj3 *camera_joint;
    f32 scale;
    f32 length;

    if (zoid == NULL)
        return;
    if (zoid->joint == NULL)
        return;
    camera_joint = (JObj3 *)zoid->camera_joint;
    if (camera_joint == 0)
        return;
    if (missile == NULL)
        return;
    a1_joint = missile->a1_joint;
    owner = missile->owner;
    if (a1_joint == NULL)
        return;
    slot = -1;
    if (owner != 0)
        slot = owner->slot;
    if (missile->update_count < 2)
        return;
    if (zoid == missile->owner && missile->update_count < 180)
        return;
    a1_joint ? (void)0 : __assert("jobj.h", 899, "jobj");
    scale = a1_joint->scale_x;
    if (scale < 0.8)
        return;
    length = sLenJobj(a1_joint, camera_joint);
    if (2.0f * length > scale)
        return;
    if (zoid->slot == slot)
        zoid->ally_smoke_timer = 60;
    else
        zoid->enemy_smoke_timer = 180;
}
