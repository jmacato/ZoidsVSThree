#include "model_archive.h"
#include "archive.h"
#pragma readonly_strings on

extern s32 sprintf(char *, const char *, ...);
extern HSD_JObj *search_PARTS(HSD_JObj *joint, HSD_JObjDesc *description, HSD_JObjDesc *target);

HSD_JObj *searchArcJoint2(ModelArchive *archive, s32 model, char *name)
{
    char symbol[256];
    HSD_JObjDesc *description;
    HSD_JObj *result;
    if (*name == 0)
        return 0;
    if (archive == (void *)0)
        return 0;
    if (archive->model_count <= model)
        return 0;
    sprintf(symbol, "%s_%s", archive->name, name);
    description = HSD_ArchiveGetPublicAddress(archive->model_data, symbol);
    if (description == (void *)0)
        return 0;
    result = search_PARTS(archive->models[model],
                          archive->animations->models[model]->joint, description);
    return result;
}
