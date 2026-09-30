/* Address: 00028098; name: FUN_00028098; body bytes: 86 */

undefined4 FUN_00028098(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  if (*(int *)(param_1 + 0x1c) == 0) {
    iVar2 = FUN_000419fc(param_2,0,1);
    uVar1 = 0xffffffff;
    if ((iVar2 != 0) && (iVar3 = FUN_000422d0(param_2), iVar3 != 0)) {
      *(undefined4 *)(iVar2 + 0x48) = 2;
      *(int *)(param_1 + 0x1c) = iVar2;
      *(undefined4 *)(param_1 + 4) = param_2;
      *(int *)(param_1 + 8) = iVar2 + 0x38;
      FUN_00035fe2(param_1);
      *(undefined4 *)(*(int *)(param_1 + 0x1c) + 0x48) = 3;
      *(undefined4 *)(param_1 + 0x1c) = 0;
      FUN_0004193c();
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

