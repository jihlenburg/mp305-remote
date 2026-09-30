/* Address: 00041d52; name: FUN_00041d52; body bytes: 98 */

void FUN_00041d52(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  if ((((2 < *(byte *)(param_2 + 0x48)) && (*(char **)(param_2 + 0x1c) != (char *)0x0)) &&
      (**(char **)(param_2 + 0x1c) != '\0')) && (*(int *)(param_2 + 0x20) != 0)) {
    iVar1 = FUN_00040c36(param_1,param_3);
    uVar2 = FUN_0004a318(0x54);
    *(undefined4 *)(iVar1 + 0x4c) = uVar2;
    FUN_0004a404(uVar2,param_2,0x54);
    *(undefined1 *)(iVar1 + 4) = 4;
    if ((int)((uint)*(byte *)(param_2 + 0x4c) << 0x19) < 0) {
      iVar3 = *(int *)(iVar1 + 0x4c);
      uVar2 = FUN_00050a40(*(undefined4 *)(param_2 + 0x1c));
      *(undefined4 *)(iVar3 + 0x1c) = uVar2;
    }
    FUN_0004197c(param_1,iVar1);
    return;
  }
  return;
}

