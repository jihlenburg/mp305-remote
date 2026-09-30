/* Address: 000405ba; name: FUN_000405ba; body bytes: 248 */

void FUN_000405ba(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  
  if ((param_1 == 0) || (param_1 == 0x400)) {
    return;
  }
  iVar3 = param_2 * 3;
  iVar1 = param_4 * 3 + param_2 * -6;
  iVar11 = (param_2 * -3 + 0x400) - iVar1;
  iVar2 = param_5 * 3 + param_3 * -6;
  iVar10 = 0;
  iVar9 = param_1;
  do {
    iVar4 = FUN_000280ee(iVar9,iVar11,iVar1,iVar3);
    uVar5 = iVar4 - param_1;
    uVar6 = uVar5;
    if ((int)uVar5 < 1) {
      uVar6 = -uVar5;
    }
    if ((int)uVar6 < 2) goto LAB_0004069c;
    iVar8 = iVar3 + (iVar9 * ((iVar11 * iVar9 * 3 >> 10) + iVar1 * 2) >> 10);
    iVar4 = iVar8;
    if (iVar8 < 1) {
      iVar4 = -iVar8;
    }
    if ((iVar4 < 2) ||
       (iVar4 = FUN_000103ea(uVar5 * 0x400,((int)uVar5 >> 0x1f) << 10 | uVar5 >> 0x16,iVar8,
                             iVar8 >> 0x1f), iVar4 == 0)) break;
    iVar9 = iVar9 - iVar4;
    iVar10 = iVar10 + 1;
  } while (iVar10 < 8);
  iVar10 = 0;
  if (param_1 < 0) {
    iVar9 = 0;
  }
  else {
    iVar9 = param_1;
    iVar4 = 0x400;
    if (param_1 < 0x401) {
      while( true ) {
        iVar8 = FUN_000280ee(iVar9,iVar11,iVar1,iVar3);
        iVar7 = iVar8 - param_1;
        if (iVar7 < 1) {
          iVar7 = param_1 - iVar8;
        }
        if (iVar7 < 2) break;
        iVar7 = iVar9;
        if (iVar8 < param_1) {
          iVar10 = iVar9;
          iVar7 = iVar4;
        }
        iVar9 = iVar10 + (iVar7 - iVar10) / 2;
        if ((iVar9 == iVar10) || (iVar4 = iVar7, iVar7 <= iVar10)) break;
      }
    }
    else {
      iVar9 = 0x400;
    }
  }
LAB_0004069c:
  FUN_000280ee(iVar9,(param_3 * -3 + 0x400) - iVar2,iVar2,param_3 * 3);
  return;
}

