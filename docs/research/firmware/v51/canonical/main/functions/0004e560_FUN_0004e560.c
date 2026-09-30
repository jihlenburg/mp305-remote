/* Address: 0004e560; name: FUN_0004e560; body bytes: 70 */

void FUN_0004e560(undefined4 param_1)

{
  int iVar1;
  undefined1 auStack_28 [16];
  undefined1 auStack_18 [16];
  
  FUN_0004bf38(param_1,auStack_28,auStack_18);
  iVar1 = FUN_0003db14(auStack_28);
  if ((iVar1 != 0) || (iVar1 = FUN_0003db14(auStack_18), iVar1 != 0)) {
    iVar1 = FUN_0003db14(auStack_28);
    if (iVar1 != 0) {
      FUN_0004d40e(param_1,auStack_28);
    }
    iVar1 = FUN_0003db14(auStack_18);
    if (iVar1 != 0) {
      FUN_0004d40e(param_1,auStack_18);
    }
  }
  return;
}

