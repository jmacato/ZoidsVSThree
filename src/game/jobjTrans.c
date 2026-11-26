#include "types.h"
#include "jobj.h"

#pragma auto_inline off
void jobjTrans(HSD_JObj *jobj, f32 *trans)
{
    if (jobj != 0) {
        f32 (*matrix)[4] = jobj->matrix;
        s32 i;
        for (i = 0; i < 3; i++) {
            matrix[i][3] += trans[i];
        }
        jobj = (jobj != 0) ? jobj->child : 0;
        while (jobj != 0) {
            jobjTrans(jobj, trans);
            jobj = (jobj != 0) ? jobj->next : 0;
        }
    }
}
