#include "zoid3.h"

typedef struct ZoidData3 {
    u8 reserved_0000[0x756];
    s16 attack_damage[12];
    u8 reserved_076E[0x7FC - 0x76E];
} ZoidData3;

extern ZoidData3 Tea_zoiddat[];
extern f32 sLenPoint3dR(f32 *point);
extern s32 hitCalc(ZoidState *attacker, s32 damage, ZoidState *zoid);
extern void setDmg123(ZoidState *attacker, ZoidState *zoid, s32 index, s32 flag);
extern void zdVoiceScG(ZoidState *zoid, s32 voice);

void ZoidCoAtackDmg(ZoidState *attacker, ZoidAttackObject *attack, ZoidState *zoid, s32 flag)
{
    s32 type;
    s32 index;
    s32 damage;
    s32 health;
    s32 i;
    f32 length;
    f32 scale;
    f32 delta[3];

    if (attacker == 0) {
        return;
    }
    if (zoid == 0) {
        return;
    }
    type = attacker->type;
    if (zoid->field_1E50 != 0) {
        return;
    }
    zoid->rumble_timer = 15;
    for (i = 0; i < 3; i++) {
        delta[i] = zoid->position[i] - attack->joint->matrix[i][3];
    }
    length = sLenPoint3dR(delta);
    if (0.0f == length) {
        for (i = 0; i < 3; i++) {
            delta[i] = zoid->position[i] - attacker->position[i];
        }
        length = sLenPoint3dR(delta);
    }
    if (0.0f == length) {
        for (i = 0; i < 3; i++) {
            delta[i] = attacker->joint->matrix[i][0];
        }
        length = sLenPoint3dR(delta);
    }
    if (0.0f == length) {
        return;
    }
    index = attacker->attack_index;
    if (index >= 0 && index <= 11) {
        damage = Tea_zoiddat[type].attack_damage[index];
    } else {
        damage = 10;
        index = 11;
    }
    setDmg123(attacker, zoid, index, flag == 1);
    damage = hitCalc(attacker, damage, zoid);
    scale = (f32)damage / length;
    if (damage > 0) {
        zoid->health_bar_timer = 60;
    }
    if (zoid->field_1E5C != 0) {
        for (i = 0; i < 3; i++) {
            zoid->knockback[i] += scale * delta[i];
            zoid->field_1D20[i] = zoid->knockback[i];
        }
    }
    if (attacker->slot == zoid->slot && attacker->slot == Zoid[0].slot && zoid->health != 0) {
        zdVoiceScG(zoid, 14);
    }
    health = zoid->health;
    zoid->health = zoid->health - damage;
    if (zoid->health < 0) {
        zoid->health = 0;
    }
    if (zoid->health == 0 && health != 0 && attacker->slot != zoid->slot) {
        attacker->kills++;
        attacker->field_1EF0 += zoid->max_health;
        if (attacker->weapon_mount == 19) {
            attacker->field_1EF4 += zoid->max_health;
        }
    }
    damage = damage;
}
