#include "zoid3.h"
#include "jobj.h"

void zdHSD_JObjAddAnim(HSD_JObj *joint, JointPose *holder, s32 number,
                       HSD_AnimJoint *animation, HSD_MatAnimJoint *material,
                       HSD_ShapeAnimJoint *shape)
{
    if (joint != (void *)0) {
        HSD_JObjRemoveAnim(joint);
        HSD_JObjAddAnim(joint, animation, material, shape);
        holder->animation_index = number;
    }
}
