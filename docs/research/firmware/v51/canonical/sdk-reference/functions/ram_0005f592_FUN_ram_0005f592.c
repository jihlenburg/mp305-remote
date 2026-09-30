/* Address: ram:0005f592; name: FUN_ram_0005f592; body bytes: 596 */

undefined4 FUN_ram_0005f592(int param_1)

{
  byte bVar1;
  byte *pbVar2;
  undefined1 uVar3;
  int iVar4;
  byte *pbVar5;
  byte *pbVar6;
  uint uVar7;
  int iVar8;
  byte bVar9;
  ushort uVar10;
  
  gp = 0x20004000;
  iVar4 = FUN_ram_20001120(*(undefined4 *)(param_1 + 0x78),0,param_1 + 0x15,0);
  if (iVar4 != 0) {
    gp = 0x20004000;
    return 1;
  }
  pbVar2 = *(byte **)(param_1 + 0x78);
  bVar9 = *pbVar2;
  *(byte *)(param_1 + 0xd) = bVar9 & 0xf;
  bVar1 = pbVar2[1];
  *(byte *)(param_1 + 0xe) = bVar1;
  if ((bVar9 & 0xf) != 7) {
    gp = 0x20004000;
    return 0x80;
  }
  *(byte *)(param_1 + 0x28) = *(byte *)(param_1 + 0x28) | 8;
  bVar9 = pbVar2[2] & 0x3f;
  if (pbVar2[2] >> 6 != 0) {
    gp = 0x20004000;
    return 5;
  }
  if (bVar1 <= (byte)(bVar9 + 1)) {
    gp = 0x20004000;
    return 3;
  }
  *(byte *)(param_1 + 0x2e) = (bVar1 - 1) - bVar9;
  pbVar5 = pbVar2 + 4;
  if ((pbVar2[3] & 1) != 0) {
    if (*(char *)(param_1 + 0x54) == '\x03') {
      if ((*pbVar2 & 0x40) == 0) {
        gp = 0x20004000;
        return 0x11;
      }
      iVar4 = *(int *)(param_1 + 100) + 0x14;
    }
    else {
      if ((uint)*(byte *)(param_1 + 0x55) != ((int)(uint)*pbVar2 >> 6 & 1U)) {
        gp = 0x20004000;
        return 0x11;
      }
      iVar4 = param_1 + 0x56;
    }
    iVar4 = tmos_memcmp(iVar4,pbVar5,6);
    pbVar5 = pbVar2 + 10;
    if (iVar4 == 0) {
      gp = 0x20004000;
      return 0x11;
    }
  }
  bVar9 = pbVar2[3];
  if ((bVar9 & 2) != 0) {
    gp = 0x20004000;
    return 0x12;
  }
  *(undefined1 *)(param_1 + 0x5c) = 0;
  if ((bVar9 & 4) != 0) {
    gp = 0x20004000;
    return 0x13;
  }
  if ((bVar9 & 0x20) != 0) {
    gp = 0x20004000;
    return 0x16;
  }
  pbVar6 = pbVar5;
  if ((bVar9 & 8) != 0) {
    pbVar6 = pbVar5 + 2;
    *(ushort *)(param_1 + 0x2a) = (pbVar5[1] & 0xf) << 8 | (ushort)*pbVar5;
    *(byte *)(param_1 + 0x29) = pbVar5[1] >> 4;
  }
  if ((bVar9 & 0x10) == 0) goto LAB_ram_0005f704;
  *(byte *)(param_1 + 0x24) = *pbVar6 & 0x3f;
  uVar10 = (pbVar6[2] & 0x1f) << 8 | (ushort)pbVar6[1];
  *(ushort *)(param_1 + 0x26) = uVar10;
  if ((char)*pbVar6 < '\0') {
    iVar4 = 300;
  }
  else {
    iVar4 = 0x1e;
  }
  uVar7 = (uint)*(byte *)(param_1 + 0xe);
  if (*(char *)(param_1 + 0x25) == '\x02') {
    iVar8 = (uVar7 + 2) * 8;
    if (DAT_ram_20001e9f == '\0') {
      iVar8 = iVar8 + 0x4a;
LAB_ram_0005f77e:
      iVar8 = iVar8 << 3;
    }
    else {
      iVar8 = (iVar8 + 0xd7) * 2;
    }
  }
  else {
    if (*(char *)(param_1 + 0x25) != '\x01') {
      iVar8 = uVar7 + 10;
      goto LAB_ram_0005f77e;
    }
    iVar8 = (uVar7 + 0xb) * 4;
  }
  iVar8 = (short)uVar10 * iVar4 - iVar8;
  if (iVar8 - 300U < 0x515) {
    *(undefined4 *)(DAT_ram_20001eb0 + 0xc) = 0xd00f;
    iVar4 = DAT_ram_20001eb0;
    fence.i();
    *(undefined4 *)(DAT_ram_20001eb0 + 8) = 0x2000;
    DAT_ram_20001e98 = 0x80;
    *(int *)(iVar4 + 100) = (iVar8 + -299) * 2;
    *(undefined4 *)(iVar4 + 0xc) = 0xf00f;
    bVar9 = *(byte *)(param_1 + 0x28) | 0x20;
  }
  else {
    bVar9 = *(byte *)(param_1 + 0x28) | 0x40;
  }
  *(byte *)(param_1 + 0x28) = bVar9;
  pbVar6 = pbVar6 + 3;
LAB_ram_0005f704:
  if ((pbVar2[3] & 0x40) != 0) {
    *(byte *)(param_1 + 0x23) = *pbVar6;
  }
  if (*(char *)(param_1 + 0x14) < '\x01') {
    *(undefined1 *)(param_1 + 0x14) = 1;
  }
  else {
    bVar9 = *(byte *)(param_1 + 0x13) >> 1;
    if (bVar9 == 0) {
      bVar9 = 1;
    }
    *(byte *)(param_1 + 0x13) = bVar9;
  }
  uVar3 = FUN_ram_000428ec(1,*(undefined1 *)(param_1 + 0x13));
  *(undefined1 *)(param_1 + 0x11) = uVar3;
  iVar4 = FUN_ram_0005dd6c(param_1);
  if ((iVar4 == 1) && ((*(byte *)(param_1 + 0x28) & 0x60) == 0x20)) {
    *(undefined1 *)(param_1 + 10) = 0xa5;
    *(ushort *)(param_1 + 0x3c) = (ushort)*(byte *)(param_1 + 0x2e);
  }
  return 0;
}

