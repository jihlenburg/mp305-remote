/* Address: 00059d90; name: FUN_00059d90; body bytes: 98 */

void FUN_00059d90(uint param_1,int param_2,undefined4 param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int local_18;
  
  local_18 = param_4;
  FUN_00065c04();
  uVar1 = FUN_00059e40(&local_18);
  if (local_18 == 0) {
    if (param_2 == 0) {
      uVar3 = 0;
      if (param_1 <= uVar1) {
        FUN_00066f6c();
        FUN_00059c6c(param_1,uVar1);
        return;
      }
    }
    else if (*DAT_1ffe0050 == 0) {
      uVar3 = 1;
    }
    else {
      uVar3 = 0;
    }
    FUN_0006582c(DAT_1ffe0040,param_1 - uVar1,uVar3);
    iVar2 = FUN_00066f6c();
    if (iVar2 == 0) {
      DAT_e000ed04 = 0x10000000;
      DataSynchronizationBarrier(0xf);
      InstructionSynchronizationBarrier(0xf);
      return;
    }
  }
  else {
    FUN_00066f6c();
  }
  return;
}

