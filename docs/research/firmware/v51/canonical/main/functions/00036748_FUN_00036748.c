/* Address: 00036748; name: FUN_00036748; body bytes: 726 */

void FUN_00036748(int param_1)

{
  undefined1 *puVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  int *piVar9;
  char cVar10;
  bool bVar11;
  undefined1 local_5c;
  undefined1 local_5b;
  char local_5a;
  byte local_59;
  undefined4 local_58;
  undefined4 local_54;
  int local_50;
  int local_4c [4];
  undefined4 local_3c;
  undefined4 local_34;
  int local_30;
  int local_2c;
  int local_28;
  
  uVar2 = FUN_0004c924(param_1,0,0x7d);
  local_59 = local_59 & 0xf8 | (char)uVar2 + 1U & 1 | (byte)((uVar2 >> 2 & 1) << 1) |
             (byte)((uVar2 >> 3 & 1) << 2);
  local_5c = FUN_0004c924(param_1,0,0x7e);
  local_5b = FUN_0004c924(param_1,0,0x7f);
  local_5a = FUN_0004c924(param_1,0,0x80);
  iVar3 = FUN_0004c5ee(param_1,0);
  bVar11 = iVar3 == 1;
  if ((local_59 & 1) == 0) {
    iVar3 = FUN_0004c834(param_1,0);
  }
  else {
    iVar3 = FUN_0004c8d0();
  }
  if ((local_59 & 1) == 0) {
    local_54 = FUN_0004c8d0(param_1,0);
  }
  else {
    local_54 = FUN_0004c834();
  }
  if ((local_59 & 1) == 0) {
    local_58 = FUN_0004baf8(param_1);
  }
  else {
    local_58 = FUN_0004bb1a();
  }
  iVar4 = FUN_0004c924(param_1,0,0x10);
  iVar5 = FUN_0004c6b4(param_1,0);
  iVar6 = FUN_0004c66c(param_1,0);
  if (iVar6 << 0x1e < 0) {
    iVar4 = iVar4 + iVar5;
  }
  iVar5 = *(int *)(param_1 + 0x18);
  local_50 = FUN_0004bf2c(param_1);
  local_50 = (iVar4 + iVar5) - local_50;
  iVar4 = FUN_0004c924(param_1,0,0x12);
  iVar5 = FUN_0004c6b4(param_1,0);
  iVar6 = FUN_0004c66c(param_1,0);
  if (iVar6 << 0x1d < 0) {
    iVar4 = iVar4 + iVar5;
  }
  iVar5 = *(int *)(param_1 + 0x14);
  local_2c = FUN_0004bf20(param_1);
  cVar10 = local_5a;
  local_2c = (iVar4 + iVar5) - local_2c;
  if ((local_59 & 1) == 0) {
    puVar1 = &stack0x00000020;
  }
  else {
    puVar1 = &stack0xfffffffc;
  }
  piVar9 = (int *)(puVar1 + -0x4c);
  local_28 = FUN_0004cbf0(param_1,0);
  iVar4 = FUN_0004c6d8(param_1,0);
  if ((local_59 & 1) == 0) {
LAB_0003689e:
    if ((local_28 != 0x3fffffff) || ((int)((uint)*(ushort *)(param_1 + 0x2a) << 0x14) < 0))
    goto LAB_000368b0;
  }
  else if ((iVar4 != 0x3fffffff) || ((int)((uint)*(ushort *)(param_1 + 0x2a) << 0x15) < 0)) {
    if ((local_59 & 1) != 0) goto LAB_000368b0;
    goto LAB_0003689e;
  }
  cVar10 = '\0';
LAB_000368b0:
  if ((bVar11) && ((local_59 & 1) == 0)) {
    if (cVar10 == '\0') {
      cVar10 = '\x01';
    }
    else if (cVar10 == '\x01') {
      cVar10 = '\0';
    }
  }
  iVar5 = 0;
  iVar6 = 0;
  local_30 = 0;
  if (cVar10 != '\0') {
    if ((int)((uint)local_59 << 0x1d) < 0) {
      iVar8 = *(ushort *)(*(int *)(param_1 + 8) + 0x28) - 1;
    }
    else {
      iVar8 = 0;
    }
    while ((iVar8 < (int)(uint)*(ushort *)(*(int *)(param_1 + 8) + 0x28) && (-1 < iVar8))) {
      local_34 = 0;
      iVar8 = FUN_00036530(param_1,&local_5c,iVar8,local_58,local_54,local_4c);
      iVar5 = local_4c[0] + iVar5 + iVar3;
      iVar6 = iVar6 + 1;
    }
    if (iVar6 != 0) {
      iVar5 = iVar5 - iVar3;
    }
    if ((local_59 & 1) == 0) {
      uVar7 = FUN_0004bb1a(param_1);
    }
    else {
      uVar7 = FUN_0004baf8();
    }
    FUN_000586ec(cVar10,uVar7,iVar5,iVar6,piVar9,&local_30);
  }
  if ((int)((uint)local_59 << 0x1d) < 0) {
    iVar6 = *(ushort *)(*(int *)(param_1 + 8) + 0x28) - 1;
  }
  else {
    iVar6 = 0;
  }
  if ((bVar11) && ((local_59 & 1) == 0)) {
    *piVar9 = *piVar9 + iVar5;
  }
  while ((iVar6 < (int)(uint)*(ushort *)(*(int *)(param_1 + 8) + 0x28) && (-1 < iVar6))) {
    local_34 = 1;
    iVar5 = FUN_00036530(param_1,&local_5c,iVar6,local_58,local_54,local_4c);
    if ((bVar11) && ((local_59 & 1) == 0)) {
      *piVar9 = *piVar9 - local_4c[0];
    }
    FUN_00026cac(param_1,&local_5c,iVar6,iVar5,local_2c,local_50,local_58,local_54,local_4c);
    FUN_00046bec(local_3c);
    local_3c = 0;
    if ((bVar11) && ((local_59 & 1) == 0)) {
      iVar6 = *piVar9 - (local_30 + iVar3);
    }
    else {
      iVar6 = local_30 + iVar3 + local_4c[0] + *piVar9;
    }
    *piVar9 = iVar6;
    iVar6 = iVar5;
  }
  if ((local_28 == 0x3fffffff) || (iVar4 == 0x3fffffff)) {
    FUN_0004dbe0(param_1);
  }
  FUN_0004e5a6(param_1,0x30,0);
  return;
}

