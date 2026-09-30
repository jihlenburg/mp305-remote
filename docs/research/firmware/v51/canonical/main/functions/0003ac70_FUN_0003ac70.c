/* Address: 0003ac70; name: FUN_0003ac70; body bytes: 28 */

undefined4 FUN_0003ac70(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0004ccf8();
  iVar2 = FUN_0004bbec(param_1);
  if (iVar2 <= iVar1) {
    return 1;
  }
  return 0;
}

