/* Address: 00047938; name: FUN_00047938; body bytes: 444 */

void FUN_00047938(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 *puVar10;
  uint local_40;
  uint uStack_3c;
  undefined1 *local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  undefined1 auStack_24 [12];
  uint *puVar9;
  
  puVar9 = &local_40;
  iVar2 = FUN_00046688(param_2);
  iVar3 = FUN_0004b9b2(&PTR_DAT_0007a71c,param_2);
  if (iVar3 != 1) {
    return;
  }
  iVar3 = FUN_00046698(param_2);
  FUN_00047af8(iVar3,auStack_24);
  if (iVar2 == 0x2f) {
    if ((*(byte *)(iVar3 + 0x58) & 3) != 2) {
      FUN_0004de6c();
      return;
    }
    FUN_00047d8e(iVar3,*(undefined4 *)(iVar3 + 0x2c));
    return;
  }
  if (iVar2 == 0x18) {
    piVar4 = (int *)FUN_0004673a(param_2);
    if (((*(int *)(iVar3 + 0x44) == 0) && (*(int *)(iVar3 + 0x48) == 0x100)) &&
       (*(int *)(iVar3 + 0x4c) == 0x100)) {
      return;
    }
    iVar5 = FUN_0004ccf8(iVar3);
    iVar6 = FUN_0004bbec(iVar3);
    uStack_3c = (uint)*(ushort *)(iVar3 + 0x4c);
    local_40 = (uint)*(ushort *)(iVar3 + 0x48);
    local_38 = auStack_24;
    FUN_0004747e(&local_34,iVar5,iVar6,*(undefined4 *)(iVar3 + 0x44));
    iVar2 = -local_34;
    if (-local_34 < *piVar4) {
      iVar2 = *piVar4;
    }
    *piVar4 = iVar2;
    if (iVar2 <= -local_30) {
      iVar2 = -local_30;
    }
    *piVar4 = iVar2;
    if (iVar2 <= local_2c - iVar5) {
      iVar2 = local_2c - iVar5;
    }
    *piVar4 = iVar2;
    if (iVar2 <= local_28 - iVar6) {
      iVar2 = local_28 - iVar6;
    }
    *piVar4 = iVar2;
    return;
  }
  if (iVar2 != 0x13) {
    if (iVar2 == 0x31) {
      puVar10 = (undefined4 *)FUN_0004673a(param_2);
      *puVar10 = *(undefined4 *)(iVar3 + 0x3c);
      puVar10[1] = *(undefined4 *)(iVar3 + 0x40);
      return;
    }
    if (((iVar2 != 0x1a) && (iVar2 != 0x1d)) && (iVar2 != 0x17)) {
      return;
    }
    FUN_0002bfc4(param_2);
    return;
  }
  puVar10 = (undefined4 *)FUN_0004673a(param_2);
  iVar2 = FUN_0004ccf8(iVar3);
  if (iVar2 == *(int *)(iVar3 + 0x3c)) {
    iVar2 = FUN_0004bbec(iVar3);
    if ((iVar2 == *(int *)(iVar3 + 0x40)) &&
       (((*(int *)(iVar3 + 0x48) != 0x100 || (*(int *)(iVar3 + 0x4c) != 0x100)) ||
        ((*(int *)(iVar3 + 0x44) != 0 ||
         ((*(int *)(iVar3 + 0x50) != *(int *)(iVar3 + 0x3c) / 2 ||
          (*(int *)(iVar3 + 0x54) != *(int *)(iVar3 + 0x40) / 2)))))))) {
      uVar7 = FUN_0004ccf8(iVar3);
      uVar8 = FUN_0004bbec(iVar3);
      uStack_3c = (uint)*(ushort *)(iVar3 + 0x4c);
      local_40 = (uint)*(ushort *)(iVar3 + 0x48);
      local_38 = auStack_24;
      FUN_0004747e(&local_34,uVar7,uVar8,*(undefined4 *)(iVar3 + 0x44));
      local_34 = local_34 + *(int *)(iVar3 + 0x14);
      local_30 = local_30 + *(int *)(iVar3 + 0x18);
      local_2c = local_2c + *(int *)(iVar3 + 0x14);
      local_28 = local_28 + *(int *)(iVar3 + 0x18);
      puVar9 = (uint *)&local_34;
      uVar7 = *puVar10;
      goto LAB_00047adc;
    }
  }
  FUN_0004ba8e(iVar3,&local_40);
  uVar7 = *puVar10;
LAB_00047adc:
  uVar1 = FUN_0003dcb8(puVar9,uVar7,0);
  *(undefined1 *)(puVar10 + 1) = uVar1;
  return;
}

