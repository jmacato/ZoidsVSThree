#include "types.h"

extern void sMissilePrologueU(s32 mode);

void sMissilePrologue(void)
{
    sMissilePrologueU(0);
}
