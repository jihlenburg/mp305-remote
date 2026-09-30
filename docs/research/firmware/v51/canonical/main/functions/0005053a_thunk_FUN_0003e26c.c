/* Address: 0005053a; name: thunk_FUN_0003e26c; body bytes: 4 */

void thunk_FUN_0003e26c(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (*(int *)(param_1 + 0x2c) != param_2) {
    iVar2 = *(int *)(param_1 + 0x30);
    iVar1 = *(int *)(param_1 + 0x34);
    iVar3 = iVar1;
    if (param_2 < iVar1) {
      iVar3 = param_2;
    }
    if ((iVar2 <= iVar3) && (iVar2 = param_2, iVar1 <= param_2)) {
      iVar2 = iVar1;
    }
    if (iVar2 < *(int *)(param_1 + 0x38)) {
      iVar2 = *(int *)(param_1 + 0x38);
    }
    if (*(int *)(param_1 + 0x2c) != iVar2) {
      FUN_0003e2b0(param_1,iVar2,param_1 + 0x2c,param_1 + 0x50,param_3);
    }
  }
  return;
}

