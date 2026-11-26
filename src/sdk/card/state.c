/* Reference:
 * https://github.com/doldecomp/sms/blob/main/libs/dolphin/src/card/CARDDir.c. */
#include "card_internal.h"

extern void DCStoreRange(void *address, u32 length);
extern void EraseCallback(s32 chan, s32 result);

CARDDir *__CARDGetDirBlock(CARDControl *card)
{
    return card->currentDir;
}

s32 CARDGetXferredBytes(s32 chan)
{
    return __CARDBlock[chan].xferred;
}

s32 __CARDUpdateDir(s32 chan, CARDCallback callback)
{
    CARDControl *card;
    CARDDirCheck *check;
    u32 addr;
    u32 offset;
    u32 block;
    CARDDir *dir;

    card = &__CARDBlock[chan];
    if (!card->attached)
        return CARD_RESULT_NOCARD;
    dir = __CARDGetDirBlock(card);
    check = CARDGetDirCheck(dir);
    ++check->checkCode;
    __CARDCheckSum(dir, CARD_SYSTEM_BLOCK_SIZE - sizeof(u32), &check->checkSum,
                   &check->checkSumInv);
    DCStoreRange(dir, CARD_SYSTEM_BLOCK_SIZE);
    card->eraseCallback = callback;
    offset = (u32)dir - (u32)card->workArea;
    block = offset / CARD_SYSTEM_BLOCK_SIZE;
    addr = card->sectorSize * block;
    return __CARDEraseSector(chan, addr, EraseCallback);
}
