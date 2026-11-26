#include "zoid3.h"

typedef struct LinerNode {
    struct LinerNode *link;
    u8 reserved_04[4];
    struct LinerNode *next;
} LinerNode;

extern void ZoidLinerAnimXor(LinerNode *a, LinerNode *b, s32 c, f32 t);

void ZoidLinerAnimNextXor(LinerNode *a, LinerNode *b, s32 c, f32 t)
{
    while (a != 0 && b != 0) {
        ZoidLinerAnimXor(a, b, c, t);
        a = a->next;
        b = b->link;
    }
}
