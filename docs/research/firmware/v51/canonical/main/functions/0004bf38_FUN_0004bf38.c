/* Address: 0004bf38; name: FUN_0004bf38; body bytes: 1538 */

void FUN_0004bf38(int param_1,int *param_2,int *param_3)

{
  bool bVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  bool bVar19;
  bool bVar20;
  int iVar21;
  
  FUN_0003ddf0(param_2,0,0,0xffffffff,0xffffffff);
  FUN_0003ddf0(param_3,0,0,0xffffffff,0xffffffff);
  iVar3 = FUN_0004cd84(param_1,0x10);
  if (iVar3 == 0) {
    return;
  }
  iVar3 = FUN_0004c53a(param_1);
  if (iVar3 == 0) {
    return;
  }
  iVar4 = FUN_00048270(0);
  if (iVar3 == 2) {
    while( true ) {
      if (iVar4 == 0) {
        return;
      }
      iVar5 = FUN_000482c2();
      if (iVar5 == param_1) break;
      iVar4 = FUN_00048270(iVar4);
    }
    if (iVar4 == 0) {
      return;
    }
  }
  iVar5 = FUN_0004bf14(param_1);
  iVar6 = FUN_0004bca4(param_1);
  iVar7 = FUN_0004bd90(param_1);
  iVar8 = FUN_0004be44(param_1);
  uVar9 = FUN_0004bd40(param_1);
  iVar21 = 0;
  if ((uVar9 & 0xc) == 0) goto LAB_0004c006;
  if (iVar3 == 1) {
LAB_0004c002:
    iVar21 = 1;
  }
  else if (iVar3 == 3) {
    if ((0 < iVar5) || (0 < iVar6)) goto LAB_0004c002;
  }
  else if ((iVar3 == 2) && (iVar14 = FUN_000482a6(iVar4), iVar14 == 0xc)) goto LAB_0004c002;
LAB_0004c006:
  bVar1 = false;
  if ((uVar9 & 3) == 0) goto LAB_0004c03a;
  if (iVar3 != 1) {
    if (iVar3 == 3) {
      if ((iVar7 < 1) && (iVar8 < 1)) goto LAB_0004c03a;
    }
    else if ((iVar3 != 2) || (iVar3 = FUN_000482a6(iVar4), iVar3 != 3)) goto LAB_0004c03a;
  }
  bVar1 = true;
LAB_0004c03a:
  if (bVar1 || iVar21 != 0) {
    iVar3 = FUN_0004c5be(param_1,0x10000);
    bVar19 = iVar3 != 1;
    iVar10 = FUN_0004c8dc(param_1,0x10000);
    iVar11 = FUN_0004c7e0(param_1,0x10000);
    iVar12 = FUN_0004c840(param_1,0x10000);
    iVar13 = FUN_0004c888(param_1,0x10000);
    iVar4 = FUN_0004c924(param_1,0x10000,1);
    iVar14 = FUN_0004bbec(param_1);
    iVar15 = FUN_0004ccf8(param_1);
    iVar3 = 0;
    if (iVar21 != 0) {
      iVar3 = iVar4;
    }
    iVar16 = 0;
    if (bVar1) {
      iVar16 = iVar4;
    }
    bVar2 = FUN_0004c924(param_1,0x10000,0x1d);
    if ((1 < bVar2) || (bVar2 = FUN_0004c924(param_1,0x10000,0x32), 1 < bVar2)) {
      iVar5 = iVar6 + iVar5 + iVar14;
      bVar20 = iVar21 == 0;
      do {
        if (bVar20) goto LAB_0004c2cc;
        bVar20 = true;
      } while (iVar5 == 0);
      param_3[1] = *(int *)(param_1 + 0x18);
      param_3[3] = *(int *)(param_1 + 0x20);
      if (bVar19) {
        iVar21 = *(int *)(param_1 + 0x1c) - iVar13;
        param_3[2] = iVar21;
        *param_3 = (iVar21 - iVar4) + 1;
      }
      else {
        iVar21 = *(int *)(param_1 + 0x14) + iVar12;
        *param_3 = iVar21;
        param_3[2] = iVar21 + iVar4 + -1;
      }
      iVar21 = ((iVar14 - iVar10) - iVar11) - iVar16;
      iVar17 = (iVar14 * iVar21) / iVar5;
      iVar18 = FUN_0004089c(0);
      if (iVar18 * 10 + 0x50 < 0x140) {
        iVar18 = 1;
      }
      else {
        iVar18 = FUN_0004089c(0);
        iVar18 = (iVar18 * 10 + 0x50) / 0xa0;
      }
      if (iVar17 <= iVar18) {
        iVar18 = FUN_0004089c(0);
        if (iVar18 * 10 + 0x50 < 0x140) {
          iVar17 = 1;
        }
        else {
          iVar18 = FUN_0004089c(0);
          iVar17 = (iVar18 * 10 + 0x50) / 0xa0;
        }
      }
      if (iVar5 - iVar14 < 1) {
        param_3[1] = iVar10 + *(int *)(param_1 + 0x18);
        param_3[3] = ((*(int *)(param_1 + 0x20) - iVar11) - iVar16) + -1;
      }
      else {
        iVar5 = ((iVar21 - iVar17) - ((iVar21 - iVar17) * iVar6) / (iVar5 - iVar14)) + iVar10 +
                *(int *)(param_1 + 0x18);
        param_3[1] = iVar5;
        param_3[3] = iVar17 + -1 + iVar5;
        iVar10 = iVar10 + *(int *)(param_1 + 0x18);
        if (iVar5 < iVar10) {
          param_3[1] = iVar10;
          iVar5 = FUN_0004089c(0);
          if (iVar5 * 10 + 0x50 < 0x140) {
            iVar5 = 1;
          }
          else {
            iVar5 = FUN_0004089c(0);
            iVar5 = (iVar5 * 10 + 0x50) / 0xa0;
          }
          if (param_3[3] < iVar5 + param_3[1]) {
            iVar5 = FUN_0004089c(0);
            if (iVar5 * 10 + 0x50 < 0x140) {
              iVar5 = 1;
            }
            else {
              iVar5 = FUN_0004089c(0);
              iVar5 = (iVar5 * 10 + 0x50) / 0xa0;
            }
            param_3[3] = iVar5 + param_3[1];
          }
        }
        iVar5 = (*(int *)(param_1 + 0x20) - iVar16) - iVar11;
        if (iVar5 < param_3[3]) {
          param_3[3] = iVar5;
          iVar5 = FUN_0004089c(0);
          if (iVar5 * 10 + 0x50 < 0x140) {
            iVar5 = 1;
          }
          else {
            iVar5 = FUN_0004089c(0);
            iVar5 = (iVar5 * 10 + 0x50) / 0xa0;
          }
          if (param_3[3] - iVar5 < param_3[1]) {
            iVar5 = FUN_0004089c(0);
            if (iVar5 * 10 + 0x50 < 0x140) {
              iVar5 = 1;
            }
            else {
              iVar5 = FUN_0004089c(0);
              iVar5 = (iVar5 * 10 + 0x50) / 0xa0;
            }
            param_3[1] = param_3[3] - iVar5;
          }
        }
      }
LAB_0004c2cc:
      iVar5 = iVar8 + iVar7 + iVar15;
      bVar1 = !bVar1;
      do {
        if (bVar1) {
          return;
        }
        bVar1 = true;
      } while (iVar5 == 0);
      iVar11 = *(int *)(param_1 + 0x20) - iVar11;
      param_2[3] = iVar11;
      param_2[1] = (iVar11 - iVar4) + 1;
      *param_2 = *(int *)(param_1 + 0x14);
      param_2[2] = *(int *)(param_1 + 0x1c);
      iVar4 = ((iVar15 - iVar12) - iVar13) - iVar3;
      iVar7 = (iVar15 * iVar4) / iVar5;
      iVar6 = FUN_0004089c(0);
      if (iVar6 * 10 + 0x50 < 0x140) {
        iVar6 = 1;
      }
      else {
        iVar6 = FUN_0004089c(0);
        iVar6 = (iVar6 * 10 + 0x50) / 0xa0;
      }
      if (iVar7 <= iVar6) {
        iVar6 = FUN_0004089c(0);
        if (iVar6 * 10 + 0x50 < 0x140) {
          iVar7 = 1;
        }
        else {
          iVar6 = FUN_0004089c(0);
          iVar7 = (iVar6 * 10 + 0x50) / 0xa0;
        }
      }
      if (iVar5 - iVar15 < 1) {
        if (bVar19) {
          *param_2 = *(int *)(param_1 + 0x14) + iVar12;
          iVar13 = ((*(int *)(param_1 + 0x1c) - iVar13) - iVar3) + -1;
        }
        else {
          *param_2 = iVar3 + -1 + *(int *)(param_1 + 0x14) + iVar12;
          iVar13 = *(int *)(param_1 + 0x1c) - iVar13;
        }
        param_2[2] = iVar13;
      }
      else {
        iVar4 = (iVar4 - iVar7) - ((iVar4 - iVar7) * iVar8) / (iVar5 - iVar15);
        if (bVar19) {
          iVar4 = iVar4 + iVar12 + *(int *)(param_1 + 0x14);
          *param_2 = iVar4;
          param_2[2] = iVar7 + -1 + iVar4;
          iVar12 = *(int *)(param_1 + 0x14) + iVar12;
          if (iVar4 < iVar12) {
            *param_2 = iVar12;
            iVar4 = FUN_0004089c(0);
            if (iVar4 * 10 + 0x50 < 0x140) {
              iVar4 = 1;
            }
            else {
              iVar4 = FUN_0004089c(0);
              iVar4 = (iVar4 * 10 + 0x50) / 0xa0;
            }
            if (param_2[2] < iVar4 + *param_2) {
              iVar4 = FUN_0004089c(0);
              if (iVar4 * 10 + 0x50 < 0x140) {
                iVar4 = 1;
              }
              else {
                iVar4 = FUN_0004089c(0);
                iVar4 = (iVar4 * 10 + 0x50) / 0xa0;
              }
              param_2[2] = iVar4 + *param_2;
            }
          }
          iVar4 = param_2[2];
          iVar3 = *(int *)(param_1 + 0x1c) - iVar3;
        }
        else {
          iVar4 = *(int *)(param_1 + 0x14) + iVar4 + iVar12 + iVar3;
          *param_2 = iVar4;
          param_2[2] = iVar7 + -1 + iVar4;
          iVar3 = *(int *)(param_1 + 0x14) + iVar12 + iVar3;
          if (iVar4 < iVar3) {
            *param_2 = iVar3;
            iVar3 = FUN_0004089c(0);
            if (iVar3 * 10 + 0x50 < 0x140) {
              iVar3 = 1;
            }
            else {
              iVar3 = FUN_0004089c(0);
              iVar3 = (iVar3 * 10 + 0x50) / 0xa0;
            }
            if (param_2[2] < iVar3 + *param_2) {
              iVar3 = FUN_0004089c(0);
              if (iVar3 * 10 + 0x50 < 0x140) {
                iVar3 = 1;
              }
              else {
                iVar3 = FUN_0004089c(0);
                iVar3 = (iVar3 * 10 + 0x50) / 0xa0;
              }
              param_2[2] = iVar3 + *param_2;
            }
          }
          iVar4 = param_2[2];
          iVar3 = *(int *)(param_1 + 0x1c);
        }
        if (iVar3 - iVar13 < iVar4) {
          param_2[2] = iVar3 - iVar13;
          iVar3 = FUN_0004089c(0);
          if (iVar3 * 10 + 0x50 < 0x140) {
            iVar3 = 1;
          }
          else {
            iVar3 = FUN_0004089c(0);
            iVar3 = (iVar3 * 10 + 0x50) / 0xa0;
          }
          if (param_2[2] - iVar3 < *param_2) {
            iVar3 = FUN_0004089c(0);
            if (iVar3 * 10 + 0x50 < 0x140) {
              iVar3 = 1;
            }
            else {
              iVar3 = FUN_0004089c(0);
              iVar3 = (iVar3 * 10 + 0x50) / 0xa0;
            }
            *param_2 = param_2[2] - iVar3;
          }
        }
      }
    }
  }
  return;
}

