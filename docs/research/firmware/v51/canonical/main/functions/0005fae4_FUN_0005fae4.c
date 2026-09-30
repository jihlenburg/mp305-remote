/* Address: 0005fae4; name: FUN_0005fae4; body bytes: 872 */

void FUN_0005fae4(undefined4 param_1)

{
  ushort uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  short sVar8;
  undefined4 uVar9;
  uint uVar10;
  
  iVar4 = FUN_00046688();
  uVar10 = 0;
  iVar5 = FUN_0004675a(param_1);
  if (iVar5 != DAT_1ffe05d8) {
    iVar5 = FUN_0004675a(param_1);
    if (iVar5 == DAT_1ffe05dc) {
      uVar10 = 1;
    }
    else {
      iVar5 = FUN_0004675a(param_1);
      if (iVar5 == DAT_1ffe05e0) {
        uVar10 = 2;
      }
      else {
        iVar5 = FUN_0004675a(param_1);
        if (iVar5 == DAT_1ffe05e4) {
          uVar10 = 3;
        }
        else {
          iVar5 = FUN_0004675a(param_1);
          if (iVar5 == DAT_1ffe05e8) {
            uVar10 = 4;
          }
          else {
            iVar5 = FUN_0004675a(param_1);
            if (iVar5 == DAT_1ffe05ec) {
              uVar10 = 5;
            }
            else {
              iVar5 = FUN_0004675a(param_1);
              if (iVar5 == DAT_1ffe05f0) {
                uVar10 = 6;
              }
              else {
                iVar5 = FUN_0004675a(param_1);
                if (iVar5 == DAT_1ffe05f4) {
                  uVar10 = 7;
                }
                else {
                  iVar5 = FUN_0004675a(param_1);
                  if (iVar5 == DAT_1ffe05f8) {
                    uVar10 = 8;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  uVar2 = (undefined1)uVar10;
  if (iVar4 != 7) {
    uVar3 = uVar2;
    if (((iVar4 != 1) && (uVar3 = DAT_1ffe0240, DAT_1ffe0245 == '\0' && DAT_1ffe0246 == '\0')) &&
       (DAT_1fffaae6 != '\x01')) {
      if (iVar4 == 0xe) {
        iVar4 = FUN_00046700(param_1);
        uVar3 = DAT_1ffe0240;
        if (iVar4 != 0x1c) {
          if (iVar4 == 0x1d) {
            DAT_1ffe02b0 = 0;
            if (uVar10 != 0) {
              uVar6 = FUN_00046756(param_1);
              FUN_0004e5a6(uVar6,7,0);
              return;
            }
          }
          else if (iVar4 + -100 < 1) {
            if (uVar10 != 0) {
              FUN_00047298(DAT_1ffe0144);
              return;
            }
          }
          else if ((int)uVar10 < (int)(DAT_1fffaaf1 - 1)) {
            FUN_000471d8(DAT_1ffe0144);
            return;
          }
        }
      }
      else if (iVar4 == 0x10) {
        if (DAT_1ffe0128 == '\0') {
          DAT_1ffe02b0 = 0;
          uVar6 = FUN_0004037c(0xffa600);
          uVar7 = FUN_0004675a(param_1);
          uVar7 = FUN_0004b9de(uVar7,0);
          FUN_0004e8e6(uVar7,uVar6,1);
          uVar6 = FUN_0004037c(0xffa600);
          uVar7 = FUN_0004675a(param_1);
          uVar7 = FUN_0004b9de(uVar7,0);
          FUN_0004e8e6(uVar7,uVar6,0);
          uVar6 = FUN_0004675a(param_1);
          FUN_0004e4b2(uVar6,0);
          uVar3 = uVar2;
        }
      }
      else if (iVar4 == 0x11) {
        uVar6 = 0xffff;
        if (uVar10 != 0) {
          uVar6 = FUN_0004037c(0xffff);
          uVar7 = FUN_0004675a(param_1);
          uVar7 = FUN_0004b9de(uVar7,0);
          FUN_0004e8e6(uVar7,uVar6,1);
          uVar6 = 0xb1b1b1;
        }
        uVar6 = FUN_0004037c(uVar6);
        uVar7 = FUN_0004675a(param_1);
        uVar7 = FUN_0004b9de(uVar7,0);
        uVar9 = 0;
        goto LAB_0005fbf4;
      }
    }
    DAT_1ffe0240 = uVar3;
    return;
  }
  DAT_1ffe0240 = uVar2;
  if (uVar10 == 0) {
    uVar6 = FUN_0004037c(0xffff);
    uVar7 = FUN_0004675a(param_1);
    uVar7 = FUN_0004b9de(uVar7,0);
    uVar9 = 1;
LAB_0005fbf4:
    FUN_0004e8e6(uVar7,uVar6,uVar9);
    return;
  }
  iVar4 = (uint)DAT_1fffa34a * 0x24;
  iVar5 = uVar10 * 4 + iVar4;
  uVar1 = *(ushort *)(&DAT_1fffa138 + iVar5 + 0xa0);
  if ((uVar1 & 7) != 0) {
    *(ushort *)(&DAT_1fffa138 + iVar5 + 0xa0) = uVar1 & 0xfff8;
    DAT_1fffab66 = DAT_1fffab66 & ~(ushort)(1 << uVar10);
    goto LAB_0005fc78;
  }
  if (uVar10 < 5) {
    sVar8 = (uVar1 & 0xfff8) + 1;
LAB_0005fc6a:
    *(short *)(&DAT_1fffa138 + iVar5 + 0xa0) = sVar8;
  }
  else {
    if (uVar10 == 5) {
      iVar5 = iVar4 + 0x1fffa14c;
      sVar8 = (*(ushort *)(&DAT_1fffa1ec + iVar4) & 0xfff8) + 2;
    }
    else if (uVar10 == 6) {
      iVar5 = iVar4 + 0x1fffa150;
      sVar8 = (*(ushort *)(&DAT_1fffa1f0 + iVar4) & 0xfff8) + 5;
    }
    else {
      if (uVar10 != 7) {
        sVar8 = (uVar1 & 0xfff8) + 4;
        goto LAB_0005fc6a;
      }
      iVar5 = iVar4 + 0x1fffa154;
      sVar8 = (*(ushort *)(&DAT_1fffa1f4 + iVar4) & 0xfff8) + 3;
    }
    *(short *)(iVar5 + 0xa0) = sVar8;
  }
  DAT_1fffab66 = DAT_1fffab66 | (ushort)(1 << uVar10);
LAB_0005fc78:
  if (((&DAT_1fffa1d8)[(uint)DAT_1fffa34a * 0x24 + uVar10 * 4] & 7) == 0) {
    uVar6 = FUN_0004037c(0xb1b1b1);
    uVar7 = FUN_0004675a(param_1);
    uVar7 = FUN_0004b9de(uVar7,0);
    FUN_0004e8e6(uVar7,uVar6,0);
    uVar6 = FUN_0004675a(param_1);
    uVar6 = FUN_0004b9de(uVar6,0);
    FUN_0004e0e6(uVar6,1);
    uVar6 = FUN_0004675a(param_1);
    uVar6 = FUN_0004b9de(uVar6,0);
    uVar6 = FUN_0004b9de(uVar6,0);
    FUN_0004e0e6(uVar6,1);
    uVar6 = FUN_0004675a(param_1);
    uVar6 = FUN_0004b9de(uVar6,1);
    FUN_0004e0e6(uVar6,1);
  }
  else {
    uVar6 = FUN_0004037c(0xffff);
    uVar7 = FUN_0004675a(param_1);
    uVar7 = FUN_0004b9de(uVar7,0);
    FUN_0004e8e6(uVar7,uVar6,1);
    uVar6 = FUN_0004675a(param_1);
    uVar6 = FUN_0004b9de(uVar6,0);
    FUN_0004aaf6(uVar6,1);
    uVar6 = FUN_0004675a(param_1);
    uVar6 = FUN_0004b9de(uVar6,0);
    uVar6 = FUN_0004b9de(uVar6,0);
    FUN_0004aaf6(uVar6,1);
    uVar6 = FUN_0004675a(param_1);
    uVar6 = FUN_0004b9de(uVar6,1);
    FUN_0004aaf6(uVar6,1);
  }
  if (DAT_1fffaacf != '\0') {
    DAT_1fff9550 = DAT_1fff9550 | 0x400;
  }
  FUN_0001cb8c(0xf);
  return;
}

