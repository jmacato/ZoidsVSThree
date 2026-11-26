#include "types.h"
#include "asm_ops.h"

#pragma optimization_level 0
#pragma peephole off

void Reset(u32 resetCode)
{
    ASM_INSN(b lab_20);
    ASM_INSN(lab_4: mfspr r8, 1008);
    ASM_INSN(ori r8, r8, 8);
    ASM_INSN(mtspr 1008, r8);
    ASM_INSN(isync);
    ASM_INSN(sync);
    ASM_INSN(nop);
    ASM_INSN(b lab_24);
    ASM_INSN(lab_20: b lab_40);
    ASM_INSN(lab_24: mftb r5, 0x10c);
    ASM_INSN(lab_28: mftb r6, 0x10c);
    ASM_INSN(subf r7, r5, r6);
    ASM_INSN(cmplwi r7, 0x1124);
    ASM_INSN(blt lab_28);
    ASM_INSN(nop);
    ASM_INSN(b lab_44);
    ASM_INSN(lab_40: b lab_60);
    ASM_INSN(lab_44: lis r8, -0x3400);
    ASM_INSN(ori r8, r8, 0x3000);
    ASM_INSN(li r4, 3);
    ASM_INSN(stw r4, 0x24(r8));
    ASM_INSN(stw r3, 0x24(r8));
    ASM_INSN(nop);
    ASM_INSN(b lab_64);
    ASM_INSN(lab_60: b lab_6c);
    ASM_INSN(lab_64: nop);
    ASM_INSN(b lab_64);
    ASM_INSN(lab_6c: b lab_4);
}
