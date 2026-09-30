/* Address: 00028100; name: FUN_00028100; body bytes: 326 */

void FUN_00028100(int param_1,undefined4 param_2,int param_3,int param_4)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  bool bVar7;
  int local_18;
  int local_14;
  
  local_18 = param_3;
  local_14 = param_4;
  iVar2 = FUN_0005051c();
  *(byte *)(param_1 + 0xa0) = *(byte *)(param_1 + 0xa0) | 1;
  if ((iVar2 == 0) || (iVar2 == 1)) goto LAB_0002815a;
  if (iVar2 != 2) {
    return;
  }
  uVar3 = FUN_00047eec();
  FUN_00048288(uVar3,&local_18);
  FUN_0004eef4(param_1,&local_18,3);
  iVar2 = FUN_0004c5ca(param_1,0);
  uVar4 = FUN_0003ac70(param_1);
  bVar7 = (uint)*(byte *)(param_1 + 0x4c) == (iVar2 == 1 & uVar4);
  if (uVar4 == 0) {
    if (bVar7) {
      if (local_14 < *(int *)(param_1 + 0x88)) goto LAB_0002815a;
      if (*(int *)(param_1 + 0x80) < local_14) goto LAB_000281f4;
    }
    else {
      if (*(int *)(param_1 + 0x90) < local_14) {
LAB_0002815a:
        *(int *)(param_1 + 0x9c) = param_1 + 0x2c;
        return;
      }
      if (local_14 < *(int *)(param_1 + 0x78)) {
LAB_000281f4:
        *(int *)(param_1 + 0x9c) = param_1 + 0x38;
        return;
      }
    }
    iVar5 = *(int *)(param_1 + 0x78) + (*(int *)(param_1 + 0x80) - *(int *)(param_1 + 0x78)) / 2;
    iVar2 = iVar5 - local_14;
    if (iVar2 < 1) {
      iVar2 = local_14 - iVar5;
    }
    iVar6 = *(int *)(param_1 + 0x88) + (*(int *)(param_1 + 0x90) - *(int *)(param_1 + 0x88)) / 2;
    iVar5 = iVar6 - local_14;
    if (iVar5 < 1) {
      iVar5 = local_14 - iVar6;
    }
  }
  else {
    if (bVar7) {
      if (*(int *)(param_1 + 0x8c) < local_18) goto LAB_0002815a;
      if (local_18 < *(int *)(param_1 + 0x74)) goto LAB_000281f4;
    }
    else {
      if (local_18 < *(int *)(param_1 + 0x84)) goto LAB_0002815a;
      if (*(int *)(param_1 + 0x7c) < local_18) goto LAB_000281f4;
    }
    iVar5 = *(int *)(param_1 + 0x74) + (*(int *)(param_1 + 0x7c) - *(int *)(param_1 + 0x74)) / 2;
    iVar2 = iVar5 - local_18;
    if (iVar2 < 1) {
      iVar2 = local_18 - iVar5;
    }
    iVar6 = *(int *)(param_1 + 0x84) + (*(int *)(param_1 + 0x8c) - *(int *)(param_1 + 0x84)) / 2;
    iVar5 = iVar6 - local_18;
    if (iVar5 < 1) {
      iVar5 = local_18 - iVar6;
    }
  }
  if (iVar5 < iVar2) {
    *(int *)(param_1 + 0x9c) = param_1 + 0x2c;
    bVar1 = *(byte *)(param_1 + 0xa0) & 0xfd;
  }
  else {
    *(int *)(param_1 + 0x9c) = param_1 + 0x38;
    bVar1 = *(byte *)(param_1 + 0xa0) | 2;
  }
  *(byte *)(param_1 + 0xa0) = bVar1;
  return;
}

