#include "zoid3.h"

extern s32 sColPosTBL(f32 *pos);

s32 zdColPosTBL(ZoidState *zoid)
{
    f32 pos[3];
    s32 i;

    if (zoid == 0) {
        return 0;
    } else {
        for (i = 0; i < 3; i++) {
            pos[i] = *(f32 *)((u8 *)zoid + 0x50 + i * 16);
        }
        return sColPosTBL(pos);
    }
}
