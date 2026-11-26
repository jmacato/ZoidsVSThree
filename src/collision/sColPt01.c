#include "ground_collision.h"

extern f32 sColPt01n(Vec3 *start, Vec3 *end, u16 *indices, GroundMask *mask, u16 *selector);

f32 sColPt01(Vec3 *start, Vec3 *end, u16 *indices, GroundMask *mask)
{
    GroundMask mask_copy = *mask;

    return sColPt01n(start, end, indices, &mask_copy, 0);
}
