extern "C" {
#pragma readonly_strings on
#pragma dont_inline on
#pragma bool off
#include "types.h"

typedef struct GameMode3 {
    s32 f00;
    s32 game_type;
    s32 f08;
    s32 f0C;
} GameMode3;
typedef struct MapInfo3 {
    u8 pad_0000[0x3248];
    s32 f3248;
    s32 f324C;
    u8 pad_3250[0xB0];
} MapInfo3;
extern GameMode3 GameMode;
extern s32 strcmp(const char *a, const char *b);
extern char *strcpy(char *dst, const void *src);
extern u32 strlen(const char *s);
extern s32 sprintf(char *buf, const char *fmt, ...);
extern void OSReport(const char *fmt, ...);
extern void ZeroMemory(void *p, u32 size);
extern void MemCpy(void *src, void *dst, u32 size);
extern void *sReadFileLenU(char *name, s32 mode, s32 *length);
extern void *sReadFileU(char *name, s32 mode);
extern void free(void *p);
extern void *malloc2(u32 size);
extern void *mallocSys(u32 size);
extern void mgSearchEnemy(void *mg);
extern void debug11(void);
extern void dspLoadNow(void);
extern s32 DVDOpen(char *name, void *info);
extern s32 DVDClose(void *info);
extern s32 fReadO2(void *file, void *mem, s32 len, s32 off);
extern s32 fReadO(void *file, void *mem, s32 len);
typedef struct DVDFileInfo3 {
    u8 pad_00[0x34];
    s32 length;
    u8 pad_38[8];
} DVDFileInfo3;
extern s32 fexist(char *name);
extern void *HSD_ArchiveParse(void *arc, void *data, u32 size);
extern void *sReadFileLen(char *name, s32 *size);
typedef struct ImageDesc3 {
    void *image;
    u16 width;
    u16 height;
    s32 format;
} ImageDesc3;
typedef struct TObj3 {
    u8 pad_00[0x58];
    ImageDesc3 *imagedesc;
} TObj3;
extern void putErr(const char *msg);
extern TObj3 *searchTObj(void *jobj);
extern s32 calc_doltexture_size(s32 format, s32 w, s32 h);
extern s32 SetTex2(void *data, void *dest, s32 size);
typedef struct ModelAnimation {
    void *joint;
    void **joint_animations;
    void **material_animations;
    void **shape_animations;
} ModelAnimation;
typedef struct ModelAnimationTable {
    ModelAnimation **models;
    void **camera;
    void **lights;
    void **fog;
} ModelAnimationTable;
typedef struct ModelArchive {
    char name[0x20];
    void *model_data;
    ModelAnimationTable *animations;
    void *owned_data;
    void *camera;
    void *lights;
    void *fog;
    s32 model_count;
    void *models[1];
} ModelArchive;
extern void *sLoad(char *name, void **data);
extern void *LoadArcLight(ModelArchive *archive);
extern void *HSD_CObjLoadDesc(void *desc);
extern void *HSD_FogLoadDesc(void *desc);
extern void *HSD_JObjLoadJoint(void *desc);
extern void HSD_JObjAddAnimAll(void *jobj, void *a, void *b, void *c);
extern void HSD_JObjReqAnimAll(void *jobj, f32 frame);
extern void HSD_ArchiveLoadDepends(void *arc, void *a, void *b, void *c);
extern void HSD_ArchiveResolveReference(void *arc, void *a);
extern ModelAnimationTable *HSD_ArchiveGetPublicAddress(void *arc, const char *name);
extern void sMakeMatrix(void *jobj);
extern void setAnimRate(void *jobj, f32 rate);
extern void Str2Lows(char *s);
extern void sArchivePurge(void *arc);
extern void *TEA_USBFileArchiveLoad(char *name, void **data);
extern s32 fexistU(char *name, s32 usb);
extern void *sArchiveMem(void *mem, s32 size);
typedef struct ClassInfo3 {
    u8 pad_00[0x30];
    void (*release)(void *obj);
    void (*destroy)(void *obj);
} ClassInfo3;
typedef struct HSD_Obj3 {
    ClassInfo3 *class_info;
    u16 reference_count;
} HSD_Obj3;
extern void HSD_LObjRemoveAll(void *lobj);
extern void HSD_JObjRemoveAnimAll(void *jobj);
extern void HSD_JObjUnref(void *jobj);
#pragma dont_inline off
static inline s32 decrement_reference(HSD_Obj3 *object)
{
    s32 result;
    if ((result = (object->reference_count == (u16)-1)))
        return result;
    result = object->reference_count == 0;
    object->reference_count--;
    return result;
}
static inline void delete_object(void *object)
{
    if (object != 0) {
        ((HSD_Obj3 *)object)->class_info->release(object);
        ((HSD_Obj3 *)object)->class_info->destroy(object);
    }
}
static inline void unreference_object(void *object)
{
    if (object != 0 && decrement_reference((HSD_Obj3 *)object))
        delete_object(object);
}
#pragma dont_inline on
typedef struct LoadColor { u8 r, g, b, a; } LoadColor;
typedef struct LoadVIInfo { u8 pad[0x48]; LoadColor clear_clr; } LoadVIInfo;
extern LoadVIInfo HSD_VIData;
extern ModelArchive *dspLoad;
extern void HSD_StateInvalidate(s32 state);
extern void HSD_SetZSortMode(s32 a, s32 b);
extern void GXSetCullMode(s32 mode);
extern void HSD_FogSet(void *fog);
extern void VIWaitForRetrace(void);
extern u32 VIGetRetraceCount(void);
extern s32 HSD_CObjSetCurrent(void *cobj);
extern void HSD_CObjEndCurrent(void);
extern void HSD_LObjSetCurrentAll(void *lobj);
extern void HSD_LObjSetupInit(void *cobj);
extern void jobjAnim(void *joint);
extern void jobjDispAll(void *joint);
extern void HSD_StartRender(s32 pass);
extern void HSD_EndRender(void);
extern void HSD_VICopyXFB(s32 pass);
extern void HSD_VISetXFBDrawDone(void);
extern void sPadAll(void);

#pragma dont_inline off
static inline void setEraseColor(LoadColor color)
{
    HSD_VIData.clear_clr = color;
}
#pragma dont_inline on

void dspLoadNowAnim(void);
void *sReadFileLen(char *name, s32 *size);
s32 sReadFileLenPtr(char *name, char *buf, s32 ofst, s32 len);
void *sArchiveLoad(char *name, void **out);
s32 LoadArc(ModelArchive *archive, char *name);
ModelArchive *LoadArc2_(char *name, s32 usb);
ModelArchive *LoadArc2B(void *mem, s32 memsize, char *name);
void PurgeArc2(ModelArchive *archive);
void *rdMapInfo(s32 mode, s32 number);
char *det_Load(char *name);
s32 jobjColor(void *jobj, char *name, s32 usb);
#pragma force_active on
static s32 adr[16];
MapInfo3 mgI;
static char det_Fname[80];
static char det_Mem[400];
static s32 fileMsgHelp[64];
static s32 cacheAiDat[1408];
static s32 cacheAiDatNum[16];
static s32 cacheRelayDat[1616];
static s32 cacheRelayDatNum[16];
static s32 arc2;
s32 usbForce;
static s32 dOpen;
s32 dspLoadF;
#pragma force_active off
#pragma dont_inline off
void dspLoadNowAnim(void)
{
    static u32 vcc;
    u32 frame;
    u32 count;
    u32 i;

    if (dspLoad == 0)
        return;
    if (dspLoadF < 1)
        return;
    frame = VIGetRetraceCount();
    if (frame == vcc)
        return;
    count = frame - vcc;
    if (count > 60)
        count = 60;
    vcc = frame;
    HSD_StateInvalidate(-1);
    HSD_SetZSortMode(0, 0);
    GXSetCullMode(0);
    setEraseColor((LoadColor){ 0, 0, 0, 0 });
    HSD_FogSet(0);
    VIWaitForRetrace();
    HSD_StartRender(0);
    if (HSD_CObjSetCurrent(dspLoad->camera) != 0) {
        HSD_LObjSetCurrentAll(dspLoad->lights);
        HSD_LObjSetupInit(dspLoad->camera);
        for (i = 0; i < count; i++)
            jobjAnim(dspLoad->models[0]);
        jobjDispAll(dspLoad->models[0]);
        HSD_CObjEndCurrent();
    }
    HSD_EndRender();
    HSD_VICopyXFB(0);
    HSD_VISetXFBDrawDone();
    VIWaitForRetrace();
    sPadAll();
}
#pragma dont_inline on

#pragma force_active on
static s32 rCbkR;
s32 dbgAllocS;
s32 dbgAllocU;
static s32 fBtl;
static s32 fMapNo;
static s32 fMsgHelp;
static s32 lenMsgHelp;
static s32 pgMsgHelp;
static s32 dspMsgHelp;
static s32 dspMsgHelpPage;
static s32 vc000;
static s64 vc001;
s64 enemyZoid;
s64 enemyChara;
#pragma force_active off
static u32 diskErrMsg[10] = {
    0x801331C4, 0x801331D0, 0x80133228, 0x8013325C, 0x801332C8, 0x80133318, 0x80389748, 0x80389748,
    0x80389748, 0x80389748
};
static const char lit_371[10] = "ZOIDS.VS3";
static const char lit_372[11] = "file error";
static const char lit_373[86] = "\x83" "f\x83" "B\x83X\x83N\x83J\x83o\x81[\x82\xaa\x8aJ\x82\xa2\x82\xc4\x82\xa2\x82\xdc\x82\xb7\x81" "B\x83Q\x81[\x83\x80\x82\xf0\x91\xb1\x82\xaf\x82\xe9\x8f\xea\x8d\x87\x82\xcd\x81" "A\n\x83" "f\x83" "B\x83X\x83N\x83J\x83o\x81[\x82\xf0\x95\xc2\x82\xdf\x82\xc4\x82\xad\x82\xbe\x82\xb3\x82\xa2\x81" "B";
static const char lit_374[50] = "\x83]\x83" "C\x83h\x83o\x81[\x83T\x83X\x82R\x82\xcc\x83" "f\x83" "B\x83X\x83N\x82\xf0\x83Z\x83" "b\x83g\n\x82\xb5\x82\xc4\x82\xad\x82\xbe\x82\xb3\x82\xa2\x81" "B";
static const char lit_375[108] = "\x82\xb1\x82\xcc\x83" "f\x83" "B\x83X\x83N\x82\xcd\x83]\x83" "C\x83h\x83o\x81[\x83T\x83X\x82R\x82\xcc\n\x83" "f\x83" "B\x83X\x83N\x82\xc5\x82\xcd\x82\xa0\x82\xe8\x82\xdc\x82\xb9\x82\xf1\x81" "B\n\x83]\x83" "C\x83h\x83o\x81[\x83T\x83X\x82R\x82\xcc\x83" "f\x83" "B\x83X\x83N\x82\xf0\x83Z\x83" "b\x83g\n\x82\xb5\x82\xc4\x82\xad\x82\xbe\x82\xb3\x82\xa2\x81" "B";
static const char lit_376[77] = "\x83" "f\x83" "B\x83X\x83N\x82\xf0\x93\xc7\x82\xdf\x82\xdc\x82\xb9\x82\xf1\x82\xc5\x82\xb5\x82\xbd\x81" "B\n\x82\xad\x82\xed\x82\xb5\x82\xad\x82\xcd\x81" "A\x96{\x91\xcc\x82\xcc\x8e\xe6\x88\xb5\x90\xe0\x96\xbe\x8f\x91\x82\xf0\n\x82\xa8\x93\xc7\x82\xdd\x82\xad\x82\xbe\x82\xb3\x82\xa2\x81" "B";
static const char lit_377[110] = "\x83G\x83\x89\x81[\x82\xaa\x94\xad\x90\xb6\x82\xb5\x82\xdc\x82\xb5\x82\xbd\x81" "B\n\x96{\x91\xcc\x82\xcc\x83p\x83\x8f\x81[\x83{\x83^\x83\x93\x82\xf0\x89\x9f\x82\xb5\x82\xc4\x93" "d\x8c\xb9\x82\xf0\n\x82n\x82" "e\x82" "e\x82\xc9\x82\xb5\x81" "A\x96{\x91\xcc\x82\xcc\x8e\xe6\x88\xb5\x90\xe0\x96\xbe\x8f\x91\x82\xcc\n\x8ew\x8e\xa6\x82\xc9\x8f]\x82\xc1\x82\xc4\x82\xad\x82\xbe\x82\xb3\x82\xa2\x81" "B";
static const char lit_396[9] = "LOADing\n";
static const char lit_692[9] = "PreOpen:";
static const char lit_719[54] = "fReadO2 ofst<0 ofst=%d error------------------------\n";
static const char lit_732[50] = "error alloc from usrHeap .......................\n";
static const char lit_739[19] = "\x83\x81\x83\x82\x83\x8a\x82\xaa\x91\xab\x82\xe8\x82\xdc\x82\xb9\x82\xf1";
void *sReadFileLen(char *name, s32 *size)
{
    DVDFileInfo3 file;
    s32 length;
    void *memory;

    if (size != 0)
        *size = 0;
    debug11();
    dspLoadNow();
    memory = 0;
    OSReport("loading file (%s) ...", name);
    if (!DVDOpen(name, &file)) {
        OSReport("cannot open file\n", name);
        return 0;
    }
    length = file.length;
    OSReport("size[%d]..", length);
    if (length != 0) {
        memory = malloc2((length + 31) & ~31);
        if (memory == 0) {
            OSReport("error........cannot allocate memory\n");
            DVDClose(&file);
            return 0;
        }
        OSReport("memAloc...[%X]....", memory);
        if (fReadO(&file, memory, length) < 0) {
            OSReport("cannot load file\n");
            DVDClose(&file);
            free(memory);
            OSReport("error\n");
            return 0;
        }
    }
    DVDClose(&file);
    OSReport("Done\n");
    if (size != 0)
        *size = length;
    return memory;
}

s32 sReadFileLenPtr(char *name, char *buf, s32 ofst, s32 len)
{
    DVDFileInfo3 file;
    s32 size;
    s32 base;
    s32 result;
    char *mem;

    debug11();
    dspLoadNow();
    OSReport("loading file (%s) ...", name);
    if (!DVDOpen(name, &file)) {
        OSReport("cannot open file\n", name);
        return -1;
    }
    size = file.length;
    OSReport("size[%d]..ofst=%d len=%d..", size, ofst, len);
    if (size <= ofst)
        size = 0;
    if (size < ofst + len)
        len = size - ofst;
    if (len <= 0)
        len = 0;
    if (len == 0)
        size = 0;
    result = len;
    if (size != 0) {
        base = ofst & ~3;
        mem = (char *)malloc2(len + 32);
        if (mem != 0) {
            fReadO2(&file, mem, (len + (ofst - base) + 31) & ~31, base);
            MemCpy(mem + (ofst - base), buf, len);
            free(mem);
        }
    }
    buf[len] = 0;
    DVDClose(&file);
    OSReport("Done\n");
    return result;
}

void *sArchiveLoad(char *name, void **out)
{
    s32 length;
    void *data;
    void *arc;

    if (out != 0)
        *out = 0;
    OSReport("archive load %s ", name);
    if (!fexist(name)) {
        OSReport("where?\n");
        return 0;
    }
    data = sReadFileLen(name, &length);
    if (data == 0)
        return 0;
    if (out != 0)
        *out = data;
    arc = mallocSys(0x44);
    if (arc == 0) {
        OSReport("error lost \n");
        free(data);
        if (out != 0)
            *out = 0;
        return 0;
    }
    OSReport("archive ok \n");
    HSD_ArchiveParse(arc, data, length);
    return arc;
}

static const char lit_821[21] = "sArcMem error lost \n";
s32 LoadArc(ModelArchive *archive, char *name)
{
    char *base;
    char *p;
    s32 length;
    s32 unused = 0;
    void *data;
    void *joint;

    p = name;
    base = name;
    for (; *p != 0; p++) {
        if (*p == '/')
            base = p + 1;
    }
    length = strlen(base);
    strcpy(archive->name, base);
    Str2Lows(archive->name);
    if (length > 4)
        archive->name[length - 4] = 0;
    archive->model_data = 0;
    archive->owned_data = 0;
    archive->models[0] = 0;
    if (!fexist(name)) {
        OSReport("not found. [%s]*************************\n", name);
        return 0;
    }
    archive->model_data = sLoad(name, &data);
    archive->owned_data = data;
    HSD_ArchiveLoadDepends(archive->model_data, 0, 0, 0);
    HSD_ArchiveResolveReference(archive->model_data, 0);
    archive->animations = HSD_ArchiveGetPublicAddress(archive->model_data, "scene_data");
    archive->lights = LoadArcLight(archive);
    if (archive->animations->models != 0) {
        joint = HSD_JObjLoadJoint(archive->animations->models[0]->joint);
        archive->models[0] = joint;
        HSD_JObjAddAnimAll(joint,
                           archive->animations->models[0]->joint_animations ? *archive->animations->models[0]->joint_animations : 0,
                           archive->animations->models[0]->material_animations ? *archive->animations->models[0]->material_animations : 0,
                           archive->animations->models[0]->shape_animations ? *archive->animations->models[0]->shape_animations : 0);
    }
    sMakeMatrix(joint);
    HSD_JObjReqAnimAll(joint, 0.0f);
    setAnimRate(joint, 1.0f);
    archive->camera = HSD_CObjLoadDesc(*archive->animations->camera);
    if (archive->animations->fog != 0 && *archive->animations->fog != 0)
        archive->fog = HSD_FogLoadDesc(*archive->animations->fog);
    OSReport("LoadArc  -----%5d %s\n", arc2, name);
    arc2++;
    return 1;
}

ModelArchive *LoadArc2_(char *name, s32 usb)
{
    char *p;
    s32 count;
    ModelAnimationTable *scene;
    char *base;
    s32 i = 0;
    void *joint;
    s32 size;
    void *model_data;
    ModelArchive *archive;
    void *data;

    data = 0;
    if (usbForce != 0)
        usb = 1;
    if (usb != 0) {
        model_data = TEA_USBFileArchiveLoad(name, &data);
    } else {
        if (!fexistU(name, usb)) {
            OSReport("not found. [%s]*************************\n", name);
            return 0;
        }
        model_data = sLoad(name, &data);
    }
    if (model_data == 0)
        return 0;
    OSReport("LoadArc2 -----%5d %s\n", arc2, name);
    arc2++;
    HSD_ArchiveLoadDepends(model_data, 0, 0, 0);
    HSD_ArchiveResolveReference(model_data, 0);
    scene = HSD_ArchiveGetPublicAddress(model_data, "scene_data");
    count = 0;
    if (scene->models != 0) {
        while (scene->models[count] != 0)
            count++;
    }
    size = count * 4 + 0x40;
    archive = (ModelArchive *)malloc2(size);
    if (archive == (void *)0) {
        if (data != 0)
            free(data);
        if (model_data != 0)
            sArchivePurge(model_data);
        putErr(lit_739);
        return 0;
    }
    ZeroMemory(archive, size);
    archive->owned_data = data;
    archive->animations = scene;
    archive->model_data = model_data;
    archive->model_count = count;
    p = name;
    base = name;
    for (; *p != 0; p++) {
        if (*p == '/')
            base = p + 1;
    }
    size = strlen(base);
    strcpy(archive->name, base);
    if (size > 4)
        archive->name[size - 4] = 0;
    if (scene->models != 0) {
        for (i = 0; i < count; i++) {
            joint = HSD_JObjLoadJoint(scene->models[i]->joint);
            if (joint != (void *)0) {
                HSD_JObjAddAnimAll(joint,
                                   scene->models[i]->joint_animations ? *scene->models[i]->joint_animations : 0,
                                   scene->models[i]->material_animations ? *scene->models[i]->material_animations : 0,
                                   scene->models[i]->shape_animations ? *scene->models[i]->shape_animations : 0);
                archive->models[i] = joint;
                sMakeMatrix(joint);
                HSD_JObjReqAnimAll(joint, 0.0f);
                setAnimRate(joint, 1.0f);
            }
        }
    }
    archive->lights = LoadArcLight(archive);
    archive->camera = HSD_CObjLoadDesc(*scene->camera);
    if (scene->fog != 0 && *scene->fog != 0)
        archive->fog = HSD_FogLoadDesc(*scene->fog);
    return archive;
}

ModelArchive *LoadArc2B(void *mem, s32 memsize, char *name)
{
    s32 i = 0;
    ModelAnimationTable *scene;
    void *joint;
    s32 count;
    ModelArchive *archive;
    void *model_data;
    s32 size;

    model_data = sArchiveMem(mem, memsize);
    if (model_data == 0)
        return 0;
    OSReport("LoadArc2B -----%5d %s\n", arc2, name);
    arc2++;
    HSD_ArchiveLoadDepends(model_data, 0, 0, 0);
    HSD_ArchiveResolveReference(model_data, 0);
    scene = HSD_ArchiveGetPublicAddress(model_data, "scene_data");
    count = 0;
    if (scene->models != 0) {
        while (scene->models[count] != 0)
            count++;
    }
    size = count * 4 + 0x40;
    archive = (ModelArchive *)malloc2(size);
    if (archive == (void *)0) {
        if (model_data != 0)
            sArchivePurge(model_data);
        putErr(lit_739);
        return 0;
    }
    ZeroMemory(archive, size);
    archive->owned_data = 0;
    archive->animations = scene;
    archive->model_data = model_data;
    archive->model_count = count;
    strcpy(archive->name, name);
    if (scene->models != 0) {
        for (i = 0; i < count; i++) {
            joint = HSD_JObjLoadJoint(scene->models[i]->joint);
            if (joint != (void *)0) {
                HSD_JObjAddAnimAll(joint,
                                   scene->models[i]->joint_animations ? *scene->models[i]->joint_animations : 0,
                                   scene->models[i]->material_animations ? *scene->models[i]->material_animations : 0,
                                   scene->models[i]->shape_animations ? *scene->models[i]->shape_animations : 0);
                archive->models[i] = joint;
                sMakeMatrix(joint);
                HSD_JObjReqAnimAll(joint, 0.0f);
                setAnimRate(joint, 1.0f);
            }
        }
    }
    archive->lights = LoadArcLight(archive);
    archive->camera = HSD_CObjLoadDesc(*scene->camera);
    if (scene->fog != 0 && *scene->fog != 0)
        archive->fog = HSD_FogLoadDesc(*scene->fog);
    return archive;
}

static const char lit_1152[19] = "ad=%s ma=%s sh=%s\n";
static const char lit_1221[21] = "light anim TBL non \n";
static const char lit_1222[32] = "light non anim  req=%d(in %d) \n";
static const char lit_1278[35] = "PurgeArc2 -----------------%5d %s\n";
#pragma dont_inline off
void PurgeArc2(ModelArchive *archive)
{
    if (archive != (void *)0 && archive->model_data != 0) {
        s32 model;
        OSReport("lobj free ---------------------------------\n");
        if (archive->lights != 0) {
            HSD_LObjRemoveAll(archive->lights);
            archive->lights = 0;
        }
        OSReport("cobj free \n");
        if (archive->camera != 0) {
            unreference_object(archive->camera);
            archive->camera = 0;
        }
        for (model = 0; model < archive->model_count; model++) {
            if (archive->models[model] != 0) {
                HSD_JObjRemoveAnimAll(archive->models[model]);
                HSD_JObjUnref(archive->models[model]);
                archive->models[model] = 0;
            }
        }
        if (archive->fog != 0) {
            unreference_object(archive->fog);
            archive->fog = 0;
        }
        if (archive->model_data != 0)
            sArchivePurge(archive->model_data);
        archive->model_data = 0;
        arc2--;
        OSReport(lit_1278, arc2, archive);
        if (archive->owned_data != 0)
            free(archive->owned_data);
        archive->owned_data = 0;
        OSReport("fl ");
        free(archive);
        OSReport("free OK \n ");
    }
}
#pragma dont_inline on

static char *rdMapStr[6] = { (char *)0x80389848, (char *)0x8038984C, (char *)0x80389850, (char *)0x80389854, (char *)0x80389858, (char *)0x8038985C };
void *rdMapInfo(s32 mode, s32 number)
{
    char name[256];
    void *data;

    if (mode == 3) {
        if (GameMode.f08 == 1)
            mode = 4;
        if (GameMode.game_type == 5)
            mode = 5;
    }
    ZeroMemory(&mgI, 0x3300);
    sprintf(name, "menu/map_info_dat/%s%03d.mg", rdMapStr[mode], number);
    data = sReadFileU(name, 0);
    if (data == (void *)0)
        return 0;
    MemCpy(data, &mgI, 0x3300);
    free(data);
    mgSearchEnemy(&mgI);
    fBtl = mode;
    fMapNo = number;
    if (mgI.f3248 < mgI.f324C)
        mgI.f3248 = mgI.f324C + 1000;
    return &mgI;
}

char *det_Load(char *name)
{
    s32 length;
    void *data;
    dspLoadF = 0;
    if (strcmp(name, det_Fname) == 0)
        return det_Mem;
    det_Mem[0] = 0;
    strcpy(det_Fname, name);
    data = sReadFileLenU(name, 0, &length);
    if (data == 0)
        return det_Mem;
    if (length > 0x18d)
        length = 0x18d;
    if (length < 0)
        length = 0;
    ((char *)data)[length] = 0;
    strcpy(det_Mem, data);
    free(data);
    return det_Mem;
}

static const char lit_1963[22] = "imgsize=%d tsize=%d \n";
s32 jobjColor(void *jobj, char *name, s32 usb)
{
    ImageDesc3 *desc;
    TObj3 *tobj;
    void *data;
    void *image;
    s32 size;

    if (jobj == (void *)0) {
        putErr("jobjColor : jobj not found.");
        return 0;
    }
    tobj = searchTObj(jobj);
    if (tobj == (void *)0) {
        putErr("jobjColor : tobj not found.");
        return 0;
    }
    desc = tobj->imagedesc;
    if (desc == (void *)0) {
        putErr("jobjColor : imagedesc(tobj) not found.");
        return 0;
    }
    size = calc_doltexture_size(desc->format, desc->width, desc->height);
    image = desc->image;
    data = sReadFileU(name, usb);
    if (data != 0 && SetTex2(data, image, size) != 0) {
        free(data);
        return 1;
    }
    if (data == (void *)0) {
        putErr("jobjColor : file not found.");
        return 0;
    }
    OSReport("tex set. error   jobj-tex (%d,%d,[%d])\n", desc->width, desc->height, desc->format);
    if (desc->format != 14) {
        putErr("jobjColor : set Tex  error    jobj-tex not CMPR");
        OSReport("jobj -tex   not CMPR\n");
    }
    free(data);
    return 0;
}

static u32 lit_1961[15] = {
    0x80014B94, 0x80014BB4, 0x80014BB4, 0x80014BCC, 0x80014BCC, 0x80014BCC, 0x80014BE8, 0x80014C04,
    0x80014B94, 0x80014BB4, 0x80014BCC, 0x80014C04, 0x80014C04, 0x80014C04, 0x80014B94
};
static const char lit_2060[29] = "menu/map_info_dat/%s%03d.msg";
static const char lit_2061[21] = "disp/top_message.dat";
static const char lit_2108[19] = "etc/ai/ai_%04d.dat";
static const char lit_2109[31] = "in cache .. AI-Open\x82\xc5\x82\xab\x82\xc8\x82\xa2 %s";
static const char lit_2138[22] = "etc/ai/relay_%04d.dat";
static const char lit_2139[34] = "in cache .. Relay-Open\x82\xc5\x82\xab\x82\xc8\x82\xa2 %s";
}
