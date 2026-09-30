/* Address: 0003fcb0; name: FUN_0003fcb0; body bytes: 696 */

void FUN_0003fcb0(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  int iVar11;
  int iVar12;
  undefined4 uVar13;
  int *piVar14;
  bool bVar15;
  int local_154;
  int local_150;
  int local_14c;
  int local_148;
  undefined1 auStack_13c [28];
  undefined4 local_120;
  undefined1 auStack_e8 [116];
  undefined4 local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  undefined4 local_54;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  undefined4 local_34;
  undefined4 uStack_30;
  int local_2c;
  int local_28;
  
  iVar11 = FUN_0004b9b2(&PTR_DAT_0007a6b0);
  if (iVar11 == 1) {
    iVar11 = FUN_00046688(param_2);
    iVar12 = FUN_00046698(param_2);
    if (iVar11 == 0x31) {
      piVar14 = (int *)FUN_0004673a(param_2);
      uVar9 = FUN_0004cb28(iVar12,0);
      iVar2 = FUN_00046bd6();
      uVar10 = FUN_0004cb70(iVar12,0);
      uVar13 = FUN_0004cb52(iVar12,0);
      local_34 = 0x1fffffff;
      uStack_30 = 0;
      local_38 = uVar10;
      FUN_00051970(&local_2c,*(undefined4 *)(iVar12 + 0x2c),uVar9,uVar13);
      iVar3 = FUN_0004c82e(iVar12,0);
      iVar4 = FUN_0004c85e(iVar12,0x20000);
      iVar5 = FUN_0004c8a0(iVar12,0x20000);
      iVar6 = FUN_0004c8fa(iVar12,0x20000);
      iVar11 = FUN_0004c7f8(iVar12,0x20000);
      iVar11 = iVar2 + iVar6 + iVar11;
      *piVar14 = iVar2 + iVar4 + iVar5 + local_2c + iVar3;
      if (iVar11 <= local_28) {
        iVar11 = local_28;
      }
      piVar14[1] = iVar11;
    }
    else if (iVar11 == 0x18) {
      piVar14 = (int *)FUN_0004673a(param_2);
      iVar11 = FUN_0004b03e(iVar12,0x20000);
      if (iVar11 < *piVar14) {
        iVar11 = *piVar14;
      }
      *piVar14 = iVar11;
    }
    else if (iVar11 == 0x1a) {
      iVar11 = FUN_00046698();
      local_54 = FUN_00046718(param_2);
      local_74 = FUN_0004cb28(iVar11,0);
      iVar12 = FUN_00046bd6();
      cVar1 = FUN_0004c924(iVar11,0,0x27);
      bVar15 = cVar1 != '\x01';
      iVar2 = FUN_0004c924(iVar11,0,0x30);
      iVar3 = FUN_0004c8fa(iVar11,0);
      if (bVar15) {
        iVar4 = FUN_0004c85e(iVar11,0);
        iVar4 = iVar2 + iVar4;
      }
      else {
        iVar4 = FUN_0004c8a0();
      }
      iVar5 = FUN_0004c82e(iVar11,0);
      iVar6 = FUN_0004c85e(iVar11,0x20000);
      iVar7 = FUN_0004c8a0(iVar11,0x20000);
      local_60 = FUN_0004c8fa(iVar11,0x20000);
      iVar8 = FUN_0004c7f8(iVar11,0x20000);
      uVar9 = FUN_0004c924(iVar11,0x20000,0x68);
      uVar10 = FUN_0004c924(iVar11,0x20000,0x69);
      FUN_00042ec4(auStack_e8);
      FUN_0004d0bc(iVar11,0x20000,auStack_e8);
      if (bVar15) {
        local_154 = *(int *)(iVar11 + 0x14) + iVar4;
        local_14c = iVar6 + iVar7 + local_154 + iVar12 + -1;
      }
      else {
        local_14c = *(int *)(iVar11 + 0x1c) - iVar4;
        local_154 = (((local_14c - iVar12) - iVar6) - iVar7) + 1;
      }
      local_150 = *(int *)(iVar11 + 0x18) + iVar3 + iVar2;
      local_148 = local_60 + iVar8 + local_150 + iVar12 + -1;
      local_4c = local_154;
      local_44 = local_14c;
      local_48 = local_150;
      local_40 = local_148;
      FUN_0003db32(&local_4c,uVar9,uVar10);
      FUN_00042a98(local_54,auStack_e8,&local_4c);
      uVar9 = FUN_0004cb70(iVar11,0);
      uVar10 = FUN_0004cb52(iVar11,0);
      FUN_00051970(&local_3c,*(undefined4 *)(iVar11 + 0x2c),local_74,uVar10,uVar9,0x1fffffff,0);
      FUN_00041db4(auStack_13c);
      FUN_0004cf40(iVar11,0,auStack_13c);
      local_120 = *(undefined4 *)(iVar11 + 0x2c);
      iVar4 = FUN_0003db0a(&local_154);
      if (bVar15) {
        local_70 = local_14c + iVar5;
        local_68 = local_70 + local_3c;
      }
      else {
        local_68 = local_154 - iVar5;
        local_70 = local_68 - local_3c;
      }
      local_6c = (iVar4 - iVar12) / 2 + iVar3 + iVar2 + *(int *)(iVar11 + 0x18);
      local_64 = local_6c + local_38;
      FUN_00041d52(local_54,auStack_13c,&local_70);
      return;
    }
  }
  return;
}

