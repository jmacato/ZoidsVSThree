/* Reference:
 * https://github.com/doldecomp/sms/blob/main/libs/dolphin/src/card/CARDBlock.c. */
#include "card_internal.h"
#include "os_cache.h"

extern void EraseCallback(s32 chan, s32 result);

void *__CARDGetFatBlock(CARDControl *card)
{
    return card->currentFat;
}

s32 __CARDAllocBlock(s32 chan, u32 cBlock, CARDCallback callback)
{
    CARDControl *card;
    u16 *fat;
    u16 iBlock;
    u16 startBlock;
    u16 prevBlock;
    u16 count;

    card = &__CARDBlock[chan];
    if (!card->attached)
        return CARD_RESULT_NOCARD;

    fat = __CARDGetFatBlock(card);
    if (fat[CARD_FAT_FREEBLOCKS] < cBlock)
        return CARD_RESULT_INSSPACE;

    fat[CARD_FAT_FREEBLOCKS] -= cBlock;
    startBlock = 0xFFFF;
    iBlock = fat[CARD_FAT_LASTSLOT];
    count = 0;
    while (0 < cBlock) {
        if (card->cBlock - CARD_NUM_SYSTEM_BLOCK < ++count)
            return CARD_RESULT_BROKEN;

        iBlock++;
        if (!CARDIsValidBlockNo(card, iBlock))
            iBlock = CARD_NUM_SYSTEM_BLOCK;

        if (fat[iBlock] == CARD_FAT_AVAIL) {
            if (startBlock == 0xFFFF)
                startBlock = iBlock;
            else
                fat[prevBlock] = iBlock;
            prevBlock = iBlock;
            fat[iBlock] = 0xFFFF;
            --cBlock;
        }
    }
    fat[CARD_FAT_LASTSLOT] = iBlock;
    card->startBlock = startBlock;

    return __CARDUpdateFatBlock(chan, fat, callback);
}

s32 __CARDFreeBlock(s32 chan, u16 nBlock, CARDCallback callback)
{
    CARDControl *card;
    u16 *fat;
    u16 nextBlock;
    CARDControl *c;

    c = &__CARDBlock[chan];
    card = c;
    if (!card->attached)
        return CARD_RESULT_NOCARD;

    fat = __CARDGetFatBlock(card);
    while (nBlock != 0xFFFF) {
        if (!CARDIsValidBlockNo(card, nBlock))
            return CARD_RESULT_BROKEN;

        nextBlock = fat[nBlock];
        fat[nBlock] = CARD_FAT_AVAIL;
        nBlock = nextBlock;
        ++fat[CARD_FAT_FREEBLOCKS];
    }
    return __CARDUpdateFatBlock(chan, fat, callback);
}


s32 __CARDUpdateFatBlock(s32 chan, u16 *fat, CARDCallback callback)
{
    CARDControl *card;
    u32 addr;

    card = &__CARDBlock[chan];
    ++fat[CARD_FAT_CHECKCODE];
    __CARDCheckSum(&fat[CARD_FAT_CHECKCODE], CARD_SYSTEM_BLOCK_SIZE - sizeof(u32),
                   &fat[CARD_FAT_CHECKSUM], &fat[CARD_FAT_CHECKSUMINV]);
    DCStoreRange(fat, CARD_SYSTEM_BLOCK_SIZE);
    card->eraseCallback = callback;
    addr = (((char *)fat - (char *)card->workArea) / CARD_SYSTEM_BLOCK_SIZE) * card->sectorSize;
    return __CARDEraseSector(chan, addr, EraseCallback);
}
