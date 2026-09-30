/* Address: 0006670c; name: FUN_0006670c; body bytes: 144 */

undefined4 FUN_0006670c(int *param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 1;
  if (((param_1 == (int *)0x0) || (param_1[0xf] == 0)) ||
     (0xffffffffU / (uint)param_1[0xf] < (uint)param_1[0x10])) {
    uVar2 = 0;
  }
  else {
    enter_critical();
    param_1[2] = param_1[0xf] * param_1[0x10] + *param_1;
    param_1[0xe] = 0;
    param_1[1] = *param_1;
    param_1[3] = (param_1[0xf] + -1) * param_1[0x10] + *param_1;
    *(undefined1 *)(param_1 + 0x11) = 0xff;
    *(undefined1 *)((int)param_1 + 0x45) = 0xff;
    if (param_2 == 0) {
      if ((param_1[4] != 0) && (iVar1 = FUN_00066ea4(param_1 + 4), iVar1 != 0)) {
        DAT_e000ed04 = 0x10000000;
        DataSynchronizationBarrier(0xf);
        InstructionSynchronizationBarrier(0xf);
      }
    }
    else {
      FUN_000656b6();
      FUN_000656b6(param_1 + 9);
    }
    exit_critical();
  }
  return uVar2;
}

