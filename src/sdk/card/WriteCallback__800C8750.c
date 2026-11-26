#include "card_internal.h"
#include "runtime_string.h"

static void WriteCallback(s32 chan, s32 result)
{
    CARDControl *card;
    CARDCallback callback;
    u16 *first;
    u16 *second;

    card = &__CARDBlock[chan];
    if (result >= 0) {
        first = (u16 *)((u8 *)card->workArea + 3 * CARD_SYSTEM_BLOCK_SIZE);
        second = (u16 *)((u8 *)card->workArea + 4 * CARD_SYSTEM_BLOCK_SIZE);
        if (card->currentFat == first) {
            card->currentFat = second;
            memcpy(second, first, CARD_SYSTEM_BLOCK_SIZE);
        } else {
            card->currentFat = first;
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
