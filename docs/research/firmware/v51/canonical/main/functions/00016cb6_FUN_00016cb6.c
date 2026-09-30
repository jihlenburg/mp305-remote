/* Address: 00016cb6; name: FUN_00016cb6; body bytes: 104 */

void FUN_00016cb6(int param_1,char param_2)

{
  uint uVar1;
  
  if (param_1 != 0) {
    FUN_00016d4c();
    uVar1 = (uint)*(short *)(param_1 + 2);
    if (-1 < (int)uVar1) {
      (&DAT_e000e280)[uVar1 >> 5] = 1 << (uVar1 & 0x1f);
    }
    uVar1 = (uint)*(short *)(param_1 + 2);
    if ((int)uVar1 < 0) {
      (&DAT_e000ed14)[uVar1 & 0xf] = param_2 << 4;
    }
    else {
      (&DAT_e000e400)[uVar1] = param_2 << 4;
    }
    uVar1 = (uint)*(short *)(param_1 + 2);
    if (-1 < (int)uVar1) {
      (&DAT_e000e100)[uVar1 >> 5] = 1 << (uVar1 & 0x1f);
    }
  }
  return;
}

