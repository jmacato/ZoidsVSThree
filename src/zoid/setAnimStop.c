#include "zoid3.h"

extern void setAnimRate(HSD_JObj *joint, f32 rate);

void setAnimStop(HSD_JObj *joint)
{
    setAnimRate(joint, 0.0f);
}
