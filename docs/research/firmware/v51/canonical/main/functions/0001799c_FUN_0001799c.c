/* Address: 0001799c; name: FUN_0001799c; body bytes: 96 */

void FUN_0001799c(void)

{
  uint uVar1;
  uint uVar2;
  
  FUN_0001814c();
  DAT_1ffe0246 = 1;
  for (uVar2 = 0; uVar1 = FUN_0004ba5c(DAT_1ffe0648), uVar2 < uVar1; uVar2 = uVar2 + 1 & 0xff) {
    if (((DAT_1fffa0c7 == 4) || ((DAT_1fffa0c7 < 3 && (uVar2 < 6)))) ||
       ((DAT_1fffa0c7 == 3 && (uVar2 < 8)))) {
      FUN_0004b9de(DAT_1ffe0648,uVar2);
      FUN_00018114();
    }
  }
  DAT_1ffe0246 = 0;
  FUN_0004b9de(DAT_1ffe0648,(byte)DAT_1fffac90 - 1);
  FUN_00047208();
  return;
}

