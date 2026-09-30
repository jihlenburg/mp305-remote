/* Address: 0005d600; name: FUN_0005d600; body bytes: 748 */

void FUN_0005d600(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint in_fpscr;
  int local_e0;
  int local_dc;
  undefined1 auStack_d8 [28];
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined2 local_ac;
  undefined1 auStack_9c [4];
  int local_98;
  int local_94;
  undefined1 auStack_90 [24];
  undefined4 local_78;
  undefined8 local_74;
  undefined8 local_6c;
  uint local_60;
  undefined2 local_48 [4];
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined1 local_30 [4];
  
  uVar2 = FUN_00046718(param_2);
  if ((*(ushort *)(param_1 + 0x48) & 0x7fff) < 2) {
    return;
  }
  cVar1 = *(char *)(param_1 + 0x3c);
  iVar11 = param_1 + 0x2c;
  if ((((cVar1 != '\x02') && (cVar1 != '\x04')) && (cVar1 != '\x01')) && (cVar1 != '\0')) {
    if ((cVar1 != '\x10') && (cVar1 != '\b')) {
      return;
    }
    FUN_00040ce4(auStack_9c);
    FUN_0004cdfc(param_1,0,auStack_9c);
    FUN_0005d980(param_1,&local_40,local_48);
    uVar3 = FUN_0004a388(*(undefined4 *)(param_1 + 0x40),*(undefined4 *)(param_1 + 0x40),
                         *(undefined4 *)(param_1 + 0x44),*(int *)(param_1 + 0x54),
                         *(int *)(param_1 + 0x50) + *(int *)(param_1 + 0x54));
    uVar4 = FUN_0004a388(*(undefined4 *)(param_1 + 0x44),*(undefined4 *)(param_1 + 0x40),
                         *(undefined4 *)(param_1 + 0x44),*(int *)(param_1 + 0x54),
                         *(int *)(param_1 + 0x50) + *(int *)(param_1 + 0x54));
    local_74._4_4_ = local_40;
    local_6c._0_4_ = uStack_3c;
    local_78 = VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
    local_6c._4_4_ = CONCAT22(local_6c._6_2_,local_48[0]);
    local_74._0_4_ = VectorSignedToFloat(uVar4,(byte)(in_fpscr >> 0x16) & 3);
    FUN_00040c74(uVar2,auStack_9c);
    for (puVar5 = (undefined4 *)FUN_0004a14a(iVar11); puVar5 != (undefined4 *)0x0;
        puVar5 = (undefined4 *)FUN_0004a144(iVar11,puVar5)) {
      FUN_00040ce4(&local_e0);
      FUN_0004cdfc(param_1,0,&local_e0);
      FUN_0005d980(param_1,&local_38,local_30);
      uVar3 = FUN_0004a388(puVar5[3],*(undefined4 *)(param_1 + 0x40),*(undefined4 *)(param_1 + 0x44)
                           ,*(int *)(param_1 + 0x54),
                           *(int *)(param_1 + 0x50) + *(int *)(param_1 + 0x54));
      uVar4 = FUN_0004a388(puVar5[4],*(undefined4 *)(param_1 + 0x40),*(undefined4 *)(param_1 + 0x44)
                           ,*(int *)(param_1 + 0x54),
                           *(int *)(param_1 + 0x50) + *(int *)(param_1 + 0x54));
      FUN_0005ddbc(param_1,&local_e0,*puVar5);
      local_b4 = local_38;
      local_b0 = uStack_34;
      local_bc = VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
      local_ac = local_30._0_2_;
      local_b8 = VectorSignedToFloat(uVar4,(byte)(in_fpscr >> 0x16) & 3);
      FUN_00040c74(uVar2,&local_e0);
    }
    return;
  }
  FUN_00042462(auStack_90);
  FUN_0004cff4(param_1,0,auStack_90);
  iVar6 = FUN_0004c6a8(param_1,0);
  iVar7 = FUN_0004c900(param_1,0);
  iVar8 = FUN_0004c7fe(param_1,0);
  iVar9 = FUN_0004c864(param_1,0);
  iVar9 = iVar9 + iVar6;
  iVar10 = FUN_0004c8a6(param_1,0);
  local_e0 = 0;
  cVar1 = *(char *)(param_1 + 0x3c);
  local_dc = 0;
  if (cVar1 == '\x02') {
    local_e0 = (*(int *)(param_1 + 0x1c) + (local_60 >> 1)) - (iVar10 + iVar6);
LAB_0005d732:
    local_dc = *(int *)(param_1 + 0x18) + iVar7 + iVar6;
  }
  else {
    if (cVar1 == '\x04') {
      local_e0 = *(int *)(param_1 + 0x14) + iVar9 + (local_60 >> 1);
      goto LAB_0005d732;
    }
    if (cVar1 == '\x01') {
      local_e0 = *(int *)(param_1 + 0x14) + iVar10 + iVar6;
      local_dc = *(int *)(param_1 + 0x18) + iVar7 + iVar6 + (local_60 >> 1);
LAB_0005d77c:
      local_e0 = local_e0 - (*(uint *)(param_1 + 0x5c) >> 1);
      local_98 = (*(int *)(param_1 + 0x1c) - iVar9) + (*(uint *)(param_1 + 0x60) >> 1);
      local_94 = local_dc;
      goto LAB_0005d79c;
    }
    if (cVar1 == '\0') {
      local_e0 = *(int *)(param_1 + 0x14) + iVar9;
      local_dc = (*(int *)(param_1 + 0x20) + (local_60 >> 1)) - (iVar8 + iVar6);
      goto LAB_0005d77c;
    }
    if ((cVar1 != '\x02') && (cVar1 != '\x04')) goto LAB_0005d77c;
  }
  local_e0 = local_e0 + -1;
  local_dc = local_dc - (*(uint *)(param_1 + 0x5c) >> 1);
  local_94 = (*(int *)(param_1 + 0x20) - (iVar8 + iVar6)) + (*(uint *)(param_1 + 0x60) >> 1);
  local_98 = local_e0;
LAB_0005d79c:
  local_74 = FUN_0004f280(&local_e0);
  local_6c = FUN_0004f280(&local_98);
  FUN_000423a0(uVar2,auStack_90);
  puVar5 = (undefined4 *)FUN_0004a14a(iVar11);
  while (puVar5 != (undefined4 *)0x0) {
    FUN_00042462(auStack_d8);
    FUN_0004cff4(param_1,0,auStack_d8);
    if ((*(char *)(param_1 + 0x3c) == '\x02') || (*(char *)(param_1 + 0x3c) == '\x04')) {
      iVar9 = puVar5[0xc] + ((uint)puVar5[9] >> 1);
      iVar8 = puVar5[0xe] - ((uint)puVar5[10] >> 1);
      iVar6 = local_e0;
      iVar7 = local_e0;
    }
    else {
      iVar6 = puVar5[0xd] + ((uint)puVar5[10] >> 1);
      iVar7 = puVar5[0xb] - ((uint)puVar5[9] >> 1);
      iVar8 = local_dc;
      iVar9 = local_dc;
    }
    FUN_0005df30(param_1,auStack_d8,*puVar5,0);
    local_bc = VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
    local_b8 = VectorSignedToFloat(iVar9,(byte)(in_fpscr >> 0x16) & 3);
    local_b4 = VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
    local_b0 = VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
    FUN_000423a0(uVar2,auStack_d8);
    puVar5 = (undefined4 *)FUN_0004a144(iVar11,puVar5);
  }
  return;
}

