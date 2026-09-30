/* Address: 000318e0; name: FUN_000318e0; body bytes: 96 */

void FUN_000318e0(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 auStack_a0 [8];
  undefined4 local_98;
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [20];
  
  FUN_0004bf38(param_1,auStack_30,auStack_20);
  iVar1 = FUN_0003db14(auStack_30);
  if (((iVar1 != 0) || (iVar1 = FUN_0003db14(auStack_20), iVar1 != 0)) &&
     (iVar1 = FUN_0005e5c8(param_1,auStack_a0), iVar1 == 1)) {
    iVar1 = FUN_0003db14(auStack_30);
    if (iVar1 != 0) {
      local_98 = 0;
      FUN_00042a98(param_2,auStack_a0,auStack_30);
    }
    iVar1 = FUN_0003db14(auStack_20);
    if (iVar1 != 0) {
      local_98 = 1;
      FUN_00042a98(param_2,auStack_a0,auStack_20);
    }
  }
  return;
}

