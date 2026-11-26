#include "card_internal.h"
#include "runtime_string.h"

static void WriteCallback(s32 chan, s32 result)
{
    CARDControl *card = &__CARDBlock[chan];
    CARDCallback callback;

    if (result >= 0) {
        CARDDir *first = (CARDDir *)((u8 *)card->workArea + 1 * CARD_SYSTEM_BLOCK_SIZE);
        CARDDir *second = (CARDDir *)((u8 *)card->workArea + 2 * CARD_SYSTEM_BLOCK_SIZE);
        if (card->currentDir == first) {
            card->currentDir = second;
            memcpy(second, first, CARD_SYSTEM_BLOCK_SIZE);
        } else {
            card->currentDir = first;
            memcpy(first, second, CARD_SYSTEM_BLOCK_SIZE);
        }
    }
    if (card->apiCallback == 0)
        __CARDPutControlBlock(card, result);
    callback = card->eraseCallback;
    if (callback != 0) {
        card->eraseCallback = 0;
        callback(chan, result);
    }
}
