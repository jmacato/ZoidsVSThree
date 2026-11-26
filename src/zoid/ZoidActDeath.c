#include "zoid3.h"

extern s32 gameEndF;
extern s32 winF;
extern void OSReport(const char *format, ...);
extern void zdEffectPurge(ZoidState *zoid);
extern void ZoidInitParam(ZoidState *zoid);
extern f32 zdColPosY(f32 *position, u16 *selector);
extern void zdSetXYZ(ZoidState *zoid);
extern void sMakeMatrix(HSD_JObj *joint);
extern void ZoidCopyAnim(ZoidState *zoid);
extern void zdCoStartPos(ZoidState *zoid);
extern void ZoidSetAnim(ZoidState *zoid, s32 anim);

void ZoidActDeath(ZoidState *zoid)
{
    s32 max_health;
    s32 gene_x;
    s32 gene_z;
    s32 i;

    if (zoid == (void *)0)
        return;
    if (zoid->joint == (void *)0)
        return;
    zoid->death_pending = 1;
    if (gameEndF != 0)
        return;
    if (winF != 0)
        return;
    zoid->lock_frames++;
    if (zoid->field_20BC == 0)
        return;
    if (zoid->field_20B8 != 0)
        zoid->field_20B8--;
    if (zoid->field_20B8 != 0)
        return;
    zoid->option_use_state = 0;
    gene_x = zoid->gene_x;
    gene_z = zoid->gene_z;
    OSReport("geneX=%d geneZ=%d \n", gene_x, gene_z);
    zdEffectPurge(zoid);
    max_health = zoid->max_health;
    ZoidInitParam(zoid);
    zoid->gene_frames = 0;
    zoid->death_pending = 1;
    zoid->gene_x = gene_x;
    zoid->gene_z = gene_z;
    zoid->health = max_health;
    zoid->max_health = max_health;
    zoid->field_20B8 = zoid->field_20B4;
    zoid->field_20BC--;
    zoid->position[0] = zoid->gene_x;
    zoid->position[2] = zoid->gene_z;
    zoid->position[1] = 100.0f;
    zoid->position[1] = 1.0f + zdColPosY(zoid->position, 0);
    if (zoid->gene_y_fixed != 0)
        zoid->position[1] = zoid->gene_y;
    for (i = 0; i < 3; i++) {
        zoid->field_1A9C[i] = zoid->position[i];
        zoid->field_1C24[i] = zoid->position[i];
        zoid->field_1A80[i] = zoid->position[i];
        zoid->displacement[i] = 0.0f;
        (&zoid->knockback[0])[i] = 0.0f;
        zoid->field_1D20[i] = 0.0f;
    }
    zdSetXYZ(zoid);
    sMakeMatrix(zoid->joint);
    ZoidCopyAnim(zoid);
    zdCoStartPos(zoid);
    ZoidSetAnim(zoid, 3);
    sMakeMatrix(zoid->joint);
    zoid->position[0] = zoid->gene_x;
    zoid->position[2] = zoid->gene_z;
    zoid->position[1] = zdColPosY(zoid->position, &zoid->ground_polygon);
    if (zoid->gene_y_fixed != 0)
        zoid->position[1] = zoid->gene_y;
    zdSetXYZ(zoid);
    sMakeMatrix(zoid->joint);
    ZoidCopyAnim(zoid);
    zdCoStartPos(zoid);
    zoid->position[0] = zoid->gene_x;
    zoid->position[2] = zoid->gene_z;
    zoid->position[1] = zdColPosY(zoid->position, &zoid->ground_polygon);
    if (zoid->gene_y_fixed != 0)
        zoid->position[1] = zoid->gene_y;
    zdSetXYZ(zoid);
    zoid->action = 0x33;
}
