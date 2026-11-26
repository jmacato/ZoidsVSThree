#include "zoid3.h"
#include "joint.h"
#include "model_archive.h"

typedef struct RaderTarget3 {
    u8 pad_00[0x4E];
    s8 flag;
} RaderTarget3;

typedef struct RaderCamera3 {
    s32 pad_00;
    s32 frame;
    u8 pad_08[0x1E8 - 0x08];
    RaderTarget3 *target;
} RaderCamera3;

extern ModelArchive *dspRader;
extern s32 pause;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void s1pSearch(RaderCamera3 *camera, ZoidState *zoid, HSD_JObj *joint);
extern void s1pRaderBattle(RaderCamera3 *camera, ZoidState *zoid, HSD_JObj *joint, HSD_JObj *base);
extern void s1pRaderMap(ZoidState *zoid, HSD_JObj *joint, HSD_JObj *base);

void s1pRader(RaderCamera3 *camera, ZoidState *zoid, HSD_JObj *joint)
{
    ZoidState *other;
    s32 found;
    s32 i;
    HSD_JObj *base;

    found = 0;
    base = GetChild(joint, 0, 5, -1, -1, -1);
    s1pSearch(camera, zoid, joint);
    if (dspRader == (void *)0)
        return;
    for (i = 0; i < 16; i++) {
        other = &Zoid[i];
        if (other == zoid)
            continue;
        if (other->joint == (void *)0)
            continue;
        if (other->death_started != 0)
            continue;
        if (zoid->slot == other->slot)
            continue;
        if (zoid->distances[i] <= zoid->search_range) {
            found = 1;
            break;
        }
    }
    if (camera->frame + 1 == pause && camera->target != 0 && camera->target->flag == 0)
        found = 0;
    if (found != 0)
        s1pRaderBattle(camera, zoid, base, base);
    else
        s1pRaderMap(zoid, base, base);
}
