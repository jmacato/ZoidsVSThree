#include "model_archive.h"
typedef struct Lsr3 {
    HSD_JObj *source;
    f32 start[3][4];
    f32 end[3][4];
    ModelArchive *archive;
    s32 effect_value;
} Lsr3;

typedef struct TeaEffect3 {
    u8 pad_00[0x0A];
    s16 value_0A;
    u8 pad_0C[0x1A - 0x0C];
} TeaEffect3;

extern Lsr3 sLsr[11];
extern TeaEffect3 Tea_effectdat[];

void sLsrSet(HSD_JObj *source, ModelArchive *archive, s32 effect)
{
    s32 i;
    s32 r;
    s32 c;
    Lsr3 *lsr;

    if (source == (void *)0) {
        return;
    }
    if (archive == (void *)0) {
        return;
    }
    for (i = 0; i < 11; i++) {
        lsr = &sLsr[i];
        if (lsr->archive == 0) {
            lsr->source = source;
            for (r = 0; r < 3; r++) {
                for (c = 0; c < 4; c++) {
                    lsr->start[r][c] = source->matrix[r][c];
                    lsr->end[r][c] = source->matrix[r][c];
                }
            }
            lsr->archive = archive;
            lsr->effect_value = Tea_effectdat[effect].value_0A;
            return;
        }
    }
}
