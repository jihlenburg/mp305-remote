/* Address: ram:00058710; name: FUN_ram_00058710; body bytes: 344 */

void FUN_ram_00058710(void)

{
  char cVar1;
  int iVar2;
  uint *puVar3;
  undefined4 *puVar4;
  int iVar5;
  uint uVar6;
  
  iVar5 = DAT_ram_20001efc;
  puVar3 = DAT_ram_20001e88;
  iVar2 = DAT_ram_20001de8;
  gp = 0x20004000;
  if (*(char *)(DAT_ram_20001de8 + 0x39) != '\b') {
    cVar1 = *(char *)(DAT_ram_20001de8 + 5);
    if (*(char *)(DAT_ram_20001de8 + 0x39) == '\x02') {
      if (cVar1 == '\'') {
LAB_ram_0005885a:
        FUN_ram_0005856c(DAT_ram_20001de8);
        return;
      }
      uVar6 = 0x26;
      if (cVar1 != '%') {
        uVar6 = 0x27;
      }
      *(char *)(DAT_ram_20001de8 + 5) = (char)uVar6;
      *puVar3 = *puVar3 & 0xfffffe7f | 0x80;
      iVar5 = DAT_ram_20001efc;
      *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) & 0xffcdffff;
      puVar4 = DAT_ram_20001eb0;
      DAT_ram_20001eb0[0x14] = 0x80;
      DAT_ram_20001e94 = 0;
      DAT_ram_20001e98 = 0;
      DAT_ram_20001e99 = 0;
      DAT_ram_20001e95 = 0;
      *puVar4 = 1;
      *puVar3 = *puVar3 & 0xfffffe7f;
      *puVar3 = *puVar3 & 0xfffffe7f | 0x100;
      *(uint *)(iVar5 + 8) = *(uint *)(iVar5 + 8) | 0x330000;
      puVar4[0x14] = 0xd9;
      *(uint *)(iVar5 + 0x2c) = *(uint *)(iVar5 + 0x2c) & 0xfffffffd;
      *puVar3 = *puVar3 & 0xffffff80 | uVar6;
    }
    else {
      if (cVar1 == '\'') {
        if ((*(byte *)(DAT_ram_20001de8 + 0x38) & 2) != 0) {
          tmos_start_reload_task(DAT_ram_20001b67,0x20,*(undefined2 *)(DAT_ram_20001de8 + 0x4a));
          *(undefined1 *)(iVar2 + 0x39) = 2;
          *(undefined1 *)(iVar2 + 5) = 0x25;
          FUN_ram_000585c6();
          return;
        }
        goto LAB_ram_0005885a;
      }
      uVar6 = 0x26;
      if (cVar1 != '%') {
        uVar6 = 0x27;
      }
      *(char *)(DAT_ram_20001de8 + 5) = (char)uVar6;
      *(uint *)(iVar5 + 0x2c) = *(uint *)(iVar5 + 0x2c) & 0xfffffffd;
      *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xffffff80 | uVar6;
    }
    *(undefined1 *)(iVar2 + 6) = 0xb2;
  }
  return;
}

