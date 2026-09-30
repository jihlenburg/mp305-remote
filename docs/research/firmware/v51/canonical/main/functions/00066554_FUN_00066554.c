/* Address: 00066554; name: FUN_00066554; body bytes: 176 */

uint FUN_00066554(uint *param_1,uint param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 0;
  FUN_00066c00();
  FUN_00065c04();
  uVar2 = *param_1;
  iVar1 = FUN_00059e98(uVar2,param_2,param_4);
  if (iVar1 == 0) {
    if (param_5 != 0) {
      if (param_3 != 0) {
        uVar3 = 0x1000000;
      }
      if (param_4 != 0) {
        uVar3 = uVar3 | 0x4000000;
      }
      FUN_00065a28(param_1 + 1,param_2 | uVar3,param_5);
      iVar1 = FUN_00066f6c();
      if (iVar1 == 0) {
        DAT_e000ed04 = 0x10000000;
        DataSynchronizationBarrier(0xf);
        InstructionSynchronizationBarrier(0xf);
      }
      uVar2 = FUN_00065698();
      if (-1 < (int)(uVar2 << 6)) {
        enter_critical();
        uVar2 = *param_1;
        iVar1 = FUN_00059e98(uVar2,param_2,param_4);
        if ((iVar1 != 0) && (param_3 != 0)) {
          *param_1 = *param_1 & ~param_2;
        }
        exit_critical();
      }
      return uVar2 & 0xffffff;
    }
  }
  else if (param_3 != 0) {
    *param_1 = *param_1 & ~param_2;
  }
  FUN_00066f6c();
  return uVar2;
}

