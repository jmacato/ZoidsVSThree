#include "types.h"

typedef struct Lsr3 {
    u8 reserved_00[0x6C];
} Lsr3;

typedef struct Lsr1_3 {
    u8 reserved_00[0x6C];
} Lsr1_3;

extern Lsr3 sLsr[11];
extern Lsr1_3 sLsr1[400];
extern void ZeroMemory(void *address, u32 size);

void sLsrPrologue(void)
{
    ZeroMemory(sLsr, sizeof(sLsr));
    ZeroMemory(sLsr1, sizeof(sLsr1));
}
