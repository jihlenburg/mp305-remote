/* Address: 00018010; name: FUN_00018010; body bytes: 66 */

void FUN_00018010(void)

{
  uint uVar1;
  uint uVar2;
  
  FUN_0001814c();
  DAT_1ffe0246 = 1;
  for (uVar2 = 0; uVar1 = FUN_0004ba5c(DAT_1ffe06fc), uVar2 < uVar1; uVar2 = uVar2 + 1 & 0xff) {
    FUN_0004b9de(DAT_1ffe06fc,uVar2);
    FUN_00018114();
  }
  DAT_1ffe0246 = 0;
  FUN_0004b9de(DAT_1ffe06fc,DAT_1ffe0866);
  FUN_00047208();
  return;
}

