/* Address: 0005ff04; name: FUN_0005ff04; body bytes: 766 */

void FUN_0005ff04(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined4 local_30;
  undefined4 uStack_2c;
  
  iVar1 = FUN_00046688(param_1);
  if (iVar1 == 7) {
    for (uVar6 = 0; uVar5 = FUN_0004ba5c(DAT_1ffe0610), uVar6 < uVar5; uVar6 = uVar6 + 1) {
      iVar1 = FUN_0004b9de(DAT_1ffe0610,uVar6);
      iVar4 = FUN_00046756(param_1);
      if (iVar1 == iVar4) {
        if ((DAT_1fffa34a != uVar6) && (DAT_1fffaacf != '\0')) {
          DAT_1fff9550 = DAT_1fff9550 | 0x400;
        }
        DAT_1fffa34a = (ushort)uVar6;
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
        uVar2 = FUN_0004037c(0x333333);
        uVar3 = FUN_00046756(param_1);
        uVar3 = FUN_0004b9de(uVar3,2);
        FUN_0004ea90(uVar3,uVar2,0);
        FUN_0005735c(1);
      }
      else {
        uVar2 = FUN_0004037c(0x333333);
        uVar3 = FUN_0004b9de(DAT_1ffe0610,uVar6);
        FUN_0004e8b2(uVar3,uVar2,0);
        uVar2 = FUN_0004037c(0xffffff);
        uVar3 = FUN_0004b9de(DAT_1ffe0610,uVar6);
        uVar3 = FUN_0004b9de(uVar3,0);
        FUN_0004ea90(uVar3,uVar2,0);
        uVar2 = FUN_0004037c(0xffffff);
        uVar3 = FUN_0004b9de(DAT_1ffe0610,uVar6);
        uVar3 = FUN_0004b9de(uVar3,1);
        FUN_0004ea90(uVar3,uVar2,0);
        uVar2 = FUN_0004037c(0xffffff);
        uVar3 = FUN_0004b9de(DAT_1ffe0610,uVar6);
        uVar3 = FUN_0004b9de(uVar3,2);
        FUN_0004ea90(uVar3,uVar2,0);
      }
    }
    DAT_1fffaad3 = 0;
    uVar2 = DAT_1ffe060c;
LAB_00060158:
    FUN_0004e5a6(uVar2,7,0);
    return;
  }
  if (iVar1 == 1) {
    uVar2 = FUN_00046756(param_1);
    uVar3 = 0xb4;
  }
  else {
    if (iVar1 != 8) {
      if (DAT_1ffe0245 == '\0' && DAT_1ffe0246 == '\0') {
        if (iVar1 == 0xe) {
          iVar1 = FUN_00046700(param_1);
          if (iVar1 != 0x1c) {
            if (iVar1 == 0x1d) {
              uVar2 = FUN_00046756(param_1);
              goto LAB_00060158;
            }
            if (iVar1 + -100 < 1) {
              FUN_00046756(param_1);
              iVar1 = FUN_0004bc12();
              if (0 < iVar1) {
                FUN_00047298(DAT_1ffe0144,local_30,uStack_2c,param_1);
                return;
              }
            }
            else {
              FUN_00046756(param_1);
              uVar6 = FUN_0004bc12();
              iVar1 = FUN_0004ba5c(DAT_1ffe0610);
              if (uVar6 < iVar1 - 1U) {
                FUN_000471d8(DAT_1ffe0144,local_30,uStack_2c,param_1);
                return;
              }
            }
          }
        }
        else {
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
            uVar2 = FUN_0004037c(0x333333);
            uVar3 = FUN_00046756(param_1);
            uVar3 = FUN_0004b9de(uVar3,2);
            FUN_0004ea90(uVar3,uVar2,0);
            uVar2 = FUN_00046756(param_1);
            FUN_0004e4b2(uVar2,0);
            return;
          }
          if (iVar1 == 0x11) {
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
            uVar2 = FUN_0004037c(0xffffff);
            uVar3 = FUN_00046756(param_1);
            uVar3 = FUN_0004b9de(uVar3,2);
            FUN_0004ea90(uVar3,uVar2,0);
            return;
          }
        }
      }
      return;
    }
    uVar2 = FUN_00046756(param_1);
    uVar3 = 0xff;
  }
  FUN_0004e8dc(uVar2,uVar3,0);
  return;
}

