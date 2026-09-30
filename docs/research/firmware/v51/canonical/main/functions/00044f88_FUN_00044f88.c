/* Address: 00044f88; name: FUN_00044f88; body bytes: 18 */

void FUN_00044f88(int param_1,int param_2,int *param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iStack_b4;
  int iStack_b0;
  int iStack_ac;
  int iStack_a8;
  undefined1 auStack_a4 [20];
  int *piStack_90;
  undefined4 *puStack_8c;
  int iStack_88;
  int iStack_84;
  int iStack_80;
  int iStack_7c;
  int iStack_78;
  undefined1 auStack_74 [28];
  undefined *puStack_58;
  undefined *puStack_54;
  undefined *puStack_50;
  undefined *puStack_4c;
  undefined1 auStack_48 [20];
  int iStack_34;
  int iStack_30;
  int *piStack_2c;
  undefined4 uStack_28;
  
  if (-1 < (int)((uint)*(ushort *)(param_2 + 0x4c) << 0x12)) {
    iStack_84 = *param_3;
    iStack_80 = param_3[1];
    iStack_7c = param_3[2];
    iStack_78 = param_3[3];
    if (((*(int *)(param_2 + 0x2c) != 0) || (*(int *)(param_2 + 0x30) != 0x100)) ||
       (*(int *)(param_2 + 0x34) != 0x100)) {
      uVar1 = FUN_0003db28(param_3);
      uVar2 = FUN_0003db0a(param_3);
      piStack_90 = (int *)(uint)*(ushort *)(param_2 + 0x30);
      iStack_88 = param_2 + 0x40;
      puStack_8c = (undefined4 *)(uint)*(ushort *)(param_2 + 0x34);
      FUN_0004747e(&iStack_84,uVar1,uVar2,*(undefined4 *)(param_2 + 0x2c));
      iStack_84 = iStack_84 + *param_3;
      iStack_80 = iStack_80 + param_3[1];
      iStack_7c = iStack_7c + *param_3;
      iStack_78 = iStack_78 + param_3[1];
    }
    iVar3 = FUN_0003db4c(&uStack_28,&iStack_84,*(undefined4 *)(param_1 + 8));
    if ((iVar3 != 0) &&
       (iVar3 = FUN_000477b0(auStack_74,*(undefined4 *)(param_2 + 0x1c),0), iVar3 == 1)) {
      puStack_8c = &uStack_28;
      iStack_88 = 0x3924d;
      piStack_90 = param_3;
      FUN_0003918c(param_1,param_2,auStack_74,0);
      FUN_000476f0(auStack_74);
    }
    return;
  }
  uStack_28 = 0x3924d;
  iStack_34 = param_1;
  iStack_30 = param_2;
  piStack_2c = param_3;
  iVar3 = FUN_000477b0(auStack_a4,*(undefined4 *)(param_2 + 0x1c),0);
  if (iVar3 == 1) {
    uVar5 = *(uint *)(param_2 + 0x24) & 0xffff;
    uVar6 = *(uint *)(param_2 + 0x24) >> 0x10;
    iVar3 = FUN_0003db28(param_2 + 0x54);
    if (iVar3 < 0) {
      iStack_b4 = *param_3;
      iStack_b0 = param_3[1];
      iStack_ac = param_3[2];
      iStack_a8 = param_3[3];
    }
    else {
      iStack_b4 = *(int *)(param_2 + 0x54);
      iStack_b0 = *(int *)(param_2 + 0x58);
      iStack_ac = *(int *)(param_2 + 0x5c);
      iStack_a8 = *(int *)(param_2 + 0x60);
    }
    FUN_0003de04(&iStack_b4,uVar5);
    FUN_0003ddfa(&iStack_b4,uVar6);
    iVar3 = iStack_b4;
    puStack_58 = &DAT_e0000001;
    puStack_54 = &DAT_e0000001;
    puStack_50 = &DAT_e0000001;
    puStack_4c = &DAT_e0000001;
    for (; iStack_b4 = iVar3, iStack_b0 <= param_3[3]; iStack_b0 = iStack_b0 + uVar6) {
      for (; iStack_b4 <= param_3[2]; iStack_b4 = iStack_b4 + uVar5) {
        iVar4 = FUN_0003db4c(auStack_48,&iStack_b4,param_3);
        if (iVar4 != 0) {
          FUN_0003918c(iStack_34,param_2,auStack_a4,&puStack_58,&iStack_b4,auStack_48,0x3924d);
        }
        iStack_ac = iStack_ac + uVar5;
      }
      iStack_a8 = iStack_a8 + uVar6;
      iStack_ac = iVar3 + uVar5 + -1;
    }
    FUN_000476f0(auStack_a4);
  }
  return;
}

