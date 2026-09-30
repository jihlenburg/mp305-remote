/* Address: 0004a0de; name: FUN_0004a0de; body bytes: 58 */

void FUN_0004a0de(undefined4 param_1,code *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0004a118();
  while (iVar1 != 0) {
    iVar2 = FUN_0004a13c(param_1,iVar1);
    if (param_2 == (code *)0x0) {
      FUN_0004a2ac(param_1,iVar1);
      FUN_00046bec(iVar1);
      iVar1 = iVar2;
    }
    else {
      (*param_2)(iVar1);
      iVar1 = iVar2;
    }
  }
  return;
}

