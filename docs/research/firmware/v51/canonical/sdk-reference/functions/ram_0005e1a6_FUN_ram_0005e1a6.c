/* Address: ram:0005e1a6; name: FUN_ram_0005e1a6; body bytes: 590 */

undefined4 FUN_ram_0005e1a6(int param_1)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  undefined4 uVar4;
  ushort uVar5;
  int iVar6;
  byte *pbVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  byte *pbVar11;
  uint uVar12;
  
  gp = 0x20004000;
  iVar3 = FUN_ram_20001120(*(undefined4 *)(param_1 + 0x78),0,param_1 + 0x15,0);
  if (iVar3 != 0) {
    gp = 0x20004000;
    return 1;
  }
  pbVar11 = *(byte **)(param_1 + 0x78);
  bVar1 = *pbVar11;
  *(byte *)(param_1 + 0xd) = bVar1 & 0xf;
  uVar9 = (uint)pbVar11[1];
  *(byte *)(param_1 + 0xe) = pbVar11[1];
  if ((bVar1 & 0xf) != 7) {
    gp = 0x20004000;
    return 7;
  }
  uVar8 = pbVar11[2] & 0x3f;
  if (uVar9 <= uVar8) {
    gp = 0x20004000;
    return 3;
  }
  if (pbVar11[2] >> 6 != 0) {
    gp = 0x20004000;
    return 5;
  }
  uVar12 = (uVar9 - 1) - uVar8;
  *(char *)(param_1 + 0x2e) = (char)uVar12;
  bVar1 = pbVar11[3];
  if ((bVar1 & 3) != 0) {
    gp = 0x20004000;
    return 0x11;
  }
  if ((bVar1 & 4) == 0) {
    pbVar7 = pbVar11 + 4;
    uVar8 = uVar8 - 1;
  }
  else {
    pbVar7 = pbVar11 + 5;
    uVar8 = uVar8 - 2;
  }
  uVar8 = uVar8 & 0xff;
  if ((bVar1 & 8) != 0) {
    if (*(byte *)(param_1 + 0x29) != pbVar7[1] >> 4) {
      gp = 0x20004000;
      return 0x14;
    }
    if (*(ushort *)(param_1 + 0x2a) != (ushort)((pbVar7[1] & 0xf) << 8 | (ushort)*pbVar7)) {
      gp = 0x20004000;
      return 0x14;
    }
    pbVar7 = pbVar7 + 2;
    uVar8 = uVar8 - 2 & 0xff;
  }
  if ((bVar1 & 0x10) == 0) goto LAB_ram_0005e2ee;
  *(byte *)(param_1 + 0x24) = *pbVar7 & 0x3f;
  bVar1 = pbVar7[2];
  bVar2 = pbVar7[1];
  uVar5 = (ushort)((uint)bVar1 << 8) & 0x1f00 | (ushort)bVar2;
  *(ushort *)(param_1 + 0x26) = uVar5;
  iVar3 = DAT_ram_20001eb0;
  if (uVar5 != 0) {
    if ((char)*pbVar7 < '\0') {
      iVar6 = 300;
    }
    else {
      iVar6 = 0x1e;
    }
    if (*(char *)(param_1 + 0x25) == '\x02') {
      iVar10 = (uVar9 + 2) * 8;
      if (DAT_ram_20001e9f == '\0') {
        iVar10 = iVar10 + 0x4a;
LAB_ram_0005e370:
        iVar10 = iVar10 << 3;
      }
      else {
        iVar10 = (iVar10 + 0xd7) * 2;
      }
    }
    else {
      if (*(char *)(param_1 + 0x25) != '\x01') {
        iVar10 = uVar9 + 10;
        goto LAB_ram_0005e370;
      }
      iVar10 = (uVar9 + 0xb) * 4;
    }
    iVar10 = ((uint)bVar1 << 8 & 0x1f00 | (uint)bVar2) * iVar6 - iVar10;
    bVar1 = *(byte *)(param_1 + 0x28);
    if (iVar10 - 300U < 0x515) {
      uVar9 = (uVar12 & 0xff) + (uint)*(ushort *)(param_1 + 0x3c);
      if (DAT_ram_20001da0 < uVar9) {
        *(byte *)(param_1 + 0x28) = bVar1 | 0x40;
        gp = 0x20004000;
        return 0x20;
      }
      *(byte *)(param_1 + 0x28) = bVar1 | 0x20;
      *(short *)(param_1 + 0x3c) = (short)uVar9;
      *(undefined4 *)(iVar3 + 0xc) = 0xd00f;
      iVar3 = DAT_ram_20001eb0;
      fence.i();
      *(undefined4 *)(DAT_ram_20001eb0 + 8) = 0x2000;
      DAT_ram_20001e98 = 0x80;
      *(int *)(iVar3 + 100) = (iVar10 + -299) * 2;
      *(undefined4 *)(iVar3 + 0xc) = 0xf00f;
    }
    else {
      *(byte *)(param_1 + 0x28) = bVar1 | 0x40;
    }
  }
  pbVar7 = pbVar7 + 3;
  uVar8 = uVar8 - 3 & 0xff;
LAB_ram_0005e2ee:
  uVar4 = 0x16;
  if ((pbVar11[3] & 0x20) == 0) {
    if ((pbVar11[3] & 0x40) != 0) {
      uVar8 = uVar8 - 1 & 0xff;
      *(byte *)(param_1 + 0x23) = *pbVar7;
    }
    uVar4 = 0x18;
    if (uVar8 == 0) {
      FUN_ram_000682c8(*(undefined1 *)(param_1 + 0x28),*(undefined1 *)(param_1 + 0x55),
                       param_1 + 0x56,*(char *)(param_1 + 0x2c) + '\x01',
                       *(undefined1 *)(param_1 + 0x2d),*(undefined1 *)(param_1 + 0x29),
                       (int)*(char *)(param_1 + 0x23),(int)*(char *)(param_1 + 0x15),
                       *(undefined2 *)(param_1 + 0x3e),0,0,(uint)*(byte *)(param_1 + 0x2e),
                       ((uint)*(byte *)(param_1 + 0xe) - (uint)*(byte *)(param_1 + 0x2e)) + 2 +
                       *(int *)(param_1 + 0x78));
      uVar4 = 0;
    }
  }
  return uVar4;
}

