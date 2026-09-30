/* Address: 00017d34; name: FUN_00017d34; body bytes: 90 */

void FUN_00017d34(void)

{
  uint uVar1;
  uint uVar2;
  
  FUN_0001814c();
  if (DAT_1fffa409 != '\0') {
    DAT_1ffe0246 = 1;
    for (uVar2 = 0; uVar1 = FUN_0004ba5c(DAT_1ffe0548), uVar2 < uVar1; uVar2 = uVar2 + 1 & 0xff) {
      FUN_0004b9de(DAT_1ffe0548,uVar2);
      FUN_00018114();
    }
    DAT_1ffe0246 = 0;
    FUN_0004b9de(DAT_1ffe0548,(byte)(&DAT_1fffa3fe)[DAT_1fffa408] - 1);
    FUN_00047208();
    return;
  }
  return;
}

