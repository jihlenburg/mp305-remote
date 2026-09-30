/* Address: ram:000597c8; name: FUN_ram_000597c8; body bytes: 124 */

void FUN_ram_000597c8(void)

{
  int iVar1;
  
  iVar1 = DAT_ram_20001de8;
  gp = 0x20004000;
  if ((DAT_ram_20001e9d != '\0') && (DAT_ram_20001e9c == '\x03')) {
    DAT_ram_20001e9d = '\0';
  }
  if ((DAT_ram_20001e9b - 6U & 0xfd) == 0) {
    DAT_ram_20001e9c = DAT_ram_20001e9b;
    DAT_ram_20001e9d = '\x01';
  }
  FUN_ram_00062262();
  FUN_ram_00058d50(iVar1);
  FUN_ram_0005d5f6(0,0x80,0x23);
  if (*(char *)(iVar1 + 0x40) != -1) {
    FUN_ram_00042494();
    *(undefined1 *)(iVar1 + 0x40) = 0xff;
  }
  return;
}

