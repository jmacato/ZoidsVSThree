#pragma readonly_strings on
#include "types.h"
#include "joint.h"

typedef struct GroundArchive3 {
    u8 pad_00[0x3C];
    HSD_JObj *model0;
} GroundArchive3;

extern GroundArchive3 Ground;
extern s32 usbForce;
extern s32 objNow;
extern s32 objSize;
extern void *MapObjDef;
extern s32 MapObjDefN;
extern void *sReadFileLenU(const char *name, s32 usb, u32 *len);
extern void sMakeMatrix(HSD_JObj *joint);
extern void GroundObjLoadSub(HSD_JObj *joint, s32 stage, s32 usb);
extern void GroundObjMapInfo(s32 usb);
extern void OSReport(const char *format, ...);

void GroundObjLoad(s32 stage, s32 usb)
{
    HSD_JObj *joint;
    u32 len;

    if (usbForce != 0)
        usb = 1;
    MapObjDef = sReadFileLenU("stage/map_obj/def.bin", usb, &len);
    if (MapObjDef == (void *)0)
        MapObjDefN = 0;
    else
        MapObjDefN = len >> 7;
    joint = Ground.model0;
    if (joint != (void *)0) {
        sMakeMatrix(joint);
        joint = joint != 0 ? joint->child : 0;
        objSize = 0;
        for (; joint != 0; joint = joint != 0 ? joint->next : 0)
            GroundObjLoadSub(joint, stage, usb);
        sMakeMatrix(Ground.model0);
        GroundObjMapInfo(usb);
        OSReport("ground stage=%d , obj=%d   objSize=%d  \n", stage, objNow, objSize);
    }
}
