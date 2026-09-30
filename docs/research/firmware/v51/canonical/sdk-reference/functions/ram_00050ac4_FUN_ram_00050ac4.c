/* Address: ram:00050ac4; name: FUN_ram_00050ac4; body bytes: 1764 */

int FUN_ram_00050ac4(int param_1,int param_2,byte *param_3)

{
  byte bVar1;
  char cVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  ushort uVar6;
  ushort uVar7;
  ushort uVar8;
  ushort uVar9;
  short *psVar10;
  undefined1 uVar11;
  short sVar12;
  int iVar13;
  undefined4 uVar14;
  int iVar15;
  int iVar16;
  undefined *puVar17;
  byte bVar18;
  ushort uVar19;
  byte *pbVar20;
  short *psVar21;
  undefined1 auStack_30 [24];
  
  gp = 0x20004000;
  psVar10 = *(short **)(param_1 + 0x34);
  if (psVar10 == (short *)0x0) {
    if (param_2 != 1) {
      gp = 0x20004000;
      return 0;
    }
    FUN_ram_00044696(0,*(undefined2 *)(param_1 + 2),*param_3,param_3[1],param_3[2],param_3[3],
                     *(undefined4 *)(param_3 + 4));
    gp = 0x20004000;
    return 0;
  }
  sVar12 = *(short *)(param_1 + 2);
  if (*psVar10 != sVar12) {
    gp = 0x20004000;
    return 8;
  }
  if ((char)psVar10[1] != '\0') {
    gp = 0x20004000;
    return 7;
  }
  iVar15 = 0;
  switch(param_2 - 1U & 0xff) {
  case 0:
    if (*(int *)(psVar10 + 0x14) != 0) {
      gp = 0x20004000;
      return 8;
    }
    iVar13 = FUN_ram_20000040(0x40,0x53);
    *(int *)(psVar10 + 0x14) = iVar13;
    if (iVar13 == 0) {
      gp = 0x20004000;
      return 8;
    }
    if ((4 < *param_3) || (1 < param_3[1])) {
      gp = 0x20004000;
      return 3;
    }
    tmos_memcpy(iVar13,param_3,0x40);
    iVar13 = *(int *)(psVar10 + 0x14);
    iVar16 = *(int *)(psVar10 + 0x36);
    *(undefined1 *)((int)psVar10 + 5) = 0;
    uVar3 = (ushort)*(undefined4 *)(iVar13 + 4) & 1 & (ushort)*(undefined4 *)(iVar16 + 0x14);
    uVar19 = *(ushort *)(iVar16 + 0x14);
    *(ushort *)(iVar16 + 0x14) = uVar19 & 0xfffe | uVar3;
    uVar5 = (ushort)((*(uint *)(iVar16 + 0x14) >> 1 & *(uint *)(iVar13 + 4) >> 1 & 1) << 1);
    *(ushort *)(iVar16 + 0x14) = uVar5 | uVar19 & 0xfffc | uVar3;
    uVar6 = (ushort)((*(uint *)(iVar16 + 0x14) >> 2 & *(uint *)(iVar13 + 4) >> 2 & 1) << 2);
    *(ushort *)(iVar16 + 0x14) = uVar6 | uVar5 | uVar19 & 0xfff8 | uVar3;
    uVar7 = (ushort)((*(uint *)(iVar16 + 0x14) >> 3 & *(uint *)(iVar13 + 4) >> 3 & 1) << 3);
    *(ushort *)(iVar16 + 0x14) = uVar7 | uVar6 | uVar5 | uVar19 & 0xfff0 | uVar3;
    uVar8 = (ushort)((*(uint *)(iVar16 + 0x14) >> 8 & *(uint *)(iVar13 + 4) >> 8 & 1) << 8);
    *(ushort *)(iVar16 + 0x14) = uVar8 | uVar7 | uVar6 | uVar5 | uVar19 & 0xfef0 | uVar3;
    uVar9 = (ushort)((*(uint *)(iVar16 + 0x14) >> 9 & *(uint *)(iVar13 + 4) >> 9 & 1) << 9);
    *(ushort *)(iVar16 + 0x14) = uVar8 | uVar7 | uVar6 | uVar5 | uVar19 & 0xfcf0 | uVar3 | uVar9;
    uVar4 = (ushort)((*(uint *)(iVar16 + 0x14) >> 10 & *(uint *)(iVar13 + 4) >> 10 & 1) << 10);
    *(ushort *)(iVar16 + 0x14) =
         uVar8 | uVar7 | uVar6 | uVar5 | uVar19 & 0xf8f0 | uVar3 | uVar9 | uVar4;
    *(ushort *)(iVar16 + 0x14) =
         uVar8 | uVar7 | uVar6 | uVar5 | uVar19 & 0xf0f0 | uVar3 | uVar9 | uVar4 |
         (ushort)((*(uint *)(iVar16 + 0x14) >> 0xb & *(uint *)(iVar13 + 4) >> 0xb & 1) << 0xb);
    if (((*(byte *)(iVar16 + 0x12) & 8) == 0) || ((*(byte *)(iVar13 + 2) & 8) == 0)) {
      if (*(int *)(psVar10 + 0x40) != 0) {
        FUN_ram_20000104();
        psVar10[0x40] = 0;
        psVar10[0x41] = 0;
      }
      pbVar20 = *(byte **)(psVar10 + 0x36);
      if ((pbVar20[1] == 0) || (param_3[1] == 0)) {
        if (((pbVar20[0x12] & 4) == 0) && ((param_3[2] & 4) == 0)) goto LAB_ram_00050d12;
        bVar18 = *pbVar20;
        bVar1 = *param_3;
        puVar17 = &UNK_ram_0006c040;
LAB_ram_00050d2c:
        bVar18 = puVar17[(uint)bVar1 + (uint)bVar18 * 5];
      }
      else {
        bVar18 = 0x18;
      }
LAB_ram_00050c78:
      *(byte *)((int)psVar10 + 5) = bVar18;
    }
    else {
      if (*(int *)(psVar10 + 0x40) != 0) {
        gp = 0x20004000;
        return 8;
      }
      iVar13 = FUN_ram_20000040(0x100,0x53);
      *(int *)(psVar10 + 0x40) = iVar13;
      if (iVar13 == 0) {
        gp = 0x20004000;
        return 3;
      }
      pbVar20 = *(byte **)(psVar10 + 0x36);
      *(undefined1 *)((int)psVar10 + 5) = 0;
      bVar18 = param_3[1];
      if (pbVar20[1] == 0) {
        if (bVar18 != 0) goto LAB_ram_00050c70;
        if (((pbVar20[0x12] & 4) != 0) || ((param_3[2] & 4) != 0)) {
          bVar18 = *pbVar20;
          bVar1 = *param_3;
          puVar17 = &UNK_ram_0006c05c;
          goto LAB_ram_00050d2c;
        }
LAB_ram_00050d12:
        bVar18 = 1;
        goto LAB_ram_00050c78;
      }
      *(undefined1 *)((int)psVar10 + 5) = 8;
      if (bVar18 != 0) {
LAB_ram_00050c70:
        bVar18 = *(byte *)((int)psVar10 + 5) | 0x10;
        goto LAB_ram_00050c78;
      }
    }
    FUN_ram_00050242(psVar10);
    if (((*(byte *)(*(int *)(psVar10 + 0x36) + 0x12) & 1) != 0) &&
       ((*(byte *)(*(int *)(psVar10 + 0x14) + 2) & 3) != 0)) {
      *(byte *)(psVar10 + 3) = *(byte *)(psVar10 + 3) | 1;
    }
    if (*(int *)(psVar10 + 0x40) != 0) {
      *(byte *)(psVar10 + 3) = *(byte *)(psVar10 + 3) | 8;
    }
    bVar18 = *(byte *)((int)psVar10 + 5);
    if (bVar18 == 1) {
      tmos_memset(psVar10 + 4,0,0x10);
      tmos_memset(psVar10 + 0xc,0,0x10);
      FUN_ram_000440ba(psVar10 + 0x1e,0x10);
      if (*(int *)(psVar10 + 0x40) == 0) {
        uVar11 = 0x10;
      }
      else {
        uVar11 = 0x50;
      }
      break;
    }
    if ((bVar18 & 0x18) != 0) {
      if ((bVar18 & 0x10) == 0) {
        tmos_memset(psVar10 + 4,0,0x10);
      }
      else {
        tmos_memcpy(psVar10 + 4,*(int *)(psVar10 + 0x36) + 2);
      }
      tmos_memset(psVar10 + 0xc,0,0x10);
      *(byte *)(psVar10 + 3) = *(byte *)(psVar10 + 3) | 4;
      FUN_ram_000440ba(psVar10 + 0x1e,0x10);
      if (*(int *)(psVar10 + 0x40) == 0) {
        uVar11 = 0x13;
      }
      else {
        uVar11 = 0x52;
      }
      break;
    }
    uVar14 = 2;
    if ((bVar18 == 2) || (uVar14 = 1, bVar18 == 4)) {
LAB_ram_00050df6:
      FUN_ram_00044e62(*psVar10,uVar14);
    }
    else if (bVar18 == 6) {
      uVar14 = 3;
      goto LAB_ram_00050df6;
    }
    *(byte *)(psVar10 + 3) = *(byte *)(psVar10 + 3) | 4;
    if (*(int *)(psVar10 + 0x40) == 0) {
      uVar11 = 0x11;
    }
    else {
      uVar11 = 0x51;
    }
    break;
  default:
    gp = 0x20004000;
    return 7;
  case 2:
    tmos_memcpy(psVar10 + 0x26,param_3,0x10);
    if (*(char *)((int)psVar10 + 3) == 'V') {
      tmos_set_event(DAT_ram_20001d4f,1);
      uVar11 = 0x55;
    }
    else if (*(char *)((int)psVar10 + 3) == '\x11') {
      uVar11 = 0x12;
    }
    else {
      FUN_ram_0004e8ec(psVar10,psVar10 + 4,psVar10 + 0x1e,psVar10 + 0x16);
      iVar13 = FUN_ram_00050272(psVar10);
      iVar15 = 0;
      if (iVar13 != 0) {
        iVar15 = 8;
      }
      uVar11 = 0x14;
    }
    break;
  case 3:
    psVar21 = psVar10 + 0x2e;
    tmos_memcpy(psVar21,param_3,0x10);
    iVar13 = *(int *)(psVar10 + 0x40);
    if (iVar13 != 0) {
      cVar2 = *(char *)((int)psVar10 + 3);
      if (cVar2 == 'Y') {
        FUN_ram_000502a6(psVar10);
        uVar11 = 0x5e;
      }
      else {
        if (cVar2 == 'Z') {
          if (DAT_ram_20001f04 == 0) {
            gp = 0x20004000;
            return 7;
          }
          if (*(code **)(DAT_ram_20001f04 + 8) != (code *)0x0) {
            (**(code **)(DAT_ram_20001f04 + 8))
                      (iVar13 + 0x40,iVar13 + 0x80,psVar21,
                       (int)(uint)*(byte *)((int)psVar10 + (*(byte *)((int)psVar10 + 7) >> 3) + 8)
                       >> (*(byte *)((int)psVar10 + 7) & 7) & 1U | 0x80,auStack_30);
            iVar13 = tmos_memcmp(psVar10 + 0x26,auStack_30,0x10);
            if (iVar13 == 0) {
              iVar15 = param_2;
            }
            FUN_ram_000502a6(psVar10);
            cVar2 = *(char *)((int)psVar10 + 7);
            uVar11 = 0x5e;
            *(char *)((int)psVar10 + 7) = cVar2 + '\x01';
            if ((byte)(cVar2 + 1U) < 0x14) {
              uVar11 = 0x56;
            }
            *(undefined1 *)((int)psVar10 + 3) = uVar11;
            gp = 0x20004000;
            return iVar15;
          }
          gp = 0x20004000;
          return 7;
        }
        if (cVar2 != '\\') {
          gp = 0x20004000;
          return 0;
        }
        if (DAT_ram_20001f04 == 0) {
          gp = 0x20004000;
          return 7;
        }
        if (*(code **)(DAT_ram_20001f04 + 8) == (code *)0x0) {
          gp = 0x20004000;
          return 7;
        }
        (**(code **)(DAT_ram_20001f04 + 8))(iVar13 + 0x80,iVar13 + 0x80,psVar10 + 4,0,auStack_30);
        FUN_ram_00044ef0(*psVar10,psVar10 + 4,auStack_30);
        uVar11 = 0x5b;
      }
      break;
    }
    FUN_ram_0004e8ec(psVar10,psVar10 + 4,psVar21,auStack_30);
    iVar15 = tmos_memcmp(auStack_30,psVar10 + 0x26,0x10);
    if (iVar15 != 1) {
      gp = 0x20004000;
      return param_2;
    }
    iVar13 = FUN_ram_000502a6(psVar10);
    iVar15 = 0;
    if (iVar13 != 0) {
      gp = 0x20004000;
      return 8;
    }
    goto LAB_ram_00050f96;
  case 4:
    bVar18 = *param_3;
    goto LAB_ram_000510d8;
  case 5:
    if (*(char *)((int)psVar10 + 3) != '\'') {
      gp = 0x20004000;
      return 7;
    }
    if (*(int *)(psVar10 + 0x3a) == 0) {
      uVar14 = FUN_ram_20000040(0x1c,0x53);
      *(undefined4 *)(psVar10 + 0x3a) = uVar14;
    }
    if (*(int *)(psVar10 + 0x3a) == 0) {
      gp = 0x20004000;
      return 7;
    }
    tmos_memcpy(*(int *)(psVar10 + 0x3a),param_3,0x10);
    iVar13 = *(int *)(psVar10 + 0x3a);
    uVar11 = FUN_ram_0004e9a0(psVar10);
    *(undefined1 *)(iVar13 + 0x1a) = uVar11;
    uVar11 = 0x28;
    break;
  case 6:
    if (*(char *)((int)psVar10 + 3) != '(') {
      gp = 0x20004000;
      return 7;
    }
    iVar13 = *(int *)(psVar10 + 0x3a);
    *(undefined2 *)(iVar13 + 0x10) = *(undefined2 *)param_3;
    tmos_memcpy(iVar13 + 0x12,param_3 + 2,8);
    uVar19 = *(ushort *)(*(int *)(psVar10 + 0x36) + 0x14);
    if (((uVar19 & 0x200) != 0) && ((*(ushort *)(*(int *)(psVar10 + 0x14) + 4) & 0x200) != 0)) {
      uVar11 = 0x29;
      break;
    }
    goto LAB_ram_00051082;
  case 7:
    if (*(char *)((int)psVar10 + 3) != ')') {
      gp = 0x20004000;
      return 7;
    }
    if (*(int *)(psVar10 + 0x3c) == 0) {
      uVar14 = FUN_ram_20000040(0x16,0x53);
      *(undefined4 *)(psVar10 + 0x3c) = uVar14;
    }
    if (*(int *)(psVar10 + 0x3c) == 0) {
      gp = 0x20004000;
      return 7;
    }
    tmos_memcpy(*(int *)(psVar10 + 0x3c),param_3,0x10);
    uVar11 = 0x2a;
    break;
  case 8:
    if (*(char *)((int)psVar10 + 3) != '*') {
      gp = 0x20004000;
      return 7;
    }
    tmos_memcpy(*(int *)(psVar10 + 0x3c) + 0x10,param_3 + 1,6);
    uVar19 = *(ushort *)(*(int *)(psVar10 + 0x36) + 0x14);
LAB_ram_00051082:
    if (((uVar19 & 0x400) == 0) || ((*(ushort *)(*(int *)(psVar10 + 0x14) + 4) & 0x400) == 0)) {
LAB_ram_000510d2:
      sVar12 = *(short *)(param_1 + 2);
      bVar18 = 0;
LAB_ram_000510d8:
      FUN_ram_0004e5a2(sVar12,bVar18);
      gp = 0x20004000;
      return 0;
    }
    uVar11 = 0x2b;
    break;
  case 9:
    if (*(char *)((int)psVar10 + 3) != '+') {
      gp = 0x20004000;
      return 7;
    }
    if (*(int *)(psVar10 + 0x3e) == 0) {
      uVar14 = FUN_ram_20000040(0x14,0x53);
      *(undefined4 *)(psVar10 + 0x3e) = uVar14;
    }
    if (*(int *)(psVar10 + 0x3e) == 0) {
      gp = 0x20004000;
      return 8;
    }
    tmos_memcpy(*(int *)(psVar10 + 0x3e),param_3,0x10);
    *(undefined4 *)(*(int *)(psVar10 + 0x3e) + 0x10) = 0xffffffff;
    goto LAB_ram_000510d2;
  case 0xb:
    if (*(byte *)((int)psVar10 + 3) < 0x50) {
      gp = 0x20004000;
      return 8;
    }
    if (*(int *)(psVar10 + 0x40) == 0) {
      gp = 0x20004000;
      return 8;
    }
    tmos_memcpy(*(int *)(psVar10 + 0x40) + 0x40,param_3,0x40);
    iVar15 = FUN_ram_000502da(psVar10);
    FUN_ram_0004e8b0(psVar10);
    cVar2 = *(char *)((int)psVar10 + 3);
    if (cVar2 == 'P') {
      tmos_start_task(DAT_ram_20001d4f,1,(uint)*(ushort *)(param_1 + 0xe) << 1);
      uVar11 = 0x53;
    }
    else if (cVar2 == 'Q') {
      uVar11 = 0x56;
    }
    else {
      if (cVar2 != 'R') {
        gp = 0x20004000;
        return iVar15;
      }
      uVar11 = 0x5c;
    }
    break;
  case 0xc:
    if (*(char *)((int)psVar10 + 3) != '^') {
      gp = 0x20004000;
      return 8;
    }
    tmos_memcpy(*(undefined4 *)(psVar10 + 0x40),param_3,0x10);
    iVar15 = FUN_ram_0005033c(psVar10);
LAB_ram_00050f96:
    uVar11 = 0x21;
  }
  *(undefined1 *)((int)psVar10 + 3) = uVar11;
  return iVar15;
}

