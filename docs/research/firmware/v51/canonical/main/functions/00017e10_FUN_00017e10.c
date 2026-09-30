/* Address: 00017e10; name: FUN_00017e10; body bytes: 86 */

void FUN_00017e10(void)

{
  undefined1 uVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  
  FUN_0001814c();
  DAT_1ffe0246 = 1;
  for (uVar5 = 0; uVar2 = FUN_0004ba5c(DAT_1ffe0458), uVar5 < uVar2; uVar5 = uVar5 + 1 & 0xff) {
    FUN_0004b9de(DAT_1ffe0458,uVar5);
    FUN_00018114();
  }
  DAT_1ffe0246 = 0;
  uVar3 = FUN_0004b9de(DAT_1ffe0454,1);
  iVar4 = FUN_0004cd84(uVar3,1);
  uVar1 = DAT_1ffe023e;
  if (iVar4 != 0) {
    uVar1 = DAT_1ffe023f;
  }
  FUN_0004b9de(DAT_1ffe0458,uVar1);
  FUN_00047208();
  return;
}

