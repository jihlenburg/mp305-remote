/* Address: 0004b654; name: FUN_0004b654; body bytes: 862 */

void FUN_0004b654(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  uint uVar8;
  bool bVar9;
  undefined1 auStack_38 [16];
  undefined1 auStack_28 [16];
  
  iVar1 = FUN_00046688(param_2);
  iVar2 = FUN_00046698(param_2);
  if (iVar1 == 1) {
    uVar7 = 0x20;
    goto LAB_0004b9a8;
  }
  if (iVar1 == 8) {
    FUN_0004e0e6(iVar2,0x20);
    FUN_0004673a(param_2);
    iVar1 = FUN_000482c2();
    if (iVar1 != 0) {
      return;
    }
    iVar1 = FUN_0004cd84(iVar2,8);
    if (iVar1 == 0) {
      return;
    }
    if ((*(byte *)(iVar2 + 0x28) & 1) == 0) {
      FUN_0004aaf6(iVar2,1);
    }
    else {
      FUN_0004e0e6();
    }
LAB_0004b760:
    FUN_0004e5a6(iVar2,0x20,0);
    return;
  }
  if (iVar1 == 3) {
    uVar6 = 0x20;
    goto LAB_0004b6ba;
  }
  if (iVar1 == 0x2f) {
    uVar7 = FUN_0004ba5c();
    for (uVar8 = 0; uVar8 < uVar7; uVar8 = uVar8 + 1) {
      FUN_0004d500(*(undefined4 *)(**(int **)(iVar2 + 8) + uVar8 * 4));
    }
    return;
  }
  if (iVar1 != 0xe) {
    if (iVar1 == 0x10) {
      iVar1 = FUN_0004cd84(iVar2,0x400);
      if (iVar1 != 0) {
        FUN_0004e4d2(iVar2,1);
      }
      FUN_0004bbe2(iVar2);
      iVar1 = FUN_000472d4();
      uVar7 = 2;
      iVar3 = FUN_00047eec();
      if (iVar3 == 0) {
        FUN_000466ae(param_2);
      }
      iVar3 = FUN_000482e0();
      if ((iVar3 == 2) || (iVar3 == 4)) {
        uVar7 = 6;
      }
      if (iVar1 == 0) {
        FUN_0004aaf6(iVar2,uVar7);
        uVar6 = 8;
        goto LAB_0004b6ba;
      }
      uVar7 = uVar7 | 8;
    }
    else {
      if (iVar1 != 9) {
        if (iVar1 == 0xb) {
          FUN_0004e0e6(iVar2,0x40);
          iVar1 = FUN_0004c53a(iVar2);
          if (iVar1 != 2) {
            return;
          }
          FUN_0004bf38(iVar2,auStack_38,auStack_28);
          FUN_0004d40e(iVar2,auStack_38);
          FUN_0004d40e(iVar2,auStack_28);
          return;
        }
        if (iVar1 != 0x11) {
          if (iVar1 == 0x2e) {
            iVar1 = FUN_0004c588(iVar2,0);
            iVar3 = FUN_0004c6e4(iVar2,0);
            if (iVar3 != 0 || iVar1 != 0) {
              FUN_0004d500(iVar2);
            }
            uVar7 = FUN_0004ba5c(iVar2);
            for (uVar8 = 0; uVar8 < uVar7; uVar8 = uVar8 + 1) {
              FUN_0004d500(*(undefined4 *)(**(int **)(iVar2 + 8) + uVar8 * 4));
            }
            return;
          }
          if (iVar1 == 0x27) {
            iVar1 = FUN_0004c924(iVar2,0,1);
            iVar3 = FUN_0004c924(iVar2,0,2);
            iVar4 = FUN_0004c588(iVar2,0);
            iVar5 = FUN_0004c6e4(iVar2,0);
            if (((iVar5 == 0 && iVar4 == 0) && (iVar1 != 0x3fffffff)) && (iVar3 != 0x3fffffff)) {
              return;
            }
          }
          else {
            if (iVar1 != 0x29) {
              if (iVar1 == 0x18) {
                uVar6 = FUN_0004b03e(iVar2,0);
                FUN_00046862(param_2,uVar6);
                return;
              }
              bVar9 = iVar1 == 0x1a;
              do {
                if (bVar9) {
                  FUN_0004b484(param_2);
                  return;
                }
                bVar9 = true;
              } while ((iVar1 == 0x1d) || (bVar9 = true, iVar1 == 0x17));
              if (iVar1 == 0x14) {
                FUN_0004e0e6(iVar2,0x20);
                uVar6 = 0x40;
              }
              else {
                if (iVar1 == 0x15) {
                  uVar7 = 0x10;
                  goto LAB_0004b9a8;
                }
                if (iVar1 != 0x16) {
                  return;
                }
                uVar6 = 0x10;
              }
              goto LAB_0004b6ba;
            }
            *(ushort *)(iVar2 + 0x2a) = *(ushort *)(iVar2 + 0x2a) | 2;
          }
          FUN_0004d500(iVar2);
          return;
        }
        uVar6 = 0xe;
LAB_0004b6ba:
        FUN_0004e0e6(iVar2,uVar6);
        return;
      }
      uVar7 = 0x40;
    }
LAB_0004b9a8:
    FUN_0004aaf6(iVar2,uVar7);
    return;
  }
  iVar1 = FUN_0004cd84(iVar2,8);
  if (iVar1 != 0) {
    iVar1 = FUN_00046700(param_2);
    if ((iVar1 == 0x13) || (iVar1 == 0x11)) {
      FUN_0004aaf6(iVar2,1);
    }
    else if ((iVar1 == 0x14) || (iVar1 == 0x12)) {
      FUN_0004e0e6(iVar2,1);
    }
    if (iVar1 == 10) {
      return;
    }
    goto LAB_0004b760;
  }
  iVar1 = FUN_0004cd84(iVar2,0x810);
  if (iVar1 == 0) {
    return;
  }
  iVar1 = FUN_0004d45a(iVar2);
  if (iVar1 != 0) {
    return;
  }
  iVar1 = FUN_0004bd90(iVar2);
  iVar3 = FUN_0004be44(iVar2);
  iVar4 = FUN_00046700(param_2);
  if (iVar4 == 0x12) {
LAB_0004b7f4:
    iVar3 = FUN_0004bbec(iVar2);
    iVar1 = FUN_0004bf2c(iVar2);
    iVar1 = iVar1 + ((int)(iVar3 + ((uint)(iVar3 >> 0x1f) >> 0x1e)) >> 2);
  }
  else {
    if (iVar4 != 0x11) {
      if (iVar4 == 0x13) {
        uVar7 = FUN_0004bd40(iVar2);
        if (((uVar7 & 3) != 0) && ((0 < iVar1 || (0 < iVar3)))) {
          iVar1 = FUN_0004ccf8(iVar2);
          iVar3 = FUN_0004bf20(iVar2);
          iVar3 = iVar3 + ((int)(iVar1 + ((uint)(iVar1 >> 0x1f) >> 0x1e)) >> 2);
          goto LAB_0004b85e;
        }
        goto LAB_0004b7f4;
      }
      if (iVar4 != 0x14) {
        return;
      }
      uVar7 = FUN_0004bd40(iVar2);
      if (((uVar7 & 3) != 0) && ((0 < iVar1 || (0 < iVar3)))) {
        iVar1 = FUN_0004ccf8(iVar2);
        iVar3 = FUN_0004bf20(iVar2);
        iVar3 = iVar3 - ((int)(iVar1 + ((uint)(iVar1 >> 0x1f) >> 0x1e)) >> 2);
LAB_0004b85e:
        FUN_0004e510(iVar2,iVar3,0);
        return;
      }
    }
    iVar3 = FUN_0004bbec(iVar2);
    iVar1 = FUN_0004bf2c(iVar2);
    iVar1 = iVar1 - ((int)(iVar3 + ((uint)(iVar3 >> 0x1f) >> 0x1e)) >> 2);
  }
  FUN_0004e538(iVar2,iVar1,0);
  return;
}

