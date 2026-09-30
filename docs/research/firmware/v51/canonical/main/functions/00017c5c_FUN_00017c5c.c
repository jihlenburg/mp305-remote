/* Address: 00017c5c; name: FUN_00017c5c; body bytes: 66 */

void FUN_00017c5c(void)

{
  int iVar1;
  uint uVar2;
  
  FUN_0001814c();
  DAT_1ffe0246 = 1;
  for (uVar2 = 0; iVar1 = FUN_0004ba5c(DAT_1ffe0718), uVar2 < iVar1 - 1U; uVar2 = uVar2 + 1 & 0xff)
  {
    FUN_0004b9de(DAT_1ffe0718,uVar2);
    FUN_00018114();
  }
  DAT_1ffe0246 = 0;
  FUN_0004b9de(DAT_1ffe0718,DAT_1ffe023d);
  FUN_00047208();
  return;
}

