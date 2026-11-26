#include "zoid3.h"

void ZoidCount(ZoidState *zoid)
{
    if (zoid == 0) {
        return;
    }
    if (zoid->field_1C4C != 0) {
        zoid->field_1C4C--;
    }
    if (zoid->field_1DFC != 0) {
        zoid->field_1DFC--;
    }
    if (zoid->field_1CB8 != 0) {
        zoid->field_1CB8--;
    }
    if (zoid->field_1CCC != 0) {
        zoid->field_1CCC--;
    }
}
