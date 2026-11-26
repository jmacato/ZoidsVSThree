#include "zoid.h"

extern f32 sMisZdAng(ZoidState *zoid, f32 *angle);

f32 sMisZd(ZoidState *zoid)
{
    return sMisZdAng(zoid, 0);
}
