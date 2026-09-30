/* Address: ram:0005f942; name: FUN_ram_0005f942; body bytes: 1168 */

/* WARNING: Removing unreachable block (ram,0x0005fcc2) */

undefined4 FUN_ram_0005f942(int param_1)

{
  char cVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  byte bVar6;
  byte bVar7;
  ushort uVar8;
  int iVar9;
  byte *pbVar10;
  byte *pbVar11;
  
  gp = 0x20004000;
  iVar4 = FUN_ram_20001120(*(undefined4 *)(param_1 + 0x78),0,param_1 + 0x15,0);
  if (iVar4 != 0) {
    gp = 0x20004000;
    return 1;
  }
  pbVar11 = *(byte **)(param_1 + 0x78);
  bVar6 = *pbVar11 & 0xf;
  *(byte *)(param_1 + 0xd) = bVar6;
  bVar7 = pbVar11[1];
  *(undefined1 *)(param_1 + 0x23) = 0x7f;
  *(undefined1 *)(param_1 + 0x54) = 0;
  bVar7 = bVar7 & 0x3f;
  *(byte *)(param_1 + 0xe) = bVar7;
  *(undefined1 *)(param_1 + 0x5c) = 0;
  if (bVar6 != 7) {
    if ((2 < bVar6) && (bVar6 != 6)) {
      gp = 0x20004000;
      return 0x80;
    }
    if (0x1f < (byte)(bVar7 - 6)) {
      gp = 0x20004000;
      return 0x80;
    }
    *(undefined1 *)(param_1 + 0x54) = 1;
    *(byte *)(param_1 + 0x55) = (byte)((int)(uint)*pbVar11 >> 6) & 1;
    tmos_memcpy(param_1 + 0x56,pbVar11 + 2,6);
    *(undefined1 *)(param_1 + 0x5c) = 0;
    if (*(char *)(param_1 + 0xd) == '\x01') {
      *(undefined1 *)(param_1 + 0x5c) = 1;
      *(byte *)(param_1 + 0x5d) = **(byte **)(param_1 + 0x78) >> 7;
      tmos_memcpy(param_1 + 0x5e,*(byte **)(param_1 + 0x78) + 8,6);
    }
    iVar4 = FUN_ram_0005dbe8(param_1);
    if ((iVar4 == 1) && (iVar4 = FUN_ram_0005dd3a(param_1), iVar4 == 1)) {
      if (((*(char *)(param_1 + 0xd) == '\0') || (*(char *)(param_1 + 0xd) == '\x06')) &&
         (((*(byte *)(param_1 + 0xf) & 1) != 0 && (*(char *)(param_1 + 0x54) != '\0')))) {
        if (*(char *)(param_1 + 0x11) == '\0') {
          FUN_ram_0005e0de(param_1);
          gp = 0x20004000;
          return 0;
        }
        *(char *)(param_1 + 0x11) = *(char *)(param_1 + 0x11) + -1;
      }
      FUN_ram_00062262();
      if (*(char *)(param_1 + 0xd) != '\x04') {
        FUN_ram_0005dd6c(param_1);
        gp = 0x20004000;
        return 6;
      }
      gp = 0x20004000;
      return 6;
    }
    gp = 0x20004000;
    return 8;
  }
  if (*(int *)(param_1 + 0x1c) << 0x11 < 0) {
    gp = 0x20004000;
    return 7;
  }
  bVar6 = pbVar11[2] & 0x3f;
  if (bVar7 != (byte)(bVar6 + 1)) {
    gp = 0x20004000;
    return 3;
  }
  bVar7 = pbVar11[2] >> 6;
  *(byte *)(param_1 + 0x28) = bVar7;
  pbVar10 = pbVar11 + 4;
  if ((pbVar11[3] & 1) == 0) {
    cVar1 = bVar6 - 1;
  }
  else {
    if ((bVar7 != 0) || (((pbVar11[3] & 0x10) != 0 && (*(char *)(param_1 + 0x21) == '\x02')))) {
      gp = 0x20004000;
      return 0x11;
    }
    *(undefined1 *)(param_1 + 0x54) = 1;
    *(byte *)(param_1 + 0x55) = (byte)((int)(uint)*pbVar11 >> 6) & 1;
    tmos_memcpy(param_1 + 0x56,pbVar10,6);
    pbVar10 = pbVar11 + 10;
    cVar1 = bVar6 - 7;
  }
  if ((pbVar11[3] & 2) != 0) {
    if (bVar7 != 0) {
      gp = 0x20004000;
      return 3;
    }
    if (((pbVar11[3] & 0x10) != 0) && (*(char *)(param_1 + 0x21) == '\x02')) {
      gp = 0x20004000;
      return 3;
    }
    *(undefined1 *)(param_1 + 0x5c) = 1;
    cVar1 = cVar1 + -6;
    *(byte *)(param_1 + 0x5d) = **(byte **)(param_1 + 0x78) >> 7;
    tmos_memcpy(param_1 + 0x5e,pbVar10,6);
    pbVar10 = pbVar10 + 6;
    *(byte *)(param_1 + 0x28) = *(byte *)(param_1 + 0x28) | 4;
  }
  bVar6 = pbVar11[3];
  if ((bVar6 & 4) != 0) {
    gp = 0x20004000;
    return 0x13;
  }
  if ((bVar6 & 8) == 0) {
    *(undefined1 *)(param_1 + 0x29) = 0xff;
  }
  else {
    cVar1 = cVar1 + -2;
    *(ushort *)(param_1 + 0x2a) = (pbVar10[1] & 0xf) << 8 | (ushort)*pbVar10;
    *(byte *)(param_1 + 0x29) = pbVar10[1] >> 4;
    pbVar10 = pbVar10 + 2;
  }
  *(undefined1 *)(param_1 + 0x22) = 0xff;
  if ((bVar6 & 0x10) == 0) {
    *(undefined1 *)(param_1 + 0x2d) = 0;
  }
  else {
    if ((bVar6 & 8) == 0) {
      gp = 0x20004000;
      return 0x15;
    }
    FUN_ram_00062262();
    *(byte *)(param_1 + 0x24) = *pbVar10 & 0x3f;
    uVar8 = (pbVar10[2] & 0x1f) << 8 | (ushort)pbVar10[1];
    *(ushort *)(param_1 + 0x26) = uVar8;
    if ((char)*pbVar10 < '\0') {
      *(ushort *)(param_1 + 0x26) = uVar8 | 0x8000;
    }
    bVar6 = pbVar10[2];
    *(byte *)(param_1 + 0x25) = bVar6 >> 5;
    if (2 < bVar6 >> 5) {
      gp = 0x20004000;
      return 0x15;
    }
    cVar1 = cVar1 + -3;
    pbVar10 = pbVar10 + 3;
  }
  bVar6 = pbVar11[3];
  if ((bVar6 & 0x20) != 0) {
    gp = 0x20004000;
    return 0x16;
  }
  if ((bVar6 & 0x40) != 0) {
    if (((bVar6 & 0x10) != 0) && (*(char *)(param_1 + 0x21) == '\x02')) {
      gp = 0x20004000;
      return 0x17;
    }
    cVar1 = cVar1 + -1;
    *(byte *)(param_1 + 0x23) = *pbVar10;
  }
  if (cVar1 != '\0') {
    gp = 0x20004000;
    return 0x18;
  }
  if (bVar7 == 0) {
    iVar4 = FUN_ram_0005dbe8(param_1);
    if (iVar4 == 0) {
      gp = 0x20004000;
      return 8;
    }
    iVar4 = FUN_ram_0005dd3a(param_1);
    if (iVar4 == 0) {
      gp = 0x20004000;
      return 8;
    }
  }
  if ((pbVar11[3] & 0x10) == 0) {
    FUN_ram_00062262();
    if (bVar7 == 0) {
      *(undefined1 *)(param_1 + 0x2e) = 0;
      FUN_ram_0005dd6c(param_1);
    }
    gp = 0x20004000;
    return 0x15;
  }
  uVar2 = 0;
  if (*(char *)(param_1 + 0x21) == '\x02') {
    uVar2 = 2;
  }
  uVar5 = (uint)*(ushort *)(param_1 + 0x26);
  *(undefined1 *)(param_1 + 0x2c) = uVar2;
  *(char *)(param_1 + 0x2d) = *(char *)(param_1 + 0x25) + '\x01';
  if ((short)*(ushort *)(param_1 + 0x26) < 0) {
    uVar5 = uVar5 & 0x1fff;
    iVar4 = 300;
  }
  else {
    iVar4 = 0x1e;
  }
  if (*(char *)(param_1 + 0x21) == '\x01') {
    iVar9 = *(byte *)(param_1 + 0xe) + 8;
  }
  else {
    iVar9 = (uint)*(byte *)(param_1 + 0xe) * 8;
    if (DAT_ram_20001e9f != '\0') {
      iVar9 = (iVar9 + 0xd7) * 2;
      goto LAB_ram_0005fbdc;
    }
    iVar9 = iVar9 + 0x4a;
  }
  iVar9 = iVar9 << 3;
LAB_ram_0005fbdc:
  uVar5 = uVar5 * iVar4 - iVar9;
  if (uVar5 - 300 < 0x4afda9) {
    if (uVar5 < 0x501) {
      *(undefined4 *)(DAT_ram_20001eb0 + 0xc) = 0xd00f;
      iVar4 = DAT_ram_20001eb0;
      fence.i();
      *(undefined4 *)(DAT_ram_20001eb0 + 8) = 0x2000;
      DAT_ram_20001e98 = 0x80;
      *(uint *)(iVar4 + 100) = (uVar5 - 299) * 2;
      *(undefined4 *)(iVar4 + 0xc) = 0xf00f;
      do {
      } while (*(int *)(iVar4 + 100) != 0);
      *(undefined1 *)(param_1 + 0x22) = *(undefined1 *)(param_1 + 0x21);
      *(undefined1 *)(param_1 + 0x21) = 8;
      FUN_ram_0005f7e6(param_1);
      *(undefined4 *)(DAT_ram_20001eb0 + 0xc) = 0xd00f;
      iVar4 = DAT_ram_20001eb0;
      fence.i();
      uVar3 = 0x20;
      *(undefined4 *)(DAT_ram_20001eb0 + 8) = 0x2000;
      DAT_ram_20001e98 = 0x80;
      *(undefined4 *)(iVar4 + 100) = 0x5ba;
      *(undefined4 *)(iVar4 + 0xc) = 0xf00f;
      FUN_ram_200010ec();
      if ((DAT_ram_20001e94 & 1) != 0) {
        DAT_ram_20001e94 = 0;
        uVar3 = FUN_ram_0005ef72(param_1);
        return uVar3;
      }
    }
    else {
      uVar3 = 0x21;
      if (*(char *)(param_1 + 0x30) == -1) {
        uVar3 = 0x7f;
        FUN_ram_00042362(FUN_ram_0005f8d4,param_1,(uVar5 - 0x271) / 0x271,param_1 + 0x30);
      }
    }
  }
  else {
    uVar3 = 0x21;
  }
  return uVar3;
}

