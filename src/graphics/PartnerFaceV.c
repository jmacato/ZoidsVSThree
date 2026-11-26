#include "types.h"

extern s32 dspPartnerMsg;
extern s32 dspPartnerMsgTm;
extern s32 dspPartnerMsgM;
extern s32 dspPartnerMsgV;

void PartnerFaceV(s32 message, s32 duration, s32 mode, s32 value)
{
    dspPartnerMsg = message;
    dspPartnerMsgTm = duration;
    dspPartnerMsgM = mode;
    dspPartnerMsgV = value;
}
