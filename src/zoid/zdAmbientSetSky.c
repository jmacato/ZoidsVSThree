#include "zoid3.h"
#include "gx_tev.h"
extern GXColor SkyAmbient;
extern void jobjAmbient(HSD_JObj *joint, GXColor color);
extern void OSReport(const char *format, ...);

void zdAmbientSetSky(ZoidState *zoid)
{
    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        jobjAmbient(zoid->joint, SkyAmbient);
        OSReport("set ambient[%s] ", zoid->name);
    }
}
