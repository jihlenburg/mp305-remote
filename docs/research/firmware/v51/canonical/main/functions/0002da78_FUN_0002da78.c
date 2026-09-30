/* Address: 0002da78; name: FUN_0002da78; body bytes: 394 */

void FUN_0002da78(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 uVar10;
  int iVar11;
  undefined4 uVar12;
  undefined4 local_b8;
  undefined4 uStack_b4;
  undefined4 local_b0;
  undefined1 auStack_ac [28];
  undefined4 local_90;
  int local_8c;
  undefined4 local_74;
  undefined4 local_70;
  byte local_61;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  int local_48;
  int iStack_44;
  int local_40;
  int local_3c;
  undefined1 auStack_38 [4];
  int local_34;
  undefined1 auStack_30 [20];
  
  iVar1 = FUN_00046688();
  iVar2 = FUN_00046698(param_1);
  if (iVar1 == 0x1a) {
    uVar4 = FUN_00046718(param_1);
    FUN_00037b16(iVar2,&local_48);
    FUN_00042ec4(&local_b8);
    FUN_0004d0bc(iVar2,0x40000,&local_b8);
    FUN_00042a98(uVar4,&local_b8,&local_48);
  }
  else if (iVar1 == 0x1d) {
    iVar1 = FUN_00046718(param_1);
    FUN_00041db4(auStack_ac);
    FUN_0004cf40(iVar2,0x40000,auStack_ac);
    FUN_00037b16(iVar2,auStack_30);
    iVar3 = FUN_0003db4c(&local_58,iVar1 + 0x18,auStack_30);
    if (iVar3 != 0) {
      iVar3 = FUN_0003759c(iVar2);
      uVar4 = FUN_0004ccf8(iVar2);
      uVar5 = FUN_000491e8(iVar3);
      local_b8 = local_74;
      local_b0 = 1;
      uStack_b4 = uVar4;
      FUN_00051970(auStack_38,uVar5,local_8c,local_70);
      iVar6 = FUN_0004bbec(iVar2);
      iVar7 = FUN_0004cb3a(iVar2,0);
      iVar11 = (*(int *)(iVar3 + 0x18) + *(int *)(iVar7 + 0xc) / 2) -
               (*(int *)(iVar2 + 0x18) + iVar6 / 2);
      iVar8 = FUN_0004bbec(iVar3);
      iVar8 = iVar8 - *(int *)(iVar7 + 0xc);
      if (0 < iVar8) {
        iVar11 = (iVar11 * 0x4000) / iVar8;
      }
      iVar11 = (*(int *)(iVar2 + 0x18) + iVar6 / 2 +
               (iVar11 * (local_34 - *(int *)(local_8c + 0xc)) >> 0xe)) -
               *(int *)(local_8c + 0xc) / 2;
      iVar6 = FUN_0004c6a2(iVar2,0);
      iVar7 = FUN_0004c924(iVar2,0,0x12);
      iVar8 = FUN_0004c924(iVar2,0,0x13);
      local_48 = *(int *)(iVar2 + 0x14) + iVar7 + iVar6;
      local_40 = (*(int *)(iVar2 + 0x1c) - iVar8) - iVar6;
      local_3c = iVar11 + local_34;
      local_61 = local_61 | 1;
      puVar9 = (undefined4 *)(iVar1 + 0x18);
      uVar4 = *puVar9;
      uVar5 = *(undefined4 *)(iVar1 + 0x1c);
      uVar10 = *(undefined4 *)(iVar1 + 0x20);
      uVar12 = *(undefined4 *)(iVar1 + 0x24);
      *puVar9 = local_58;
      *(undefined4 *)(iVar1 + 0x1c) = uStack_54;
      *(undefined4 *)(iVar1 + 0x20) = uStack_50;
      *(undefined4 *)(iVar1 + 0x24) = uStack_4c;
      iStack_44 = iVar11;
      local_90 = FUN_000491e8(iVar3);
      FUN_00041d52(iVar1,auStack_ac,&local_48);
      *puVar9 = uVar4;
      *(undefined4 *)(iVar1 + 0x1c) = uVar5;
      *(undefined4 *)(iVar1 + 0x20) = uVar10;
      *(undefined4 *)(iVar1 + 0x24) = uVar12;
    }
  }
  return;
}

