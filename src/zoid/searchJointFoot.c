#include "zoid3.h"

extern HSD_JObj *searchJoint(ZoidState *zoid, const char *part);

void searchJointFoot(ZoidState *zoid, FootJoint *foot, const char *part)
{
    foot->joint = searchJoint(zoid, part);
    if (foot->joint != (void *)0) {
        zoid->foot_count++;
        foot->offset = foot->joint->translation.y;
    }
}
