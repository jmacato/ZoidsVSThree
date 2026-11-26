#pragma readonly_strings on
#include "zoid3.h"
#include "ground_collision.h"

typedef struct GameMode3 {
    s32 reserved_00;
    s32 game_type;
    u8 reserved_08[0x48];
} GameMode3;

extern GameMode3 GameMode;
extern s32 sCamNN;
extern s32 gameEndF;
extern s32 sprintf(char *dst, const char *format, ...);
extern void dummyFunc(const char *text);
extern void sZoidTarget(ZoidState *zoid);
extern void angLimit(f32 *angle);
extern void zdCalcRot(ZoidState *zoid);
extern void calcAngA(ZoidState *zoid);
extern void ZoidMove(ZoidState *zoid);
extern void sColGetPolygonCenter(u16 polygon, f32 *center);
extern void sLinear1D(f32 *value, f32 target, f32 step);
extern f32 zdColPosY(f32 *point, u16 *selector);
extern void zdLinier(ZoidState *zoid);
extern void zdSetXYZ(ZoidState *zoid);
extern void sMakeMatrix(HSD_JObj *joint);
extern void zdFootBak(ZoidState *zoid);
extern void zdGroundPolyClear(ZoidState *zoid);
extern void ZoidDownBody(ZoidState *zoid);
extern void ZoidGround(ZoidState *zoid);
extern void ZoidSpdA(ZoidState *zoid);
extern void ZoidCoBAK(ZoidState *zoid, u8 *object);
extern void ZoidGrdON(ZoidState *zoid);
extern void ZoidCount(ZoidState *zoid);
extern void zdCalcCoDmg(ZoidState *zoid);
extern void zdEffectMountInt(ZoidState *zoid);
extern void zdCoObjSpark(ZoidState *zoid);
extern void zdVoiceSc(ZoidState *zoid, s32 voice);
extern void zdVoiceScG(ZoidState *zoid, s32 voice);
extern void PartnerFace(s32 face, s32 frames);

void ZoidAllMove(void)
{
    ZoidState *zoid;
    s32 n;
    s32 m;
    s32 k;
    s32 j;
    s32 p;
    s32 i;
    ZoidState *partner;
    s32 best;
    s32 count;
    f32 dead;
    f32 after;
    f32 before;
    u16 selector2;
    char text[256];
    u16 selector;
    f32 center[3];

    for (i = 0; i < 16; i++) {
        sprintf(text, "\n[Z%02d]", i);
        dummyFunc(text);
        zoid = &Zoid[i];
        if (zoid->joint == 0)
            continue;
        sZoidTarget(zoid);
        if (zoid->rumble_timer != 0)
            zoid->rumble_timer--;
        if (zoid->field_1E50 != 0)
            zoid->field_1E50--;
        if (zoid->health_bar_timer != 0)
            zoid->health_bar_timer--;
        dummyFunc("G");
        angLimit(&zoid->heading);
        dummyFunc("R");
        zdCalcRot(zoid);
        angLimit(&zoid->heading);
        dummyFunc("M");
        calcAngA(zoid);
        dummyFunc("A");
        ZoidMove(zoid);
        dummyFunc("o");
        if (zoid->field_0170 == 0 && zoid->field_1EB8 == GROUND_POLYGON_NONE && zoid->action == 0
            && zoid->field_1DF4 == 0) {
            for (j = 0; j < 3; j++)
                zoid->position[j] = zoid->previous_position[j];
            sColPosY((Vec3 *)zoid->position, &selector);
            if (zoid->field_1EBA != GROUND_POLYGON_NONE) {
                sColGetPolygonCenter(zoid->field_1EBA, center);
                sLinear1D(&zoid->position[0], center[0], 0.1f);
                sLinear1D(&zoid->position[2], center[2], 0.1f);
            }
        } else if (zoid->ground_polygon != GROUND_POLYGON_NONE) {
            zoid->field_1EBA = zoid->ground_polygon;
        }
        zdColPosY(zoid->position, &selector2);
        if (selector2 != GROUND_POLYGON_NONE) {
            zoid->field_1EB8 = selector2;
            for (k = 0; k < 3; k++)
                zoid->previous_position[k] = zoid->position[k];
        } else if (zoid->field_1EB8 != GROUND_POLYGON_NONE) {
            for (k = 0; k < 3; k++)
                zoid->position[k] = zoid->previous_position[k];
        }
        dummyFunc("L");
        zdLinier(zoid);
        zdSetXYZ(zoid);
        sMakeMatrix(zoid->joint);
        zdFootBak(zoid);
        dummyFunc("D");
        zdGroundPolyClear(zoid);
        if (zoid->action != 0x33) {
            if (zoid->death_pending != 0)
                ZoidDownBody(zoid);
            if (zoid->death_pending == 0)
                ZoidGround(zoid);
        }
        dummyFunc("A");
        angLimit(&zoid->heading);
        zoid->previous_animation = zoid->current_animation;
        zoid->field_1C9C = zoid->field_1C90[0];
        zoid->field_19FC = zoid->position[1] - zoid->field_1C24[1];
        for (m = 0; m < 4; m++) {
            for (n = 0; n < 3; n++)
                zoid->child_matrix[n][m] = zoid->joint->child->matrix[n][m];
        }
        zoid->field_1A40[0] = zoid->joint->child->translation.x;
        zoid->field_1A40[1] = zoid->joint->child->translation.y;
        zoid->field_1A40[2] = zoid->joint->child->translation.z;
        zoid->heading_delta = zoid->joint->child->rotation[1];
        if (*(HSD_JObj **)&zoid->field_1A7C != 0) {
            for (p = 0; p < 3; p++)
                zoid->field_1A8C[p] = zoid->field_1A7C->matrix[p][3];
        }
        dummyFunc("s");
        ZoidSpdA(zoid);
        dummyFunc("b");
        ZoidCoBAK(zoid, zoid->body_coobj);
        ZoidCoBAK(zoid, zoid->head_coobj);
        ZoidCoBAK(zoid, zoid->neck_coobj);
        ZoidCoBAK(zoid, zoid->bust_coobj);
        ZoidCoBAK(zoid, zoid->hip_coobj);
        ZoidCoBAK(zoid, zoid->tail_coobjs[0]);
        ZoidCoBAK(zoid, zoid->l_arm1_coobj);
        ZoidCoBAK(zoid, zoid->r_arm1_coobj);
        ZoidCoBAK(zoid, zoid->l_leg1_coobj);
        ZoidCoBAK(zoid, zoid->r_leg1_coobj);
        ZoidCoBAK(zoid, zoid->l_arm2_coobj);
        ZoidCoBAK(zoid, zoid->r_arm2_coobj);
        ZoidCoBAK(zoid, zoid->l_leg2_coobj);
        ZoidCoBAK(zoid, zoid->r_leg2_coobj);
        dummyFunc("g ");
        ZoidGrdON(zoid);
        dummyFunc("c\n");
        ZoidCount(zoid);
        dummyFunc("d\n");
        for (k = 0; k < 3; k++) {
            dead = 1.0f / 600.0f;
            sLinear1D(&zoid->knockback[k], 0.0f, dead);
        }
        zdCalcCoDmg(zoid);
        dummyFunc("E");
        zdEffectMountInt(zoid);
        zdCoObjSpark(zoid);
        dummyFunc(" .z\n");
        zoid->field_1C14 = 0;
    }
    dummyFunc("ZM.pt-----------------\n");
    zoid = Zoid;
    partner = &Zoid[2];
    if (zoid->joint != 0 && partner->joint != 0 && sCamNN == 1 && zoid->slot == partner->slot && gameEndF == 0
        && GameMode.game_type == 1) {
        if (partner->max_health == 0)
            partner->max_health = 100;
        before = (f32)partner->field_0150 / (f32)partner->max_health;
        after = (f32)partner->health / (f32)partner->max_health;
        if (before >= 0.5 && after < 0.5) {
            zdVoiceScG(partner, 12);
            PartnerFace(4, 60);
        }
        if (partner->field_0150 != 0 && partner->health == 0 && zoid->health != 0)
            zdVoiceSc(partner, 15);
        if (zoid->field_0150 != 0 && zoid->health == 0 && partner->health != 0)
            zdVoiceSc(zoid, 9);
    }
    dummyFunc("En\n");
    if (GameMode.game_type == 1 || GameMode.game_type == 4) {
        i = 0;
        count = 0;
        best = -1;
        for (; i < 16; i++) {
            zoid = &Zoid[i];
            if (zoid->joint != 0 && zoid->slot != Zoid[0].slot) {
                if (zoid->health == 0 && zoid->field_0150 != 0)
                    best = i;
                if (zoid->health != 0)
                    count++;
            }
        }
        if (best != -1)
            zdVoiceSc(&Zoid[best], 8);
    }
    for (i = 0; i < 16; i++) {
        zoid = &Zoid[i];
        if (zoid->joint != 0)
            zoid->field_0150 = zoid->health;
    }
}
