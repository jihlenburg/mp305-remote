/* Address: 0004b03e; name: FUN_0004b03e; body bytes: 202 */

int FUN_0004b03e(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar7 = 0;
  iVar1 = FUN_0004c984();
  if ((iVar1 != 0) && (uVar2 = FUN_0004c972(param_1,param_2), 2 < uVar2)) {
    iVar3 = FUN_0004c97e(param_1,param_2);
    iVar7 = FUN_0004c95a(param_1,param_2);
    iVar4 = FUN_0004c966(param_1,param_2);
    iVar5 = iVar7;
    if (iVar7 < 1) {
      iVar5 = -iVar7;
    }
    iVar6 = iVar4;
    if (iVar4 < 1) {
      iVar6 = -iVar4;
    }
    if (iVar6 < iVar5) {
      if (iVar7 < 1) {
        iVar7 = -iVar7;
      }
    }
    else {
      iVar7 = iVar4;
      if (iVar4 < 1) {
        iVar7 = -iVar4;
      }
    }
    iVar7 = iVar7 + iVar3 + iVar1 / 2 + 1;
    if (iVar7 < 0) {
      iVar7 = 0;
    }
  }
  iVar1 = FUN_0004c7da(param_1,param_2);
  if ((iVar1 != 0) && (uVar2 = FUN_0004c7c8(param_1,param_2), 2 < uVar2)) {
    iVar5 = FUN_0004c7d4(param_1,param_2);
    if (iVar7 <= iVar5 + iVar1) {
      iVar7 = iVar5 + iVar1;
    }
  }
  iVar5 = FUN_0004c924(param_1,param_2,0x68);
  iVar1 = FUN_0004c924(param_1,param_2,0x69);
  if (iVar1 < iVar5) {
    iVar1 = iVar5;
  }
  if (0 < iVar1) {
    iVar7 = iVar7 + iVar1;
  }
  return iVar7;
}

