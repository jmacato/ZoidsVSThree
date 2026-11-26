#include "jobj.h"
#include "zoid3.h"

#define JOBJ_INSTANCE 0x1000

#pragma dont_inline on
extern void zdHSD_JObjAddAnim(HSD_JObj *joint, JointPose *pose, s32 number,
                             HSD_AnimJoint *animation, HSD_MatAnimJoint *material,
                             HSD_ShapeAnimJoint *shape);
void zdHSD_JObjAddAnimAll(HSD_JObj *joint, JointPose *pose, s32 number,
                         HSD_AnimJoint *animation, HSD_MatAnimJoint *material,
                         HSD_ShapeAnimJoint *shape)
{
    if (joint != (void *)0) {
        zdHSD_JObjAddAnim(joint, pose, number, animation, material, shape);
        joint = joint ? joint->child : 0;
        animation = animation ? animation->child : 0;
        pose = pose ? pose->child : 0;
        material = material ? material->child : 0;
        shape = shape ? shape->child : 0;
        while (joint != 0 && animation != 0) {
            zdHSD_JObjAddAnimAll(joint, pose, number, animation, material, shape);
            joint = joint->next;
            animation = animation ? animation->next : 0;
            pose = pose ? pose->next : 0;
            material = material ? material->next : 0;
            shape = shape ? shape->next : 0;
        }
    }
}