/* Address: 00047b78; name: FUN_00047b78; body bytes: 266 */

void FUN_00047b78(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  undefined1 auStack_24 [8];
  
  if (10 < (*(ushort *)(param_1 + 0x58) & 0xfff) >> 8) {
    param_2 = 0;
    param_3 = 0;
  }
  if ((*(int *)(param_1 + 0x50) != param_2) || (*(int *)(param_1 + 0x54) != param_3)) {
    FUN_0004ef90(param_1);
    uVar1 = FUN_0004ccf8(param_1);
    uVar2 = FUN_0004bbec(param_1);
    FUN_00047af8(param_1,auStack_24);
    FUN_0004747e(&local_34,uVar1,uVar2,*(undefined4 *)(param_1 + 0x44),
                 *(undefined2 *)(param_1 + 0x48),*(undefined2 *)(param_1 + 0x4c),auStack_24);
    local_34 = *(int *)(param_1 + 0x14) + local_34;
    local_30 = *(int *)(param_1 + 0x18) + local_30;
    local_2c = *(int *)(param_1 + 0x14) + local_2c;
    local_28 = *(int *)(param_1 + 0x18) + local_28;
    FUN_0004d40e(param_1,&local_34);
    FUN_0004f266(param_1 + 0x50,param_2,param_3);
    uVar3 = FUN_0004bb48(param_1);
    FUN_00040850(uVar3,0);
    FUN_0004de6c(param_1);
    FUN_00040850(uVar3,1);
    FUN_00047af8(param_1,auStack_24);
    FUN_0004747e(&local_34,uVar1,uVar2,*(undefined4 *)(param_1 + 0x44),
                 *(undefined2 *)(param_1 + 0x48),*(undefined2 *)(param_1 + 0x4c),auStack_24);
    local_34 = local_34 + *(int *)(param_1 + 0x14);
    local_30 = local_30 + *(int *)(param_1 + 0x18);
    local_2c = local_2c + *(int *)(param_1 + 0x14);
    local_28 = local_28 + *(int *)(param_1 + 0x18);
    FUN_0004d40e(param_1,&local_34);
  }
  return;
}

