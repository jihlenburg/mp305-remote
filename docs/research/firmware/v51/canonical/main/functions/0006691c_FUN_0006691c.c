/* Address: 0006691c; name: FUN_0006691c; body bytes: 240 */

undefined4 FUN_0006691c(int param_1,undefined4 param_2,int param_3)

{
  bool bVar1;
  int iVar2;
  undefined1 auStack_38 [12];
  int iStack_2c;
  undefined4 uStack_28;
  int local_24;
  
  bVar1 = false;
  iStack_2c = param_1;
  uStack_28 = param_2;
  local_24 = param_3;
  FUN_00066c00();
  while( true ) {
    enter_critical();
    iVar2 = *(int *)(param_1 + 0x38);
    if (iVar2 != 0) {
      FUN_000599fc(param_1,param_2);
      *(int *)(param_1 + 0x38) = iVar2 + -1;
      if ((*(int *)(param_1 + 0x10) != 0) && (iVar2 = FUN_00066ea4(param_1 + 0x10), iVar2 != 0)) {
        DAT_e000ed04 = 0x10000000;
        DataSynchronizationBarrier(0xf);
        InstructionSynchronizationBarrier(0xf);
      }
      exit_critical();
      return 1;
    }
    if (local_24 == 0) break;
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
    iVar2 = FUN_00066b3c(auStack_38,&local_24);
    if (iVar2 == 0) {
      iVar2 = FUN_00059c50(param_1);
      if (iVar2 == 0) {
        FUN_00059ed0(param_1);
        FUN_00066f6c();
      }
      else {
        FUN_000659c8(param_1 + 0x24,local_24);
        FUN_00059ed0(param_1);
        iVar2 = FUN_00066f6c();
        if (iVar2 == 0) {
          DAT_e000ed04 = 0x10000000;
          DataSynchronizationBarrier(0xf);
          InstructionSynchronizationBarrier(0xf);
        }
      }
    }
    else {
      FUN_00059ed0();
      FUN_00066f6c();
      iVar2 = FUN_00059c50(param_1);
      if (iVar2 != 0) {
        return 0;
      }
    }
  }
  exit_critical();
  return 0;
}

