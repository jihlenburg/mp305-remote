/* Address: 00050536; name: thunk_FUN_0003e222; body bytes: 4 */

void thunk_FUN_0003e222(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if ((*(byte *)(param_1 + 0x70) & 7) == 2) {
    iVar2 = *(int *)(param_1 + 0x30);
    iVar1 = *(int *)(param_1 + 0x34);
    iVar3 = iVar1;
    if (param_2 < iVar1) {
      iVar3 = param_2;
    }
    if ((iVar2 <= iVar3) && (iVar2 = param_2, iVar1 <= param_2)) {
      iVar2 = iVar1;
    }
    if (*(int *)(param_1 + 0x2c) < iVar2) {
      iVar2 = *(int *)(param_1 + 0x2c);
    }
    if (*(int *)(param_1 + 0x38) != iVar2) {
      FUN_0003e2b0(param_1,iVar2,param_1 + 0x38,param_1 + 0x60,param_3);
    }
  }
  return;
}

