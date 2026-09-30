/* Address: 0005673c; name: FUN_0005673c; body bytes: 130 */

void FUN_0005673c(void)

{
  ushort uVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  
  for (uVar4 = 0; uVar3 = FUN_0004ba5c(DAT_1ffe0640), uVar4 < uVar3; uVar4 = uVar4 + 1 & 0xff) {
    if (DAT_1fffa0c7 == 5) {
      uVar2 = FUN_0004b9de(DAT_1ffe0640,uVar4);
      FUN_000499de(uVar2,&DAT_000567d8,(&DAT_1ffe07e0)[(uint)DAT_1fffa0c7 * 0xb + uVar4]);
    }
    else {
      uVar1 = (&DAT_1ffe07e0)[(uint)DAT_1fffa0c7 * 0xb + uVar4];
      uVar2 = FUN_0004b9de(DAT_1ffe0640,uVar4);
      FUN_000499de(uVar2,"%d.%02dV",uVar1 / 1000,(uVar1 / 10) % 100);
    }
  }
  return;
}

