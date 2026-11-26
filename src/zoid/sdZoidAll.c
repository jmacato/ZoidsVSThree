#include "zoid3.h"
#include "dobj.h"
#include "gx_pixel.h"

extern s32 nowShadow;
extern ModelArchive *sdTest;
extern void sdZoidParts(ZoidState *zoid);

void sdZoidAll(void)
{
    s32 i;

    if (nowShadow == 1 && sdTest != 0 && &sdTest->models[0] != 0 && sdTest->models[0] != 0) {
        ((HSD_DObj *)sdTest->models[0]->display_object)->mobj->pe->z_comp = GX_LESS;
        for (i = 0; i < 16; i++) {
            sdZoidParts(&Zoid[i]);
        }
    }
}
