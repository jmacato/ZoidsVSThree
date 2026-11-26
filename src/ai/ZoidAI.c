#include "zoid3.h"
#include "zoid_ai.h"
#include "game_zoid_entry.h"

typedef struct GameMode3 {
    u8 reserved_00[4];
    s32 game_type;
    u8 reserved_08[0x3C];
    s32 field_44;
} GameMode3;

extern GameMode3 GameMode;
extern s32 sCamNN;
extern s32 valAiZ;
extern void chkTargetZoid(ZoidState *zoid);

void ZoidAI(void)
{
    ZoidState *zoid;
    s32 first = 1;
    s32 index;

    if (sCamNN != 1) {
        first = 2;
    }
    if (sCamNN == 4) {
        first = 4;
    }
    if (GameMode.field_44 != 0) {
        first = 0;
    }
    Zoid[0].ai_active = 0;
    Zoid[1].ai_active = 0;
    if (GameMode.game_type == 5) {
        Zoid[2].ai_active = 0;
        Zoid[3].ai_active = 0;
        first = 4;
        for (index = 0; index < 4; index++) {
            Zoid[index].ai_active = GameZoid[index].option;
        }
    }
    for (index = first; index < 16; index++) {
        zoid = &Zoid[index];
        if (zoid->joint != (void *)0 && zoid->death_started == 0) {
            zoid->ai_active = 1;
        }
    }
    if (GameMode.game_type == 5) {
        first = 0;
    }
    for (index = first; index < 16; index++) {
        zoid = &Zoid[index];
        if (zoid->joint != (void *)0 && zoid->death_started == 0 && zoid->ai_active != 0 && zoid->ai != 0) {
            valAiZ = index;
            ai(index);
        }
    }
    for (index = 0; index < first; index++) {
        zoid = &Zoid[index];
        if (zoid->joint != 0 && zoid->ai != 0 && zoid->ai_active == 0) {
            zoid->ai->mode = 0;
        }
    }
    for (index = first; index < 16; index++) {
        zoid = &Zoid[index];
        if (zoid->death_started == 0 && zoid->ai_active != 0 && zoid->ai != 0) {
            valAiZ = index;
            chkTargetZoid(zoid);
            zdExecAI(zoid);
        }
    }
}
