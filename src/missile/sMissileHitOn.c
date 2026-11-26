#include "types.h"

extern void sHitOn(void *missile);

void sMissileHitOn(void *missile)
{
    sHitOn(missile);
}
