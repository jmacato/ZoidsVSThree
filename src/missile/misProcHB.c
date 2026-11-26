#include "ground_collision.h"
#include "model_archive.h"
#include "angle.h"
#include "matrix.h"
#include "joint_matrix.h"

typedef struct Missile3 {
    u8 pad_00[0x3C];
    u8 pad_3C[4];
    f32 velocity[3];
    f32 spin;
    f32 speed;
    f32 turn_rate;
    f32 matrix[3][4];
    u8 pad_88[0x30];
    f32 step_length;
    f32 inverse[3][4];
} Missile3;

extern void PSMTXRotRad(Mtx m, char axis, f32 rad);
extern f32 atan2f(f32, f32);

void misProcHB(Missile3 *missile, Vec3 *target)
{
    Vec3 local;
    Mtx rot;
    f32 pitch;
    Vec3 position;
    f32 angle;
    f32 diff;
    f32 horizontal_speed;
    s32 i;

    for (i = 0; i < 3; i++) {
        (&position.x)[i] = missile->matrix[i][3];
    }
    angle = DEG2RAD_D(3.0);
    if (missile->matrix[1][0] > 0.0f) {
        PSMTXRotRad(rot, 'Z', -angle);
        PSMTXConcat(missile->matrix, rot, missile->matrix);
    }
    if (missile->matrix[1][0] < 0.0f) {
        PSMTXRotRad(rot, 'Z', angle);
        PSMTXConcat(missile->matrix, rot, missile->matrix);
    }
    angle = sColPosY(&position, 0);
    if (position.y > 1.0f + angle) {
        missile->velocity[1] -= 0.025;
        for (i = 0; i < 3; i++) {
            (&position.x)[i] += missile->velocity[i];
        }
        angle = sColPosY(&position, 0);
        if (position.y > 0.07 + angle) {
            for (i = 0; i < 3; i++) {
                missile->matrix[i][3] = (&position.x)[i];
            }
            return;
        }
        for (i = 0; i < 3; i++) {
            missile->velocity[i] *= 0.5f;
        }
        missile->velocity[1] = 0.0f;
        missile->matrix[1][3] = 1.0f + angle;
        return;
    }
    position.y = 1.0f + angle;
    missile->velocity[1] = 0.0f;
    PSMTXMultVec(missile->inverse, target, &local);
    if (local.z < 0.0f) {
        angle = missile->turn_rate;
        missile->spin += angle;
        PSMTXRotRad(rot, 'Y', angle);
        PSMTXConcat(missile->matrix, rot, missile->matrix);
    }
    if (local.z > 0.0f) {
        angle = -missile->turn_rate;
        missile->spin += angle;
        PSMTXRotRad(rot, 'Y', angle);
        PSMTXConcat(missile->matrix, rot, missile->matrix);
    }
    if (missile->speed <= 0.0f)
        return;
    missile->velocity[0] = missile->matrix[0][0] * missile->speed;
    missile->velocity[2] = missile->matrix[2][0] * missile->speed;
    for (i = 0; i < 3; i++) {
        (&position.x)[i] += missile->velocity[i];
    }
    angle = sColPosY(&position, 0);
    diff = angle - missile->matrix[1][3];
    horizontal_speed = missile->speed;
    pitch = atan2f(diff, horizontal_speed);
    position.y = missile->matrix[1][3];
    angle = sColPosY(&position, 0);
    position.y = 0.1 + angle;
    for (i = 0; i < 3; i++) {
        missile->matrix[i][3] = (&position.x)[i];
    }
}
