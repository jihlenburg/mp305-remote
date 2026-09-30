/* Address: 0006590c; name: FUN_0006590c; body bytes: 146 */

void FUN_0006590c(int param_1)

{
  int iVar1;
  
  enter_critical();
  if (param_1 == 0) {
    param_1 = DAT_1ffe0000;
  }
  iVar1 = FUN_00065666(param_1 + 4);
  if (iVar1 == 0) {
    if ((&DAT_1ffe0d9c)[*(uint *)(param_1 + 0x2c) * 5] == 0) {
      DAT_1ffe0010 = DAT_1ffe0010 & ~(1 << (*(uint *)(param_1 + 0x2c) & 0xff));
    }
  }
  if (*(int *)(param_1 + 0x28) != 0) {
    FUN_00065666(param_1 + 0x18);
  }
  DAT_1ffe0024 = DAT_1ffe0024 + 1;
  if (param_1 == DAT_1ffe0000) {
    FUN_00065702(&DAT_1ffe0e3c,param_1 + 4);
    DAT_1ffe0004 = DAT_1ffe0004 + 1;
  }
  else {
    DAT_1ffe0008 = DAT_1ffe0008 + -1;
    FUN_00059e24();
  }
  exit_critical();
  if (param_1 != DAT_1ffe0000) {
    FUN_00059a8e(param_1);
  }
  if ((DAT_1ffe0014 != 0) && (param_1 == DAT_1ffe0000)) {
    DAT_e000ed04 = 0x10000000;
    DataSynchronizationBarrier(0xf);
    InstructionSynchronizationBarrier(0xf);
  }
  return;
}

