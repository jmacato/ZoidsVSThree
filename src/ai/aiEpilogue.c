#include "types.h"

typedef struct AiData3 {
    u8 bytes[0xF0];
} AiData3;

extern AiData3 aiDat[16];
extern void ZeroMemory(void *address, u32 size);

void aiEpilogue(s32 index)
{
    ZeroMemory(&aiDat[index], sizeof(AiData3));
}
