#include "types.h"

typedef struct AiData3 {
    u8 b[0xF0];
} AiData3;

extern AiData3 aiDat[];

extern s32 printf(const char *format, ...);

void DEV_EXPRINT(char *str, s32 index)
{
    if (index == 1) {
        printf("%d : %d : ", index, *(s16 *)&aiDat[index].b[0xD0]);
        printf(str);
    }
}
