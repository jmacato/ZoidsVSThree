#include "ground_collision.h"

extern f32 sColPt01n(Vec3 *start, Vec3 *end, u16 *indices, GroundMask *mask, u16 *selector);

f32 sColPtN(Vec3 *start, Vec3 *end, GroundMask *mask, u16 *selector)
{
    u16 *start_indices;
    u16 *end_indices;
    f32 fraction;
    GroundMask start_mask;
    GroundMask end_mask;

    start_indices = sColPosTBL(start);
    end_indices = sColPosTBL(end);
    start_mask = *mask;
    fraction = sColPt01n(start, end, start_indices, &start_mask, selector);
    if (fraction != GROUND_NO_HIT)
        return fraction;
    if (start_indices == end_indices)
        return GROUND_NO_HIT;
    end_mask = *mask;
    return sColPt01n(start, end, end_indices, &end_mask, selector);
}
