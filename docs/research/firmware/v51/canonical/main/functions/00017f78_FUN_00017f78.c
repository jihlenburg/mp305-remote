/* Address: 00017f78; name: FUN_00017f78; body bytes: 66 */

void FUN_00017f78(void)

{
  byte bVar1;
  
  FUN_0001814c();
  DAT_1ffe0246 = 1;
  for (bVar1 = 0; bVar1 < DAT_1fffaaf1; bVar1 = bVar1 + 1) {
    FUN_0004b9de(DAT_1ffe05d4,bVar1);
    FUN_00018114();
  }
  DAT_1ffe0246 = 0;
  FUN_0004b9de(DAT_1ffe05d4,DAT_1ffe0240);
  FUN_00047208();
  return;
}

