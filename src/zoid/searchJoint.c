#pragma readonly_strings on
#include "zoid3.h"
#include "zoid_collision.h"

extern s32 sprintf(char *buffer, const char *format, ...);
extern void OSReport(const char *format, ...);
extern void *HSD_ArchiveGetPublicAddress(struct HSD_Archive *archive, const char *name);
extern HSD_JObj *search_PARTS(HSD_JObj *joint, HSD_JObjDesc *description, HSD_JObjDesc *target);

#pragma auto_inline off
HSD_JObj *searchJoint(ZoidState *zoid, const char *part)
{
    char name[256];
    HSD_JObjDesc *description;
    HSD_JObjDesc *root;

    if (*part == 0)
        return 0;
    sprintf(name, "%s_%s", zoid->name, part);
    description = HSD_ArchiveGetPublicAddress(zoid->archive, name);
    if (description == (void *)0) {
        OSReport("joint error [%s] \n ============", name);
        return 0;
    }
    root = zoid->animations->models[0]->joint;
    return search_PARTS(zoid->joint, root, description);
}
