/* Address: 00048428; name: FUN_00048428; body bytes: 380 */

void FUN_00048428(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  short sVar10;
  int iVar11;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  
  if ((*(int *)(param_1 + 0x48) == 0) && (*(int *)(param_1 + 0x4c) == 0)) {
    return;
  }
  iVar11 = *(int *)(param_1 + 0x70);
  if (iVar11 == 0) {
    iVar11 = FUN_00047f68(param_1);
    if (iVar11 == 0) {
      return;
    }
    FUN_0003a78c(param_1);
    FUN_0004e0e6(*(undefined4 *)(param_1 + 0x68),0x20);
    FUN_0004e5a6(iVar11,9,0);
    if ((int)((uint)*(byte *)(param_1 + 10) << 0x1e) < 0) {
      return;
    }
  }
  sVar10 = 0;
  iVar8 = 0x100;
  iVar9 = 0x100;
  iVar4 = iVar11;
  do {
    sVar1 = FUN_0004cbac(iVar4,0);
    sVar10 = sVar1 + sVar10;
    iVar2 = FUN_0004cbb2(iVar4,0);
    iVar3 = FUN_0004cbc2(iVar4,0);
    iVar8 = iVar8 * iVar2 * 0x100 >> 0x10;
    iVar9 = iVar3 * iVar9 * 0x100 >> 0x10;
    iVar4 = FUN_0004bc8c(iVar4);
  } while (iVar4 != 0);
  if (((sVar10 != 0) || (iVar8 != 0x100)) || (iVar9 != 0x100)) {
    local_30 = iVar4;
    local_2c = iVar4;
    FUN_0004f292(param_1 + 0x48,(int)-sVar10,(int)(short)(0x10000 / iVar8),
                 (int)(short)(0x10000 / iVar9),&local_30,0);
  }
  local_38 = iVar4;
  local_34 = iVar4;
  if ((*(byte *)(param_1 + 0x98) & 0xf) == 3) {
    uVar5 = FUN_0004be44(iVar11);
    uVar6 = FUN_0004bd90(iVar11);
    local_38 = FUN_00035d0c(iVar11,*(undefined4 *)(param_1 + 0x48),uVar6,uVar5,3);
  }
  else {
    uVar5 = FUN_0004bf14();
    uVar6 = FUN_0004bca4(iVar11);
    local_34 = FUN_00035d0c(iVar11,*(undefined4 *)(param_1 + 0x4c),uVar5,uVar6,0xc);
  }
  uVar7 = FUN_0004bd40(iVar11);
  if (((uVar7 & 1) == 0) && (0 < local_38)) {
    local_38 = iVar4;
  }
  if ((-1 < (int)(uVar7 << 0x1e)) && (local_38 < 0)) {
    local_38 = iVar4;
  }
  if ((-1 < (int)(uVar7 << 0x1d)) && (0 < local_34)) {
    local_34 = iVar4;
  }
  if ((-1 < (int)(uVar7 << 0x1c)) && (local_34 < 0)) {
    local_34 = iVar4;
  }
  FUN_0005e4e8(param_1,&local_38,&local_34);
  FUN_0004e44e(iVar11,local_38,local_34);
  if (-1 < (int)((uint)*(byte *)(param_1 + 10) << 0x1e)) {
    *(int *)(param_1 + 0x50) = *(int *)(param_1 + 0x50) + local_38;
    *(int *)(param_1 + 0x54) = *(int *)(param_1 + 0x54) + local_34;
  }
  return;
}

