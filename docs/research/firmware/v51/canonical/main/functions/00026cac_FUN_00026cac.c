/* Address: 00026cac; name: FUN_00026cac; body bytes: 1046 */

void FUN_00026cac(undefined4 param_1,undefined1 *param_2,int param_3,int param_4,int param_5,
                 int param_6,undefined4 param_7,int param_8,int *param_9)

{
  ushort uVar1;
  code *pcVar2;
  code *pcVar3;
  code *pcVar4;
  code *pcVar5;
  code *pcVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  undefined4 uVar11;
  uint uVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  bool bVar19;
  int local_54;
  int local_50;
  code *local_4c;
  code *local_48;
  undefined4 local_44;
  int local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined1 *puStack_30;
  int local_2c;
  int iStack_28;
  
  if ((param_2[3] & 1) == 0) {
    pcVar2 = (code *)0x3ddfb;
    local_4c = (code *)0x3db0b;
    local_48 = (code *)0x3db29;
    pcVar3 = (code *)0x4c74b;
    pcVar4 = (code *)0x4c715;
    pcVar5 = (code *)0x4c727;
    pcVar6 = (code *)0x4c739;
  }
  else {
    pcVar2 = (code *)0x3de05;
    local_4c = (code *)0x3db29;
    local_48 = (code *)0x3db0b;
    pcVar3 = (code *)0x4c727;
    pcVar4 = (code *)0x4c739;
    pcVar5 = (code *)0x4c74b;
    pcVar6 = (code *)0x4c715;
  }
  do {
    if (param_9[5] == 0) break;
    bVar19 = false;
    iVar8 = param_9[1] - param_9[2];
    iVar7 = 0;
    for (uVar9 = 0; uVar9 < (uint)param_9[5]; uVar9 = uVar9 + 1) {
      iVar10 = param_9[4];
      if ((*(byte *)(iVar10 + uVar9 * 0x18 + 0x14) & 1) == 0) {
        iVar7 = iVar7 + *(int *)(iVar10 + uVar9 * 0x18 + 0x10);
      }
      else {
        iVar8 = iVar8 - *(int *)(iVar10 + uVar9 * 0x18 + 0xc);
      }
    }
    for (uVar9 = 0; uVar9 < (uint)param_9[5]; uVar9 = uVar9 + 1) {
      iVar10 = param_9[4];
      iVar13 = uVar9 * 0x18 + 0x14;
      if ((*(byte *)(iVar10 + iVar13) & 1) == 0) {
        if (iVar7 == 0) {
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        local_40 = uVar9 * 0x18 + 0x10;
        iVar16 = *(int *)(iVar10 + local_40) * (iVar8 / iVar7);
        iVar17 = *(int *)(iVar10 + uVar9 * 0x18 + 8);
        iVar15 = *(int *)(iVar10 + uVar9 * 0x18 + 4);
        iVar18 = iVar17;
        if (iVar16 < iVar17) {
          iVar18 = iVar16;
        }
        if ((iVar15 <= iVar18) && (iVar15 = iVar17, iVar16 < iVar17)) {
          iVar15 = iVar16;
        }
        if (iVar15 != iVar16) {
          *(undefined4 *)(iVar10 + iVar13) = 1;
          bVar19 = true;
        }
        *(int *)(param_9[4] + uVar9 * 0x18 + 0xc) = iVar15;
        iVar7 = iVar7 - *(int *)(param_9[4] + local_40);
        iVar8 = iVar8 - iVar15;
      }
    }
  } while (bVar19);
  local_34 = param_1;
  puStack_30 = param_2;
  local_2c = param_3;
  iStack_28 = param_4;
  iVar7 = FUN_0004c5ee(param_1,0);
  bVar19 = iVar7 == 1;
  local_54 = 0;
  local_50 = 0;
  FUN_000586ec(*param_2,param_7,param_9[1],param_9[3],&local_54,&local_50);
  if ((param_2[3] & bVar19) != 0) {
    iVar7 = FUN_0004bb1a(local_34);
    local_54 = iVar7 + local_54;
  }
  iVar7 = FUN_0004b9de(local_34,local_2c);
  do {
    if ((iVar7 == 0) || (local_2c == iStack_28)) {
      return;
    }
    iVar8 = FUN_0004cd92(iVar7,0x60001);
    if (iVar8 == 0) {
      iVar8 = FUN_0004c6c0(iVar7,0);
      if (iVar8 == 0) {
        *(ushort *)(iVar7 + 0x2a) = *(ushort *)(iVar7 + 0x2a) & 0xf3ff;
      }
      else {
        iVar8 = 0;
        for (uVar9 = 0; uVar9 < (uint)param_9[5]; uVar9 = uVar9 + 1) {
          if (*(int *)(param_9[4] + uVar9 * 0x18) == iVar7) {
            iVar8 = *(int *)(param_9[4] + uVar9 * 0x18 + 0xc);
            break;
          }
        }
        if ((param_2[3] & 1) == 0) {
          uVar1 = *(ushort *)(iVar7 + 0x2a) & 0xf7ff | 0x400;
        }
        else {
          uVar1 = *(ushort *)(iVar7 + 0x2a) & 0xfbff | 0x800;
        }
        *(ushort *)(iVar7 + 0x2a) = uVar1;
        iVar10 = (*local_4c)();
        if (iVar10 != iVar8) {
          FUN_0004d3d8(iVar7);
          local_44 = *(undefined4 *)(iVar7 + 0x14);
          local_40 = *(int *)(iVar7 + 0x18);
          local_3c = *(undefined4 *)(iVar7 + 0x1c);
          local_38 = *(undefined4 *)(iVar7 + 0x20);
          (*pcVar2)(iVar7 + 0x14,iVar8);
          FUN_0004e5a6(iVar7,0x2e,&local_44);
          uVar11 = FUN_0004bc8c(iVar7);
          FUN_0004e5a6(uVar11,0x27,iVar7);
          FUN_0004d3d8(iVar7);
        }
      }
      if (param_2[1] == '\x01') {
        iVar8 = (*local_48)(iVar7 + 0x14);
        iVar13 = *param_9;
        iVar10 = (*pcVar6)(iVar7,0);
        iVar10 = (iVar13 - iVar8) - iVar10;
      }
      else if (param_2[1] == '\x02') {
        iVar8 = (*local_48)(iVar7 + 0x14);
        iVar15 = *param_9;
        iVar10 = (*pcVar5)(iVar7,0);
        iVar13 = (*pcVar6)(iVar7,0);
        iVar10 = (int)((iVar15 + 1U & 0xfffffffe) - iVar8) / 2 + (iVar10 - iVar13) / 2;
      }
      else {
        iVar10 = (*pcVar5)(iVar7,0);
      }
      if ((param_2[3] & bVar19) != 0) {
        iVar8 = (*local_4c)(iVar7 + 0x14);
        local_54 = local_54 - iVar8;
      }
      uVar9 = FUN_0004c924(iVar7,0,0x6a);
      uVar12 = FUN_0004c924(iVar7,0,0x6b);
      iVar8 = FUN_0004ccf8(iVar7);
      iVar13 = FUN_0004bbec(iVar7);
      if (((uVar9 & 0x7fffffff) >> 0x1d == 1) &&
         (uVar14 = uVar9 & 0x9fffffff, (int)uVar14 < 0x1fffffff)) {
        if (0xfffffff < (int)uVar14) {
          uVar14 = 0xfffffff - uVar14;
        }
        uVar9 = (int)(iVar8 * uVar14) / 100;
      }
      if (((uVar12 & 0x7fffffff) >> 0x1d == 1) &&
         (uVar14 = uVar12 & 0x9fffffff, (int)uVar14 < 0x1fffffff)) {
        if (0xfffffff < (int)uVar14) {
          uVar14 = 0xfffffff - uVar14;
        }
        uVar12 = (int)(iVar13 * uVar14) / 100;
      }
      iVar15 = *(int *)(iVar7 + 0x14);
      iVar13 = (param_6 - *(int *)(iVar7 + 0x18)) + uVar12;
      iVar8 = iVar10;
      if ((param_2[3] & 1) != 0) {
        iVar8 = (*pcVar3)(iVar7,0);
        iVar8 = iVar8 + local_54;
      }
      iVar8 = iVar8 + uVar9 + (param_5 - iVar15);
      if ((param_2[3] & 1) == 0) {
        iVar10 = (*pcVar3)(iVar7,0);
        iVar10 = iVar10 + local_54;
      }
      iVar10 = iVar10 + iVar13;
      if (iVar8 != 0 || iVar10 != 0) {
        FUN_0004d3d8(iVar7);
        *(int *)(iVar7 + 0x14) = *(int *)(iVar7 + 0x14) + iVar8;
        *(int *)(iVar7 + 0x1c) = *(int *)(iVar7 + 0x1c) + iVar8;
        *(int *)(iVar7 + 0x18) = *(int *)(iVar7 + 0x18) + iVar10;
        *(int *)(iVar7 + 0x20) = *(int *)(iVar7 + 0x20) + iVar10;
        FUN_0004d3d8(iVar7);
        FUN_0004d528(iVar7,iVar8,iVar10,0);
      }
      if ((param_2[3] & bVar19) == 0) {
        iVar8 = (*local_4c)(iVar7 + 0x14);
        iVar10 = iVar8 + param_8 + local_50;
        iVar8 = (*pcVar3)(iVar7,0);
        iVar7 = (*pcVar4)(iVar7,0);
        local_54 = iVar7 + iVar10 + iVar8 + local_54;
      }
      else {
        local_54 = local_54 - (param_8 + local_50);
      }
    }
    iVar7 = FUN_000377d4(local_34,((byte)param_2[3] & 7) >> 2,&local_2c);
  } while( true );
}

