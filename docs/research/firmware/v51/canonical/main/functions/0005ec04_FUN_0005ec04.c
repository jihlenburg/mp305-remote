/* Address: 0005ec04; name: FUN_0005ec04; body bytes: 302 */

void FUN_0005ec04(int param_1,uint param_2,ushort *param_3,ushort *param_4)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  ushort *puVar4;
  int iVar5;
  ushort *puVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  undefined2 uVar12;
  ushort *local_28;
  
  iVar10 = (int)param_2 >> 1;
  iVar11 = iVar10;
  if ((param_2 & 1) == 0) {
    iVar11 = iVar10 + -1;
  }
  iVar2 = FUN_0004a318();
  puVar4 = param_3;
  local_28 = param_4;
  for (iVar3 = 0; iVar3 < param_1; iVar3 = iVar3 + 1) {
    local_28 = puVar4 + param_1;
    iVar5 = param_2 * local_28[-1];
    iVar7 = param_1;
    while (iVar7 = iVar7 + -1, -1 < iVar7) {
      uVar9 = 0;
      *(short *)(iVar2 + iVar7 * 2) = (short)iVar5;
      if (iVar7 + iVar10 < param_1) {
        uVar9 = (uint)puVar4[iVar7 + iVar10];
      }
      if ((iVar7 - iVar11) + -1 < 0) {
        uVar1 = *puVar4;
      }
      else {
        uVar1 = puVar4[(iVar7 - iVar11) + -1];
      }
      iVar5 = (uint)uVar1 + (iVar5 - uVar9);
    }
    FUN_0004a404(puVar4,iVar2,param_1 << 1);
    puVar4 = local_28;
  }
  iVar3 = 0x3fc0;
  puVar6 = (ushort *)(param_1 * param_1);
  for (puVar4 = (ushort *)0x0; puVar4 <= puVar6 && (int)puVar6 - (int)puVar4 != 0;
      puVar4 = (ushort *)((int)puVar4 + 1)) {
    uVar9 = (uint)param_3[(int)puVar4];
    if (uVar9 != 0) {
      if (uVar9 == 0x3fc0) {
        param_3[(int)puVar4] = (ushort)(0x3fc0 / param_2);
      }
      else {
        param_3[(int)puVar4] = (ushort)((int)uVar9 / (int)param_2);
      }
    }
  }
  for (iVar5 = 0; iVar5 < param_1; iVar5 = iVar5 + 1) {
    puVar6 = param_3 + iVar5;
    iVar7 = param_2 * *puVar6;
    puVar4 = puVar6;
    for (iVar3 = 0; iVar3 < param_1; iVar3 = iVar3 + 1) {
      if (iVar7 < 0) {
        uVar12 = 0;
      }
      else {
        uVar12 = (undefined2)(iVar7 >> 6);
      }
      *(undefined2 *)(iVar2 + iVar3 * 2) = uVar12;
      if (iVar3 - iVar10 < 1) {
        uVar1 = *puVar4;
      }
      else {
        uVar1 = param_3[(iVar3 - iVar10) * param_1 + iVar5];
      }
      iVar8 = iVar3 + iVar11 + 1;
      if (param_1 <= iVar8) {
        iVar8 = param_1 + -1;
      }
      puVar4 = puVar4 + param_1;
      iVar7 = (uint)param_3[iVar8 * param_1 + iVar5] + (iVar7 - (uint)uVar1);
    }
    for (iVar3 = 0; iVar3 < param_1; iVar3 = iVar3 + 1) {
      *puVar6 = *(ushort *)(iVar2 + iVar3 * 2);
      puVar6 = puVar6 + param_1;
    }
  }
  FUN_00046bec(iVar2,iVar3,puVar6,local_28);
  return;
}

