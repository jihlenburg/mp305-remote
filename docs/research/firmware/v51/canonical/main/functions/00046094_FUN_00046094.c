/* Address: 00046094; name: FUN_00046094; body bytes: 914 */

uint FUN_00046094(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  undefined4 uVar11;
  uint uVar12;
  bool bVar13;
  undefined1 auStack_1fc [28];
  undefined4 local_1e0;
  undefined4 local_1dc;
  undefined4 local_1c4;
  undefined4 local_1c0;
  undefined1 local_1b1;
  undefined1 auStack_1a8 [28];
  undefined1 *local_18c;
  undefined4 local_188;
  undefined4 local_170;
  undefined4 local_16c;
  undefined1 local_15d;
  byte local_15c;
  undefined1 auStack_154 [128];
  undefined1 auStack_d4 [4];
  uint local_d0;
  uint local_c8;
  uint uStack_c4;
  undefined4 local_b8;
  undefined4 local_a8;
  undefined1 auStack_94 [56];
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  undefined4 local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_2c;
  
  uVar7 = FUN_0004b9b2(&PTR_DAT_0007a6d4);
  if (uVar7 != 1) {
    return uVar7;
  }
  iVar8 = FUN_00046688(param_2);
  uVar7 = FUN_00046698(param_2);
  if (iVar8 == 0x10) {
    FUN_0004bbe2();
    iVar8 = FUN_000472d4();
    FUN_00047eec();
    uVar9 = FUN_000482e0();
    if (uVar9 != 4) {
      return uVar9;
    }
    if (iVar8 != 0) goto LAB_000461ae;
  }
  else {
    if ((iVar8 == 0x11) || (iVar8 == 0x12)) goto LAB_00046102;
    if (iVar8 == 8) {
LAB_00024fcc:
      uVar11 = FUN_00047eec();
      iVar8 = FUN_000482c2();
      if (iVar8 == 0) {
        iVar8 = FUN_00046248(uVar7);
        if (iVar8 == 0) {
          FUN_00046304(uVar7);
        }
        else {
          FUN_00045fa8();
          if (*(int *)(uVar7 + 0x44) != *(int *)(uVar7 + 0x40)) {
            *(int *)(uVar7 + 0x44) = *(int *)(uVar7 + 0x40);
            uVar9 = FUN_0004e5a6(uVar7,0x20,&stack0xfffffff0);
            if (uVar9 != 1) {
              return uVar9;
            }
            FUN_0004d3d8(uVar7);
          }
          iVar8 = FUN_000482e0(uVar11);
          if (iVar8 == 4) {
            uVar11 = FUN_0004bbe2(uVar7);
            FUN_0004743a(uVar11,0);
          }
        }
      }
      else {
        *(undefined4 *)(uVar7 + 0x40) = *(undefined4 *)(uVar7 + 0x44);
        FUN_0004d3d8();
      }
      return 1;
    }
    if ((iVar8 == 0x2f) || (iVar8 == 0x2e)) {
      uVar7 = FUN_0004deac();
      return uVar7;
    }
    if (iVar8 == 0x31) {
      iVar8 = FUN_0004673a(param_2);
      FUN_0004cb2e(uVar7,0);
      uVar7 = FUN_00046bd6();
      *(uint *)(iVar8 + 4) = uVar7;
      return uVar7;
    }
    if (iVar8 != 0xe) {
      if (iVar8 != 0xf) {
        if (iVar8 != 0x1a) {
          return uVar7;
        }
        iVar8 = FUN_00046698();
        local_44 = FUN_00046718(param_2);
        iVar2 = FUN_0004c69c(iVar8,0);
        local_2c = FUN_0004c924(iVar8,0,0x12);
        local_2c = local_2c + iVar2;
        iVar3 = FUN_0004c924(iVar8,0,0x13);
        FUN_00041db4(auStack_1fc);
        FUN_0004cf40(iVar8,0x20000,auStack_1fc);
        puVar4 = *(undefined1 **)(iVar8 + 0x30);
        if (puVar4 == (undefined1 *)0x0) {
          FUN_000461e8(iVar8,auStack_154,0x80);
          puVar4 = auStack_154;
        }
        bVar13 = (*(byte *)(iVar8 + 0x4c) & 0xf) != 1;
        cVar1 = FUN_0004c924(iVar8,0,0x27);
        if (*(int *)(iVar8 + 0x34) != 0) {
          iVar5 = FUN_00047ecc();
          if (iVar5 == 2) {
            FUN_00051970(&local_c8,*(undefined4 *)(iVar8 + 0x34),local_1dc,local_1c0,local_1c4,
                         0x1fffffff,local_1b1);
            uVar7 = uStack_c4;
            uVar9 = local_c8;
          }
          else {
            iVar6 = FUN_0004775c(*(undefined4 *)(iVar8 + 0x34),auStack_d4);
            if (iVar6 == 1) {
              uVar7 = local_d0 >> 0x10;
              uVar9 = local_d0 & 0xffff;
            }
            else {
              uVar7 = 0xffffffff;
              uVar9 = 0xffffffff;
            }
          }
          local_3c = *(int *)(iVar8 + 0x18);
          local_34 = local_3c + (uVar7 - 1);
          local_40 = *(int *)(iVar8 + 0x14);
          local_38 = local_40 + (uVar9 - 1);
          if (cVar1 != '\x01' && bVar13) {
            iVar6 = -(iVar3 + iVar2);
            uVar11 = 8;
          }
          else {
            uVar11 = 7;
            iVar6 = local_2c;
          }
          FUN_0003d7de(iVar8 + 0x14,&local_40,uVar11,iVar6,0);
          if (iVar5 == 2) {
            local_1e0 = *(undefined4 *)(iVar8 + 0x34);
            FUN_00041d52(local_44,auStack_1fc,&local_40);
          }
          else {
            FUN_00041b74(auStack_d4);
            FUN_0004ce8c(iVar8,0x20000,auStack_d4);
            FUN_0004f266(auStack_94,(int)uVar9 / 2,(int)uVar7 / 2);
            local_a8 = FUN_0004c924(iVar8,0x20000,0x6e);
            local_b8 = *(undefined4 *)(iVar8 + 0x34);
            FUN_00041acc(local_44,auStack_d4,&local_40);
          }
        }
        FUN_00041db4(auStack_1a8);
        FUN_0004cf40(iVar8,0,auStack_1a8);
        FUN_00051970(&local_4c,puVar4,local_188,local_16c,local_170,0x1fffffff,local_15d);
        local_5c = *(int *)(iVar8 + 0x14);
        local_54 = local_5c + local_4c + -1;
        local_58 = *(int *)(iVar8 + 0x18);
        local_50 = local_58 + local_48 + -1;
        if (*(int *)(iVar8 + 0x34) == 0) {
          iVar2 = 0;
          uVar11 = 9;
        }
        else if (cVar1 != '\x01' && bVar13) {
          uVar11 = 7;
          iVar2 = local_2c;
        }
        else {
          uVar11 = 8;
          iVar2 = -(iVar3 + iVar2);
        }
        FUN_0003d7de(iVar8 + 0x14,&local_5c,uVar11,iVar2,0);
        if (*(int *)(iVar8 + 0x30) == 0) {
          local_15c = local_15c | 0x40;
        }
        local_18c = puVar4;
        uVar7 = FUN_00041d52(local_44,auStack_1a8,&local_5c);
        return uVar7;
      }
      iVar8 = FUN_00046248();
      if (iVar8 == 0) {
LAB_000461ae:
        uVar7 = FUN_00046304(uVar7);
        return uVar7;
      }
      iVar8 = FUN_0004673e(param_2);
      uVar10 = *(int *)(uVar7 + 0x40) + iVar8;
      uVar12 = *(int *)(uVar7 + 0x3c) - 1;
      uVar9 = uVar12;
      if ((int)uVar10 < (int)uVar12) {
        uVar9 = uVar10;
      }
      if ((int)uVar9 < 0) {
        uVar10 = 0;
      }
      else if ((int)uVar12 <= (int)uVar10) {
        uVar10 = *(int *)(uVar7 + 0x3c) - 1;
      }
LAB_00046186:
      *(uint *)(uVar7 + 0x40) = uVar10;
      uVar7 = FUN_00058850(uVar7);
      return uVar7;
    }
    uVar9 = FUN_00046700(param_2);
    if ((uVar9 == 0x13) || (uVar9 == 0x12)) {
      iVar8 = FUN_00046248(uVar7);
      if (iVar8 == 0) goto LAB_000461ae;
      uVar10 = *(int *)(uVar7 + 0x40) + 1;
      if (*(uint *)(uVar7 + 0x3c) <= uVar10) {
        return uVar10;
      }
      goto LAB_00046186;
    }
    if ((uVar9 == 0x14) || (uVar9 == 0x11)) {
      iVar8 = FUN_00046248(uVar7);
      if (iVar8 == 0) goto LAB_000461ae;
      if (*(int *)(uVar7 + 0x40) == 0) {
        return 0;
      }
      uVar10 = *(int *)(uVar7 + 0x40) - 1;
      goto LAB_00046186;
    }
    if (uVar9 != 0x1b) {
      if (uVar9 != 10) {
        return uVar9;
      }
      uVar9 = FUN_00048258();
      if (uVar9 == uVar7) {
        return uVar9;
      }
      goto LAB_00024fcc;
    }
  }
  *(undefined4 *)(uVar7 + 0x40) = *(undefined4 *)(uVar7 + 0x44);
LAB_00046102:
  uVar7 = FUN_00045fa8(uVar7);
  return uVar7;
}

