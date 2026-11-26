#include "zoid3.h"

typedef struct AnimTablesVS3 {
    s32 pad_0000;
    s32 *table_a;
    s32 *table_b;
    s32 *table_c;
} AnimTablesVS3;

typedef struct AnimRefVS3 {
    AnimTablesVS3 *tables;
} AnimRefVS3;

typedef struct AnimLinkVS3 {
    AnimRefVS3 *ref;
} AnimLinkVS3;

typedef struct AnimSetVS3 {
    u8 pad_0000[0x24];
    AnimLinkVS3 *link;
} AnimSetVS3;

extern void zdHSD_JObjAddAnimAll2s(HSD_JObj *joint, JointPose *pose, s32 index, s32 a, s32 b, s32 c);

void sAddAnimAllXor2ANIM(ZoidState *zoid, s32 index)
{
    AnimLinkVS3 *link;
    s32 *table_a;
    s32 *table_b;
    s32 *table_c;
    AnimSetVS3 *set;

    if (zoid == (void *)0) {
        return;
    }
    if (zoid->joint == (void *)0) {
        return;
    }
    set = (AnimSetVS3 *)zoid->field_0038;
    if (set == 0) {
        return;
    }
    link = set->link;
    if (link == (void *)0) {
        return;
    }
    table_a = link->ref->tables->table_a;
    table_b = link->ref->tables->table_b;
    table_c = link->ref->tables->table_c;
    if (index > 0x65) {
        index = 0;
    }
    zdHSD_JObjAddAnimAll2s(zoid->joint, zoid->pose, index,
                           table_a != 0 ? table_a[index] : 0,
                           table_b != 0 ? table_b[index] : 0,
                           table_c != 0 ? table_c[index] : 0);
}
