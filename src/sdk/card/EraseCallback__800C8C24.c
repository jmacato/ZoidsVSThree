#include "card_internal.h"
extern void WriteCallback(s32 chan, s32 result);

static inline CARDDir *GetDirBlock(CARDControl *card)
{
    return card->currentDir;
}

static void EraseCallback(s32 chan, s32 result)
{
    CARDControl *card;
    CARDCallback callback;
    CARDDir *dir;
    u32 addr;
    u32 offset;
    u32 block;

    card = &__CARDBlock[chan];
    if (result < 0)
        goto error;
    dir = GetDirBlock(card);
    offset = (u32)((u8 *)dir - (u8 *)card->workArea);
    block = offset / CARD_SYSTEM_BLOCK_SIZE;
    addr = card->sectorSize * block;
    result = __CARDWrite(chan, addr, CARD_SYSTEM_BLOCK_SIZE, dir, WriteCallback);
    if (result < 0)
        goto error;
    return;

error:
    if (card->apiCallback == 0)
        __CARDPutControlBlock(card, result);
    callback = card->eraseCallback;
    if (callback != 0) {
        card->eraseCallback = 0;
        callback(chan, result);
    }
}
