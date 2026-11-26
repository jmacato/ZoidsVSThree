#include "weapon.h"

extern void ZeroMemory(void *memory, s32 size);

void sWeaponPrologue(void)
{
    ZeroMemory(sWeapon, 0x2ADF0);
}
