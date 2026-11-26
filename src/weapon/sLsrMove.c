#include "types.h"
#include "joint.h"
#include "joint_matrix.h"

typedef struct Lsr3 {
    HSD_JObj *source;
    f32 start[3][4];
    f32 end[3][4];
    void *archive;
    s32 effect;
} Lsr3;

typedef struct Lsr1_3 {
    f32 start[3][4];
    f32 end[3][4];
    HSD_JObj *joint;
    HSD_JObj *start_joint;
    HSD_JObj *end_joint;
} Lsr1_3;

extern Lsr3 sLsr[11];
extern Lsr1_3 sLsr1[400];
extern void sLsr1Set(Lsr3 *lsr);
extern void sLsr1Purge(Lsr1_3 *beam);
extern void HSD_JObjAnimAll(HSD_JObj *joint);
extern s32 getEndF(HSD_JObj *joint);
extern void PSMTXCopy(f32 src[3][4], f32 dst[3][4]);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);

static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & 0x00800000) && (jobj->flags & 0x40);
}

#define HSD_JObjSetMtxDirty(jobj) \
    do { \
        if ((jobj) != 0 && !HSD_JObjMtxIsDirty(jobj)) \
            HSD_JObjSetMtxDirtySub(jobj); \
    } while (0)

static inline void HSD_JObjCopyMtx(HSD_JObj *jobj, f32 mtx[3][4])
{
    jobj ? (void)0 : __assert("jobj.h", 1173, "jobj");
    mtx ? (void)0 : __assert("jobj.h", 1174, "mtx");
    PSMTXCopy(mtx, jobj->matrix);
    jobj->flags |= 0x03800000;
    HSD_JObjSetMtxDirty(jobj);
}

void sLsrMove(void)
{
    s32 i;
    s32 r;
    s32 c;
    Lsr3 *lsr;
    Lsr1_3 *beam;

    for (i = 0; i < 11; i++) {
        lsr = &sLsr[i];
        if (lsr->archive != (void *)0) {
            if (lsr->effect == 0) {
                lsr->archive = 0;
            } else {
                lsr->effect--;
                for (r = 0; r < 3; r++) {
                    for (c = 0; c < 4; c++) {
                        lsr->end[r][c] = lsr->start[r][c];
                        lsr->start[r][c] = lsr->source->matrix[r][c];
                    }
                }
                sLsr1Set(lsr);
            }
        }
    }
    for (i = 0; i < 400; i++) {
        beam = &sLsr1[i];
        if (beam->joint != (void *)0) {
            HSD_JObjAnimAll(beam->joint);
            if (getEndF(beam->joint) != 0) {
                sLsr1Purge(beam);
            } else {
                HSD_JObjCopyMtx(beam->joint, beam->start);
                HSD_JObjCopyMtx(beam->start_joint, beam->start);
                HSD_JObjCopyMtx(beam->end_joint, beam->end);
            }
        }
    }
}
