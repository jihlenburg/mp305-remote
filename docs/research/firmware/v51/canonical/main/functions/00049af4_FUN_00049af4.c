/* Address: 00049af4; name: FUN_00049af4; body bytes: 658 */

/* Recovered from stored Thumb pointer at 0007ab0c; callback identification is inferred until
   reviewed. */

void FUN_00049af4(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined1 auStack_88 [33];
  undefined2 local_67;
  undefined1 local_65;
  undefined4 local_64;
  undefined2 local_5f;
  undefined1 local_5d;
  undefined4 local_4a;
  undefined4 local_3e;
  undefined2 local_2f;
  undefined1 local_2d;
  int local_2c;
  int local_20;
  undefined4 local_18;
  
  iVar2 = FUN_00046688(param_2);
  if ((((iVar2 == 0x1a) || (iVar2 == 0x1b)) ||
      (iVar3 = FUN_0004b9b2(&DAT_0007ab00,param_2), iVar3 == 1)) &&
     (iVar3 = FUN_00046698(param_2), iVar2 == 0x1a)) {
    FUN_00042ec4(auStack_88);
    FUN_0004d0bc(iVar3,0,auStack_88);
    local_18._0_3_ = CONCAT12(local_65,local_67);
    uVar4 = FUN_000402b8(local_18);
    uVar5 = FUN_0004029c();
    puVar1 = (undefined4 *)(iVar3 + 0x2c);
    uVar4 = FUN_000403d2(*puVar1,uVar5,uVar4);
    local_18._0_2_ = (undefined2)uVar4;
    local_67 = (undefined2)local_18;
    local_18._2_1_ = (undefined1)((uint)uVar4 >> 0x10);
    local_65 = local_18._2_1_;
    local_18 = uVar4;
    uVar4 = FUN_000402b8(local_64);
    uVar5 = FUN_0004029c();
    uVar4 = FUN_000403d2(*puVar1,uVar5,uVar4);
    local_64._0_3_ = (undefined3)uVar4;
    local_18._3_1_ = (undefined1)((uint)uVar4 >> 0x18);
    local_18._0_3_ = CONCAT12(local_5d,local_5f);
    uVar4 = FUN_000402b8(local_18);
    uVar5 = FUN_0004029c();
    uVar4 = FUN_000403d2(*puVar1,uVar5,uVar4);
    local_18._0_2_ = (undefined2)uVar4;
    local_5f = (undefined2)local_18;
    local_18._2_1_ = (undefined1)((uint)uVar4 >> 0x10);
    local_5d = local_18._2_1_;
    local_18._3_1_ = (undefined1)((uint)uVar4 >> 0x18);
    local_18._0_3_ = CONCAT12(local_2d,local_2f);
    uVar4 = FUN_000402b8(local_18);
    uVar5 = FUN_0004029c();
    uVar4 = FUN_000403d2(*puVar1,uVar5,uVar4);
    local_18._0_2_ = (undefined2)uVar4;
    local_2f = (undefined2)local_18;
    local_18._2_1_ = (undefined1)((uint)uVar4 >> 0x10);
    local_2d = local_18._2_1_;
    local_18 = uVar4;
    uVar4 = FUN_000402b8(local_4a);
    uVar5 = FUN_0004029c();
    local_18 = FUN_000403d2(*puVar1,uVar5,uVar4);
    local_4a._0_3_ = (undefined3)local_18;
    uVar4 = FUN_000402b8(local_3e);
    uVar5 = FUN_0004029c();
    local_18 = FUN_000403d2(*puVar1,uVar5,uVar4);
    local_3e._0_3_ = (undefined3)local_18;
    uVar4 = FUN_0004029c();
    local_18._0_3_ = CONCAT12(local_65,local_67);
    uVar4 = FUN_000403d2(local_18,uVar4,*(undefined1 *)(iVar3 + 0x2f));
    local_18._0_2_ = (undefined2)uVar4;
    local_67 = (undefined2)local_18;
    local_18._2_1_ = (undefined1)((uint)uVar4 >> 0x10);
    local_65 = local_18._2_1_;
    local_18 = uVar4;
    uVar4 = FUN_0004029c();
    local_18 = FUN_000403d2(local_64,uVar4,*(undefined1 *)(iVar3 + 0x2f));
    local_64._0_3_ = (undefined3)local_18;
    uVar4 = FUN_0004029c();
    local_18._0_3_ = CONCAT12(local_5d,local_5f);
    uVar4 = FUN_000403d2(local_18,uVar4,*(undefined1 *)(iVar3 + 0x2f));
    local_18._0_2_ = (undefined2)uVar4;
    local_5f = (undefined2)local_18;
    local_18._2_1_ = (undefined1)((uint)uVar4 >> 0x10);
    local_5d = local_18._2_1_;
    local_18 = uVar4;
    uVar4 = FUN_0004029c();
    local_18 = FUN_000403d2(local_4a,uVar4,*(undefined1 *)(iVar3 + 0x2f));
    local_4a._0_3_ = (undefined3)local_18;
    uVar4 = FUN_0004029c();
    local_18._0_3_ = CONCAT12(local_2d,local_2f);
    uVar4 = FUN_000403d2(local_18,uVar4,*(undefined1 *)(iVar3 + 0x2f));
    local_18._0_2_ = (undefined2)uVar4;
    local_2f = (undefined2)local_18;
    local_18._2_1_ = (undefined1)((uint)uVar4 >> 0x10);
    local_2d = local_18._2_1_;
    local_18 = uVar4;
    uVar4 = FUN_0004029c();
    local_18 = FUN_000403d2(local_3e,uVar4,*(undefined1 *)(iVar3 + 0x2f));
    local_3e._0_3_ = (undefined3)local_18;
    local_2c = (int)(local_2c * (*(byte *)(iVar3 + 0x2f) - 0x50)) / 0xaf;
    local_20 = (int)(local_20 * (*(byte *)(iVar3 + 0x2f) - 0x50)) / 0xaf;
    uVar4 = FUN_00046718(param_2);
    FUN_00042a98(uVar4,auStack_88,iVar3 + 0x14);
  }
  return;
}

