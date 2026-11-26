#include "ground_collision.h"

f32 zdColPosY(Vec3 *point, u16 *selector)
{
    GroundMask mask = (GroundMask){{7, 0, 0, 0}};
    return sColPosAndY(point, selector, &mask);
}
