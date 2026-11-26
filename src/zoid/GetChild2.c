#include "model_archive.h"
#include "jobj.h"

extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth,
                          s32 fifth);

HSD_JObj *GetChild2(ModelArchive *archive, s32 model, s32 second, s32 third, s32 fourth,
                    s32 fifth)
{
    if (archive == 0)
        return 0;
    if (archive->model_count <= model)
        return 0;
    if (archive->models[model] == 0)
        return 0;
    return GetChild(archive->models[model], 0, second, third, fourth, fifth);
}
