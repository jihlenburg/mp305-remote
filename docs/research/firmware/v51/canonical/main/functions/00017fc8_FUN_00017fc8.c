/* Address: 00017fc8; name: FUN_00017fc8; body bytes: 60 */

void FUN_00017fc8(void)

{
  byte bVar1;
  
  FUN_0001814c();
  DAT_1ffe0246 = 1;
  bVar1 = 0;
  do {
    FUN_0004b9de(DAT_1ffe0610,bVar1);
    FUN_00018114();
    bVar1 = bVar1 + 1;
  } while (bVar1 < 10);
  DAT_1ffe0246 = 0;
  FUN_0004b9de(DAT_1ffe0610,DAT_1fffa34a);
  FUN_00047208();
  return;
}

