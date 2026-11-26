#include "zoid3.h"
#include "ground_collision.h"

#define DEG(x) (2.0 * (3.1415926 * (x)) / 360.0)

extern f32 zdGetBasePoly(ZoidState *zoid, f32 *point);
extern f32 zdColPosY(f32 *point, u16 *selector);
extern void sLinear1D(f32 *value, f32 target, f32 step);
extern void chkDeep(FootJoint *foot, s32 *found, f32 *minimum);
extern void chkDeepCo(void *coobj, s32 *found, f32 *depth);
extern f32 sLenPoint3dR(f32 *point);
extern void zdSetXYZ(ZoidState *zoid);
extern void calcBaseF(ZoidState *zoid);
extern void calcBaseB(ZoidState *zoid);
extern void sMakeMatrix(HSD_JObj *joint);
extern void ik3d(ZoidState *zoid, FootJoint *foot);
extern void ik3dF(ZoidState *zoid, FootJoint *foot);

void ZoidPutXZ(ZoidState *zoid)
{
    HSD_JObj *joint;
    f32 rx;
    f32 rz;
    s32 flag38;
    f32 dead;
    f32 deep;
    s32 found;
    s32 flag28;
    f32 pos[3];
    u16 selector;
    u16 poly;
    s32 landed;
    s32 count;
    f32 rate;
    f32 low;
    f32 diff;
    f32 height;
    f32 dx;
    f32 add;
    f32 sum;
    f32 limit;
    f32 y;
    f32 len;
    f32 probe;
    s32 mode;
    u8 *control;
    u8 *slider;
    Vec3 *normal;
    HSD_JObj *jobj;
    s32 mount;
    s32 lifted;
    GroundPolygon *polygon;
    s32 any;
    s32 supported;
    s32 all_supported;
    s32 any2;
    s32 i;
    s32 j;
    s32 k;

    lifted = 0;
    landed = 0;
    joint = zoid->joint;
    if (zoid == (void *)0)
        return;
    if (zoid->joint == (void *)0)
        return;
    control = (u8 *)zoid->anim_data;
    if (control == 0)
        return;
    slider = (u8 *)zoid->slider_info;
    if (slider == 0)
        return;
    rate = DEG((f32)((f32) * (u16 *)(slider + 0x706) / 60.0));
    limit = DEG((f32) * (u16 *)(slider + 0x708));
    mode = zoid->current_animation;
    dead = 2.0 + 2.0f * zoid->senter_translation_y;
    if (mode == 2)
        mode = 1;
    flag28 = *(s32 *)(control + 0x108) == 1 && (mode == 5 || mode == 6);
    y = zdGetBasePoly(zoid, zoid->position);
    poly = zoid->ground_polygon;
    if (poly == 0xFFFF && zoid->field_1EB8 != 0xFFFF)
        y = zoid->position[1] - 100.0f;
    zoid->ground_height = y;
    mount = zoid->weapon_mount;
    flag38 = 1;
    switch (zoid->action) {
    case 13: case 14: case 15: case 16: case 17:
        flag38 = 0;
    }
    jobj = zoid->field_1A7C;
    if (jobj != 0) {
        for (i = 0; i < 3; i++)
            pos[i] = jobj->matrix[i][3];
        probe = zdColPosY(pos, &selector);
        if (selector != -1)
            polygon = &grdcPolygon[selector];
        else
            polygon = 0;
        if (polygon != 0)
            normal = &grdcNormal[polygon->normal_index];
        else
            normal = 0;
        rx = probe - jobj->matrix[1][3];
        if (rx > 1.0f)
            rx = 0.0f;
        if (rx > 0.0f) {
            if (zoid->death_pending != 0 && rx > 0.025)
                rx = 0.025f;
            if (flag38)
                zoid->joint->child->translation.y += rx;
            else
                zoid->position[1] += rx;
        }
    }
    diff = y - zoid->position[1];
    if (diff < zoid->field_19FC - 0.2) {
        lifted = 1;
        diff = zoid->field_19FC - 0.2;
        y = zoid->position[1] + diff;
    }
    low = y;
    if (*(s32 *)(control + 0xF8) != 0 || zoid->field_0170 != 0) {
        any = 0;
        if (*(s32 *)(control + 0xF8) == 2) {
            if (mode == 4 || mode == 5 || mode == 6)
                any = 1;
        } else {
            any = 1;
        }
        if (any) {
            zoid->height_offset = 0.0f;
            landed = 1;
            if (zoid->position[1] < y)
                zoid->position[1] = y;
        }
    }
    if (flag28) {
        height = zoid->position[1] - zoid->ground_height;
        zoid->field_1C34 = 1;
        lifted = 0;
        sLinear1D(&zoid->height_offset, 0.0f, 0.1f);
        if (height <= 1.0f) {
            zoid->field_1BFC = 0;
            sLinear1D(&zoid->position[1], y, 0.1f);
        } else {
            zoid->field_1C34 = 0;
            lifted = 1;
            zoid->field_1BFC = *(s32 *)(control + 0xE4) + 10;
        }
        if (height <= 0.5)
            zoid->position[1] = y;
    }
    if (zoid->field_1C34 == 0) {
        found = 0;
        deep = 100.0f;
        sum = 0.0f;
        count = 0;
        supported = 0;
        all_supported = 1;
        if (landed == 0) {
            if (*(s32 *)(control + 0xF4) != 2) {
                if (zoid->feet[0].joint != 0) {
                    chkDeep(&zoid->feet[0], &found, &deep);
                    if (low > zoid->feet[0].ground)
                        low = zoid->feet[0].ground;
                    count++;
                    sum += zoid->feet[0].ground;
                    if (!(zoid->feet[0].flags & FOOT_FLAG_SUPPORTED))
                        all_supported = 0;
                    else
                        supported++;
                }
                if (zoid->feet[1].joint != 0) {
                    chkDeep(&zoid->feet[1], &found, &deep);
                    if (low > zoid->feet[1].ground)
                        low = zoid->feet[1].ground;
                    count++;
                    sum += zoid->feet[1].ground;
                    if (!(zoid->feet[1].flags & FOOT_FLAG_SUPPORTED))
                        all_supported = 0;
                    else
                        supported++;
                }
            }
            if (zoid->feet[2].joint != 0) {
                chkDeep(&zoid->feet[2], &found, &deep);
                if (low > zoid->feet[2].ground)
                    low = zoid->feet[2].ground;
                count++;
                sum += zoid->feet[2].ground;
                if (!(zoid->feet[2].flags & FOOT_FLAG_SUPPORTED))
                    all_supported = 0;
                else
                    supported++;
            }
            if (zoid->feet[3].joint != 0) {
                chkDeep(&zoid->feet[3], &found, &deep);
                if (low > zoid->feet[3].ground)
                    low = zoid->feet[3].ground;
                count++;
                sum += zoid->feet[3].ground;
                if (!(zoid->feet[3].flags & FOOT_FLAG_SUPPORTED))
                    all_supported = 0;
                else
                    supported++;
            }
            if (zoid->feet[2].joint != 0 && zoid->feet[3].joint != 0) {
                if (zoid->feet[2].depth < 0.0f && zoid->feet[3].depth < 0.0f)
                    found = 0;
            }
            if (count < 1) {
                (void)0;
            } else {
                sum = sum / count;
            }
            if (*(s32 *)(control + 0x104)) {
                (void)0;
            }
            add = 0.0002f;
            any2 = 0;
            if (all_supported == 0) {
                if (found == 0 || !(deep > 0.2))
                    any2 = 1;
            }
            if (zoid->feet[3].joint != 0 && !(zoid->feet[3].flags & FOOT_FLAG_CONTACT))
                any2 = 1;
            if (zoid->feet[2].joint != 0 && !(zoid->feet[2].flags & FOOT_FLAG_CONTACT))
                any2 = 1;
            if (any2) {
                if (zoid->height_offset_speed >= 0.0f)
                    zoid->height_offset_speed = 0.0f;
                if (mode == 4 || mode == 5)
                    add *= 0.1;
                zoid->height_offset_speed -= add;
                if (count - supported >= 2)
                    zoid->height_offset_speed -= add;
            }
            if (zoid->height_offset_speed > 0.01)
                zoid->height_offset_speed = 0.01f;
            if (zoid->height_offset_speed < -0.01)
                zoid->height_offset_speed = -0.01f;
            zoid->height_offset += zoid->height_offset_speed;
        }
        if (supported <= 1 && *(s32 *)(control + 0xF4) == 4)
            found = 0;
        if (found != 0) {
            f32 add2;
            add2 = 0.0f;
            if (deep > 0.01)
                add2 = 0.0001f;
            if (deep > 0.1)
                add2 = 0.02f;
            if (deep > 0.7)
                add2 = 0.01f;
            if (deep > 1.0f)
                add2 = 0.1f;
            if (zoid->field_1DD4 != 0)
                add2 = deep / 10.0;
            if (zoid->field_1DD8 != 0)
                add2 = deep / 20.0;
            zoid->height_offset += add2;
            deep -= add2;
            if (deep <= 0.0f)
                zoid->height_offset += deep;
            zoid->height_offset_speed = 0.0f;
        }
        found = 0;
        deep = 0.0f;
        chkDeepCo(zoid->bust_coobj, &found, &deep);
        if (slider[0x70B] & 4) {
            chkDeepCo(zoid->hip_coobj, &found, &deep);
            chkDeepCo(zoid->neck_coobj, &found, &deep);
        }
        if (found != 0 && (slider[0x70B] & 4))
            zoid->height_offset += deep;
        if (zoid->field_1DD4 != 0)
            zoid->field_1DD4--;
        if (zoid->field_1DD8 != 0)
            zoid->field_1DD8--;
        if (mode > 3 && landed != 0)
            supported = 1;
        if (supported == 0 || lifted != 0) {
            zoid->field_1BFC++;
            if (zoid->field_0170 != 0)
                zoid->field_1BFC = 0;
            if (zoid->field_1360 != 0)
                zoid->field_1BFC = 0;
            if ((slider[0x70F] & 4) && *(void **)(zoid->bust_coobj + 0x18) != 0)
                zoid->field_1BFC = 0;
            if ((slider[0x70F] & 8) && *(void **)(zoid->hip_coobj + 0x18) != 0)
                zoid->field_1BFC = 0;
            if (zoid->field_1BFC > *(s32 *)(control + 0xE4) && zoid->field_1BE4 == 0 && zoid->field_0170 == 0
                && *(s32 *)(control + 0xF8) == 0 && zoid->action != 2 && zoid->action != 1) {
                zoid->action = 1;
                zoid->jump_phase = 32;
                zoid->velocity[0] = 0.0f;
                zoid->velocity[1] = -0.001f;
                zoid->velocity[2] = 0.0f;
                zoid->field_1BFC = 0;
                zoid->action = 2;
                if (0.0f == zoid->displacement[1])
                    zoid->displacement[1] = -0.001f;
                len = sLenPoint3dR(zoid->displacement);
                if (len > 0.7) {
                    for (k = 0; k < 3; k++)
                        zoid->displacement[k] *= 0.7 / len;
                }
                return;
            }
        } else {
            zoid->field_1BFC = 0;
        }
        if (zoid->height_offset < low - y - 2.0f)
            zoid->height_offset = low - y - 2.0f;
        zoid->position[1] = y;
    }
    y = zoid->position[1];
    if (y > zoid->ground_height && zoid->height_offset < 0.0f) {
        dx = y - zoid->ground_height;
        if (dx > -zoid->height_offset) {
            y += zoid->height_offset;
            zoid->height_offset = 0.0f;
        } else {
            y = zoid->ground_height;
            zoid->height_offset += dx;
        }
        zoid->position[1] = y;
    }
    rx = 0.0f;
    rz = 0.0f;
    if (poly != GROUND_POLYGON_NONE)
        sColGetRxRz(&grdcNormal[grdcPolygon[poly].normal_index], zoid->heading, &rx, &rz);
    if (rx > limit)
        rx = limit;
    if (rz > limit)
        rz = limit;
    if (rx < -limit)
        rx = -limit;
    if (rz < -limit)
        rz = -limit;
    if (*(s32 *)(control + 0xF8) == 1) {
        if (zoid->position[1] > 2.0f + zoid->ground_height) {
            rx = 0.0f;
            rz = 0.0f;
        }
    }
    sLinear1D(&zoid->ground_rx, rx, rate);
    sLinear1D(&zoid->ground_rz, rz, rate);
    zdSetXYZ(zoid);
    calcBaseF(zoid);
    calcBaseB(zoid);
    zdSetXYZ(zoid);
    sMakeMatrix(zoid->joint);
    zoid->ground_normal_count = 0;
    for (j = 0; j < 3; j++)
        zoid->ground_normal_sum[j] = 0.0f;
    if (*(s32 *)(control + 0xF4) != 2) {
        ik3d(zoid, &zoid->feet[0]);
        ik3d(zoid, &zoid->feet[1]);
        if (zoid->field_1360 != 0 && mount != -1) {
            if (mount == 0x13)
                mount = 0;
            else
                mount++;
            if (*(s8 *)(slider + mount * 16 + 8) == 1 && (slider[0x70B] & 0x10)) {
                ik3dF(zoid, &zoid->feet[0]);
                ik3dF(zoid, &zoid->feet[1]);
            }
        }
    }
    ik3d(zoid, &zoid->feet[2]);
    ik3d(zoid, &zoid->feet[3]);
    if (zoid->field_1C04 & 1) {
        ik3dF(zoid, &zoid->feet[2]);
        ik3dF(zoid, &zoid->feet[3]);
        zoid->field_1C04 &= ~1;
    }
    if (zoid->field_1BFC < 0)
        zoid->field_1BFC = 0;
    (void)sum;
    (void)sum;
}
