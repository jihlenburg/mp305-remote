/* Address: 00029610; name: FUN_00029610; body bytes: 212 */

void FUN_00029610(int param_1,int param_2,int param_3,uint param_4)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined1 auStack_ac [28];
  undefined4 local_90;
  undefined4 local_8c;
  int local_74;
  undefined4 local_58;
  int local_54;
  undefined4 local_50;
  int local_4c;
  undefined4 local_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  
  if (param_3 != 0xffff) {
    iVar8 = *(int *)(param_1 + 0x2c);
    uVar1 = *(ushort *)(iVar8 + 0x28);
    if (uVar1 != param_4) {
      *(short *)(iVar8 + 0x28) = (short)param_4;
      *(ushort *)(iVar8 + 0x2a) = *(ushort *)(iVar8 + 0x2a) | 8;
    }
    FUN_00041db4(auStack_ac);
    FUN_0004cf40(iVar8,0x40000,auStack_ac);
    local_74 = FUN_0004cb76(iVar8,0x40000);
    iVar2 = FUN_0003758e(param_1);
    if (iVar2 != 0) {
      iVar3 = FUN_00046bd6(local_8c);
      local_54 = (param_3 * (local_74 + iVar3) + *(int *)(iVar2 + 0x18)) - local_74 / 2;
      local_4c = iVar3 + -1 + local_54 + local_74;
      local_58 = *(undefined4 *)(iVar8 + 0x14);
      local_50 = *(undefined4 *)(iVar8 + 0x1c);
      iVar3 = FUN_0003db4c(&local_3c,param_2 + 0x18,&local_58);
      if (iVar3 != 0) {
        puVar9 = (undefined4 *)(param_2 + 0x18);
        uVar4 = *puVar9;
        uVar5 = *(undefined4 *)(param_2 + 0x1c);
        uVar6 = *(undefined4 *)(param_2 + 0x20);
        uVar7 = *(undefined4 *)(param_2 + 0x24);
        *puVar9 = local_3c;
        *(undefined4 *)(param_2 + 0x1c) = uStack_38;
        *(undefined4 *)(param_2 + 0x20) = uStack_34;
        *(undefined4 *)(param_2 + 0x24) = uStack_30;
        local_90 = FUN_000491e8(iVar2);
        FUN_00041d52(param_2,auStack_ac,iVar2 + 0x14);
        *puVar9 = uVar4;
        *(undefined4 *)(param_2 + 0x1c) = uVar5;
        *(undefined4 *)(param_2 + 0x20) = uVar6;
        *(undefined4 *)(param_2 + 0x24) = uVar7;
      }
      *(ushort *)(iVar8 + 0x28) = uVar1;
      *(ushort *)(iVar8 + 0x2a) = *(ushort *)(iVar8 + 0x2a) & 0xfff7;
    }
  }
  return;
}

