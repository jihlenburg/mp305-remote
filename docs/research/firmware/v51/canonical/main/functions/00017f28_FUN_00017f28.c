/* Address: 00017f28; name: FUN_00017f28; body bytes: 66 */

void FUN_00017f28(void)

{
  uint uVar1;
  uint uVar2;
  
  FUN_0001814c();
  DAT_1ffe0246 = 1;
  for (uVar2 = 0; uVar1 = FUN_0004ba5c(DAT_1ffe06e4), uVar2 < uVar1; uVar2 = uVar2 + 1 & 0xff) {
    FUN_0004b9de(DAT_1ffe06e4,uVar2);
    FUN_00018114();
  }
  DAT_1ffe0246 = 0;
  FUN_0004b9de(DAT_1ffe06e4,DAT_1ffe0864);
  FUN_00047208();
  return;
}

