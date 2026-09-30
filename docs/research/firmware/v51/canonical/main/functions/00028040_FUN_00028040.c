/* Address: 00028040; name: FUN_00028040; body bytes: 38 */

void FUN_00028040(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_00046688();
  iVar2 = FUN_00046756(param_1);
  if ((iVar1 == 0x35) && (*(int *)(iVar2 + 0x2f8) != 0)) {
    FUN_00052aae();
    return;
  }
  return;
}

