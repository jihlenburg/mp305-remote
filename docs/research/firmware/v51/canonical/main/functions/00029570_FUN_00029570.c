/* Address: 00029570; name: FUN_00029570; body bytes: 160 */

void FUN_00029570(int param_1,undefined4 param_2,int param_3,uint param_4)

{
  ushort uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined1 auStack_a8 [112];
  undefined4 local_38;
  int local_34;
  undefined4 local_30;
  int local_2c;
  
  if (param_3 != 0xffff) {
    iVar6 = *(int *)(param_1 + 0x2c);
    uVar1 = *(ushort *)(iVar6 + 0x28);
    if (uVar1 != param_4) {
      *(short *)(iVar6 + 0x28) = (short)param_4;
      *(ushort *)(iVar6 + 0x2a) = *(ushort *)(iVar6 + 0x2a) | 8;
    }
    uVar2 = FUN_0004cb2e(iVar6,0x40000);
    iVar3 = FUN_0004cb76(iVar6,0x40000);
    iVar4 = FUN_00046bd6(uVar2);
    iVar5 = FUN_0003758e(param_1);
    local_34 = (param_3 * (iVar4 + iVar3) + *(int *)(iVar5 + 0x18)) - iVar3 / 2;
    local_2c = local_34 + iVar4 + iVar3 + -1;
    local_38 = *(undefined4 *)(*(int *)(param_1 + 0x2c) + 0x14);
    local_30 = *(undefined4 *)(*(int *)(param_1 + 0x2c) + 0x1c);
    FUN_00042ec4(auStack_a8);
    FUN_0004d0bc(iVar6,0x40000,auStack_a8);
    FUN_00042a98(param_2,auStack_a8,&local_38);
    *(ushort *)(iVar6 + 0x28) = uVar1;
    *(ushort *)(iVar6 + 0x2a) = *(ushort *)(iVar6 + 0x2a) & 0xfff7;
  }
  return;
}

