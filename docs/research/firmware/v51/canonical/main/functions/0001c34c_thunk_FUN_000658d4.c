/* Address: 0001c34c; name: thunk_FUN_000658d4; body bytes: 4 */

void thunk_FUN_000658d4(int param_1)

{
  int iVar1;
  undefined4 extraout_r2;
  
  if (param_1 != 0) {
    FUN_00065c04(DAT_1ffe0034);
    FUN_0005982c(extraout_r2,0);
    iVar1 = FUN_00066f6c();
    if (iVar1 != 0) {
      return;
    }
  }
  DataSynchronizationBarrier(0xf);
  InstructionSynchronizationBarrier(0xf);
  DAT_e000ed04 = 0x10000000;
  return;
}

