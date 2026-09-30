/* Address: ram:00001d1a; name: FUN_ram_00001d1a; body bytes: 106 */

void FUN_ram_00001d1a(uint *param_1,uint param_2,uint param_3)

{
  uint uVar1;
  uint extraout_t1;
  uint uVar2;
  uint extraout_a1;
  int extraout_a2;
  uint uVar3;
  uint *puVar4;
  int extraout_a4;
  int extraout_a5;
  
  gp = &DAT_ram_20002000;
  uVar1 = 0xf;
  if (0xf < param_3) {
    if (((uint)param_1 & 0xf) != 0) {
      (*(code *)(((uint)param_1 & 0xf) * 4 + 0x1d50))();
      param_1 = (uint *)(extraout_a4 - (extraout_a5 + -0x10));
      param_3 = extraout_a2 + extraout_a5 + -0x10;
      uVar1 = extraout_t1;
      param_2 = extraout_a1;
      if (param_3 <= extraout_t1) goto LAB_ram_00001d44;
    }
    uVar2 = 0;
    if (param_2 != 0) {
      uVar2 = param_2 & 0xff | (param_2 & 0xff) << 8;
      uVar2 = uVar2 | uVar2 << 0x10;
    }
    uVar3 = param_3 & 0xfffffff0;
    param_3 = param_3 & 0xf;
    puVar4 = (uint *)(uVar3 + (int)param_1);
    do {
      *param_1 = uVar2;
      param_1[1] = uVar2;
      param_1[2] = uVar2;
      param_1[3] = uVar2;
      param_1 = param_1 + 4;
    } while (param_1 < puVar4);
    if (param_3 == 0) {
      return;
    }
  }
LAB_ram_00001d44:
                    /* WARNING: Could not recover jumptable at 0x00001d50. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)(&UNK_ram_00001d54 + (uVar1 - param_3) * 4))();
  return;
}

