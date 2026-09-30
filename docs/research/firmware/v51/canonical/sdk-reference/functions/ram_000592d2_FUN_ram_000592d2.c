/* Address: ram:000592d2; name: FUN_ram_000592d2; body bytes: 744 */

/* WARNING: Removing unreachable block (ram,0x000594e8) */

undefined4 FUN_ram_000592d2(int param_1)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  undefined4 uVar4;
  ushort uVar5;
  uint uVar6;
  byte bVar7;
  byte bVar8;
  int iVar9;
  byte *pbVar10;
  
  gp = 0x20004000;
  iVar3 = FUN_ram_20001120(*(undefined4 *)(param_1 + 0x98),0,0,0);
  if (iVar3 != 0) {
    gp = 0x20004000;
    return 1;
  }
  pbVar2 = *(byte **)(param_1 + 0x98);
  bVar1 = *pbVar2;
  bVar7 = bVar1 & 0xf;
  *(byte *)(param_1 + 9) = bVar7;
  bVar8 = pbVar2[1] & 0x3f;
  *(byte *)(param_1 + 10) = bVar8;
  if (bVar7 != 7) {
    if ((bVar1 & 0xe) != 0) {
      gp = 0x20004000;
      return 0x80;
    }
    if (0x1f < (byte)(bVar8 - 6)) {
      gp = 0x20004000;
      return 0x80;
    }
    *(undefined1 *)(param_1 + 0x74) = 1;
    *(byte *)(param_1 + 0x75) = (byte)((int)(uint)*pbVar2 >> 6) & 1;
    tmos_memcpy(param_1 + 0x76,pbVar2 + 2,6);
    *(undefined1 *)(param_1 + 0x7c) = 0;
    if (*(char *)(param_1 + 9) == '\x01') {
      *(undefined1 *)(param_1 + 0x7c) = 1;
      *(byte *)(param_1 + 0x7d) = **(byte **)(param_1 + 0x98) >> 7;
      tmos_memcpy(param_1 + 0x7e,*(byte **)(param_1 + 0x98) + 8,6);
    }
    iVar3 = FUN_ram_00058ee0(param_1);
    if (iVar3 != 1) {
      gp = 0x20004000;
      return 8;
    }
    uVar4 = FUN_ram_00059074(param_1);
    return uVar4;
  }
  *(undefined1 *)(param_1 + 0x3a) = 0xff;
  bVar1 = pbVar2[2];
  bVar7 = bVar1 >> 6;
  *(byte *)(param_1 + 0x3d) = bVar7;
  if (bVar7 != 1) {
    gp = 0x20004000;
    return 5;
  }
  if (bVar8 != (byte)((bVar1 & 0x3f) + 1)) {
    gp = 0x20004000;
    return 3;
  }
  bVar1 = pbVar2[3];
  if ((bVar1 & 0xbf) != 0x18) {
    gp = 0x20004000;
    return 2;
  }
  pbVar10 = pbVar2 + 4;
  if ((bVar1 & 8) != 0) {
    pbVar10 = pbVar2 + 6;
    *(ushort *)(param_1 + 0x44) = (pbVar2[5] & 0xf) << 8 | (ushort)pbVar2[4];
    *(byte *)(param_1 + 0x3f) = pbVar2[5] >> 4;
  }
  uVar6 = 0;
  if ((bVar1 & 0x10) == 0) goto LAB_ram_0005940a;
  FUN_ram_00062262();
  *(byte *)(param_1 + 0x3b) = *pbVar10 & 0x3f;
  uVar5 = (pbVar10[2] & 0x1f) << 8 | (ushort)pbVar10[1];
  *(ushort *)(param_1 + 0x42) = uVar5;
  *(byte *)(param_1 + 0x3c) = pbVar10[2] >> 5;
  if ((char)*pbVar10 < '\0') {
    iVar3 = 300;
  }
  else {
    iVar3 = 0x1e;
  }
  if (*(char *)(param_1 + 0x39) == '\x01') {
    iVar9 = *(byte *)(param_1 + 10) + 10;
LAB_ram_000593d8:
    iVar9 = iVar9 << 3;
  }
  else {
    iVar9 = (*(byte *)(param_1 + 10) + 2) * 8;
    if (DAT_ram_20001e9f == '\0') {
      iVar9 = iVar9 + 0x4a;
      goto LAB_ram_000593d8;
    }
    iVar9 = (iVar9 + 0xd7) * 2;
  }
  uVar6 = (short)uVar5 * iVar3 - iVar9;
  if (0x7ffffed3 < uVar6 - 300) {
    gp = 0x20004000;
    return 0x21;
  }
  *(char *)(param_1 + 0x3a) = *(char *)(param_1 + 0x39);
LAB_ram_0005940a:
  if (((pbVar2[3] & 0x40) == 0) || (*(char *)(param_1 + 0x39) != '\x02')) {
    uVar4 = 0;
    if (*(char *)(param_1 + 0x3a) != -1) {
      if (uVar6 < 0x501) {
        *(undefined4 *)(DAT_ram_20001eb0 + 0xc) = 0xd00f;
        iVar3 = DAT_ram_20001eb0;
        fence.i();
        *(undefined4 *)(DAT_ram_20001eb0 + 8) = 0x2000;
        DAT_ram_20001e98 = 0x80;
        *(uint *)(iVar3 + 100) = (uVar6 - 299) * 2;
        *(undefined4 *)(iVar3 + 0xc) = 0xf00f;
        do {
        } while (*(int *)(iVar3 + 100) != 0);
        *(undefined1 *)(param_1 + 0x39) = 8;
        FUN_ram_000588dc(param_1);
        *(undefined4 *)(DAT_ram_20001eb0 + 0xc) = 0xd00f;
        iVar3 = DAT_ram_20001eb0;
        fence.i();
        *(undefined4 *)(DAT_ram_20001eb0 + 8) = 0x2000;
        DAT_ram_20001e98 = 0x80;
        *(undefined4 *)(iVar3 + 100) = 0x592;
        *(undefined4 *)(iVar3 + 0xc) = 0xf00f;
        FUN_ram_200010ec();
        if ((DAT_ram_20001e94 & 1) != 0) {
          DAT_ram_20001e94 = 0;
          uVar4 = FUN_ram_000590b8(param_1);
          return uVar4;
        }
      }
      else if (*(char *)(param_1 + 0x40) == -1) {
        FUN_ram_00042362(&LAB_ram_000589d8,param_1,(uVar6 - 0x271) / 0x271,param_1 + 0x40);
      }
    }
  }
  else {
    uVar4 = 0x17;
  }
  return uVar4;
}

