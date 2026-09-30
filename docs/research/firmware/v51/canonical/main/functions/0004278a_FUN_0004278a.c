/* Address: 0004278a; name: FUN_0004278a; body bytes: 594 */

undefined4 FUN_0004278a(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  byte bVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  
  bVar1 = *(byte *)(param_5 + 0x1c);
  iVar8 = *(int *)(param_5 + 0x18);
  FUN_0003da22(&local_3c,param_5 + 8);
  if ((bVar1 & 1) == 0) {
    if (param_3 < local_38) {
      return 0;
    }
    if (local_30 < param_3) {
      return 0;
    }
  }
  else {
    if (param_3 < local_38) {
      return 1;
    }
    if (local_30 < param_3) {
      return 1;
    }
  }
  if (((param_2 < local_3c + iVar8) || (local_34 - iVar8 < param_2 + param_4)) &&
     ((param_3 < local_38 + iVar8 || (local_30 - iVar8 < param_3)))) {
    iVar9 = FUN_0003db28(&local_3c);
    iVar4 = FUN_0003db0a(&local_3c);
    param_3 = param_3 - local_38;
    if (param_3 < iVar8) {
      param_3 = (iVar8 - param_3) + -1;
    }
    else {
      param_3 = param_3 - (iVar4 - iVar8);
    }
    iVar4 = *(int *)(param_5 + 0x20);
    iVar11 = 0;
    uVar7 = (uint)*(ushort *)(*(int *)(iVar4 + 0xc) + param_3 * 2);
    iVar10 = *(ushort *)(*(int *)(iVar4 + 0xc) + param_3 * 2 + 2) - uVar7;
    iVar12 = uVar7 + *(int *)(iVar4 + 4);
    uVar7 = (uint)*(ushort *)(*(int *)(iVar4 + 8) + param_3 * 2);
    iVar9 = (((local_3c - param_2) + iVar9) - iVar8) + uVar7;
    iVar4 = ((local_3c - param_2) + iVar8) - uVar7;
    iVar8 = iVar4 + -1;
    if ((bVar1 & 1) == 0) {
      for (; iVar11 < iVar10; iVar11 = iVar11 + 1) {
        uVar3 = *(undefined1 *)((iVar10 - iVar11) + iVar12 + -1);
        iVar4 = iVar9 + iVar11;
        if ((-1 < iVar4) && (iVar4 < param_4)) {
          uVar2 = FUN_00053592(uVar3,*(undefined1 *)(param_1 + iVar4));
          *(undefined1 *)(param_1 + iVar4) = uVar2;
        }
        iVar4 = iVar8 - iVar11;
        if ((-1 < iVar4) && (iVar4 < param_4)) {
          uVar3 = FUN_00053592(uVar3,*(undefined1 *)(param_1 + iVar4));
          *(undefined1 *)(param_1 + iVar4) = uVar3;
        }
      }
      iVar9 = iVar9 + iVar11;
      iVar4 = param_4;
      if (iVar9 < param_4) {
        iVar4 = iVar9;
      }
      if (iVar4 < 0) {
        iVar9 = 0;
      }
      else if (param_4 <= iVar9) {
        iVar9 = param_4;
      }
      FUN_0004a602(iVar9 + param_1,param_4 - iVar9);
      iVar8 = iVar8 - iVar10;
      iVar9 = param_4;
      if (iVar8 + 1 < param_4) {
        iVar9 = iVar8 + 1;
      }
      if (iVar9 < 0) {
        param_4 = 0;
      }
      else if (iVar8 + 1 < param_4) {
        param_4 = iVar8 + 1;
      }
    }
    else {
      for (; iVar11 < iVar10; iVar11 = iVar11 + 1) {
        iVar5 = 0xff - (uint)*(byte *)((iVar10 - iVar11) + iVar12 + -1);
        iVar6 = iVar9 + iVar11;
        if ((-1 < iVar6) && (iVar6 < param_4)) {
          uVar3 = FUN_00053592(iVar5,*(undefined1 *)(param_1 + iVar6));
          *(undefined1 *)(param_1 + iVar6) = uVar3;
        }
        iVar6 = iVar8 - iVar11;
        if ((-1 < iVar6) && (iVar6 < param_4)) {
          uVar3 = FUN_00053592(iVar5,*(undefined1 *)(param_1 + iVar6));
          *(undefined1 *)(param_1 + iVar6) = uVar3;
        }
      }
      iVar8 = param_4;
      if (iVar4 < param_4) {
        iVar8 = iVar4;
      }
      if (iVar8 < 0) {
        iVar8 = 0;
      }
      else {
        iVar8 = param_4;
        if (iVar4 < param_4) {
          iVar8 = iVar4;
        }
      }
      iVar9 = iVar9 - iVar8;
      iVar10 = param_4 - iVar8;
      iVar4 = iVar10;
      if (iVar9 < iVar10) {
        iVar4 = iVar9;
      }
      if (iVar4 < 0) {
        param_4 = 0;
      }
      else {
        param_4 = iVar9;
        if (iVar10 <= iVar9) {
          param_4 = iVar10;
        }
      }
      param_1 = param_1 + iVar8;
    }
  }
  else {
    if ((bVar1 & 1) == 0) {
      iVar8 = local_3c - param_2;
      if (iVar8 <= param_4) {
        if (-1 < iVar8) {
          FUN_0004a602(param_1,iVar8);
        }
        iVar9 = (local_34 - param_2) + 1;
        if (0 < iVar9) {
          if (iVar9 < param_4) {
            FUN_0004a602(param_1 + iVar9,param_4 - iVar9);
          }
          if (iVar8 != 0) {
            return 2;
          }
          if (iVar9 != param_4) {
            return 2;
          }
          return 1;
        }
      }
      return 0;
    }
    local_3c = local_3c - param_2;
    if (local_3c < 0) {
      local_3c = 0;
    }
    if (param_4 < local_3c) {
      return 2;
    }
    iVar8 = ((local_34 - param_2) - local_3c) + 1;
    if (param_4 < local_3c + iVar8) {
      iVar8 = param_4 - local_3c;
    }
    param_4 = iVar8;
    if (param_4 < 0) {
      return 2;
    }
    param_1 = local_3c + param_1;
  }
  FUN_0004a602(param_1,param_4);
  return 2;
}

