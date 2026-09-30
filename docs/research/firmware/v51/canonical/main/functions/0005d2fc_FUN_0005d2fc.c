/* Address: 0005d2fc; name: FUN_0005d2fc; body bytes: 432 */

void FUN_0005d2fc(int param_1,undefined4 param_2)

{
  bool bVar1;
  undefined1 *puVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  undefined1 *puVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  undefined8 uVar12;
  undefined1 auStack_16c [28];
  undefined8 local_150;
  undefined8 local_148;
  byte local_12f;
  undefined1 auStack_12c [28];
  undefined8 local_110;
  undefined8 local_108;
  undefined1 auStack_e4 [68];
  undefined1 auStack_a0 [8];
  uint local_98;
  int iStack_94;
  undefined1 auStack_44 [8];
  undefined4 local_3c;
  undefined1 auStack_38 [12];
  int iStack_2c;
  undefined4 local_28;
  
  iStack_2c = param_1;
  local_28 = param_2;
  local_3c = FUN_00046718(param_2);
  if (1 < (*(ushort *)(param_1 + 0x48) & 0x7fff)) {
    FUN_00041db4(auStack_a0);
    FUN_0004cf40(param_1,0x20000,auStack_a0);
    FUN_00042462(auStack_16c);
    FUN_0004cff4(param_1,0x20000,auStack_16c);
    if ((*(char *)(param_1 + 0x3c) == '\x10') || (*(char *)(param_1 + 0x3c) == '\b')) {
      local_12f = local_12f & 0xef;
    }
    FUN_00042462(auStack_12c);
    FUN_0004cff4(param_1,&LAB_00050000,auStack_12c);
    FUN_00042462(auStack_e4);
    FUN_0004cff4(param_1,0,auStack_e4);
    uVar10 = *(ushort *)(param_1 + 0x48) & 0x7fff;
    iVar11 = 0;
    for (uVar9 = 0; uVar9 < uVar10; uVar9 = uVar9 + 1) {
      uVar3 = (*(uint *)(param_1 + 0x48) & 0x3fffffff) >> 0xf;
      bVar1 = uVar9 == uVar3 * (uVar9 / uVar3);
      if (bVar1) {
        iVar11 = iVar11 + 1;
      }
      uVar3 = (uint)bVar1;
      iVar4 = FUN_0004a388(uVar9,0,uVar10 - 1,*(undefined4 *)(param_1 + 0x40),
                           *(undefined4 *)(param_1 + 0x44));
      iVar5 = param_1 + 0x2c;
      local_98 = uVar9;
      iStack_94 = iVar4;
      iVar6 = FUN_0004a14a();
      while (iVar6 != 0) {
        if ((*(int *)(iVar6 + 0xc) <= iVar4) && (iVar4 <= *(int *)(iVar6 + 0x10))) {
          if (uVar3 == 0) {
            uVar7 = *(undefined4 *)(iVar6 + 8);
            puVar8 = &LAB_00050000;
            puVar2 = &stack0x00000020;
          }
          else {
            FUN_0005de60(param_1,auStack_a0,*(undefined4 *)(iVar6 + 4));
            puVar8 = (undefined1 *)0x20000;
            puVar2 = &stack0xffffffe0;
            uVar7 = *(undefined4 *)(iVar6 + 4);
          }
          FUN_0005df30(param_1,puVar2 + -0x14c,uVar7,puVar8);
          break;
        }
        FUN_0004cf40(param_1,0x20000,auStack_a0);
        FUN_0004cff4(param_1,0x20000,auStack_16c);
        FUN_0004cff4(param_1,&LAB_00050000,auStack_12c);
        iVar6 = FUN_0004a144(iVar5,iVar6);
      }
      FUN_0005db06(param_1,uVar9,uVar3,auStack_38,auStack_44);
      if (((*(uint *)(param_1 + 0x48) & 0x7fffffff) >> 0x1e & uVar3) != 0) {
        FUN_0005d4b0(param_1,local_28,auStack_a0,iVar11,iVar4,auStack_44,uVar9);
      }
      if (uVar3 == 0) {
        uVar12 = FUN_0004f280(auStack_38);
        local_110 = uVar12;
        uVar12 = FUN_0004f280(auStack_44);
        puVar2 = &stack0x00000020;
      }
      else {
        uVar12 = FUN_0004f280(auStack_38);
        local_150 = uVar12;
        uVar12 = FUN_0004f280(auStack_44);
        puVar2 = &stack0xffffffe0;
        local_148 = uVar12;
        uVar12 = local_108;
      }
      local_108 = uVar12;
      FUN_000423a0(local_3c,puVar2 + -0x14c);
    }
  }
  return;
}

