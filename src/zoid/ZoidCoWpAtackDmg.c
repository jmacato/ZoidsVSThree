#include "zoid3.h"
#include "game_part_data.h"

typedef struct WeaponState3 {
    u8 pad_00[0xC];
    s32 type;
    u8 pad_10[0x2C];
    ZoidState *owner;
    u8 pad_40[0x3C8];
    s16 drain;
} WeaponState3;

extern f32 sLenPoint3dR(Vec3 *point);
extern s32 hitCalc(ZoidState *attacker, s32 damage, ZoidState *zoid);
extern void zdVoiceScG(ZoidState *zoid, s32 id);

void ZoidCoWpAtackDmg(WeaponState3 *weapon, void *co, ZoidState *zoid)
{
    s32 part_damage;
    f32 length;
    s32 health;
    f32 scale;
    s32 damage;
    ZoidState *owner;
    s32 i;
    Vec3 delta;

    if (weapon != (void *)0 && zoid->field_1E50 == 0) {
        owner = weapon->owner;
        zoid->rumble_timer = 15;
        for (i = 0; i < 3; i++) {
            ((f32 *)&delta)[i] = zoid->position[i] - (*(HSD_JObj **)co)->matrix[i][3];
        }
        length = sLenPoint3dR(&delta);
        if (0.0f != length) {
            for (i = 0; i < 3; i++) {
                ((f32 *)&delta)[i] = ((f32 *)&delta)[i] / length;
            }
            part_damage = Tea_partsdat[weapon->type].contact_damage;
            damage = hitCalc(owner, part_damage, zoid);
            scale = 1.0f;
            if (part_damage & 1) {
                scale = 0.2f;
            }
            if (damage > 0) {
                zoid->health_bar_timer = 60;
                for (i = 0; i < 3; i++) {
                    zoid->knockback[i] += scale * ((f32 *)&delta)[i];
                }
            }
            if (owner != 0 && owner->slot == zoid->slot && (u8)owner->slot == Zoid[0].slot && zoid->health != 0) {
                zdVoiceScG(zoid, 14);
            }
            health = zoid->health;
            zoid->health = zoid->health - damage;
            if (zoid->health < 0) {
                zoid->health = 0;
            }
            if (health != 0 && zoid->health == 0 && owner != 0 && owner->slot != zoid->slot) {
                owner->kills++;
                owner->field_1EF0 += zoid->max_health;
                if (owner->weapon_mount == 19) {
                    owner->field_1EF4 += zoid->max_health;
                }
            }
            if (owner != 0 && weapon->drain != 0 && owner->option_type == 1) {
                owner->option_energy -= 900;
                if (owner->option_energy < 0) {
                    owner->option_energy = 0;
                }
            }
        }
    }
    part_damage = part_damage;
}
