#include "types.h"

extern void PartnerFaceV(s32 message, s32 duration, s32 mode, s32 value);

void PartnerFace(s32 message, s32 duration)
{
    PartnerFaceV(message, duration, -1, -1);
}
