/* Address: ram:0004f5dc; name: FUN_ram_0004f5dc; body bytes: 612 */

undefined4 FUN_ram_0004f5dc(undefined2 *param_1,byte *param_2)

{
  byte bVar1;
  undefined2 *puVar2;
  int iVar3;
  byte *pbVar4;
  undefined *puVar5;
  byte bVar6;
  undefined1 uVar7;
  undefined4 uVar8;
  
  gp = 0x20004000;
  iVar3 = FUN_ram_20000040(0x40,0x53);
  *(int *)(param_1 + 0x14) = iVar3;
  if (iVar3 == 0) {
LAB_ram_0004f704:
    uVar8 = 8;
  }
  else {
    tmos_memcpy(iVar3,param_2,0x40);
    pbVar4 = *(byte **)(param_1 + 0x36);
    if (((pbVar4[0x12] & 8) == 0) || ((*(byte *)(*(int *)(param_1 + 0x14) + 2) & 8) == 0)) {
      if ((param_2[1] == 0) || (pbVar4[1] == 0)) {
        if (((pbVar4[0x12] | param_2[2]) & 4) == 0) {
LAB_ram_0004f666:
          bVar6 = 1;
        }
        else {
          bVar6 = *param_2;
          bVar1 = *pbVar4;
          puVar5 = &UNK_ram_0006c040;
LAB_ram_0004f728:
          bVar6 = puVar5[(uint)bVar1 + (uint)bVar6 * 5];
        }
      }
      else {
        bVar6 = 0x18;
      }
LAB_ram_0004f67c:
      *(byte *)((int)param_1 + 5) = bVar6;
    }
    else {
      if (*(int *)(param_1 + 0x40) != 0) goto LAB_ram_0004f704;
      iVar3 = FUN_ram_20000040(0x100,0x53);
      *(int *)(param_1 + 0x40) = iVar3;
      if (iVar3 == 0) {
        gp = 0x20004000;
        return 3;
      }
      *(undefined1 *)((int)param_1 + 5) = 0;
      pbVar4 = *(byte **)(param_1 + 0x36);
      bVar6 = param_2[1];
      if (bVar6 != 0) {
        if (pbVar4[1] != 0) goto LAB_ram_0004f66c;
LAB_ram_0004f674:
        bVar6 = *(byte *)((int)param_1 + 5) | 0x10;
        goto LAB_ram_0004f67c;
      }
      if (pbVar4[1] == 0) {
        if (((param_2[2] & 4) != 0) || ((pbVar4[0x12] & 4) != 0)) {
          bVar6 = *param_2;
          bVar1 = *pbVar4;
          puVar5 = &UNK_ram_0006c05c;
          goto LAB_ram_0004f728;
        }
        goto LAB_ram_0004f666;
      }
LAB_ram_0004f66c:
      *(undefined1 *)((int)param_1 + 5) = 8;
      if (bVar6 != 0) goto LAB_ram_0004f674;
    }
    if (((*(byte *)(*(int *)(param_1 + 0x36) + 0x12) & 1) != 0) &&
       ((*(byte *)(*(int *)(param_1 + 0x14) + 2) & 3) == 1)) {
      *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 1;
    }
    if (*(int *)(param_1 + 0x40) != 0) {
      *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 8;
    }
    bVar6 = *(byte *)((int)param_1 + 5);
    if (bVar6 == 1) {
      tmos_memset(param_1 + 4,0,0x10);
      tmos_memset(param_1 + 0xc,0,0x10);
      FUN_ram_000440ba(param_1 + 0x1e,0x10);
      if (*(int *)(param_1 + 0x40) == 0) {
        FUN_ram_0004e8ec(param_1,param_1 + 4,param_1 + 0x1e,param_1 + 0x16);
        iVar3 = FUN_ram_00050272(param_1);
        uVar7 = 0x10;
      }
      else {
        iVar3 = FUN_ram_000502da(param_1);
        uVar7 = 0x50;
      }
joined_r0x0004f7da:
      if (iVar3 != 0) goto LAB_ram_0004f704;
    }
    else {
      if ((bVar6 & 0x18) != 0) {
        puVar2 = param_1 + 4;
        if ((bVar6 & 0x10) == 0) {
          tmos_memset(puVar2,0,0x10);
        }
        else {
          tmos_memcpy(puVar2,*(int *)(param_1 + 0x36) + 2);
        }
        tmos_memset(param_1 + 0xc,0,0x10);
        *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 4;
        FUN_ram_000440ba(param_1 + 0x1e,0x10);
        if (*(int *)(param_1 + 0x40) == 0) {
          FUN_ram_0004e8ec(param_1,puVar2,param_1 + 0x1e,param_1 + 0x16);
          iVar3 = FUN_ram_00050272(param_1);
          uVar7 = 0x13;
        }
        else {
          iVar3 = FUN_ram_000502da(param_1);
          uVar7 = 0x52;
        }
        goto joined_r0x0004f7da;
      }
      uVar8 = 1;
      if ((bVar6 == 2) || (uVar8 = 2, bVar6 == 4)) {
LAB_ram_0004f81c:
        FUN_ram_00044e62(*param_1,uVar8);
      }
      else if (bVar6 == 6) {
        uVar8 = 3;
        goto LAB_ram_0004f81c;
      }
      *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 4;
      if (*(int *)(param_1 + 0x40) == 0) {
        uVar7 = 0x11;
      }
      else {
        uVar7 = 0x51;
      }
    }
    *(undefined1 *)((int)param_1 + 3) = uVar7;
    uVar8 = 0;
  }
  return uVar8;
}

