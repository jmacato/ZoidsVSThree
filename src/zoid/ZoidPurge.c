#pragma readonly_strings on
#include "zoid3.h"

extern void OSReport(const char *format, ...);
extern void sWeaponUnMountAll(ZoidState *zoid);
extern void ZoidCopyMatReset(ZoidState *zoid);
extern void stStJobjUnref(JointPose *pose);
extern void jobjUnrefAll(HSD_JObj *joint);
extern void free(void *memory);
extern void sArchivePurge(struct HSD_Archive *archive);
extern void ZeroMemory(void *dst, u32 size);

void ZoidPurge(ZoidState *zoid)
{
    s32 i;

    if (zoid == (void *)0)
        return;
    if (zoid->name[0] == 0)
        return;
    OSReport("zoid purge! [%s] \n", zoid);
    zoid->field_1E9A = 0;
    sWeaponUnMountAll(zoid);
    ZoidCopyMatReset(zoid);
    if (zoid->pose != 0) {
        stStJobjUnref(zoid->pose);
        zoid->pose = 0;
    }
    if (zoid->field_0038 != 0) {
        PurgeArc2(zoid->field_0038);
        zoid->field_0038 = 0;
    }
    if (zoid->joint != 0) {
        jobjUnrefAll(zoid->joint);
        zoid->joint = 0;
    }
    if (zoid->ai != 0) {
        free(zoid->ai);
        zoid->ai = 0;
    }
    if (zoid->anim_data != 0) {
        free(zoid->anim_data);
        zoid->anim_data = 0;
    }
    if (zoid->slider_info != 0) {
        free(zoid->slider_info);
        zoid->slider_info = 0;
    }
    if (zoid->field_2090 != 0) {
        free(zoid->field_2090);
        zoid->field_2090 = 0;
    }
    if (zoid->archive != 0) {
        sArchivePurge(zoid->archive);
        zoid->archive = 0;
    }
    if (zoid->field_0028 != 0) {
        free(zoid->field_0028);
    }
    zoid->field_0028 = 0;
    if (zoid->field_003C != 0) {
        free(zoid->field_003C);
    }
    zoid->field_003C = 0;
    ZeroMemory(zoid, sizeof(ZoidState));
    for (i = 0; i < 16; i++) {
        if (zoid == &Zoid[i]) {
            zoid->index = i;
        }
    }
}
