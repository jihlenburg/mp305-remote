/* Address: 0004dbe0; name: FUN_0004dbe0; body bytes: 646 */

undefined4 FUN_0004dbe0(int param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  int iVar9;
  undefined1 auStack_48 [16];
  undefined1 auStack_38 [20];
  
  if (((-1 < (int)((uint)*(ushort *)(param_1 + 0x2a) << 0x14)) ||
      (-1 < (int)((uint)*(ushort *)(param_1 + 0x2a) << 0x15))) &&
     (iVar2 = FUN_0004bc8c(param_1), iVar2 != 0)) {
    if ((int)((uint)*(ushort *)(param_1 + 0x2a) << 0x14) < 0) {
      iVar3 = FUN_0004ccf8(param_1);
    }
    else {
      uVar5 = FUN_0004cbde(param_1,0);
      if (((uVar5 & 0x7fffffff) >> 0x1d == 1) && ((int)(uVar5 & 0x9fffffff) < 0x1fffffff)) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
      iVar3 = FUN_0004bb1a(iVar2);
      if (uVar5 == 0x3fffffff) {
        uVar5 = FUN_00026050(param_1);
      }
      else if (bVar1) {
        if (((int)((uint)*(ushort *)(iVar2 + 0x2a) << 0x14) < 0) ||
           (iVar4 = FUN_0004cbde(iVar2,0), iVar4 != 0x3fffffff)) {
          uVar5 = uVar5 & 0x9fffffff;
          if (0xfffffff < (int)uVar5) {
            uVar5 = 0xfffffff - uVar5;
          }
          iVar4 = FUN_0004c720(param_1,0);
          iVar9 = FUN_0004c732(param_1,0);
          uVar5 = (int)(uVar5 * iVar3) / 100 - (iVar9 + iVar4);
        }
        else {
          iVar4 = FUN_0004c9e8(param_1,0);
          iVar9 = FUN_0004ca46(param_1,0);
          uVar5 = iVar4 + iVar9;
        }
      }
      uVar7 = FUN_0004c924(param_1,0,4);
      uVar8 = FUN_0004c924(param_1,0,5);
      iVar3 = FUN_0003fe14(uVar5,uVar7,uVar8,iVar3);
    }
    if ((int)((uint)*(ushort *)(param_1 + 0x2a) << 0x15) < 0) {
      iVar4 = FUN_0004bbec(param_1);
    }
    else {
      uVar5 = FUN_0004c6cc(param_1,0);
      if (((uVar5 & 0x7fffffff) >> 0x1d == 1) && ((int)(uVar5 & 0x9fffffff) < 0x1fffffff)) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
      iVar4 = FUN_0004baf8(iVar2);
      if (uVar5 == 0x3fffffff) {
        uVar5 = FUN_00025f5c(param_1);
      }
      else if (bVar1) {
        if (((int)((uint)*(ushort *)(iVar2 + 0x2a) << 0x15) < 0) ||
           (iVar9 = FUN_0004c6cc(iVar2,0), iVar9 != 0x3fffffff)) {
          uVar5 = uVar5 & 0x9fffffff;
          if (0xfffffff < (int)uVar5) {
            uVar5 = 0xfffffff - uVar5;
          }
          iVar9 = FUN_0004c744(param_1,0);
          iVar6 = FUN_0004c70e(param_1,0);
          uVar5 = (int)(uVar5 * iVar4) / 100 - (iVar9 + iVar6);
        }
        else {
          iVar9 = FUN_0004caa4(param_1,0);
          iVar6 = FUN_0004c98a(param_1,0);
          uVar5 = iVar9 + iVar6;
        }
      }
      uVar7 = FUN_0004c924(param_1,0,6);
      uVar8 = FUN_0004c924(param_1,0,7);
      iVar4 = FUN_0003fdac(uVar5,uVar7,uVar8,iVar4);
    }
    iVar9 = FUN_0004ccf8(param_1);
    if ((iVar9 != iVar3) || (iVar9 = FUN_0004bbec(param_1), iVar9 != iVar4)) {
      FUN_0004d3d8(param_1);
      FUN_0004bb3c(param_1,auStack_48);
      FUN_0004bab4(iVar2,auStack_38);
      iVar9 = FUN_0003db8c(auStack_48,auStack_38,0);
      if (iVar9 == 0) {
        FUN_0004e560(iVar2);
      }
      *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x18) + iVar4 + -1;
      iVar4 = FUN_0004c5b2(param_1,0);
      if (iVar4 == 1) {
        *(int *)(param_1 + 0x14) = (*(int *)(param_1 + 0x1c) - iVar3) + 1;
      }
      else {
        *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x14) + iVar3 + -1;
      }
      FUN_0004e5a6(param_1,0x2e,auStack_48);
      FUN_0004e5a6(iVar2,0x27,param_1);
      FUN_0004d3d8(param_1);
      *(ushort *)(param_1 + 0x2a) = *(ushort *)(param_1 + 0x2a) | 2;
      iVar3 = FUN_0003db8c(param_1 + 0x14,auStack_38,0);
      if ((iVar9 != 0) || (iVar3 != 0)) {
        FUN_0004e560(iVar2);
      }
      FUN_0004de6c(param_1);
      return 1;
    }
  }
  return 0;
}

