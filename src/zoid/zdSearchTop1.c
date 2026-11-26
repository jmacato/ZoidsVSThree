#include "zoid3.h"

void zdSearchTop1(f32 *top, ZoidState *zoid)
{
    if (zoid == 0) return;
    if (top == 0) return;
    if (zoid->field_0060 > *top) {
        *top = zoid->field_0060;
    }
}
