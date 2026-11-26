#include "types.h"

extern u8 prmTblParam[];
extern s32 prmTblZ[];
extern s32 sprintf(char *buf, const char *format, ...);
extern s32 sReadLenPtr(char *name, u8 *dst, s32 offset, s32 length);

void prmTblSet(s32 index, s32 zoid_id)
{
    char path[0x100];
    sprintf(path, "zoid/idp/zoid_%03d.prm", zoid_id);
    sReadLenPtr(path, prmTblParam + index * 0x750, 0, 0x750);
    prmTblZ[index] = zoid_id;
}
