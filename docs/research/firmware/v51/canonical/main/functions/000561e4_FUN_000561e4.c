/* Address: 000561e4; name: FUN_000561e4; body bytes: 86 */

void FUN_000561e4(void)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  
  for (uVar3 = 6; uVar1 = FUN_0004ba5c(DAT_1ffe0648), uVar3 < uVar1; uVar3 = uVar3 + 1 & 0xff) {
    if ((DAT_1fffa0c7 < 3) || ((DAT_1fffa0c7 == 3 && (7 < uVar3)))) {
      uVar2 = FUN_0004b9de(DAT_1ffe0648,uVar3);
      FUN_0004aa6e(uVar2,1);
    }
    else {
      uVar2 = FUN_0004b9de(DAT_1ffe0648,uVar3);
      FUN_0004e00e(uVar2,1);
    }
  }
  uVar2 = FUN_0004b9de(DAT_1ffe0648,0);
  FUN_0004e4b2(uVar2,0);
  return;
}

