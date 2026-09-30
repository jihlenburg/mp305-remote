/* Address: 00047f68; name: FUN_00047f68; body bytes: 748 */

int FUN_00047f68(int param_1)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined4 uVar8;
  byte bVar9;
  int iVar10;
  uint uVar11;
  short sVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  int iVar16;
  uint uVar17;
  int local_6c;
  int local_68;
  uint local_64;
  int local_60;
  int local_5c;
  undefined4 local_58;
  undefined4 local_54;
  uint local_4c;
  undefined4 local_44;
  uint local_3c;
  uint local_38;
  int local_34;
  int local_30;
  int local_2c;
  
  iVar16 = 0;
  local_44 = 0;
  uVar2 = (uint)*(byte *)(param_1 + 0x24);
  iVar15 = *(int *)(param_1 + 0x68);
  local_4c = 0;
  uVar17 = 0;
  *(int *)(param_1 + 0x50) = *(int *)(param_1 + 0x50) + *(int *)(param_1 + 0x48);
  *(int *)(param_1 + 0x54) = *(int *)(param_1 + 0x4c) + *(int *)(param_1 + 0x54);
  do {
    if (iVar15 == 0) {
LAB_00048230:
      if (iVar16 != 0) {
        *(byte *)(param_1 + 0x98) = *(byte *)(param_1 + 0x98) & 0xf0 | (byte)local_44 & 0xf;
        *(undefined4 *)(param_1 + 0x50) = 0;
        *(int *)(param_1 + 0x70) = iVar16;
        *(undefined4 *)(param_1 + 0x54) = 0;
      }
      return iVar16;
    }
    sVar12 = 0;
    iVar10 = 0x100;
    iVar13 = 0x100;
    local_58 = 0;
    local_54 = 0;
    for (iVar5 = iVar15; iVar5 != 0; iVar5 = FUN_0004bc8c(iVar5)) {
      sVar1 = FUN_0004cbac(iVar5,0);
      sVar12 = sVar1 + sVar12;
      iVar3 = FUN_0004cbb2(iVar5,0);
      iVar4 = FUN_0004cbc2(iVar5,0);
      iVar13 = iVar13 * iVar4 >> 8;
      iVar10 = iVar3 * iVar10 >> 8;
    }
    local_60 = *(int *)(param_1 + 0x50);
    local_5c = *(int *)(param_1 + 0x54);
    if (((sVar12 != 0) || (iVar10 != 0x100)) || (iVar13 != 0x100)) {
      FUN_0004f292(&local_60,(int)-sVar12,0x10000 / iVar10,0x10000 / iVar13,&local_58,0);
    }
    iVar13 = local_60;
    if (local_60 < 1) {
      iVar13 = -local_60;
    }
    iVar5 = local_5c;
    if (local_5c < 1) {
      iVar5 = -local_5c;
    }
    if (iVar5 < iVar13) {
      uVar17 = 1;
    }
    else {
      local_4c = 1;
    }
    iVar13 = FUN_0004cd84(iVar15,0x10);
    if (iVar13 != 0) {
      local_38 = local_4c;
      local_3c = local_4c;
      uVar6 = FUN_0004bd40(iVar15);
      uVar14 = uVar17;
      if ((uVar6 & 1) == 0) {
        uVar14 = 0;
      }
      local_64 = uVar17;
      if (-1 < (int)(uVar6 << 0x1e)) {
        local_64 = 0;
      }
      if (-1 < (int)(uVar6 << 0x1d)) {
        local_38 = 0;
      }
      if (-1 < (int)(uVar6 << 0x1c)) {
        local_3c = 0;
      }
      uVar6 = 0;
      local_68 = 0;
      local_6c = 0;
      local_34 = FUN_0004bef4(iVar15);
      if (local_34 == 0) {
LAB_000480b4:
        local_68 = FUN_0004bd90(iVar15);
        local_6c = FUN_0004be44(iVar15);
      }
      else {
        uVar7 = FUN_0004ba5c(iVar15);
        for (uVar11 = 0; uVar11 < uVar7; uVar11 = uVar11 + 1) {
          uVar8 = FUN_0004b9de(iVar15,uVar11);
          iVar13 = FUN_0004cd84(uVar8,0x1000);
          if ((iVar13 != 0) && (uVar6 = uVar6 + 1, uVar6 == 2)) {
            local_68 = 1;
            local_6c = 1;
            break;
          }
        }
        if ((local_34 == 0) || (uVar6 < 2)) goto LAB_000480b4;
      }
      uVar6 = 0;
      local_30 = 0;
      local_34 = 0;
      local_2c = FUN_0004bf04(iVar15);
      if (local_2c == 0) {
LAB_0004810e:
        local_30 = FUN_0004bf14(iVar15);
        local_34 = FUN_0004bca4(iVar15);
      }
      else {
        uVar7 = FUN_0004ba5c(iVar15);
        for (uVar11 = 0; uVar11 < uVar7; uVar11 = uVar11 + 1) {
          uVar8 = FUN_0004b9de(iVar15,uVar11);
          iVar13 = FUN_0004cd84(uVar8,0x1000);
          if ((iVar13 != 0) && (uVar6 = uVar6 + 1, uVar6 == 2)) {
            local_30 = 1;
            local_34 = 1;
            break;
          }
        }
        if ((local_2c == 0) || (uVar6 < 2)) goto LAB_0004810e;
      }
      if (((0 < local_30) || (0 < local_34)) &&
         (((local_38 != 0 && ((int)uVar2 <= local_5c)) ||
          ((local_3c != 0 && (local_5c <= (int)-uVar2)))))) {
        local_44 = 0xc;
        iVar16 = iVar15;
      }
      if (((0 < local_68) || (0 < local_6c)) &&
         (((uVar14 != 0 && ((int)uVar2 <= local_60)) ||
          ((local_64 != 0 && (local_60 <= (int)-uVar2)))))) {
        local_44 = 3;
        iVar16 = iVar15;
      }
      if (local_30 < 1) {
        local_38 = 0;
      }
      if (local_34 < 1) {
        local_3c = 0;
      }
      if (local_68 < 1) {
        uVar14 = 0;
      }
      if (local_6c < 1) {
        local_64 = 0;
      }
      if ((((uVar14 != 0) && ((int)uVar2 <= local_60)) ||
          ((local_64 != 0 && (local_60 <= (int)-uVar2)))) ||
         (((local_38 != 0 && ((int)uVar2 <= local_5c)) ||
          ((local_3c != 0 && (local_5c <= (int)-uVar2)))))) {
        if (uVar17 == 0) {
          bVar9 = 0xc;
        }
        else {
          bVar9 = 3;
        }
        *(byte *)(param_1 + 0x98) = *(byte *)(param_1 + 0x98) & 0xf0 | bVar9;
        goto LAB_00048230;
      }
    }
    uVar14 = FUN_0004cd84(iVar15,0x100);
    if (((uVar17 & ~uVar14) != 0) ||
       (uVar14 = FUN_0004cd84(iVar15,0x200), (local_4c & ~uVar14) != 0)) goto LAB_00048230;
    iVar15 = FUN_0004bc8c(iVar15);
  } while( true );
}

