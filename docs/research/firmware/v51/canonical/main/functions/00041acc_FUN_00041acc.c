/* Address: 00041acc; name: FUN_00041acc; body bytes: 168 */

void FUN_00041acc(undefined4 param_1,int param_2,undefined4 *param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  
  if ((((*(int *)(param_2 + 0x1c) != 0) && (2 < *(byte *)(param_2 + 0x4c))) &&
      (0 < *(int *)(param_2 + 0x30))) && (0 < *(int *)(param_2 + 0x34))) {
    iVar3 = param_2;
    puVar6 = param_3;
    iVar1 = FUN_0004a318(0x6c);
    FUN_0004a404(iVar1,param_2,0x6c);
    iVar2 = FUN_0004775c(*(undefined4 *)(iVar1 + 0x1c),iVar1 + 0x20);
    if (iVar2 != 1) {
      FUN_00046bec(iVar1,iVar3,puVar6,param_4);
      return;
    }
    iVar3 = FUN_00040c36(param_1,param_3);
    *(int *)(iVar3 + 0x4c) = iVar1;
    *(undefined1 *)(iVar3 + 4) = 5;
    uVar4 = FUN_0003db0a(param_3);
    uVar5 = FUN_0003db28(param_3);
    FUN_0004747e(iVar3 + 0x18,uVar5,uVar4,*(undefined4 *)(param_2 + 0x2c),
                 *(undefined2 *)(param_2 + 0x30),*(undefined2 *)(param_2 + 0x34),param_2 + 0x40);
    FUN_0003ddd6(iVar3 + 0x18,*param_3,param_3[1]);
    FUN_0004197c(param_1,iVar3);
    return;
  }
  return;
}

