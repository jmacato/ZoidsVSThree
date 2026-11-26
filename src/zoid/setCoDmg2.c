#include "types.h"

typedef struct CoObj {
    u8 reserved[0x6C];
    s32 health;
    s32 maximum_health;
} CoObj;

typedef struct CoDamage {
    u32 flags;
    s32 health, maximum_health;
} CoDamage;

void setCoDmg2(CoObj *first, CoObj *second, CoDamage *damage)
{
    f32 first_ratio;
    f32 second_ratio;
    damage->maximum_health = 0;
    damage->health = 0;
    first_ratio = 1000.f;
    second_ratio = 1000.f;
    if (first->maximum_health != 0) {
        first_ratio = (f32)first->health / (f32)first->maximum_health;
        damage->health = first->health;
        damage->maximum_health = first->maximum_health;
    } else {
        first_ratio = 1000.f;
    }
    if (second->maximum_health != 0) {
        second_ratio = (f32)second->health / (f32)second->maximum_health;
    } else {
        second_ratio = 1000.f;
    }
    if (first_ratio != 1000.f || second_ratio != 1000.f) {
        if (first_ratio > second_ratio) {
            damage->health = second->health;
            damage->maximum_health = second->maximum_health;
        }
        if (damage->health < 0) {
            damage->health = 0;
        }
    }
}
