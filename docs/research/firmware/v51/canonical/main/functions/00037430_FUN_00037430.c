/* Address: 00037430; name: FUN_00037430; body bytes: 44 */

int FUN_00037430(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = 0;
  iVar4 = 0;
  while ((iVar1 = FUN_00048270(iVar1), iVar3 = iVar4, iVar1 != 0 &&
         (iVar2 = FUN_000482e0(), iVar3 = iVar1, iVar2 != 1))) {
    iVar3 = FUN_00048264(iVar1);
    if (iVar3 == param_1) {
      iVar4 = iVar1;
    }
  }
  return iVar3;
}

