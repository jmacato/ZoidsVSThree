/* #line 1	"zoid3.h"	/* stack depth 1 */
/* #line 1	"joint.h"	/* stack depth 2 */
/* #line 1	"types.h"	/* stack depth 3 */
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;
typedef struct Vec3 {
f32 x;
f32 y;
f32 z;
} Vec3;
/* #line 4	"joint.h"	/* stack depth 2 */
typedef struct HSD_JObj {
struct HSD_ClassInfo *class_info;
u16 reference_count;
u16 individual_reference_count;
struct HSD_JObj *next;
struct HSD_JObj *parent;
struct HSD_JObj *child;
u32 flags;
void *display_object;
f32 rotation[4];
Vec3 scale;
Vec3 translation;
f32 matrix[3][4];
Vec3 *scale_pointer;
void *envelope_matrix;
struct HSD_AObj *animation;
void *render_object;
u32 object_id;
} HSD_JObj;
typedef struct MaterialPose {
struct MaterialPose *next;
struct HSD_MObj *material;
f32 alpha;
u32 render_mode;
} MaterialPose;
typedef struct JointPose {
struct JointPose *next;
struct JointPose *child;
MaterialPose *materials;
f32 rotation[4];
Vec3 scale;
Vec3 translation;
f32 matrix[3][4];
s32 animation_index;
u32 saved_flags;
} JointPose;
typedef struct HSD_JObjDesc {
const char *name;
u32 flags;
struct HSD_JObjDesc *child;
struct HSD_JObjDesc *next;
union {
struct HSD_DObjDesc *dobjdesc;
void *spline;
struct HSD_SList *ptcl;
} u;
Vec3 rotation;
Vec3 scale;
Vec3 position;
f32 (*matrix)[4];
struct HSD_RObjDesc *render_desc;
} HSD_JObjDesc;
/* #line 4	"zoid3.h"	/* stack depth 1 */
/* #line 1	"zoid_collision.h"	/* stack depth 2 */
/* #line 1	"joint.h"	/* stack depth 3 */
/* #line 4	"zoid_collision.h"	/* stack depth 2 */
typedef struct CoObj {
HSD_JObj *joint, *base_joint;
f32 minimum_scale, maximum_scale;
s32 object_contact, ground_contact;
u8 reserved_18[4];
u16 ground_polygon_index;
u8 reserved_1E[0xE];
f32 inverse[3][4];
u32 field_5C;
s32 health, maximum_health;
f32 position[3];
f32 base_position[3];
f32 movement[3];
f32 ground_y;
} CoObj;
typedef char CoObjSizeCheck[sizeof(CoObj) == 0x90 ? 1 : -1];
typedef struct CoDamage {
u32 flags;
s32 health, maximum_health;
} CoDamage;
typedef char CoDamageSizeCheck[sizeof(CoDamage) == 12 ? 1 : -1];
/* #line 5	"zoid3.h"	/* stack depth 1 */
/* #line 1	"model_archive.h"	/* stack depth 2 */
/* #line 1	"joint.h"	/* stack depth 3 */
/* #line 4	"model_archive.h"	/* stack depth 2 */
typedef struct ModelAnimation {
HSD_JObjDesc *joint;
struct HSD_AnimJoint **joint_animations;
struct HSD_MatAnimJoint **material_animations;
struct HSD_ShapeAnimJoint **shape_animations;
} ModelAnimation;
typedef struct ModelLightAnimation {
struct HSD_LightDesc *light;
struct HSD_LightAnim **animations;
} ModelLightAnimation;
typedef struct ModelAnimationTable {
ModelAnimation **models;
union HSD_CObjDesc **camera;
ModelLightAnimation **lights;
struct HSD_FogDesc **fog;
} ModelAnimationTable;
typedef struct ModelArchive {
char name[0x20];
struct HSD_Archive *model_data;
ModelAnimationTable *animations;
void *owned_data;
struct HSD_CObj *camera;
struct HSD_LObj *lights;
struct HSD_Fog *fog;
s32 model_count;
HSD_JObj *models[1];
} ModelArchive;
extern ModelArchive *LoadArc2(char *name);
extern void PurgeArc2(ModelArchive *archive);
extern void SetAnimArc2(ModelArchive *archive, s32 model, s32 selected);
/* #line 6	"zoid3.h"	/* stack depth 1 */
enum ZoidAIMode {
AI_MODE_NONE,
AI_MODE_POINT,
AI_MODE_TARGET,
AI_MODE_RUN
};
enum ZoidAIRadius {
AI_RADIUS_NONE,
AI_RADIUS_EXACT,
AI_RADIUS_IN,
AI_RADIUS_OUT
};
enum ZoidAIAngle {
AI_ANGLE_NONE,
AI_ANGLE_KEEP,
AI_ANGLE_CIRCLE
};
enum ZoidAIPartnerCommand {
AI_PARTNER_NONE,
AI_PARTNER_ATTACK_LOCKED,
AI_PARTNER_COME_NEAR,
AI_PARTNER_KEEP_DISTANCE,
AI_PARTNER_CLOSE_COMBAT
};
typedef struct ZoidAIState {
s32 nearest_enemies[16];
s32 mode;
u32 flags;
s32 target_index;
Vec3 destination;
Vec3 field_58;
f32 target_distance;
f32 target_angle;
s32 turn_speed;
s32 field_70;
Vec3 goal;
s32 missile_hit;
s32 partner_command;
} ZoidAIState;
typedef char ZoidAIStateSizeCheck[sizeof(ZoidAIState) == 0x88 ? 1 : -1];
typedef struct WeaponMountEntry {
s32 active;
s32 slot;
s32 field_08;
} WeaponMountEntry;
typedef struct WeaponMount {
s32 active;
s32 state;
WeaponMountEntry entries[4];
} WeaponMount;
enum ZoidWeaponMountIndex {
WEAPON_MOUNT_SHIELD = 10,
WEAPON_MOUNT_BOOSTER = 11,
WEAPON_MOUNT_SMOKE_MINE = 12,
WEAPON_MOUNT_SUPER_ATTACK = 19
};
enum ZoidOptionType {
ZOID_OPTION_NONE,
ZOID_OPTION_SHIELD,
ZOID_OPTION_BOOSTER,
ZOID_OPTION_CAMOUFLAGE,
ZOID_OPTION_SMOKE,
ZOID_OPTION_MINE
};
enum ZoidStelState {
ZOID_STEL_OFF,
ZOID_STEL_FADING,
ZOID_STEL_ON
};
typedef struct WeaponSlot {
s32 weapon;
s32 field_04;
HSD_JObj *joint;
} WeaponSlot;
typedef struct CameraMountInfo {
s32 joint_slot;
s32 angle;
s32 distance;
s32 height;
} CameraMountInfo;
typedef struct ZoidControlData {
s32 ground_modes[22];
u8 reserved_0058[0x40];
s32 max_senter_roll;
s32 field_009C;
s32 field_00A0;
s32 field_00A4;
s32 anim6_rate;
s32 max_reverse_speed;
s32 anim3_rate;
s32 anim4_min_speed;
s32 anim4_rate;
s32 base_max_speed;
s32 anim5_rate;
s32 max_steer;
s32 max_f_base_ry;
s32 max_face_yaw;
s32 step_launch_y;
s32 acceleration;
s32 deceleration;
s32 stick_turn_rate;
s32 sweep_radius;
s32 max_unsupported_frames;
f32 field_00E8;
f32 field_00EC;
f32 field_00F0;
s32 field_00F4;
s32 field_00F8;
s32 sweep_joint_index;
s32 field_0100;
u8 reserved_0104[0x3C];
s32 field_0140[20];
s32 attack_chain_length;
CameraMountInfo camera_mounts[20];
u8 reserved_02D4[0x10];
s32 pull_range_offset;
u8 reserved_02E8[4];
s32 dmg3_launch_scale;
s32 down_input_frames;
s32 max_down_frames;
u8 reserved_02F8[0x10];
s32 detail_distance;
} ZoidControlData;
typedef char ZoidControlDataSizeCheck[sizeof(ZoidControlData) == 0x30C ? 1 : -1];
typedef struct ZoidAttackObject {
HSD_JObj *joint;
f32 inverse[3][4];
u8 touched[16];
} ZoidAttackObject;
typedef char ZoidAttackObjectSizeCheck[sizeof(ZoidAttackObject) == 0x44 ? 1 : -1];
typedef struct FootJoint {
HSD_JObj *joint;
f32 offset;
f32 ground;
f32 height;
f32 depth;
f32 field_14;
f32 field_18;
f32 rot_z;
f32 rot_x;
u32 flags;
s32 no_contact_frames;
f32 field_2C;
u16 ground_polygon_index;
u8 reserved_32[2];
} FootJoint;
typedef char FootJointSizeCheck[sizeof(FootJoint) == 0x34 ? 1 : -1];
typedef struct ZoidLimb {
f32 position[3];
u8 reserved_0C[0xC];
HSD_JObj *joint;
} ZoidLimb;
enum ZoidAction {
ZOID_ACTION_WALK,
ZOID_ACTION_JUMP_1,
ZOID_ACTION_JUMP_2,
ZOID_ACTION_TURN,
ZOID_ACTION_TURN_R0,
ZOID_ACTION_TURN_L0,
ZOID_ACTION_TURN_R1,
ZOID_ACTION_TURN_L1,
ZOID_ACTION_TURN_R2,
ZOID_ACTION_TURN_L2,
ZOID_ACTION_STOP,
ZOID_ACTION_ATTACK_0,
ZOID_ACTION_ATTACK_1,
ZOID_ACTION_ATTACK_2,
ZOID_ACTION_ATTACK_3,
ZOID_ACTION_ATTACK_4,
ZOID_ACTION_ATTACK_5,
ZOID_ACTION_ATTACK_6,
ZOID_ACTION_ATTACK_7,
ZOID_ACTION_ATTACK_8,
ZOID_ACTION_ATTACK_9,
ZOID_ACTION_STEP_0,
ZOID_ACTION_STEP_1,
ZOID_ACTION_STEP_2,
ZOID_ACTION_STEP_3,
ZOID_ACTION_DMG2_0,
ZOID_ACTION_DMG2_1,
ZOID_ACTION_DMG2_2,
ZOID_ACTION_DMG2_3,
ZOID_ACTION_DMG2_4,
ZOID_ACTION_DMG2_5,
ZOID_ACTION_DMG2_6,
ZOID_ACTION_DMG3_0,
ZOID_ACTION_DMG3_1,
ZOID_ACTION_DMG3_2,
ZOID_ACTION_DMG3_3,
ZOID_ACTION_DMG3_4,
ZOID_ACTION_DMG3_5,
ZOID_ACTION_DMG3_6,
ZOID_ACTION_DEADLY,
ZOID_ACTION_DEAD,
ZOID_ACTION_DEATH,
ZOID_ACTION_DASH,
ZOID_ACTION_STEP_REQUEST_0,
ZOID_ACTION_STEP_REQUEST_1,
ZOID_ACTION_STEP_REQUEST_2,
ZOID_ACTION_STEP_REQUEST_3
};
typedef struct ZoidState {
char name[0x20];
s32 type;
s32 person;
void *field_0028;
void *camera;
struct HSD_Archive *archive;
ModelAnimationTable *animations;
void *field_0038;
void *field_003C;
HSD_JObj *joint;
JointPose *pose;
struct HSD_AObj *aobj;
u8 pad_004C[0x14];
f32 field_0060;
u8 pad_0064[0x8];
s32 field_006C;
s32 field_0070;
u8 pad_0074[0xd4];
s32 field_0148;
s32 field_014C;
s32 field_0150;
s32 health;
s32 max_health;
s16 option_type;
u8 option_use_state;
u8 option_use_previous;
s16 option_energy_max;
s16 option_energy;
s16 option_start_cost;
s16 option_hold_cost;
s16 option_recharge;
s16 booster_on;
s16 field_016C;
u8 pad_016E[0x2];
s32 field_0170;
s16 additional_parts[3];
u8 pad_017A[0x2];
CoDamage damages[6];
ZoidAttackObject attack_objects[10];
u8 body_coobj[0xA0];
u8 head_coobj[0xA0];
u8 neck_coobj[0xA0];
u8 bust_coobj[0xA0];
u8 hip_coobj[0xA0];
u8 tail_coobjs[8][0xA0];
u8 l_arm1_coobj[0xA0];
u8 l_arm2_coobj[0xA0];
u8 r_arm1_coobj[0xA0];
u8 r_arm2_coobj[0xA0];
u8 l_leg1_coobj[0xA0];
u8 l_leg2_coobj[0xA0];
u8 r_leg1_coobj[0xA0];
u8 r_leg2_coobj[0xA0];
u8 l_foot_coobj[0xA0];
u8 r_foot_coobj[0xA0];
HSD_JObj *body_base_joint;
HSD_JObj *head_base_joint;
u8 pad_12D4[0x4];
HSD_JObj *bust_base_joint;
HSD_JObj *hip_base_joint;
HSD_JObj *tail_base_joints[8];
s32 super_attack_enabled;
s32 super_attack_cooldown;
s32 super_attack_input;
s32 face_lock;
s32 mount_has_weapon[20];
s32 field_1360;
s32 field_1364;
s32 weapon_mount;
s32 weapon_mount_count;
s32 selected_weapon_mount;
s32 field_1374;
WeaponMount weapon_mounts[20];
WeaponMountEntry mount_extra[20];
WeaponSlot weapon_slots[30];
s32 camera_joint;
f32 clip_point[3];
f32 field_1A40[3];
f32 previous_child_translation[3];
f32 child_translation_delta[3];
f32 child_translation[3];
s32 ground_turn;
s32 field_1A74;
f32 field_1A78;
HSD_JObj *field_1A7C;
f32 field_1A80[3];
f32 field_1A8C[3];
s32 field_1A98;
f32 field_1A9C[3];
f32 field_1AA8;
HSD_JObj *spik_joints[6];
HSD_JObj *f_base_joint;
HSD_JObj *b_base_joint;
HSD_JObj *field_1ACC;
HSD_JObj *buckle_joint;
u8 pad_1AD4[0x4];
HSD_JObj *field_1AD8;
HSD_JObj *field_1ADC;
u8 pad_1AE0[0x4];
HSD_JObj *field_1AE4;
f32 senter_translation_y;
f32 senter_translation_z;
f32 senter_roll;
f32 senter_roll_speed;
FootJoint feet[4];
f32 ground_normal_sum[3];
s32 ground_normal_count;
s32 foot_count;
u8 pad_1BDC[0x4];
s32 death_pending;
s32 field_1BE4;
u8 pad_1BE8[0x4];
void *field_1BEC;
f32 ground_height;
f32 field_19FC;
u8 pad_1BF8[0x4];
s32 field_1BFC;
s32 foot_contacts;
u32 field_1C04;
s32 grounded;
s32 grounded_frames;
f32 max_ground_depth;
s32 field_1C14;
f32 position[3];
f32 field_1C24[3];
f32 height_offset;
s32 field_1C34;
f32 height_offset_speed;
f32 child_translation_y;
s32 field_1C40;
s32 movement_flags;
s32 field_1C48;
s32 field_1C4C;
f32 step_heading;
f32 field_1C54;
f32 field_1C58;
f32 stick_steady_frames;
f32 stick_frames;
f32 stick_angle;
f32 field_1C68;
f32 field_1C6C;
f32 field_1C70;
f32 field_1C74;
f32 field_1C78;
f32 heading;
f32 high_angle;
f32 field_1C84;
u8 pad_1C88[0x4];
f32 field_1C8C;
f32 field_1C90[3];
f32 field_1C9C;
s32 field_1CA0;
f32 steer;
f32 f_base_ry;
f32 f_base_ry_speed;
f32 face_yaw;
f32 face_pitch;
s32 field_1CB8;
f32 field_1CBC;
f32 field_1CC0[3];
s32 field_1CCC;
f32 ground_rx;
f32 ground_rz;
f32 f_base_rx;
f32 f_base_rz;
u8 pad_1CE0[0x8];
f32 field_1CE8;
f32 slide_speed;
f32 field_1CF0;
s32 slide_frames;
s32 field_1CF8;
f32 launch_velocity[3];
f32 step_launch_x;
f32 step_launch_y;
f32 step_launch_z;
f32 knockback[3];
f32 field_1D20[3];
f32 field_1D2C;
f32 displacement[3];
f32 speed;
f32 previous_displacement[3];
f32 displacement_change[3];
f32 field_1D58;
f32 field_1D5C;
f32 field_1D60;
s32 effect_mounts[5][3];
s32 field_1DA0;
s32 requested_action;
s32 action;
s32 field_1DAC;
s32 field_1DB0;
s32 action_phase;
s32 gene_frames;
u32 field_1DBC;
s32 jump_phase;
s32 jump_attack_phase;
f32 velocity[3];
s32 field_1DD4;
s32 field_1DD8;
s32 current_animation;
s32 previous_animation;
s32 field_1DE4;
f32 anim_rate;
s32 field_1DEC;
s32 attack_index;
s32 field_1DF4;
s32 field_1DF8;
s32 field_1DFC;
f32 child_matrix[3][4];
f32 heading_delta;
s32 anim1_frames;
f32 animation_end_frame;
s32 animation_stopped;
s32 animation_looped;
f32 anim_current_frame;
s32 animation_frame;
u16 ally_smoke_timer;
u16 enemy_smoke_timer;
s32 field_1E50;
s32 field_1E54;
s32 health_bar_timer;
s32 field_1E5C;
s32 field_1E60;
s32 field_1E64;
s32 field_1E68;
s32 death_started;
s32 lock_frames;
s32 field_1E74;
s32 field_1E78;
s32 field_1E7C;
s32 rumble_timer;
u8 index;
u8 slot;
u8 target_pending;
u8 lock_active;
u8 target_slot;
u8 lock_obj;
u8 pad_1E8A[0x2];
f32 field_1E8C;
Vec3 *lock_point;
f32 field_1E94;
s8 attack_target;
u8 pad_1E99[0x1];
u8 field_1E9A;
u8 pad_1E9B[0x5];
s32 field_1EA0;
u8 pad_1EA4[0x8];
u16 field_1EAC;
u16 field_1EAE;
u16 field_1EB0;
u16 field_1EB2;
u16 contact_bits;
u16 ground_polygon;
u16 field_1EB8;
u16 field_1EBA;
f32 previous_position[3];
struct GroundMask *ground_material;
Vec3 *ground_normal;
s32 option_active;
s32 stel_state;
s32 previous_stel_state;
u32 transparency_flags;
f32 transformation;
s32 interpolation_remaining;
s32 interpolation_duration;
s32 kills;
s32 field_1EF0;
s32 field_1EF4;
f32 field_1EF8;
f32 search_range;
s32 armor;
s32 field_1F04;
f32 distances[16];
f32 field_1F48[16];
u8 contact[16];
u8 attack_in_range[16];
u8 target_visibility[16];
f32 target_angles[16];
f32 field_1FF8[24];
f32 field_2058;
f32 field_205C;
s32 field_2060;
u16 *slider_info;
u16 slider_positions[11];
u8 pad_207E[0x12];
void *field_2090;
void *anim_data;
ZoidAIState *ai;
s32 ai_active;
s32 field_20A0;
s32 gene_x;
s32 gene_z;
s32 gene_y;
s32 gene_y_fixed;
s32 field_20B4;
s32 field_20B8;
s32 field_20BC;
s32 field_20C0;
s32 field_20C4;
s32 radar_range_bonus;
s32 search_range_bonus;
s32 field_20D0;
s32 armor_bonus;
s32 field_20D8;
s32 speed_bonus;
s32 bullet_power_bonus;
s32 melee_power_bonus;
s32 turn_bonus;
s32 field_20EC;
u8 pad_20F0[0x4];
s32 field_20F4;
s32 field_20F8;
u8 cg_table[0x2000];
s32 field_40FC;
} ZoidState;
typedef char ZoidStateSizeCheck[sizeof(ZoidState) == 0x4100 ? 1 : -1];
extern ZoidState Zoid[16];
/* #line 1	"ZoidWalk.c"	/* stack depth 0 */
extern void ZoidWalkSumuSpd(ZoidState *zoid);
extern void ZoidWalkSusumu(ZoidState *zoid);
extern void ZoidWalkSusumu3(ZoidState *zoid);
void ZoidWalk(ZoidState *zoid)
{
s32 i = 0;
if (zoid) i = 0;
ZoidWalkSumuSpd(zoid);
if (zoid->field_0170 != 0) {
ZoidWalkSusumu3(zoid);
} else {
ZoidWalkSusumu(zoid);
}
}
