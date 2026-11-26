#include "zoid3.h"

typedef struct ZoidDataVS3 {
    u8 pad_0000[0xEE];
    s16 animation_sounds[175];
    s16 animation_volumes[175];
    s16 animation_effects[175];
    s16 animation_effect_mounts[175];
    u8 pad_0666[0x7FC - 0x666];
} ZoidDataVS3;

typedef struct CameraStateVS3 CameraStateVS3;

extern ZoidDataVS3 Tea_zoiddat[];
extern s32 gameEndF;
extern CameraStateVS3 *camTmp;
extern void camSeTm(CameraStateVS3 *camera, s16 sound, Vec3 *point, s16 volume);
extern void zdEffectMount(ZoidState *zoid, s32 mount, s32 effect);

void zdAnimEffect(ZoidState *zoid, s32 animation)
{
    s32 effect = Tea_zoiddat[zoid->type].animation_effects[animation];
    s32 mount = Tea_zoiddat[zoid->type].animation_effect_mounts[animation];
    s32 sound = Tea_zoiddat[zoid->type].animation_sounds[animation];
    s16 volume = Tea_zoiddat[zoid->type].animation_volumes[animation];

    if (sound > 0 && gameEndF <= 2) {
        camSeTm(camTmp, sound, (Vec3 *)zoid->position, volume);
    }
    if (effect < 0x88 && effect > 0 && mount <= 0x1B) {
        zdEffectMount(zoid, mount, effect);
    }
}
