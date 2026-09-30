/* Address: 00017ec4; name: FUN_00017ec4; body bytes: 88 */

void FUN_00017ec4(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  
  FUN_0001814c();
  DAT_1ffe0246 = 1;
  for (uVar4 = 0; uVar1 = FUN_0004ba5c(DAT_1ffe05b0), uVar4 < uVar1; uVar4 = uVar4 + 1 & 0xff) {
    FUN_0004b9de(DAT_1ffe05b0,uVar4);
    FUN_00018114();
  }
  DAT_1ffe0246 = 0;
  FUN_0004b9de(DAT_1ffe05b0,DAT_1ffe0244);
  FUN_00047208();
  uVar2 = FUN_0004037c(0xffa600);
  uVar3 = FUN_0004b9de(DAT_1ffe05b0,DAT_1ffe0244);
  FUN_0004e8b2(uVar3,uVar2,0);
  return;
}

