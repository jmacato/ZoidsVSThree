#include "zoid3.h"
#include "model_archive.h"

typedef struct PadState3 {
    u8 reserved_00[0x42];
    s8 field_42;
    u8 reserved_43[5];
    s8 field_48;
    u8 reserved_49[5];
    s8 field_4E;
    u8 reserved_4F[8];
    s8 field_57;
    s8 field_58;
    u8 reserved_59[4];
    s8 pressed_a;
    s8 pressed_b;
    u8 reserved_5F[0x29];
} PadState3;

typedef struct GameModeState3 {
    u8 reserved_00[4];
    s32 game_type;
    u8 reserved_08[4];
    s32 field_0C;
} GameModeState3;

extern GameModeState3 GameMode;
extern ModelArchive *dspPause;
extern s32 pBak;
extern s32 pause;
extern volatile s32 menuRet;
extern s32 gameTime;
extern s32 sCamNN;
extern PadState3 *sPad1, *sPad2;
extern PadState3 sPad[];
extern s32 jobjAnim(HSD_JObj *joint);
extern void SeOn(s32 id);

void sDispPauseProc(void)
{
    HSD_JObj *root;
    HSD_JObj *cursor;
    HSD_JObj *select;
    HSD_JObj *extra;
    PadState3 *pad;
    s32 index;
    s32 slot;
    s32 i;
    ZoidState *target;

    if (dspPause != 0) {
        root = dspPause->models[0];
        cursor = dspPause->models[7];
        select = dspPause->models[8];
        extra = dspPause->models[9];
        if (root != 0) {
            if (pBak != pause) {
                SetAnimArc2(dspPause, 0, 0);
                if (cursor != 0)
                    SetAnimArc2(dspPause, 7, 0);
                if (select != 0)
                    SetAnimArc2(dspPause, 8, 0);
                jobjAnim(root);
                pBak = pause;
                menuRet = 0;
            }
            pad = sPad1;
            if (pause == 2)
                pad = sPad2;
            if (pause != 0)
                pad = &sPad[pause - 1];
            if (pad->field_4E == 0) {
                if (pad->field_58 != 0 || pad->field_57 != 0) {
                    menuRet = 1 - menuRet;
                    SeOn(0x71);
                }
                if (pad->field_48 != 0 && pad->field_42 == 0) {
                    index = -1;
                    if (menuRet == 1) {
                        if (GameMode.game_type == 2) {
                            if (pause != 0)
                                index = pause - 1;
                        } else {
                            index = 0;
                        }
                        if (pause != 0)
                            index = pause - 1;
                        gameTime = 0;
                        if (index != -1) {
                            GameMode.field_0C = index;
                            Zoid[index].field_0148 = 1;
                            Zoid[index].health = 0;
                            Zoid[index].knockback[0] = 3.0f;
                            Zoid[index].knockback[1] = 0.0f;
                            Zoid[index].knockback[2] = 0.0f;
                            Zoid[index].requested_action = 0x22;
                            if (sCamNN == 4) {
                                slot = Zoid[index].slot;
                                for (i = 0; i < 16; i++) {
                                    target = &Zoid[i];
                                    if (target->joint != 0 && target->slot == slot && target->death_started == 0 && target->health != 0) {
                                        target->health = 0;
                                        target->knockback[0] = 3.0f;
                                        target->knockback[1] = 0.0f;
                                        target->knockback[2] = 0.0f;
                                        target->requested_action = 0x22;
                                    }
                                }
                            }
                        }
                    }
                    pause = 0;
                    pad->pressed_a = 0;
                    SeOn(0x10);
                }
                if (pad->pressed_b != 0 && pause != 0) {
                    pause = 0;
                    SeOn(0x6c);
                }
            }
        }
    }
}
