/* Address: 000279dc; name: FUN_000279dc; body bytes: 604 */

void FUN_000279dc(undefined4 param_1)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  uint uVar7;
  int iVar8;
  undefined4 *puVar9;
  uint uVar10;
  undefined4 uVar11;
  
  iVar3 = FUN_00046688(param_1);
  uVar4 = FUN_0004675a(param_1);
  DAT_1ffe02b4 = 0;
  if (iVar3 == 7) {
    uVar10 = 0;
    uVar11 = 0xffffff;
    while( true ) {
      FUN_00046756(param_1);
      FUN_0004bc8c();
      uVar7 = FUN_0004ba5c();
      if (uVar7 <= uVar10) break;
      iVar3 = FUN_00046756(param_1);
      FUN_00046756(param_1);
      uVar6 = FUN_0004bc8c();
      iVar8 = FUN_0004b9de(uVar6,uVar10);
      if (iVar3 == iVar8) {
        bVar1 = (byte)uVar10;
        if ((int)(char)DAT_1ffe0242 == uVar10) {
          DAT_1ffe0242 = 0xff;
          uVar6 = uVar11;
        }
        else {
          uVar6 = 0xffa600;
          DAT_1ffe0242 = bVar1;
        }
        uVar6 = FUN_0004037c(uVar6);
        uVar5 = FUN_00046756(param_1);
        FUN_0004e8b2(uVar5,uVar6,0);
        uVar6 = FUN_0004b9de(DAT_1ffe0454,1);
        iVar3 = FUN_0004cd84(uVar6,1);
        bVar2 = bVar1;
        if (iVar3 != 0) {
          bVar2 = DAT_1ffe023e;
          DAT_1ffe023f = bVar1;
        }
      }
      else {
        uVar6 = FUN_0004037c(0xffffff);
        FUN_00046756(param_1);
        uVar5 = FUN_0004bc8c();
        uVar5 = FUN_0004b9de(uVar5,uVar10);
        FUN_0004e8b2(uVar5,uVar6,0);
        bVar2 = DAT_1ffe023e;
      }
      DAT_1ffe023e = bVar2;
      uVar10 = uVar10 + 1 & 0xff;
    }
    uVar6 = FUN_0004b9de(uVar4,1);
    iVar3 = FUN_0004cd84(uVar6,1);
    if (iVar3 == 0) {
      if (DAT_1ffe0242 != 0xff) {
        uVar11 = 0xffa600;
      }
      uVar11 = FUN_0004037c(uVar11);
      uVar6 = 1;
    }
    else {
      if (DAT_1ffe0242 != 0xff) {
        uVar11 = 0xffa600;
      }
      uVar11 = FUN_0004037c(uVar11);
      uVar6 = 2;
    }
    uVar4 = FUN_0004b9de(uVar4,uVar6);
    FUN_0004e8b2(uVar4,uVar11,0);
    iVar3 = FUN_000466ae(param_1);
    if (iVar3 != 0) {
      FUN_0001cb8c(0xf);
      return;
    }
  }
  else if (iVar3 == 1) {
    uVar10 = 0;
    while( true ) {
      FUN_00046756(param_1);
      FUN_0004bc8c();
      uVar7 = FUN_0004ba5c();
      if (uVar7 <= uVar10) break;
      iVar3 = FUN_00046756(param_1);
      FUN_00046756(param_1);
      uVar4 = FUN_0004bc8c();
      iVar8 = FUN_0004b9de(uVar4,uVar10);
      if (iVar3 == iVar8) {
        uVar4 = FUN_0004b9de(DAT_1ffe0454,1);
        iVar3 = FUN_0004cd84(uVar4,1);
        if (iVar3 == 0) {
          DAT_1ffe023e = (char)uVar10;
          return;
        }
        DAT_1ffe023f = (char)uVar10;
        return;
      }
      uVar10 = uVar10 + 1 & 0xff;
    }
  }
  else if ((DAT_1ffe0245 == '\0' && DAT_1ffe0246 == '\0') && (DAT_1ffe0128 == '\0')) {
    if (iVar3 == 0xe) {
      iVar3 = FUN_00046700(param_1);
      if (iVar3 != 0x1c) {
        if (iVar3 == 0x1d) {
          uVar4 = FUN_0004b9de(DAT_1ffe0454,1);
          iVar3 = FUN_0004cd84(uVar4,1);
          if (iVar3 == 0) {
            puVar9 = &DAT_1ffe045c;
          }
          else {
            puVar9 = &DAT_1ffe0460;
          }
          FUN_0004e5a6(*puVar9,7,0,param_1);
          return;
        }
        uVar4 = FUN_0004b9de(DAT_1ffe0454,1);
        iVar8 = FUN_0004cd84(uVar4,1);
        if (iVar8 == 0) {
          if (iVar3 + -100 < 1) {
            if (DAT_1ffe023e != 0) {
              DAT_1ffe023e = DAT_1ffe023e - 1;
              goto LAB_00027bc6;
            }
          }
          else {
            iVar3 = FUN_0004ba5c(DAT_1ffe0458);
            if ((uint)DAT_1ffe023e < iVar3 - 1U) {
              DAT_1ffe023e = DAT_1ffe023e + 1;
              goto LAB_00027c2e;
            }
          }
        }
        else if (iVar3 + -100 < 1) {
          if (DAT_1ffe023f != 0) {
            DAT_1ffe023f = DAT_1ffe023f - 1;
LAB_00027bc6:
            FUN_00047298(DAT_1ffe0144);
            return;
          }
        }
        else {
          iVar3 = FUN_0004ba5c(DAT_1ffe0458);
          if ((uint)DAT_1ffe023f < iVar3 - 1U) {
            DAT_1ffe023f = DAT_1ffe023f + 1;
LAB_00027c2e:
            FUN_000471d8(DAT_1ffe0144);
            return;
          }
        }
      }
    }
    else if (iVar3 == 0x10) {
      DAT_1ffe0242 = 0xff;
      uVar4 = FUN_00046756(param_1);
      FUN_0004e5a6(uVar4,7,0);
      uVar4 = FUN_00046756(param_1);
      FUN_0004e4b2(uVar4,0);
      return;
    }
  }
  return;
}

