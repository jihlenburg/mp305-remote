/* Address: 00065144; name: FUN_00065144; body bytes: 354 */

void FUN_00065144(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  undefined1 auStack_24 [20];
  
  uVar4 = (*(ushort *)(param_1 + 0x58) & 0xfff) >> 8;
  if (uVar4 == 0xb) {
    FUN_00047c84(param_1,0);
    FUN_00047b78(param_1,0);
    if (*(int *)(param_1 + 0x3c) == 0) {
      return;
    }
    if (*(int *)(param_1 + 0x40) == 0) {
      return;
    }
    iVar6 = FUN_0004ccf8(param_1);
    iVar5 = (iVar6 << 8) / *(int *)(param_1 + 0x3c);
    iVar6 = FUN_0004bbec(param_1);
    iVar6 = (iVar6 << 8) / *(int *)(param_1 + 0x40);
  }
  else {
    if (uVar4 != 0xc) {
      return;
    }
    FUN_00047c84(param_1,0);
    FUN_00047b78(param_1,0);
    iVar5 = 0x100;
    iVar6 = 0x100;
  }
  FUN_0004ef90();
  uVar1 = FUN_0004ccf8(param_1);
  uVar2 = FUN_0004bbec(param_1);
  FUN_00047af8(param_1,auStack_24);
  FUN_0004747e(&local_34,uVar1,uVar2,*(undefined4 *)(param_1 + 0x44),*(undefined2 *)(param_1 + 0x48)
               ,*(undefined2 *)(param_1 + 0x4c),auStack_24);
  local_34 = local_34 + *(int *)(param_1 + 0x14) + -1;
  local_30 = local_30 + *(int *)(param_1 + 0x18) + -1;
  local_2c = local_2c + *(int *)(param_1 + 0x14) + 1;
  local_28 = local_28 + *(int *)(param_1 + 0x18) + 1;
  FUN_0004d40e(param_1,&local_34);
  *(int *)(param_1 + 0x48) = iVar5;
  *(int *)(param_1 + 0x4c) = iVar6;
  uVar3 = FUN_0004bb48(param_1);
  FUN_00040850(uVar3,0);
  FUN_0004de6c(param_1);
  FUN_00040850(uVar3,1);
  FUN_0004747e(&local_34,uVar1,uVar2,*(undefined4 *)(param_1 + 0x44),*(undefined2 *)(param_1 + 0x48)
               ,*(undefined2 *)(param_1 + 0x4c),auStack_24);
  local_34 = local_34 + *(int *)(param_1 + 0x14) + -1;
  local_30 = local_30 + *(int *)(param_1 + 0x18) + -1;
  local_2c = local_2c + *(int *)(param_1 + 0x14) + 1;
  local_28 = local_28 + *(int *)(param_1 + 0x18) + 1;
  FUN_0004d40e(param_1,&local_34);
  return;
}

