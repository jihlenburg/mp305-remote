/* Address: 00026594; name: FUN_00026594; body bytes: 916 */

void FUN_00026594(undefined4 param_1)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  undefined4 local_30;
  undefined4 uStack_2c;
  
  iVar3 = FUN_00046688(param_1);
  if (iVar3 == 7) {
    uVar10 = 0;
    do {
      FUN_00046756(param_1);
      FUN_0004bc8c();
      uVar6 = FUN_0004ba5c();
      if (uVar6 <= uVar10) {
        FUN_0004e5a6(DAT_1ffe0330,7,0);
        if (DAT_1fffaacf == '\0') {
          DAT_1ffe02b4 = 0;
          return;
        }
        DAT_1ffe02b4 = 0;
        DAT_1fff9550 = DAT_1fff9550 | 0x800;
        return;
      }
      FUN_00046756(param_1);
      uVar4 = FUN_0004bc8c();
      iVar3 = FUN_0004b9de(uVar4,uVar10);
      iVar7 = FUN_00046756(param_1);
      if (iVar3 == iVar7) {
        uVar4 = FUN_0004037c(0xffa600);
        uVar5 = FUN_00046756(param_1);
        FUN_0004e8b2(uVar5,uVar4,0);
        bVar1 = (byte)uVar10;
        if (DAT_1ffe0330 == DAT_1ffe0634) {
LAB_00026640:
          if (DAT_1fffa0c7 == uVar10) goto LAB_000267bc;
          DAT_1fffa0c7 = bVar1;
          uVar4 = FUN_0004037c(0xffffff);
          uVar5 = FUN_0004b9de(DAT_1ffe0640,DAT_1ffe032d);
          FUN_0004e8b2(uVar5,uVar4,0);
          uVar4 = FUN_0004037c(0xffffff);
          uVar5 = FUN_0004b9de(DAT_1ffe0648,(byte)DAT_1fffac90 - 1);
          FUN_0004e8b2(uVar5,uVar4,0);
          uVar4 = FUN_0004037c(0xffffff);
          uVar5 = FUN_0004b9de(DAT_1ffe0650,DAT_1ffe032e);
          FUN_0004e8b2(uVar5,uVar4,0);
          uVar9 = (uint)DAT_1fffa0c7;
          uVar6 = 0;
          do {
            if (*(ushort *)((int)&DAT_1fffa0dc + uVar9 * 2) <=
                (ushort)(&DAT_1ffe07e0)[uVar9 * 0xb + uVar6]) {
              DAT_1ffe032d = (byte)uVar6;
              break;
            }
            uVar6 = uVar6 + 1 & 0xff;
          } while (uVar6 < 0xb);
          uVar2 = 0;
          do {
            if ((ushort)(&DAT_1fffa0e8)[uVar9] <= (ushort)((uVar2 + 1) * 100)) {
              DAT_1ffe032e = (byte)uVar2;
              break;
            }
            uVar2 = uVar2 + 1 & 0xff;
          } while (uVar2 < 0x32);
          DAT_1fffac90._0_1_ = (&DAT_1fffa0c8)[uVar9];
          FUN_00056608();
          FUN_0005673c();
          FUN_00056678();
          FUN_000561e4();
          FUN_00056120();
          bVar1 = DAT_1ffe032e;
        }
        else {
          FUN_00046756(param_1);
          iVar3 = FUN_0004bc8c();
          if (iVar3 == DAT_1ffe0638) goto LAB_00026640;
          if (DAT_1ffe0330 == DAT_1ffe063c) {
LAB_00026742:
            DAT_1ffe032d = bVar1;
            FUN_00056678();
            goto LAB_000267bc;
          }
          FUN_00046756(param_1);
          iVar3 = FUN_0004bc8c();
          if (iVar3 == DAT_1ffe0640) goto LAB_00026742;
          if (DAT_1ffe0330 == DAT_1ffe0644) {
LAB_00026768:
            DAT_1fffac90._0_1_ = bVar1 + 1;
            FUN_00056120();
            goto LAB_000267bc;
          }
          FUN_00046756(param_1);
          iVar3 = FUN_0004bc8c();
          if (iVar3 == DAT_1ffe0648) goto LAB_00026768;
          if (DAT_1ffe0330 != DAT_1ffe064c) {
            FUN_00046756(param_1);
            iVar3 = FUN_0004bc8c();
            if (iVar3 != DAT_1ffe0650) goto LAB_000267bc;
          }
        }
        DAT_1ffe032e = bVar1;
        FUN_000567e0();
      }
      else {
        uVar4 = FUN_0004037c(0xffffff);
        FUN_00046756(param_1);
        uVar5 = FUN_0004bc8c();
        uVar5 = FUN_0004b9de(uVar5,uVar10);
        FUN_0004e8b2(uVar5,uVar4,0);
      }
LAB_000267bc:
      uVar10 = uVar10 + 1 & 0xff;
    } while( true );
  }
  if (DAT_1ffe0245 != '\0' || DAT_1ffe0246 != '\0') {
    return;
  }
  if (iVar3 != 0xe) {
    if (iVar3 == 0x10) {
      DAT_1ffe02b4 = 0;
      uVar4 = FUN_0004037c(0xffa600);
      uVar5 = FUN_00046756(param_1);
      FUN_0004e8b2(uVar5,uVar4,2);
      uVar4 = FUN_0004037c(0xffa600);
      uVar5 = FUN_00046756(param_1);
      FUN_0004e8b2(uVar5,uVar4,4);
      uVar4 = FUN_0004037c(0);
      uVar5 = FUN_00046756(param_1);
      FUN_0004ea90(uVar5,uVar4,4);
      uVar4 = FUN_00046756(param_1);
      FUN_0004e4b2(uVar4,0);
      return;
    }
    if (iVar3 != 0x11) {
      return;
    }
    uVar4 = FUN_0004037c(0xffffff);
    uVar5 = FUN_00046756(param_1);
    FUN_0004e8b2(uVar5,uVar4,0);
    return;
  }
  iVar3 = FUN_00046700(param_1);
  if (iVar3 == 0x1c) {
    return;
  }
  if (iVar3 == 0x1d) {
    uVar4 = FUN_00046756(param_1);
    FUN_0004e5a6(uVar4,7,0);
    return;
  }
  uVar10 = 0;
  while( true ) {
    FUN_00046756(param_1);
    FUN_0004bc8c();
    uVar9 = FUN_0004ba5c();
    uVar6 = 0;
    if (uVar9 <= uVar10) break;
    FUN_00046756(param_1);
    uVar4 = FUN_0004bc8c();
    iVar7 = FUN_0004b9de(uVar4,uVar10);
    iVar8 = FUN_00046756(param_1);
    uVar6 = uVar10;
    if (iVar7 == iVar8) break;
    uVar10 = uVar10 + 1 & 0xff;
  }
  if (iVar3 + -100 < 1) {
    if (uVar6 == 0) {
      return;
    }
    FUN_00047298(DAT_1ffe0144,local_30,uStack_2c,param_1);
    return;
  }
  FUN_00046756(param_1);
  FUN_0004bc8c();
  iVar3 = FUN_0004ba5c();
  if (uVar6 < iVar3 - 1U) {
    FUN_00046756(param_1);
    iVar3 = FUN_0004bc8c();
    if (iVar3 != DAT_1ffe0648) goto LAB_000268c2;
  }
  FUN_00046756(param_1);
  iVar3 = FUN_0004bc8c();
  if (iVar3 != DAT_1ffe0648) {
    return;
  }
  if ((DAT_1fffac94._2_1_ < 3) && (uVar6 < 5)) {
LAB_000268c2:
    FUN_000471d8(DAT_1ffe0144,local_30,uStack_2c,param_1);
    return;
  }
  if (DAT_1fffac94._2_1_ == 3) {
    if (uVar6 < 7) goto LAB_000268c2;
  }
  else if ((DAT_1fffac94._2_1_ == 4) && (uVar6 < 0xb)) goto LAB_000268c2;
  return;
}

