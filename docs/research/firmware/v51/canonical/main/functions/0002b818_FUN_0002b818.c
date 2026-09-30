/* Address: 0002b818; name: FUN_0002b818; body bytes: 522 */

void FUN_0002b818(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  uint in_fpscr;
  int iVar8;
  undefined1 auStack_1d4 [8];
  int local_1cc;
  undefined1 auStack_164 [8];
  int local_15c;
  undefined1 auStack_124 [12];
  undefined4 local_118;
  undefined2 local_103;
  undefined1 local_101;
  undefined1 auStack_b4 [12];
  undefined4 local_a8;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined2 local_88;
  undefined1 local_86;
  int local_68;
  undefined4 local_64;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  int local_40;
  int iStack_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  
  local_68 = param_1 + 0x38;
  iVar1 = FUN_0004a23c();
  if ((iVar1 == 0) && (iVar1 = FUN_0003db4c(&local_38,param_2 + 0x18,param_1 + 0x14), iVar1 != 0)) {
    puVar5 = (undefined4 *)(param_2 + 0x18);
    uVar2 = *puVar5;
    local_64 = *(undefined4 *)(param_2 + 0x1c);
    local_48 = *(undefined4 *)(param_2 + 0x20);
    uStack_44 = *(undefined4 *)(param_2 + 0x24);
    *puVar5 = local_38;
    *(undefined4 *)(param_2 + 0x1c) = uStack_34;
    *(undefined4 *)(param_2 + 0x20) = uStack_30;
    *(undefined4 *)(param_2 + 0x24) = uStack_2c;
    FUN_00042462(auStack_164);
    FUN_0004cff4(param_1,0x60000,auStack_164);
    FUN_00042ec4(auStack_1d4);
    FUN_0004d0bc(param_1,0x60000,auStack_1d4);
    iVar3 = FUN_0004cbe4(param_1,0x60000);
    iVar3 = iVar3 / 2;
    iVar1 = FUN_0004cbe4(param_1,0x60000);
    iVar1 = iVar1 / 2;
    for (piVar4 = (int *)FUN_0004a14a(local_68); piVar4 != (int *)0x0;
        piVar4 = (int *)FUN_0004a144(local_68,piVar4)) {
      FUN_0004a404(auStack_b4,auStack_164,0x40);
      FUN_0004a404(auStack_124,auStack_1d4,0x70);
      local_88 = (undefined2)piVar4[3];
      local_86 = *(undefined1 *)((int)piVar4 + 0xe);
      local_103 = (undefined2)piVar4[3];
      local_101 = *(undefined1 *)((int)piVar4 + 0xe);
      if ((int)((uint)*(ushort *)(piVar4 + 5) << 0x17) < 0) {
        local_40 = *piVar4;
        iVar7 = piVar4[1];
LAB_0002b8f4:
        iVar6 = *(int *)(param_1 + 0x14) + local_40;
        iVar7 = *(int *)(param_1 + 0x18) + iVar7;
        if ((iVar3 == 0) || (iVar1 == 0)) {
          local_40 = 0;
        }
        else {
          local_40 = 1;
        }
        local_58 = iVar6 - iVar3;
        local_50 = iVar6 + iVar3;
        local_54 = iVar7 - iVar1;
        local_4c = iVar7 + iVar1;
        if ((*(byte *)(piVar4 + 5) & 3) != 0) {
          iVar8 = iVar6;
          if ((*(byte *)(piVar4 + 5) & 1) != 0) {
            iVar8 = *(int *)(param_1 + 0x14);
          }
          local_98 = VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
          local_94 = VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
          iVar8 = iVar6;
          if ((int)((uint)*(byte *)(piVar4 + 5) << 0x1e) < 0) {
            iVar8 = *(int *)(param_1 + 0x1c);
          }
          local_90 = VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
          local_a8 = 0;
          local_118 = 0;
          local_8c = local_94;
          FUN_000423a0(param_2,auStack_b4);
          if (local_40 != 0) {
            FUN_00042a98(param_2,auStack_124,&local_58);
          }
        }
        if ((*(byte *)(piVar4 + 5) & 0xc) != 0) {
          local_98 = VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
          iVar6 = iVar7;
          if ((int)((uint)*(byte *)(piVar4 + 5) << 0x1d) < 0) {
            iVar6 = *(int *)(param_1 + 0x18);
          }
          local_94 = VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
          if ((int)((uint)*(byte *)(piVar4 + 5) << 0x1c) < 0) {
            iVar7 = *(int *)(param_1 + 0x20);
          }
          local_8c = VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
          local_a8 = 1;
          local_118 = 1;
          local_90 = local_98;
          FUN_000423a0(param_2,auStack_b4);
          if (local_40 != 0) {
            FUN_00042a98(param_2,auStack_124,&local_58);
          }
        }
        local_15c = local_15c + 1;
        local_1cc = local_1cc + 1;
      }
      else if (piVar4[2] != 0x7fffffff) {
        FUN_0003f77c(param_1,piVar4[4],piVar4[2],&local_40);
        iVar7 = iStack_3c;
        goto LAB_0002b8f4;
      }
    }
    *puVar5 = uVar2;
    *(undefined4 *)(param_2 + 0x1c) = local_64;
    *(undefined4 *)(param_2 + 0x20) = local_48;
    *(undefined4 *)(param_2 + 0x24) = uStack_44;
  }
  return;
}

