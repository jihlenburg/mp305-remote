/* Address: ram:0006969c; name: FUN_ram_0006969c; body bytes: 140 */

void FUN_ram_0006969c(void)

{
  uint uVar1;
  int iVar2;
  
  gp = 0x20004000;
  for (uVar1 = 0; uVar1 < DAT_ram_20001a8d; uVar1 = uVar1 + 1 & 0xff) {
    iVar2 = uVar1 * 0x10;
    tmos_memset(DAT_ram_20001a88 + iVar2,0xff,6);
    tmos_memset(DAT_ram_20001a88 + iVar2 + 6,0xff,6);
    iVar2 = DAT_ram_20001a88 + iVar2;
    *(undefined2 *)(iVar2 + 0xc) = 0;
    *(undefined1 *)(iVar2 + 0xe) = 0;
  }
  FUN_ram_00042b1c();
  DAT_ram_20001a86 = DAT_ram_20001a8d;
  return;
}

