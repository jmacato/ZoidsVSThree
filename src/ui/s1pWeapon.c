#pragma readonly_strings on
#include "zoid3.h"
#include "model_archive.h"

typedef struct WeaponCamera {
    s32 mode;
    s32 half;
    u8 reserved_08[0x580];
    s32 target_marker_count;
} WeaponCamera;

typedef struct PartEntry3 {
    u8 reserved_00[0x33];
    char english_name[0xC7];
    s16 icon;
    u8 reserved_FC[0x124 - 0xFC];
} PartEntry3;

typedef struct GameMode3 {
    s32 reserved_00;
    s32 game_type;
    u8 reserved_08[0x40];
} GameMode3;

extern ModelArchive *dsp1p;
extern PartEntry3 Tea_partsdat[451];
extern GameMode3 GameMode;
extern s32 sCamNN, sCamNS;
extern s32 vsyncN;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);
extern void sMakeMatrix(HSD_JObj *joint);
extern void jobjDispAll(HSD_JObj *joint);
extern void HSD_JObjDisp(HSD_JObj *joint, s32 mtx, u32 flags, s32 rendermode);
extern s32 sWeaponGetNumber(ZoidState *zoid, s32 selected);
extern s32 sWeaponGetMountBullet(ZoidState *zoid, s32 index);
extern void putAscJobjLR_sp(HSD_JObj *joint, s32 a, char *text, s32 b, f32 c);

void s1pWeapon(WeaponCamera *camera, ZoidState *zoid, HSD_JObj *joint)
{
    s32 idx;
    s32 num;
    s32 num2;
    s32 sel;
    HSD_JObj *frame;
    char *name;
    HSD_JObj *dst;
    s32 i;
    s32 digits[3];
    s16 icon;
    HSD_JObj *head;
    HSD_JObj *pos;
    s32 count;
    s32 k;
    s32 bullet;
    s32 icon2;

    if (dsp1p == 0)
        return;
    if (zoid->weapon_mount_count <= 0)
        return;
    sel = zoid->selected_weapon_mount;
    if (sel != -1 && zoid->weapon_mounts[sel].active == 0)
        return;
    if (sel == 19)
        sel = -1;
    if (sel == -1) {
        for (i = 0, sel = 0; i < 10; i++, sel++) {
            if (zoid->weapon_mounts[sel].active != 0)
                break;
        }
        if (i == 10)
            return;
    }
    if (joint == 0)
        return;
    head = GetChild(joint, 0, 3, -1, -1, -1);
    if (head == 0)
        return;
    frame = dsp1p->models[9];
    if (GameMode.game_type == 5)
        frame = dsp1p->models[17];
    if (sCamNN == 2 && sCamNS == 1 && camera->half == 0)
        frame = dsp1p->models[10];
    if (frame == 0)
        return;
    jobjCopyPos(head, frame);
    sMakeMatrix(frame);
    HSD_JObjDisp(GetChild(frame, 0, -1, -1, -1, -1), 0, 7, 0);
    if (sel != -1) {
        num = sWeaponGetNumber(zoid, sel);
        count = camera->target_marker_count;
        pos = GetChild(frame, 0, 0, -1, -1, -1);
        HSD_JObjDisp(pos, 0, 7, 0);
        jobjDispAll(pos);
        pos = GetChild(frame, 0, 0, 0, -1, -1);
        dst = GetChild(dsp1p->models[12], 0, 0, count / 10 % 10, -1, -1);
        jobjCopyPos(pos, dst);
        HSD_JObjDisp(dst, 0, 7, 0);
        pos = GetChild(frame, 0, 0, 1, -1, -1);
        dst = GetChild(dsp1p->models[12], 0, 0, count % 10, -1, -1);
        jobjCopyPos(pos, dst);
        HSD_JObjDisp(dst, 0, 7, 0);
        bullet = sWeaponGetMountBullet(zoid, sel);
        if (bullet >= 999)
            bullet = 999;
        pos = GetChild(frame, 0, 2, -1, -1, -1);
        icon = -1;
        if (num != -1)
            icon = Tea_partsdat[num].icon;
        if (icon > 19 || icon < 0)
            icon = 0;
        if (icon >= 0) {
            dst = GetChild(dsp1p->models[11], 0, icon, bullet != 0 ? -1 : 0, -1, -1);
            jobjCopyPos(pos, dst);
            if (zoid->weapon_mount != -1 || (vsyncN & 8))
                HSD_JObjDisp(dst, 0, 7, 0);
        }
        bullet = sWeaponGetMountBullet(zoid, sel);
        if (bullet >= 999)
            bullet = 999;
        digits[0] = bullet / 100 % 10;
        digits[1] = bullet / 10 % 10;
        digits[2] = bullet % 10;
        for (i = 0; i < 3; i++) {
            pos = GetChild(frame, 0, 4, i, -1, -1);
            dst = GetChild(dsp1p->models[12], 0, 1, digits[i], -1, -1);
            jobjCopyPos(pos, dst);
            HSD_JObjDisp(dst, 0, 7, 0);
        }
        pos = GetChild(frame, 0, 3, -1, -1, -1);
        if (pos != 0) {
            name = 0;
            if (num != -1)
                name = Tea_partsdat[num].english_name;
            if (name != 0) {
                if (sCamNN == 2 && sCamNS == 1 && camera->half == 0)
                    putAscJobjLR_sp(pos, 2, name, 0, 0.0f);
                else
                    putAscJobjLR_sp(pos, 2, name, 1, 0.0f);
            }
        }
    }
    if (zoid->weapon_mount_count > 1) {
        idx = sel + 1;
        k = 0;
        for (i = 0; i < 10; i++, idx++) {
            if (idx >= 10)
                idx -= 10;
            if (idx == sel)
                return;
            if (zoid->weapon_mounts[idx].active == 0)
                continue;
            num2 = sWeaponGetNumber(zoid, idx);
            if (num2 == -1)
                continue;
            icon2 = Tea_partsdat[num2].icon;
            if (icon2 > 19 || icon2 < 0)
                icon2 = 0;
            pos = GetChild(frame, 0, 2, k, -1, -1);
            dst = GetChild(dsp1p->models[11], 0, icon2, 0, -1, -1);
            jobjCopyPos(pos, dst);
            HSD_JObjDisp(dst, 0, 7, 0);
            k++;
        }
    }
}
