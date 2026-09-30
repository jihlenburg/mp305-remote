/* Address: 00066a10; name: FUN_00066a10; body bytes: 296 */

undefined4 FUN_00066a10(int *param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined1 auStack_30 [12];
  int *piStack_24;
  int local_20;
  
  bVar1 = false;
  iVar3 = 0;
  piStack_24 = param_1;
  local_20 = param_2;
  FUN_00066c00();
  do {
    while( true ) {
      enter_critical();
      if (param_1[0xe] != 0) {
        param_1[0xe] = param_1[0xe] + -1;
        if (*param_1 == 0) {
          iVar3 = FUN_00059fd4();
          param_1[2] = iVar3;
        }
        if ((param_1[4] != 0) && (iVar3 = FUN_00066ea4(param_1 + 4), iVar3 != 0)) {
          DAT_e000ed04 = 0x10000000;
          DataSynchronizationBarrier(0xf);
          InstructionSynchronizationBarrier(0xf);
        }
        exit_critical();
        return 1;
      }
      if (local_20 == 0) goto LAB_00066a70;
      if (!bVar1) {
        FUN_000659ac(auStack_30);
        bVar1 = true;
      }
      exit_critical();
      FUN_00065c04();
      enter_critical();
      if ((char)param_1[0x11] == -1) {
        *(undefined1 *)(param_1 + 0x11) = 0;
      }
      if (*(char *)((int)param_1 + 0x45) == -1) {
        *(undefined1 *)((int)param_1 + 0x45) = 0;
      }
      exit_critical();
      iVar2 = FUN_00066b3c(auStack_30,&local_20);
      if (iVar2 != 0) break;
      iVar2 = FUN_00059c50(param_1);
      if (iVar2 == 0) {
        FUN_00059ed0(param_1);
        FUN_00066f6c();
      }
      else {
        if (*param_1 == 0) {
          enter_critical();
          iVar3 = FUN_00066df4(param_1[2]);
          exit_critical();
        }
        FUN_000659c8(param_1 + 9,local_20);
        FUN_00059ed0(param_1);
        iVar2 = FUN_00066f6c();
        if (iVar2 == 0) {
          DAT_e000ed04 = 0x10000000;
          DataSynchronizationBarrier(0xf);
          InstructionSynchronizationBarrier(0xf);
        }
      }
    }
    FUN_00059ed0();
    FUN_00066f6c();
    iVar2 = FUN_00059c50(param_1);
  } while (iVar2 == 0);
  if (iVar3 != 0) {
    enter_critical();
    if (param_1[9] == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = 5 - *(int *)param_1[0xc];
    }
    FUN_00065a6c(param_1[2],iVar3);
LAB_00066a70:
    exit_critical();
  }
  return 0;
}

