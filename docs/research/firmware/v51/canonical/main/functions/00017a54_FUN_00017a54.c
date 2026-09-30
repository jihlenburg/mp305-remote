/* Address: 00017a54; name: FUN_00017a54; body bytes: 66 */

void FUN_00017a54(void)

{
  uint uVar1;
  uint uVar2;
  
  FUN_0001814c();
  DAT_1ffe0246 = 1;
  for (uVar2 = 0; uVar1 = FUN_0004ba5c(DAT_1ffe0638), uVar2 < uVar1; uVar2 = uVar2 + 1 & 0xff) {
    FUN_0004b9de(DAT_1ffe0638,uVar2);
    FUN_00018114();
  }
  DAT_1ffe0246 = 0;
  FUN_0004b9de(DAT_1ffe0638,DAT_1fffa0c7);
  FUN_00047208();
  return;
}

