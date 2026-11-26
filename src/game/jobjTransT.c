#include "types.h"
#include "jobj.h"

extern void jobjTrans(HSD_JObj *jobj, f32 *trans);

void jobjTransT(HSD_JObj *jobj, f32 *trans)
{
    f32 delta[3];
    s32 i;

    for (i = 0; i < 3; i++) {
        delta[i] = trans[i] - jobj->matrix[i][3];
    }
    jobj->translation.x = trans[0];
    jobj->translation.y = trans[1];
    jobj->translation.z = trans[2];
    jobjTrans(jobj, delta);
}
