/* Address: ram:00069f0c; name: GAPBondMgr_SetParameter; body bytes: 1504 */

undefined4 GAPBondMgr_SetParameter(uint param_1,int param_2,uint *param_3)

{
  byte bVar1;
  bool bVar2;
  byte bVar3;
  byte bVar4;
  char cVar5;
  undefined *puVar6;
  uint uVar7;
  int iVar8;
  undefined4 uVar9;
  uint uVar10;
  uint uVar11;
  byte bVar12;
  byte *pbVar13;
  undefined1 auStack_44 [8];
  undefined1 auStack_3c [27];
  char cStack_21;
  
  gp = 0x20004000;
  bVar3 = DAT_ram_20001a9b;
  bVar4 = DAT_ram_20001a8f;
  bVar12 = DAT_ram_20001a93;
  switch(param_1 - 0x400 & 0xffff) {
  case 0:
    if (param_2 != 1) {
      gp = 0x20004000;
      return 0x18;
    }
    bVar12 = (byte)*param_3;
    bVar4 = DAT_ram_200019c7;
    bVar3 = bVar12;
    goto joined_r0x0006a04a;
  case 1:
    if (param_2 != 1) {
      gp = 0x20004000;
      return 0x18;
    }
    bVar12 = (byte)*param_3;
    if (1 < bVar12) {
      gp = 0x20004000;
      return 0x18;
    }
    pbVar13 = &DAT_ram_20001a98;
    goto LAB_ram_00069f8c;
  case 2:
    if (param_2 != 1) {
      gp = 0x20004000;
      return 0x18;
    }
    bVar12 = (byte)*param_3;
    bVar4 = DAT_ram_20001a91;
    bVar3 = bVar12;
    goto joined_r0x0006a080;
  case 3:
    if (param_2 != 1) {
      gp = 0x20004000;
      return 0x18;
    }
    bVar3 = (byte)*param_3;
    bVar1 = (byte)*param_3;
    goto joined_r0x0006a2d6;
  case 4:
    if (param_2 != 0x10) {
      gp = 0x20004000;
      return 0x18;
    }
    uVar9 = 0x10;
    puVar6 = &DAT_ram_20001b24;
    goto LAB_ram_00069fe0;
  case 5:
    if (param_2 != 1) {
      gp = 0x20004000;
      return 0x18;
    }
    bVar12 = (byte)*param_3;
    if (1 < bVar12) {
      gp = 0x20004000;
      return 0x18;
    }
    pbVar13 = &DAT_ram_20001a98;
    goto LAB_ram_0006a000;
  case 6:
    if (param_2 == 1) {
      gp = 0x20004000;
      DAT_ram_20001a9a = (byte)*param_3;
      return 0;
    }
    break;
  case 7:
    if (param_2 != 4) {
      gp = 0x20004000;
      return 0x18;
    }
    uVar10 = *param_3;
    uVar7 = DAT_ram_20001a94;
    uVar11 = uVar10;
    goto joined_r0x0006a0fa;
  case 8:
    if (param_2 != 1) {
      gp = 0x20004000;
      return 0x18;
    }
    bVar4 = (byte)*param_3;
    bVar12 = DAT_ram_200019ca;
    bVar3 = (byte)*param_3;
joined_r0x0006a04a:
    if (bVar3 < 3) {
      gp = 0x20004000;
      DAT_ram_200019c7 = bVar4;
      DAT_ram_200019ca = bVar12;
      return 0;
    }
    gp = 0x20004000;
    return 0x18;
  case 9:
    if (param_2 != 1) {
      gp = 0x20004000;
      return 0x18;
    }
    bVar12 = (byte)*param_3;
    if (1 < bVar12) {
      gp = 0x20004000;
      return 0x18;
    }
    pbVar13 = &DAT_ram_20001a90;
LAB_ram_00069f8c:
    if (bVar12 == 0) {
      bVar12 = *pbVar13 & 0xfb;
    }
    else {
      bVar12 = *pbVar13 | 4;
    }
LAB_ram_00069f96:
    *pbVar13 = bVar12;
    gp = 0x20004000;
    return 0;
  case 10:
    if (param_2 != 1) {
      gp = 0x20004000;
      return 0x18;
    }
    bVar4 = (byte)*param_3;
    bVar12 = DAT_ram_20001a99;
    bVar3 = (byte)*param_3;
joined_r0x0006a080:
    if (bVar3 < 5) {
      gp = 0x20004000;
      DAT_ram_20001a91 = bVar4;
      DAT_ram_20001a99 = bVar12;
      return 0;
    }
    gp = 0x20004000;
    return 0x18;
  case 0xb:
    if (param_2 != 1) {
      gp = 0x20004000;
      return 0x18;
    }
    bVar12 = (byte)*param_3;
    bVar1 = bVar12;
    goto joined_r0x0006a2d6;
  case 0xc:
    if (param_2 != 0x10) {
      gp = 0x20004000;
      return 0x18;
    }
    uVar9 = 0x10;
    puVar6 = &DAT_ram_20001b14;
    goto LAB_ram_00069fe0;
  case 0xd:
    if (param_2 != 1) {
      gp = 0x20004000;
      return 0x18;
    }
    bVar12 = (byte)*param_3;
    if (1 < bVar12) {
      gp = 0x20004000;
      return 0x18;
    }
    pbVar13 = &DAT_ram_20001a90;
LAB_ram_0006a000:
    if (bVar12 == 0) {
      bVar12 = *pbVar13 & 0xfe;
    }
    else {
      bVar12 = *pbVar13 | 1;
    }
    goto LAB_ram_00069f96;
  case 0xe:
    if (param_2 == 1) {
      gp = 0x20004000;
      DAT_ram_20001a92 = (byte)*param_3;
      return 0;
    }
    break;
  case 0xf:
    if (param_2 != 4) {
      gp = 0x20004000;
      return 0x18;
    }
    uVar7 = *param_3;
    uVar10 = DAT_ram_20001a9c;
    uVar11 = *param_3;
joined_r0x0006a0fa:
    if (uVar11 < 1000000) {
      gp = 0x20004000;
      DAT_ram_20001a94 = uVar7;
      DAT_ram_20001a9c = uVar10;
      return 0;
    }
    gp = 0x20004000;
    return 0x18;
  case 0x10:
    if (param_2 != 0) {
      gp = 0x20004000;
      return 0x18;
    }
    iVar8 = thunk_FUN_ram_0004e07e();
    if (iVar8 != 0) {
      gp = 0x20004000;
      DAT_ram_20001a8c = 1;
      return 0;
    }
    FUN_ram_00068c56();
    goto LAB_ram_0006a116;
  case 0x11:
    if (param_2 != 1) {
      gp = 0x20004000;
      return 0x18;
    }
    bVar4 = (byte)*param_3;
    bVar1 = (byte)*param_3;
joined_r0x0006a2d6:
    if (bVar1 < 2) {
      gp = 0x20004000;
      DAT_ram_20001a8f = bVar4;
      DAT_ram_20001a93 = bVar12;
      DAT_ram_20001a9b = bVar3;
      return 0;
    }
    break;
  case 0x12:
    if (param_2 != 1) {
      gp = 0x20004000;
      return 0x18;
    }
    bVar12 = (byte)*param_3;
    bVar3 = DAT_ram_200019c9;
    bVar4 = bVar12;
    goto joined_r0x0006a312;
  case 0x13:
    if (param_2 != 1) {
      gp = 0x20004000;
      return 0x18;
    }
    bVar3 = (byte)*param_3;
    bVar12 = DAT_ram_200019c5;
    bVar4 = (byte)*param_3 - 7;
joined_r0x0006a312:
    if (bVar4 < 10) {
      gp = 0x20004000;
      DAT_ram_200019c5 = bVar12;
      DAT_ram_200019c9 = bVar3;
      return 0;
    }
    gp = 0x20004000;
    return 0x18;
  case 0x14:
    if (param_2 == 1) {
      bVar12 = (byte)*param_3;
      if (DAT_ram_20001a85 != '\0') {
        gp = 0x20004000;
        DAT_ram_20001a85 = bVar12;
        return 0;
      }
      if (bVar12 == 1) {
        DAT_ram_20001a85 = bVar12;
        FUN_ram_00068dbc();
        gp = 0x20004000;
        return 0;
      }
      gp = 0x20004000;
      DAT_ram_20001a85 = bVar12;
      return 0;
    }
    break;
  default:
    if (0x3f < param_1) {
      gp = 0x20004000;
      return 2;
    }
    if (param_2 == 2) {
      uVar9 = GAP_SetParamValue(param_1,(short)*param_3);
      gp = 0x20004000;
      return uVar9;
    }
    gp = 0x20004000;
    return 2;
  case 0x16:
    if ((param_2 == 1) && ((byte)*param_3 < 4)) {
      gp = 0x20004000;
      DAT_ram_200019c6 = (byte)*param_3;
      return 0;
    }
    break;
  case 0x17:
    if (param_2 != 7) {
      gp = 0x20004000;
      return 0x18;
    }
    tmos_memcpy(auStack_44,(byte *)((int)param_3 + 1),6);
    uVar7 = FUN_ram_00069942((byte)*param_3,auStack_44,auStack_3c);
    if (DAT_ram_20001a8d <= uVar7) {
      gp = 0x20004000;
      return 2;
    }
    iVar8 = FUN_ram_0004dfa2(auStack_3c);
    if (iVar8 != 0) {
      *(undefined1 *)(uVar7 * 0x10 + DAT_ram_20001a88 + 0xe) = 1;
      gp = 0x20004000;
      return 0x16;
    }
    FUN_ram_00068b10(uVar7);
LAB_ram_0006a116:
    FUN_ram_000430e4();
    FUN_ram_00068dbc();
    gp = 0x20004000;
    return 0;
  case 0x18:
    if (param_2 == 1) {
      gp = 0x20004000;
      DAT_ram_200019c4 = (byte)*param_3;
      return 0;
    }
    break;
  case 0x19:
    FUN_ram_00042e10(1);
    gp = 0x20004000;
    return 0;
  case 0x1a:
  case 0x1b:
    if (param_2 != 7) {
      if (param_2 != 1) {
        gp = 0x20004000;
        return 0x18;
      }
      if (param_1 == 0x41a) {
        gp = 0x20004000;
        DAT_ram_20001f10 = DAT_ram_20001f10 | 2;
        return 0;
      }
      gp = 0x20004000;
      DAT_ram_20001f10 = DAT_ram_20001f10 & 0xfd;
      return 0;
    }
    tmos_memcpy(auStack_44,(byte *)((int)param_3 + 1),6);
    uVar7 = FUN_ram_00069942((byte)*param_3,auStack_44,0);
    if (uVar7 < DAT_ram_20001a8d) {
      uVar7 = uVar7 * 6 + 0x21 & 0xff;
      iVar8 = tmos_snv_read(uVar7,0x1c,auStack_3c);
      if (iVar8 == 0) {
        cStack_21 = '\x01';
        if (param_1 != 0x41a) {
          cStack_21 = -1;
        }
        FUN_ram_00042e5e(uVar7,0x1c,auStack_3c);
        FUN_ram_00042e10(DAT_ram_200019c4);
        uVar9 = 0;
      }
      else {
        uVar9 = 2;
      }
      FUN_ram_00069e34();
      gp = 0x20004000;
      return uVar9;
    }
    if (DAT_ram_20001f0f == '\0') {
      gp = 0x20004000;
      return 2;
    }
    if (param_1 != 0x41a) {
      gp = 0x20004000;
      DAT_ram_20001f10 = DAT_ram_20001f10 & 0xfe;
      return 0;
    }
    DAT_ram_20001f10 = DAT_ram_20001f10 | 1;
    uVar9 = 7;
    puVar6 = &DAT_ram_20001f08;
LAB_ram_00069fe0:
    tmos_memcpy(puVar6,param_3,uVar9);
    gp = 0x20004000;
    return 0;
  case 0x1c:
    DAT_ram_200019cb = 0;
    goto LAB_ram_0006a264;
  case 0x1d:
    DAT_ram_200019cb = 1;
    for (bVar12 = 0; bVar12 < DAT_ram_20001a8d; bVar12 = bVar12 + 1) {
      cVar5 = bVar12 * '\x06' + '!';
      iVar8 = tmos_snv_read(cVar5,0x1c,auStack_3c);
      if ((iVar8 == 0) && (cStack_21 != -1)) {
        cStack_21 = -1;
        FUN_ram_00042e5e(cVar5,0x1c,auStack_3c);
        FUN_ram_00042e10(DAT_ram_200019c4);
      }
    }
LAB_ram_0006a264:
    FUN_ram_00069e34();
    gp = 0x20004000;
    return 0;
  case 0x1e:
    if (param_2 == 1) {
      gp = 0x20004000;
      DAT_ram_200019c8 = (byte)*param_3;
      return 0;
    }
    break;
  case 0x1f:
    if (param_2 == 1) {
      bVar12 = (byte)*param_3;
      bVar2 = DAT_ram_20001a84 == '\0';
      DAT_ram_20001a84 = bVar12;
      if ((bVar2) && (bVar12 == 1)) {
        FUN_ram_00068dbc();
      }
      thunk_FUN_ram_00065758(DAT_ram_20001a84);
      gp = 0x20004000;
      return 0;
    }
    break;
  case 0x20:
    if ((param_2 == 0x24) &&
       (uVar7 = FUN_ram_00069942(*(byte *)((int)param_3 + 1),(byte *)((int)param_3 + 2),0),
       uVar7 < DAT_ram_20001a8d)) {
      uVar7 = uVar7 * 6 & 0xff;
      if ((byte)*param_3 == 8) {
        uVar7 = uVar7 + 0x22;
      }
      else {
        uVar7 = uVar7 + 0x21;
      }
      iVar8 = tmos_snv_read(uVar7 & 0xff,0x1c,auStack_3c);
      if (iVar8 == 0) {
        tmos_memcpy(auStack_3c,param_3 + 2,0x1b);
        FUN_ram_00042e5e(uVar7 & 0xff,0x1c,auStack_3c);
        FUN_ram_00042e10(DAT_ram_200019c4);
      }
    }
    break;
  case 0x21:
    if (DAT_ram_20001bcc < 0x45) {
      gp = 0x20004000;
      return 0x1b;
    }
    if (param_2 != 1) {
      gp = 0x20004000;
      return 0x18;
    }
    if (1 < (byte)*param_3) {
      gp = 0x20004000;
      return 0x18;
    }
    if ((byte)*param_3 == 0) {
LAB_ram_0006a482:
      pbVar13 = &DAT_ram_20001a98;
      bVar12 = DAT_ram_20001a98 & 0xf7;
      goto LAB_ram_0006a490;
    }
    if (DAT_ram_20001f04 == 0) {
      gp = 0x20004000;
      return 0x15;
    }
    pbVar13 = &DAT_ram_20001a98;
    goto LAB_ram_0006a478;
  case 0x22:
    if (DAT_ram_20001bcc < 0x45) {
      gp = 0x20004000;
      return 0x1b;
    }
    if (param_2 != 1) {
      gp = 0x20004000;
      return 0x18;
    }
    if (1 < (byte)*param_3) {
      gp = 0x20004000;
      return 0x18;
    }
    if ((byte)*param_3 == 0) goto LAB_ram_0006a482;
    if (DAT_ram_20001f04 == 0) {
      gp = 0x20004000;
      return 0x15;
    }
    pbVar13 = &DAT_ram_20001a90;
LAB_ram_0006a478:
    bVar12 = *pbVar13 | 8;
LAB_ram_0006a490:
    *pbVar13 = bVar12;
    gp = 0x20004000;
    return 0;
  }
  return 0x18;
}

