/* Address: ram:0005d9ec; name: FUN_ram_0005d9ec; body bytes: 376 */

undefined4 FUN_ram_0005d9ec(void)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined1 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  int iVar10;
  
  iVar2 = DAT_ram_20001dd8;
  gp = 0x20004000;
  if ((*(byte *)(DAT_ram_20001dd8 + 0x4d) & 1) == 0) {
    puVar6 = &DAT_ram_20001e38;
  }
  else {
    if (DAT_ram_20001d62 == '\0') {
      gp = 0x20004000;
      return 0x12;
    }
    puVar6 = &DAT_ram_20001e3e;
  }
  tmos_memcpy(DAT_ram_20001dd8 + 0x4e,puVar6,6);
  *(undefined1 *)(iVar2 + 0xb) = 1;
  *(undefined1 *)(iVar2 + 0x11) = 1;
  *(undefined1 *)(iVar2 + 0x13) = 1;
  *(undefined1 *)(iVar2 + 8) = 2;
  if (*(char *)(iVar2 + 0x12) != '\0') {
    uVar3 = FUN_ram_00041b28();
    if (DAT_ram_20001db4 != 0) {
      if (uVar3 < 0x401) {
        gp = 0x20004000;
        return 7;
      }
      uVar3 = uVar3 - 0x400;
    }
    if (DAT_ram_20001e04 != 0) {
      if (uVar3 <= (uint)DAT_ram_20001bcc * (uint)DAT_ram_20001bcb) {
        gp = 0x20004000;
        return 7;
      }
      uVar3 = uVar3 - (uint)DAT_ram_20001bcc * (uint)DAT_ram_20001bcb;
    }
    uVar4 = FUN_ram_00041bc6();
    if (uVar4 < uVar3 >> 1) {
      *(short *)(iVar2 + 0x42) = (short)(uVar4 >> 4);
      if ((uVar4 >> 4 & 0xffff) == 0) {
        gp = 0x20004000;
        return 7;
      }
    }
    else {
      *(short *)(iVar2 + 0x42) = (short)(uVar3 >> 5);
    }
    puVar5 = (undefined4 *)FUN_ram_20000040((*(ushort *)(iVar2 + 0x42) & 0xfff) << 4,0x205);
    uVar1 = *(ushort *)(iVar2 + 0x42);
    *(undefined4 **)(iVar2 + 0x44) = puVar5;
    puVar9 = puVar5;
    for (iVar10 = 0; iVar10 < (int)(uint)uVar1; iVar10 = iVar10 + 1) {
      if (iVar10 < (int)(uVar1 - 1)) {
        puVar7 = puVar9 + 4;
        puVar8 = puVar7;
      }
      else {
        puVar7 = (undefined4 *)0x0;
        puVar8 = puVar9;
      }
      *puVar9 = puVar7;
      puVar9 = puVar8;
    }
    *(undefined4 **)(iVar2 + 0x48) = puVar5;
  }
  if (*(char *)(iVar2 + 0x20) == '\x03') {
    uVar3 = (uint)*(ushort *)(iVar2 + 0x16) + (uint)*(ushort *)(iVar2 + 0x32);
  }
  else if (*(char *)(iVar2 + 0x20) == '\x02') {
    uVar3 = (uint)*(ushort *)(iVar2 + 0x32);
  }
  else {
    uVar3 = (uint)*(ushort *)(iVar2 + 0x16);
  }
  tmos_start_reload_task(DAT_ram_20001b67,4,uVar3);
  tmos_set_event(DAT_ram_20001b67,4);
  if (*(ushort *)(iVar2 + 0x38) != 0) {
    FUN_ram_00042362(FUN_ram_0006049c,iVar2,(uint)*(ushort *)(iVar2 + 0x38) << 4,iVar2 + 0x31);
  }
  DAT_ram_20001d60 = 0;
  return 0;
}

