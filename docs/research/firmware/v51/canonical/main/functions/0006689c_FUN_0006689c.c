/* Address: 0006689c; name: FUN_0006689c; body bytes: 126 */

undefined4 FUN_0006689c(int param_1,undefined4 param_2,undefined4 *param_3,int param_4)

{
  char cVar1;
  bool bVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  
  FUN_000657c0();
  uVar6 = 0;
  bVar2 = (bool)isCurrentModePrivileged();
  if (bVar2) {
    uVar6 = getBasePriority();
  }
  bVar2 = (bool)isCurrentModePrivileged();
  if (bVar2) {
    setBasePriority(0x50);
  }
  DataSynchronizationBarrier(0xf);
  InstructionSynchronizationBarrier(0xf);
  if ((*(uint *)(param_1 + 0x38) < *(uint *)(param_1 + 0x3c)) || (param_4 == 2)) {
    cVar1 = *(char *)(param_1 + 0x45);
    FUN_00059a22(param_1,param_2,param_4);
    if ((int)cVar1 == 0xffffffff) {
      if (((*(int *)(param_1 + 0x24) != 0) && (iVar5 = FUN_00066ea4(param_1 + 0x24), iVar5 != 0)) &&
         (param_3 != (undefined4 *)0x0)) {
        *param_3 = 1;
      }
    }
    else {
      uVar4 = FUN_0006568c();
      if ((uint)(int)cVar1 < uVar4) {
        *(char *)(param_1 + 0x45) = cVar1 + '\x01';
      }
    }
    uVar3 = 1;
  }
  else {
    uVar3 = 0;
  }
  bVar2 = (bool)isCurrentModePrivileged();
  if (bVar2) {
    setBasePriority(uVar6);
  }
  return uVar3;
}

