/* Address: 0002178c; name: FUN_0002178c; body bytes: 678 */

void FUN_0002178c(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  
  iVar1 = FUN_00046688();
  if (iVar1 == 7) {
    uVar7 = 0;
    uVar2 = 0xffffff;
    while( true ) {
      FUN_00046756(param_1);
      FUN_0004bc8c();
      uVar6 = FUN_0004ba5c();
      if (uVar6 <= uVar7) break;
      iVar1 = FUN_00046756(param_1);
      FUN_00046756(param_1);
      uVar3 = FUN_0004bc8c();
      iVar5 = FUN_0004b9de(uVar3,uVar7);
      if (iVar1 == iVar5) {
        if ((int)DAT_1ffe024a == uVar7) {
          DAT_1ffe024a = -1;
          uVar3 = FUN_0004037c(0);
          uVar4 = FUN_00046756(param_1);
          FUN_0004e8b2(uVar4,uVar3,0);
          uVar3 = FUN_0004037c(0xffffff);
          uVar4 = FUN_00046756(param_1);
          FUN_0004ea90(uVar4,uVar3,0);
          uVar3 = uVar2;
        }
        else {
          DAT_1ffe024a = (char)uVar7;
          uVar3 = FUN_0004037c(0xffa600);
          uVar4 = FUN_00046756(param_1);
          FUN_0004e8b2(uVar4,uVar3,0);
          uVar3 = FUN_0004037c(0);
          uVar4 = FUN_00046756(param_1);
          FUN_0004ea90(uVar4,uVar3,0);
          uVar3 = 0;
        }
        uVar3 = FUN_0004037c(uVar3);
        uVar4 = FUN_00046756(param_1);
      }
      else {
        uVar3 = FUN_0004037c(0);
        FUN_00046756(param_1);
        uVar4 = FUN_0004bc8c();
        uVar4 = FUN_0004b9de(uVar4,uVar7);
        FUN_0004e8b2(uVar4,uVar3,0);
        uVar3 = FUN_0004037c(0xffffff);
        FUN_00046756(param_1);
        uVar4 = FUN_0004bc8c();
        uVar4 = FUN_0004b9de(uVar4,uVar7);
        FUN_0004ea90(uVar4,uVar3,0);
        uVar3 = FUN_0004037c(0xffffff);
        FUN_00046756(param_1);
        uVar4 = FUN_0004bc8c();
        uVar4 = FUN_0004b9de(uVar4,uVar7);
      }
      uVar4 = FUN_0004b9de(uVar4,0);
      FUN_0004e960(uVar4,uVar3,0);
      uVar7 = uVar7 + 1 & 0xff;
    }
    if (DAT_1ffe024a == -1) {
      FUN_0004aaf6(DAT_1ffe0714,0x80);
      uVar2 = 0x333333;
    }
    else {
      FUN_0004e0e6();
    }
    uVar3 = FUN_0004037c(uVar2);
    uVar4 = FUN_0004b9de(DAT_1ffe0714,0);
    FUN_0004e8e6(uVar4,uVar3,0);
    uVar3 = FUN_0004037c(uVar2);
    uVar4 = FUN_0004b9de(DAT_1ffe0714,0);
    uVar4 = FUN_0004b9de(uVar4,0);
    FUN_0004e8b2(uVar4,uVar3,0);
    uVar3 = FUN_0004037c(uVar2);
    uVar4 = FUN_0004b9de(DAT_1ffe0714,0);
    uVar4 = FUN_0004b9de(uVar4,1);
    FUN_0004e8b2(uVar4,uVar3,0);
    uVar2 = FUN_0004037c(uVar2);
    uVar3 = FUN_0004b9de(DAT_1ffe0714,1);
    FUN_0004ea90(uVar3,uVar2,0);
    FUN_0001cb8c(0xf);
    return;
  }
  if (iVar1 == 1) {
    uVar7 = 0;
    while( true ) {
      FUN_00046756(param_1);
      FUN_0004bc8c();
      uVar6 = FUN_0004ba5c();
      if (uVar6 <= uVar7) break;
      iVar1 = FUN_00046756(param_1);
      FUN_00046756(param_1);
      uVar2 = FUN_0004bc8c();
      iVar5 = FUN_0004b9de(uVar2,uVar7);
      if (iVar1 == iVar5) {
        DAT_1ffe023d = (byte)uVar7;
      }
      uVar7 = uVar7 + 1 & 0xff;
    }
  }
  else if ((DAT_1ffe0245 == '\0' && DAT_1ffe0246 == '\0') && (DAT_1ffe0128 == '\0')) {
    if (iVar1 == 0xe) {
      iVar1 = FUN_00046700(param_1);
      if (iVar1 != 0x1c) {
        if (iVar1 == 0x1d) {
          if (DAT_1ffe024a != -1) {
            FUN_0004e5a6(DAT_1ffe0714,7,0);
            return;
          }
        }
        else if (iVar1 + -100 < 1) {
          if (DAT_1ffe023d != 0) {
            FUN_00047298(DAT_1ffe0144);
            DAT_1ffe023d = DAT_1ffe023d - 1;
          }
        }
        else {
          iVar1 = FUN_0004ba5c(DAT_1ffe0718);
          if ((uint)DAT_1ffe023d < iVar1 - 2U) {
            FUN_000471d8(DAT_1ffe0144);
            DAT_1ffe023d = DAT_1ffe023d + 1;
          }
        }
      }
    }
    else if (iVar1 == 0x10) {
      DAT_1ffe024a = 0xff;
      uVar2 = FUN_00046756(param_1);
      FUN_0004e5a6(uVar2,7,0);
      uVar2 = FUN_00046756(param_1);
      FUN_0004e4b2(uVar2,0);
      return;
    }
  }
  return;
}

