/* Address: ram:0005e55c; name: FUN_ram_0005e55c; body bytes: 486 */

undefined4 FUN_ram_0005e55c(int param_1)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  undefined4 uVar4;
  byte *pbVar5;
  ushort uVar6;
  int iVar7;
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
  pbVar5 = *(byte **)(param_1 + 0x78);
  bVar1 = *pbVar5;
  *(byte *)(param_1 + 0xd) = bVar1 & 0xf;
  uVar9 = (uint)pbVar5[1];
  *(byte *)(param_1 + 0xe) = pbVar5[1];
  if ((bVar1 & 0xf) != 7) {
    gp = 0x20004000;
    return 7;
  }
  uVar8 = pbVar5[2] & 0x3f;
  if (uVar9 <= uVar8) {
    gp = 0x20004000;
    return 3;
  }
  if (pbVar5[2] >> 6 != 0) {
    gp = 0x20004000;
    return 5;
  }
  uVar12 = (uVar9 - 1) - uVar8;
  *(char *)(param_1 + 0x2e) = (char)uVar12;
  bVar1 = pbVar5[3];
  if ((bVar1 & 3) != 0) {
    gp = 0x20004000;
    return 0x11;
  }
  if ((bVar1 & 4) == 0) {
    pbVar11 = pbVar5 + 4;
    uVar8 = uVar8 - 1;
  }
  else {
    pbVar11 = pbVar5 + 5;
    uVar8 = uVar8 - 2;
  }
  uVar8 = uVar8 & 0xff;
  if ((bVar1 & 8) != 0) {
    if (*(byte *)(param_1 + 0x29) != pbVar11[1] >> 4) {
      gp = 0x20004000;
      return 0x14;
    }
    if (*(ushort *)(param_1 + 0x2a) != (ushort)((pbVar11[1] & 0xf) << 8 | (ushort)*pbVar11)) {
      gp = 0x20004000;
      return 0x14;
    }
    pbVar11 = pbVar11 + 2;
    uVar8 = uVar8 - 2 & 0xff;
  }
  if ((bVar1 & 0x10) == 0) goto LAB_ram_0005e696;
  *(byte *)(param_1 + 0x24) = *pbVar11 & 0x3f;
  bVar1 = pbVar11[2];
  bVar2 = pbVar11[1];
  uVar6 = (ushort)((uint)bVar1 << 8) & 0x1f00 | (ushort)bVar2;
  *(ushort *)(param_1 + 0x26) = uVar6;
  iVar3 = DAT_ram_20001eb0;
  if (uVar6 != 0) {
    if ((char)*pbVar11 < '\0') {
      iVar7 = 300;
    }
    else {
      iVar7 = 0x1e;
    }
    if (*(char *)(param_1 + 0xbc) == '\x03') {
      iVar10 = (uVar9 + 2) * 8;
      if (DAT_ram_20001e9f == '\0') {
        iVar10 = iVar10 + 0x4a;
LAB_ram_0005e6ce:
        iVar10 = iVar10 << 3;
      }
      else {
        iVar10 = (iVar10 + 0xd7) * 2;
      }
    }
    else {
      if (*(char *)(param_1 + 0xbc) != '\x02') {
        iVar10 = uVar9 + 10;
        goto LAB_ram_0005e6ce;
      }
      iVar10 = (uVar9 + 0xb) * 4;
    }
    iVar10 = ((uint)bVar1 << 8 & 0x1f00 | (uint)bVar2) * iVar7 - iVar10;
    if (iVar10 - 300U < 0x515) {
      uVar9 = (uVar12 & 0xff) + (uint)*(ushort *)(param_1 + 0x3c);
      if (uVar9 <= DAT_ram_20001da0) {
        *(undefined1 *)(param_1 + 0x28) = 1;
        *(short *)(param_1 + 0x3c) = (short)uVar9;
        *(undefined4 *)(iVar3 + 0xc) = 0xd00f;
        iVar3 = DAT_ram_20001eb0;
        fence.i();
        *(undefined4 *)(DAT_ram_20001eb0 + 8) = 0x2000;
        DAT_ram_20001e98 = 0x80;
        *(int *)(iVar3 + 100) = (iVar10 + -299) * 2;
        *(undefined4 *)(iVar3 + 0xc) = 0xf00f;
        goto LAB_ram_0005e68e;
      }
      *(undefined1 *)(param_1 + 0x2e) = 0;
    }
    *(undefined1 *)(param_1 + 0x28) = 2;
  }
LAB_ram_0005e68e:
  uVar8 = uVar8 - 3 & 0xff;
LAB_ram_0005e696:
  uVar4 = 0x16;
  if ((pbVar5[3] & 0x20) == 0) {
    if ((pbVar5[3] & 0x40) != 0) {
      uVar8 = uVar8 - 1 & 0xff;
    }
    uVar4 = 0;
    if (uVar8 != 0) {
      uVar4 = 0x18;
    }
  }
  return uVar4;
}

