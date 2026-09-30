/* Address: 00042244; name: FUN_00042244; body bytes: 140 */

void FUN_00042244(undefined4 param_1,int param_2,undefined4 *param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  if ((0 < *(int *)(param_2 + 0x30)) && (0 < *(int *)(param_2 + 0x34))) {
    iVar1 = FUN_00040c36(param_1,param_3,param_3,param_4,param_2,param_3,param_4);
    uVar2 = FUN_0004a318(0x6c);
    *(undefined4 *)(iVar1 + 0x4c) = uVar2;
    FUN_0004a404(uVar2,param_2,0x6c);
    *(undefined1 *)(iVar1 + 4) = 6;
    *(undefined4 *)(iVar1 + 0x48) = 0;
    uVar2 = FUN_0003db0a(param_3);
    uVar3 = FUN_0003db28(param_3);
    FUN_0004747e(iVar1 + 0x18,uVar3,uVar2,*(undefined4 *)(param_2 + 0x2c),
                 *(undefined2 *)(param_2 + 0x30),*(undefined2 *)(param_2 + 0x34),param_2 + 0x40);
    FUN_0003ddd6(iVar1 + 0x18,*param_3,param_3[1]);
    *(undefined1 *)(*(int *)(param_2 + 0x1c) + 0x44) = 1;
    FUN_0004197c(param_1,iVar1);
    return;
  }
  return;
}

