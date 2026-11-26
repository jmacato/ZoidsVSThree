#include "zoid3.h"
#include "model_archive.h"

extern ModelArchive *steFile;
extern struct HSD_MObj *steMobj;
extern ModelArchive *sdTest;
extern void ZeroMemory(void *address, u32 size);
extern struct HSD_MObj *searchMObj(HSD_JObj *joint);

void ZoidPrologue(void)
{
    s32 i;

    for (i = 0; i < 16; i++) {
        ZeroMemory(&Zoid[i], sizeof(ZoidState));
        Zoid[i].index = i;
    }
    steMobj = 0;
    if (steFile == (void *)0) {
        steFile = LoadArc2("zoid/stels_mat.dat");
        if (steFile != 0) {
            steMobj = searchMObj(steFile->models[0]);
        }
    }
    sdTest = LoadArc2("debug/c_.dat");
}
