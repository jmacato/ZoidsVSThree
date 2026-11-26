extern "C" {
#pragma readonly_strings on
#pragma dont_inline on
#pragma bool off
#include "types.h"

#include "zoid3.h"
#include "model_archive.h"
typedef struct WeaponInverse3 {
    HSD_JObj *joint;
    u8 reserved_04[0x34];
} WeaponInverse3;
typedef struct WeaponState3 {
    s32 active;
    u32 flags;
    u32 state_flags;
    s32 type;
    ModelArchive *archive;
    s32 model;
    void *pose;
    void *field_1C;
    HSD_JObj *counter_joint;
    HSD_JObj *link_joint;
    HSD_JObj *link_target;
    HSD_JObj *pre_link_joint;
    HSD_JObj *pre_link_target;
    HSD_JObj *target_joint;
    HSD_JObj *scope_joint;
    ZoidState *owner;
    u8 pad_40[8];
    HSD_JObj *barrels[12];
    HSD_JObj *trace_joints[13];
    f32 trace_positions[13][3];
    WeaponInverse3 inverses[12];
    s32 animation;
    s32 ammo;
    f32 range;
    f32 rate;
    s32 color;
    s32 bullet_kind;
    s32 marker_count;
    s32 marker_cursor;
    s16 drain;
    u8 pad_40A[0x6DC - 0x40A];
} WeaponState3;
typedef struct PartData3 {
    u8 reserved_00[0x5C];
    s32 bullet;
    u8 reserved_60[4];
    u32 flags;
    u8 reserved_68[6];
    s16 range;
    u8 reserved_70[4];
    s16 marker_count;
    s16 rate;
    u8 reserved_78[0x124 - 0x78];
} PartData3;
typedef struct BulletData3 {
    u8 reserved_00[0x12];
    s16 trace;
    u8 reserved_14[0x4C - 0x14];
} BulletData3;
typedef struct ImageDesc3 {
    void *image;
    u16 width;
    u16 height;
    s32 format;
} ImageDesc3;
typedef struct TObj3 {
    u8 pad_00[0x58];
    ImageDesc3 *imagedesc;
} TObj3;
extern WeaponState3 sWeapon[100];
extern PartData3 Tea_partsdat[];
extern BulletData3 Tea_bulletdat[];
extern s32 sprintf(char *buffer, const char *format, ...);
extern void OSReport(const char *format, ...);
extern void free(void *p);
extern void *sReadFileU(char *name, s32 mode);
extern void putErr(const char *msg);
extern TObj3 *searchTObj(void *jobj);
extern s32 calc_doltexture_size(s32 format, s32 w, s32 h);
extern s32 SetTex2(void *data, void *dest, s32 size);
extern HSD_JObj *searchArcJoint2(ModelArchive *archive, s32 model, char *name);
extern HSD_JObj *makeJobj(void);
extern void stCopyObj(HSD_JObj *source, void *pose);
extern void stCopyMatMobj(HSD_JObj *source, void *pose);
extern void sWeaponSetAnim(s32 weapon, s32 animation);

s32 WeaponColor(WeaponState3 *weapon, s32 color, s32 usb);
#pragma force_active on
WeaponState3 sWeapon[100];
typedef struct Laser3 {
    HSD_JObj *source;
    u8 reserved_04[0x60];
    ModelArchive *archive;
    u8 reserved_68[4];
} Laser3;
static Laser3 sLsr[11];
static s32 sLsr1[10800];
#pragma force_active off
static const char lit_488[14] = "counter_joint";
static const char lit_489[13] = "target_joint";
static const char lit_490[14] = "target1_joint";
static const char lit_491[12] = "scope_joint";
static const char lit_492[14] = "pa_%02d_joint";
static const char lit_493[14] = "te_%02d_joint";
static const char lit_494[11] = "link_joint";
static const char lit_495[15] = "pre_link_joint";
static const char lit_496[11] = "a_%x_joint";
static const char lit_552[14] = "weapon/%s.dat";
static const char lit_565[40] = "mount wp    zoid=%d mt=%d act=%d wp=%d\n";
static const char lit_1579[12] = "start_joint";
static const char lit_1580[10] = "end_joint";
extern void PurgeArc(ModelArchive *archive);

void sLsrEpilogue(void)
{
    s32 i;
    ModelArchive *archive;

    for (i = 0; i < 11; i++) {
        archive = sLsr[i].archive;
        if (archive != (void *)0) {
            PurgeArc(archive);
            sLsr[i].archive = 0;
            sLsr[i].source = 0;
        }
    }
}

s32 WeaponColor(WeaponState3 *weapon, s32 color, s32 usb)
{
    register ImageDesc3 *desc;
    TObj3 *tobj;
    void *data;
    void *image;
    s32 size;
    HSD_JObj *model;
    char name[256];

    if (color < 0)
        return 0;
    if (weapon == (void *)0)
        return 0;
    if (weapon->archive == (void *)0)
        return 0;
    if (weapon->color == color)
        return 1;
    model = weapon->archive->models[weapon->model];
    if (model == (void *)0) {
        putErr("wpColor : Weapon.jobj not found.");
        return 0;
    }
    tobj = searchTObj(model);
    if (tobj == (void *)0) {
        putErr("zoidColor : tobj not found.");
        return 0;
    }
    desc = tobj->imagedesc;
    if (desc == (void *)0) {
        putErr("wpColor : imagedesc(tobj) not found.");
        return 0;
    }
    size = calc_doltexture_size(desc->format, desc->width, desc->height);
    image = desc->image;
    sprintf(name, "weapon/all_tex/%s_%c.tpl", weapon->archive, color + 0x41);
    data = sReadFileU(name, usb);
    if (data != 0 && SetTex2(data, image, size) != 0) {
        weapon->color = color;
        free(data);
        OSReport("tex2\n");
        return 1;
    }
    if (data == (void *)0) {
        putErr("wpColor : file not found.");
        return 0;
    }
    OSReport("tex set. error   wp-tex (%d,%d,[%d])\n", desc->width, desc->height, desc->format);
    if (desc->format != 14) {
        putErr("wpColor : set Tex  error    wp-tex not CMPR");
        OSReport("wp -tex   not CMPR\n");
    }
    free(data);
    return 0;
}

s32 sWeaponSetN(ModelArchive *archive, s32 type, s32 model, ZoidState *zoid, s32 slot, s32 ammo)
{
    char name[256];
    WeaponState3 *weapon;
    s32 bullet;
    HSD_JObj *joint;
    HSD_JObj *link;
    HSD_JObj *target;
    s32 i;
    s32 j;
    s32 index;

    if (zoid == (void *)0)
        return -1;
    if (archive == 0)
        return -1;
    if (slot >= 30)
        return -1;
    if (slot < 0)
        return -1;
    joint = zoid->weapon_slots[slot].joint;
    if (joint == (void *)0)
        return -1;
    if (zoid->weapon_slots[slot].weapon != -1)
        return -2;
    for (i = 0; i < 100; i++) {
        weapon = &sWeapon[i];
        if (weapon->active == 0)
            break;
    }
    if (i == 100)
        return -1;
    index = i;
    if (weapon->active != 0)
        return -1;
    weapon->archive = archive;
    weapon->model = model;
    weapon->owner = zoid;
    weapon->type = type;
    weapon->field_1C = joint;
    weapon->counter_joint = searchArcJoint2(weapon->archive, model, lit_488);
    weapon->target_joint = searchArcJoint2(weapon->archive, model, lit_489);
    if (weapon->target_joint == (void *)0)
        weapon->target_joint = searchArcJoint2(weapon->archive, model, lit_490);
    weapon->scope_joint = searchArcJoint2(weapon->archive, model, lit_491);
    for (i = 0; i < 12; i++) {
        sprintf(name, lit_492, i);
        weapon->barrels[i] = searchArcJoint2(weapon->archive, model, name);
    }
    for (i = 0; i < 13; i++) {
        sprintf(name, lit_493, i);
        weapon->trace_joints[i] = searchArcJoint2(weapon->archive, model, name);
        for (j = 0; j < 3; j++)
            weapon->trace_positions[i][j] = zoid->position[j];
    }
    link = searchArcJoint2(weapon->archive, model, lit_494);
    if (link != 0 && slot < 29) {
        target = zoid->weapon_slots[slot + 1].joint;
        if (target != 0) {
            weapon->link_joint = link;
            weapon->link_target = target;
        }
    }
    link = searchArcJoint2(weapon->archive, model, lit_495);
    if (link != 0 && slot > 0) {
        target = zoid->weapon_slots[slot - 1].joint;
        if (target != 0) {
            weapon->pre_link_joint = link;
            weapon->pre_link_target = target;
        }
    }
    for (i = 0; i < 12; i++) {
        sprintf(name, lit_496, i);
        weapon->inverses[i].joint = searchArcJoint2(weapon->archive, model, name);
    }
    weapon->pose = makeJobj();
    stCopyObj(archive->models[model], weapon->pose);
    stCopyMatMobj(archive->models[model], weapon->pose);
    weapon->active = 1;
    weapon->ammo = ammo;
    weapon->animation = 0;
    weapon->marker_count = Tea_partsdat[type].marker_count;
    if (weapon->marker_count > 20)
        weapon->marker_count = 20;
    weapon->bullet_kind = 0;
    bullet = Tea_partsdat[type].bullet;
    /* The address's high word occupies r0 until MWCC removes it after allocation. */
    if (bullet > 0)
        ((WeaponState3 *)(s32)(s64)(s32)weapon)->bullet_kind = Tea_bulletdat[bullet].trace;
    weapon->range = Tea_partsdat[type].range;
    weapon->rate = 0.01 * Tea_partsdat[type].rate;
    weapon->drain = Tea_partsdat[type].flags & 0x37;
    zoid->weapon_slots[slot].weapon = index;
    sWeaponSetAnim(index, 4);
    return index;
}
}
