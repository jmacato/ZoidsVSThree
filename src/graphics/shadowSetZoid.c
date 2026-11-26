#include "zoid3.h"

extern void HSD_ShadowDeleteObject(void *shadow, HSD_JObj *jobj);
extern void ZoidShadowLo(void *shadow, ZoidState *zoid);

void shadowSetZoid(void *shadow, s32 index)
{
    s32 i;

    if (shadow != 0) {
        HSD_ShadowDeleteObject(shadow, 0);
        ZoidShadowLo(shadow, &Zoid[index]);
        for (i = 0; i < 16; i++) {
            if (i != index && Zoid[index].joint != (void *)0 && !(Zoid[index].distances[i] > 100.0f)) {
                ZoidShadowLo(shadow, &Zoid[i]);
            }
        }
    }
}
