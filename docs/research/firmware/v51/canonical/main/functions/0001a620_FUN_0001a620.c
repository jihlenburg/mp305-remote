/* Address: 0001a620; name: FUN_0001a620; body bytes: 60 */

void FUN_0001a620(void)

{
  int iVar1;
  
  iVar1 = FUN_00018ee0(1);
  if (iVar1 == 0) {
    DAT_1fffa9f2 = 0;
    DAT_1fffa9ec = 0;
    DAT_1fffa9ee = 0;
    DAT_1fffa9f0 = 0;
  }
  else {
    DAT_1fffa9ec = FUN_00018d72(1);
    DAT_1fffa9ee = FUN_00018cd6(1);
    DAT_1fffa9f0 = FUN_00018db4(1);
    DAT_1fffa9f2 = FUN_00018d1a(1);
  }
  return;
}

