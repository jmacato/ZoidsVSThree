#include "zoid3.h"
#pragma readonly_strings on

extern void dummyFunc(const char *);

void zdZuri(ZoidState *zoid)
{
    f64 tmp;
    dummyFunc("Zuri>");
    if (zoid->field_1C90[2] > 0.1) {
        return;
    }
    if (zoid->field_1C90[2] > -0.1) {
        return;
    }
}
