#include "zoid3.h"

extern void zdOptionUse3(ZoidState *zoid);
extern void zdOptionUse4(ZoidState *zoid);
extern void zdOptionUse5(ZoidState *zoid);

void zdOptionUse(ZoidState *zoid)
{
    if (zoid->option_type == ZOID_OPTION_CAMOUFLAGE)
        zdOptionUse3(zoid);
    if (zoid->option_type == ZOID_OPTION_SMOKE)
        zdOptionUse4(zoid);
    if (zoid->option_type == ZOID_OPTION_MINE)
        zdOptionUse5(zoid);
}
