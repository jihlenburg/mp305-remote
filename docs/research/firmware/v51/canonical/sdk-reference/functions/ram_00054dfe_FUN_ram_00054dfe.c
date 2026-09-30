/* Address: ram:00054dfe; name: FUN_ram_00054dfe; body bytes: 542 */

/* WARNING: Removing unreachable block (ram,0x00054f52) */

undefined4 FUN_ram_00054dfe(void)

{
  byte bVar1;
  byte bVar2;
  short sVar3;
  int iVar4;
  undefined4 uVar5;
  undefined1 *puVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  short sVar11;
  
  gp = 0x20004000;
  iVar4 = FUN_ram_00054de4();
  if (iVar4 == 0) {
    gp = 0x20004000;
    return 0;
  }
  if (*(char *)(iVar4 + 0x35) == '\0') {
LAB_ram_00054e22:
    puVar6 = &DAT_ram_20001e38;
LAB_ram_00054e2c:
    tmos_memcpy(iVar4 + 0x36,puVar6,6);
  }
  else {
    if (*(char *)(iVar4 + 0x35) == '\x01') {
LAB_ram_00054e40:
      if (DAT_ram_20001d62 == '\0') {
        gp = 0x20004000;
        return 0x12;
      }
      puVar6 = &DAT_ram_20001e3e;
      goto LAB_ram_00054e2c;
    }
    if (*(int *)(iVar4 + 0x30) == 0) {
      *(undefined1 *)(iVar4 + 0x34) = 0;
      if (*(char *)(iVar4 + 0x3c) != '\0') {
        iVar9 = FUN_ram_20000c00(iVar4 + 0x3c);
        *(int *)(iVar4 + 0x30) = iVar9;
        if (iVar9 != 0) {
          FUN_ram_0005d732();
          if (*(char *)(*(int *)(iVar4 + 0x30) + 10) != '\0') {
            *(undefined1 *)(iVar4 + 0x34) = 2;
            tmos_memcpy(iVar4 + 0x36,*(int *)(iVar4 + 0x30) + 0xc,6);
          }
        }
        goto LAB_ram_00054ea8;
      }
LAB_ram_00054e64:
      *(undefined1 *)(iVar4 + 0x34) = 1;
      if (*(char *)(iVar4 + 0x35) == '\x02') goto LAB_ram_00054e22;
      goto LAB_ram_00054e40;
    }
LAB_ram_00054ea8:
    if (*(char *)(iVar4 + 0x34) != '\x02') goto LAB_ram_00054e64;
  }
  if ((DAT_ram_20001d61 != '\0') && (*(char *)(iVar4 + 0x3c) != '\0')) {
    if ((*(byte *)(iVar4 + 0x43) & 0xc0) == 0x40) {
      uVar5 = FUN_ram_20000c50();
    }
    else {
      uVar5 = FUN_ram_20000c00(iVar4 + 0x3c);
    }
    *(undefined4 *)(iVar4 + 0x30) = uVar5;
    if ((*(int *)(iVar4 + 0x30) != 0) && (*(char *)(*(int *)(iVar4 + 0x30) + 0x12) != '\0')) {
      *(undefined1 *)(iVar4 + 0x3c) = 2;
    }
  }
  *(undefined1 *)(iVar4 + 0xc) = 1;
  *(undefined1 *)(iVar4 + 9) = 1;
  bVar2 = DAT_ram_20001bd5;
  DAT_ram_20001d60 = 0;
  bVar1 = *(byte *)(iVar4 + 0xe);
  *(ushort *)(iVar4 + 0x74) = (ushort)DAT_ram_20001bd5;
  if (6 < (bVar1 & 0xf)) {
    sVar11 = bVar2 + 4;
    if (*(char *)(iVar4 + 100) == '\x02') {
      sVar11 = bVar2 + 0x3c;
    }
    uVar8 = (uint)DAT_ram_20001e9e;
    *(short *)(iVar4 + 0x74) = sVar11;
    uVar7 = *(ushort *)(iVar4 + 0x1c) / 0xfa;
    iVar9 = (uint)*(ushort *)(iVar4 + 0x1c) * 8 + 0x2b;
    if (*(char *)(iVar4 + 99) == '\x02') {
      iVar9 = uVar8 + 0x236 + iVar9 * 8;
      iVar10 = uVar7 << 10;
    }
    else {
      iVar9 = uVar8 + 0xbe + iVar9;
      iVar10 = uVar7 << 9;
    }
    sVar3 = FUN_ram_0006bae2((uint)DAT_ram_20001b8c * (iVar10 + iVar9),
                             (int)((longlong)(iVar10 + iVar9) * (ulonglong)(uint)DAT_ram_20001b8c >>
                                  0x20),1000000,0);
    *(short *)(iVar4 + 0x74) = sVar3 + sVar11;
  }
  *(undefined2 *)(iVar4 + 0x6e) = 0;
  if (*(short *)(iVar4 + 0x6c) == 0) {
    if (bVar1 != 1) goto LAB_ram_00054fc4;
    if (*(char *)(iVar4 + 0x16) != -1) {
      FUN_ram_00042494();
      *(undefined1 *)(iVar4 + 0x16) = 0xff;
    }
    iVar9 = 0x800;
  }
  else {
    if (*(char *)(iVar4 + 0x16) != -1) {
      FUN_ram_00042494();
      *(undefined1 *)(iVar4 + 0x16) = 0xff;
    }
    iVar9 = (uint)*(ushort *)(iVar4 + 0x6c) << 4;
  }
  FUN_ram_00042362(FUN_ram_00055846,iVar4,iVar9,iVar4 + 0x16);
LAB_ram_00054fc4:
  tmos_set_event(DAT_ram_20001b67,1);
  return 0;
}

