/* Address: 00050a40; name: FUN_00050a40; body bytes: 36 */

int FUN_00050a40(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_00050a64();
  iVar2 = FUN_0004a318();
  if (iVar2 != 0) {
    FUN_0004a404(iVar2,param_1,iVar1 + 1);
    return iVar2;
  }
  return 0;
}

