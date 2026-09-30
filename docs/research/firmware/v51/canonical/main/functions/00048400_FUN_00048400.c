/* Address: 00048400; name: FUN_00048400; body bytes: 36 */

void FUN_00048400(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = 0;
  if (param_1 != 0) {
    FUN_0003a5e0();
    return;
  }
  while (iVar1 = FUN_00048270(iVar1), iVar1 != 0) {
    FUN_0003a5e0(iVar1,param_2);
  }
  DAT_2003a474 = iVar1;
  return;
}

