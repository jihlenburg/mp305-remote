/* Address: 0001d674; name: FUN_0001d674; body bytes: 122 */

void FUN_0001d674(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  
  uVar1 = FUN_0004675a();
  iVar2 = FUN_00046688(param_1);
  if (DAT_1ffe0245 == '\0') {
    if (iVar2 == 0xe) {
      iVar2 = FUN_00046700(param_1);
      if ((iVar2 != 0x1c) && (iVar2 != 0x1d)) {
        if (iVar2 + -100 < 1) {
          iVar2 = FUN_0004bc12(uVar1);
          if (0 < iVar2) {
            FUN_00047298(DAT_1ffe0144);
            return;
          }
        }
        else {
          uVar3 = FUN_0004bc12(uVar1);
          iVar2 = FUN_0004ba5c(DAT_1ffe061c);
          if (uVar3 < iVar2 - 1U) {
            FUN_000471d8(DAT_1ffe0144);
            return;
          }
        }
      }
    }
    else if (iVar2 == 0x10) {
      uVar1 = FUN_00046756(param_1);
      FUN_0004e4b2(uVar1,0);
      return;
    }
  }
  return;
}

