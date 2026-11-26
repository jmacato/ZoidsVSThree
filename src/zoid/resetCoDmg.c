#include "zoid3.h"

extern void setCoDmgR(void *dst, void *src);

void resetCoDmg(ZoidState *zoid)
{
    setCoDmgR((u8 *)zoid + 0x50c, (u8 *)zoid + 0x5ac);
    setCoDmgR((u8 *)zoid + 0x64c, (u8 *)zoid + 0x6ec);
    setCoDmgR((u8 *)zoid + 0xc8c, (u8 *)zoid + 0xd2c);
    setCoDmgR((u8 *)zoid + 0xdcc, (u8 *)zoid + 0xe6c);
    setCoDmgR((u8 *)zoid + 0xf0c, (u8 *)zoid + 0xfac);
    setCoDmgR((u8 *)zoid + 0x104c, (u8 *)zoid + 0x10ec);
}
