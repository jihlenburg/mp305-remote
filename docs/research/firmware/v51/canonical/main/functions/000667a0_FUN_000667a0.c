/* Address: 000667a0; name: FUN_000667a0; body bytes: 246 */

undefined4 FUN_000667a0(int param_1,undefined4 param_2,int param_3,int param_4)

{
  bool bVar1;
  int iVar2;
  undefined1 auStack_38 [8];
  int iStack_30;
  undefined4 uStack_2c;
  int local_28;
  int iStack_24;
  
  bVar1 = false;
  iStack_30 = param_1;
  uStack_2c = param_2;
  local_28 = param_3;
  iStack_24 = param_4;
  FUN_00066c00();
  while( true ) {
    enter_critical();
    if ((*(uint *)(param_1 + 0x38) < *(uint *)(param_1 + 0x3c)) || (param_4 == 2)) {
      iVar2 = FUN_00059a22(param_1,param_2,param_4);
      if (*(int *)(param_1 + 0x24) != 0) {
        iVar2 = FUN_00066ea4(param_1 + 0x24);
      }
      if (iVar2 != 0) {
        DAT_e000ed04 = 0x10000000;
        DataSynchronizationBarrier(0xf);
        InstructionSynchronizationBarrier(0xf);
      }
      exit_critical();
      return 1;
    }
    if (local_28 == 0) {
      exit_critical();
      return 0;
    }
    if (!bVar1) {
      FUN_000659ac(auStack_38);
      bVar1 = true;
    }
    exit_critical();
    FUN_00065c04();
    enter_critical();
    if (*(char *)(param_1 + 0x44) == -1) {
      *(undefined1 *)(param_1 + 0x44) = 0;
    }
    if (*(char *)(param_1 + 0x45) == -1) {
      *(undefined1 *)(param_1 + 0x45) = 0;
    }
    exit_critical();
    iVar2 = FUN_00066b3c(auStack_38,&local_28);
    if (iVar2 != 0) break;
    enter_critical();
    if (*(int *)(param_1 + 0x38) == *(int *)(param_1 + 0x3c)) {
      exit_critical();
      FUN_000659c8(param_1 + 0x10,local_28);
      FUN_00059ed0(param_1);
      iVar2 = FUN_00066f6c();
      if (iVar2 == 0) {
        DAT_e000ed04 = 0x10000000;
        DataSynchronizationBarrier(0xf);
        InstructionSynchronizationBarrier(0xf);
      }
    }
    else {
      exit_critical();
      FUN_00059ed0(param_1);
      FUN_00066f6c();
    }
  }
  FUN_00059ed0(param_1);
  FUN_00066f6c();
  return 0;
}

