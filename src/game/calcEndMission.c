#pragma auto_inline off
#include "zoid3.h"
#include "game_mode.h"

typedef struct MgI3 {
    u8 reserved_0000[0x2AA4];
    s32 kind;
    s32 condition;
    u8 reserved_2AAC[0x307C - 0x2AAC];
    s16 id;
    s16 health;
    s16 kills;
    s16 x;
    s16 z;
    s16 radius;
    s16 type;
    s16 reserved_308A;
    s16 hold_x;
    s16 hold_z;
    s16 hold_radius;
    u8 reserved_3092[2];
    s8 required_kills;
} MgI3;

extern MgI3 mgI;
extern s32 gameTime;
extern s32 AreaIn;
extern s32 AreaIn2;
extern s32 grdObjAlive(s32 index);
extern s32 grdObjDead(s32 index);
extern f64 __frsqrte(f64);

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

s32 calcEndMission(void)
{
    ZoidState *other;
    s32 i;
    s32 slot;
    s32 alive;
    ZoidState *zoid;
    ZoidState *first;
    ZoidState *partner;
    f32 dx;
    f32 dz;
    f32 dist;

    first = &Zoid[0];
    zoid = first;
    if ((partner = &Zoid[2])->joint == 0)
        partner = 0;
    slot = first->slot;
    if (first->death_started != 0)
        return 3;
    switch (mgI.condition) {
    case 3:
        if (partner != 0 && partner->slot == slot && partner->death_started != 0)
            return 3;
        break;
    case 4:
        for (i = 1; i < 16; i++) {
            other = &Zoid[i];
            if (other->joint != 0 && other->type == mgI.type && other->death_started != 0)
                return 3;
        }
    case 5:
        for (i = 1; i < 16; i++) {
            other = &Zoid[i];
            if (other->joint != 0 && other->slot != slot && other->type == mgI.type)
                break;
        }
        if (i == 16)
            break;
        dx = other->position[0] - mgI.hold_x;
        dz = other->position[2] - mgI.hold_z;
        dist = sqrtf(dx * dx + dz * dz);
        if (dist < mgI.hold_radius)
            AreaIn2 = 1;
        if (AreaIn2 != 0)
            return 3;
        break;
    case 6:
        if (gameTime == 0 && mgI.required_kills > first->kills)
            return 3;
        break;
    case 7:
        if (gameTime == 0 && grdObjDead(mgI.type) < mgI.required_kills)
            return 3;
        break;
    }
    switch (mgI.kind) {
    case 0:
        for (i = 0, alive = 0; i < 16; i++) {
            other = &Zoid[i];
            if (other->joint != 0 && other->slot != slot) {
                if (other->death_started == 0)
                    alive++;
                else if (other->field_20BC != 0)
                    alive++;
            }
        }
        if (alive == 0)
            return 1;
        break;
    case 1:
        if (grdObjAlive(mgI.id) == 0)
            return 1;
        break;
    case 2:
        for (i = 1, alive = 0; i < 16; i++) {
            other = &Zoid[i];
            if (other->joint != 0 && other->slot != slot && other->type == mgI.id) {
                alive++;
                if (other->health <= mgI.health)
                    return 1;
            }
        }
        break;
    case 7:
        for (i = 1; i < 16; i++) {
            zoid = &Zoid[i];
            if (zoid->joint != 0 && zoid->slot == slot && zoid->type == mgI.id)
                break;
        }
        if (i == 16)
            break;
    case 3:
        dx = zoid->position[0] - mgI.x;
        dz = zoid->position[2] - mgI.z;
        dist = sqrtf(dx * dx + dz * dz);
        if (dist < mgI.radius)
            AreaIn = 1;
        if (AreaIn != 0)
            return 1;
        break;
    case 4:
        if (first->kills >= mgI.kills)
            return 1;
        break;
    case 5:
        if (gameTime == 0)
            return 1;
        break;
    case 6:
        for (i = 1, alive = 0; i < 16; i++) {
            other = &Zoid[i];
            if (other->joint != 0 && other->slot != slot && other->type == mgI.id && other->death_started == 0)
                alive++;
        }
        if (alive == 0)
            return 1;
        break;
    }
    return 0;
}
