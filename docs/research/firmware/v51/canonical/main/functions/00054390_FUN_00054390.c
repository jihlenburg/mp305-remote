/* Address: 00054390; name: FUN_00054390; body bytes: 186 */

void FUN_00054390(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined *puVar3;
  uint uVar4;
  undefined1 auStack_38 [32];
  
  if ((DAT_1fffab09 != '\0') && (DAT_1fffabc4 != DAT_1fff9a70)) {
    DAT_1fffab09 = 0;
    DAT_1ffe023d = 0;
    FUN_0001814c();
    FUN_0004b288(DAT_1ffe0718);
    FUN_0001046a(&DAT_1fffabc4,&DAT_1fff9a70,0xc4);
    for (uVar4 = 0; uVar4 < DAT_1fff9a74; uVar4 = uVar4 + 1 & 0xff) {
      FUN_0001046a(auStack_38,&DAT_1fffabd0 + uVar4 * 0x26,0x1f);
      if ((&DAT_1fffabc9)[uVar4 * 0x26] == '\0') {
        puVar3 = &DAT_0007f128;
      }
      else {
        puVar3 = &DAT_0007f1c0;
      }
      FUN_00021fe0(auStack_38,puVar3);
    }
    FUN_00021fe0(&DAT_00054468,&DAT_0007f444);
    for (uVar4 = 0; iVar2 = FUN_0004ba5c(DAT_1ffe0718), uVar4 < iVar2 - 1U; uVar4 = uVar4 + 1 & 0xff
        ) {
      uVar1 = FUN_0004b9de(DAT_1ffe0718,uVar4);
      FUN_0004aa4c(uVar1,0x2178d,0);
    }
    FUN_00018114(DAT_1ffe0348);
    return;
  }
  return;
}

