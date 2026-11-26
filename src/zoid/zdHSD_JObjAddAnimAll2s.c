#include "zoid3.h"
#include "jobj.h"

extern void zdHSD_JObjAddAnimAll(HSD_JObj *joint, JointPose *pose, s32 number,
                                HSD_AnimJoint *animation, HSD_MatAnimJoint *material,
                                HSD_ShapeAnimJoint *shape);

void zdHSD_JObjAddAnimAll2s(HSD_JObj *joint, JointPose *pose, s32 number,
                            HSD_AnimJoint *animation, HSD_MatAnimJoint *material,
                            HSD_ShapeAnimJoint *shape)
{
    if (joint != (void *)0) {
        joint = joint ? joint->child : 0;
        animation = animation ? *(HSD_AnimJoint **)animation : 0;
        pose = pose ? pose->child : 0;
        material = material ? *(HSD_MatAnimJoint **)material : 0;
        shape = shape ? *(HSD_ShapeAnimJoint **)shape : 0;
        zdHSD_JObjAddAnimAll(joint, pose, number, animation, material, shape);
    }
}
