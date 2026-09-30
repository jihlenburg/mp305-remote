/* Address: 00059098; name: FUN_00059098; body bytes: 660 */

void FUN_00059098(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint unaff_r4;
  undefined4 local_30;
  undefined4 uStack_2c;
  
  iVar1 = FUN_00046688(param_1);
  if (iVar1 == 7) {
    for (uVar6 = 0; uVar5 = FUN_0004ba5c(DAT_1ffe0548), uVar6 < uVar5; uVar6 = uVar6 + 1 & 0xff) {
      iVar1 = FUN_0004b9de(DAT_1ffe0548,uVar6);
      iVar4 = FUN_00046756(param_1);
      if (iVar1 == iVar4) {
        unaff_r4 = uVar6 + 1 & 0xff;
        DAT_1ffe0241 = 1;
        uVar2 = FUN_0004037c(0xffa600);
        uVar3 = FUN_00046756(param_1);
        FUN_0004e8b2(uVar3,uVar2,0);
        uVar2 = FUN_0004037c(0x333333);
        uVar3 = FUN_00046756(param_1);
        uVar3 = FUN_0004b9de(uVar3,0);
        FUN_0004ea90(uVar3,uVar2,0);
        uVar2 = FUN_0004037c(0x333333);
        uVar3 = FUN_00046756(param_1);
      }
      else {
        uVar2 = FUN_0004037c(0x333333);
        uVar3 = FUN_0004b9de(DAT_1ffe0548,uVar6);
        FUN_0004e8b2(uVar3,uVar2,0);
        uVar2 = FUN_0004037c(0xffffff);
        uVar3 = FUN_0004b9de(DAT_1ffe0548,uVar6);
        uVar3 = FUN_0004b9de(uVar3,0);
        FUN_0004ea90(uVar3,uVar2,0);
        uVar2 = FUN_0004037c(0xffffff);
        uVar3 = FUN_0004b9de(DAT_1ffe0548,uVar6);
      }
      uVar3 = FUN_0004b9de(uVar3,1);
      FUN_0004ea90(uVar3,uVar2,0);
    }
    uVar6 = 0;
    do {
      uVar5 = uVar6;
      if ((byte)(&DAT_1fffa3fe)[uVar6] == unaff_r4) break;
      uVar6 = uVar6 + 1 & 0xff;
      uVar5 = unaff_r4;
    } while (uVar6 < 10);
    DAT_1fffab48 = 0;
    uVar2 = DAT_1ffe0544;
    if (DAT_1fffa408 != uVar5) {
      DAT_1fffab48 = 0;
      DAT_1fffaaf0 = (char)uVar5;
      DAT_1fffaaef = 1;
      DAT_1fffaaed = 0;
      return;
    }
LAB_000592a0:
    FUN_0004e5a6(uVar2,7,0);
    return;
  }
  if (iVar1 == 1) {
    uVar2 = FUN_00046756(param_1);
    uVar3 = 0xb4;
  }
  else {
    if (iVar1 != 8) {
      if (DAT_1ffe0245 != '\0' || DAT_1ffe0246 != '\0') {
        return;
      }
      if (iVar1 != 0xe) {
        if (iVar1 == 0x10) {
          uVar2 = FUN_0004037c(0xffa600);
          uVar3 = FUN_00046756(param_1);
          FUN_0004e8b2(uVar3,uVar2,0);
          uVar2 = FUN_0004037c(0x333333);
          uVar3 = FUN_00046756(param_1);
          uVar3 = FUN_0004b9de(uVar3,0);
          FUN_0004ea90(uVar3,uVar2,0);
          uVar2 = FUN_0004037c(0x333333);
          uVar3 = FUN_00046756(param_1);
          uVar3 = FUN_0004b9de(uVar3,1);
          FUN_0004ea90(uVar3,uVar2,0);
          uVar2 = FUN_00046756(param_1);
          FUN_0004e4b2(uVar2,0);
          return;
        }
        if (iVar1 != 0x11) {
          return;
        }
        uVar2 = FUN_0004037c(0x333333);
        uVar3 = FUN_00046756(param_1);
        FUN_0004e8b2(uVar3,uVar2,0);
        uVar2 = FUN_0004037c(0xffffff);
        uVar3 = FUN_00046756(param_1);
        uVar3 = FUN_0004b9de(uVar3,0);
        FUN_0004ea90(uVar3,uVar2,0);
        uVar2 = FUN_0004037c(0xffffff);
        uVar3 = FUN_00046756(param_1);
        uVar3 = FUN_0004b9de(uVar3,1);
        FUN_0004ea90(uVar3,uVar2,0);
        return;
      }
      iVar1 = FUN_00046700(param_1);
      if (iVar1 == 0x1c) {
        return;
      }
      if (iVar1 != 0x1d) {
        if (0 < iVar1 + -100) {
          FUN_00046756(param_1);
          uVar6 = FUN_0004bc12();
          iVar1 = FUN_0004ba5c(DAT_1ffe0548);
          if (iVar1 - 1U <= uVar6) {
            return;
          }
          FUN_000471d8(DAT_1ffe0144,local_30,uStack_2c,param_1);
          return;
        }
        FUN_00046756(param_1);
        iVar1 = FUN_0004bc12();
        if (iVar1 < 1) {
          return;
        }
        FUN_00047298(DAT_1ffe0144,local_30,uStack_2c,param_1);
        return;
      }
      uVar2 = FUN_00046756(param_1);
      goto LAB_000592a0;
    }
    uVar2 = FUN_00046756(param_1);
    uVar3 = 0xff;
  }
  FUN_0004e8dc(uVar2,uVar3,0);
  return;
}

