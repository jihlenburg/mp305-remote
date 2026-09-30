/* Address: 0004fb30; name: FUN_0004fb30; body bytes: 370 */

void FUN_0004fb30(int param_1,uint param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  undefined1 auStack_78 [104];
  
  uVar9 = *(uint *)(param_1 + 0x2c);
  if ((*(byte *)(param_1 + 0x3c) & 3) == 1) {
    uVar7 = uVar9 / *(uint *)(param_1 + 0x38);
    uVar11 = *(uint *)(param_1 + 0x30) / uVar7;
    if (param_2 < uVar7) {
      uVar10 = *(uint *)(param_1 + 0x30) - uVar11 * uVar7;
      uVar8 = (uint)(short)((short)uVar10 - (short)param_2);
      if ((int)uVar8 < 1) {
        uVar8 = -uVar8;
      }
      if (uVar7 >> 1 < uVar8) {
        if (param_2 < uVar10) {
          param_2 = param_2 + uVar7;
        }
        else {
          param_2 = param_2 - uVar7;
        }
      }
      param_2 = uVar7 * uVar11 + param_2;
    }
  }
  if (uVar9 <= param_2) {
    param_2 = uVar9 - 1;
  }
  *(uint *)(param_1 + 0x30) = param_2;
  *(uint *)(param_1 + 0x34) = param_2;
  iVar1 = FUN_0003759c();
  if (iVar1 != 0) {
    uVar2 = FUN_000491e8();
    iVar3 = FUN_0004b108(iVar1,0,uVar2);
    iVar6 = 0;
    if (iVar3 != 1) {
      if (iVar3 == 2) {
        iVar3 = FUN_0004bb1a(param_1,0);
        iVar6 = FUN_0004ccf8(iVar1);
        iVar6 = (iVar3 - iVar6) / 2;
      }
      else if (iVar3 == 3) {
        iVar6 = FUN_0004bb1a(param_1,0);
        iVar3 = FUN_0004ccf8(iVar1);
        iVar6 = iVar6 - iVar3;
      }
    }
    FUN_0004eb0e(iVar1,iVar6);
    uVar2 = FUN_0004cb3a(param_1,0);
    iVar3 = FUN_0004cb82(param_1,0);
    iVar6 = FUN_00046bd6(uVar2);
    iVar4 = FUN_0004baf8(param_1);
    iVar5 = FUN_0004c924(param_1,0,100);
    if ((param_3 == 0) || (iVar5 == 0)) {
      FUN_0003a6ba(param_1);
    }
    iVar3 = (iVar4 / 2 - iVar6 / 2) - *(int *)(param_1 + 0x30) * (iVar6 + iVar3);
    if ((param_3 == 0) || (iVar5 == 0)) {
      FUN_0003c97c(iVar1,0x5e7b9);
      FUN_0004eb3a(iVar1,iVar3);
      return;
    }
    FUN_0003c9f8(auStack_78);
    FUN_0003cb2a(auStack_78,iVar1);
    FUN_0003cafa(auStack_78,0x5e7b9);
    uVar2 = FUN_0004cd44(iVar1);
    FUN_0003cb1e(auStack_78,uVar2,iVar3);
    FUN_0003caea(auStack_78,iVar5);
    FUN_0003cadc(auStack_78,0x5e267);
    FUN_0003cafe(auStack_78,0x3ca83);
    FUN_0003cb6c(auStack_78);
  }
  return;
}

