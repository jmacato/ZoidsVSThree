#include "zoid.h"

extern s32 ZoidInit_(ZoidState *zoid, s32 type, s32 flags);

s32 ZoidInit(ZoidState *zoid, s32 type)
{
    return ZoidInit_(zoid, type, 0);
}
