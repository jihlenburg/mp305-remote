/* Address: ram:0005f570; name: FUN_ram_0005f570; body bytes: 34 */

void FUN_ram_0005f570(void)

{
  int iVar1;
  
  iVar1 = DAT_ram_20001dd8;
  gp = 0x20004000;
  *(uint *)(DAT_ram_20001dd8 + 0x1c) = *(uint *)(DAT_ram_20001dd8 + 0x1c) & 0xfffffff1;
  *(undefined1 *)(iVar1 + 0xb1) = 0x44;
  FUN_ram_0005d5f6(0,0x80,0xe);
  return;
}

