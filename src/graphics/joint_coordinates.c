#include "jobj.h"

void sGlobal2Local(HSD_JObj *joint)
{
    Mtx local;

    if (joint->parent != 0)
        HSD_MtxInverseConcat(joint->parent->matrix, joint->matrix, local);
    else
        PSMTXCopy(joint->matrix, local);
    HSD_MtxGetTranslate(local, &joint->translation);
    HSD_MtxGetRotation(local, (Vec3 *)&joint->rotation);
    HSD_MtxGetScale(local, &joint->scale);
}
