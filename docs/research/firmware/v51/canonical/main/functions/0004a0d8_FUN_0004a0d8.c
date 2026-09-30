/* Address: 0004a0d8; name: FUN_0004a0d8; body bytes: 6 */

/* WARNING: Removing unreachable block (ram,0x0004a0fa) */

void FUN_0004a0d8(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0004a118();
  while (iVar1 != 0) {
    iVar2 = FUN_0004a13c(param_1,iVar1);
    FUN_0004a2ac(param_1,iVar1);
    FUN_00046bec(iVar1);
    iVar1 = iVar2;
  }
  return;
}

