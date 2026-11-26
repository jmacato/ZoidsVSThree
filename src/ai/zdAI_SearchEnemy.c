#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);

s32 zdAI_SearchEnemy(s32 index)
{
    ZoidState *zoid;
    s32 j;
    s32 *list;
    s32 i;
    ZoidState *other;
    s32 a;
    s32 b;

    aiCmdReport("aiCmd-searchEnemy \n");
    if (index < 0) {
        return -1;
    }
    if (index >= 16) {
        return -1;
    }
    zoid = &Zoid[index];
    if (zoid->joint == (void *)0) {
        return -1;
    }
    list = zoid->ai->nearest_enemies;
    if (list == 0) {
        return -1;
    }
    for (i = 0; i < 16; i++) {
        list[i] = -1;
    }
    for (i = 0, j = 0; i < 16; i++) {
        other = &Zoid[i];
        if (other->joint != (void *)0 && zoid != other && zoid->slot != other->slot && zoid->target_visibility[i] != 0) {
            list[j] = i;
            j++;
        }
    }
    for (i = 0; i < 16; i++) {
        a = list[i];
        if (a != -1) {
            for (j = i; j < 16; j++) {
                b = list[j];
                if (b != -1 && j != i) {
                    if (zoid->distances[a] < zoid->distances[b]) {
                    } else {
                        list[i] = b;
                        list[j] = a;
                        a = b;
                    }
                }
            }
        }
    }
    return list[0];
}
