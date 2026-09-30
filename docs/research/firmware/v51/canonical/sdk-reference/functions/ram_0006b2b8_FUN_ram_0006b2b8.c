/* Address: ram:0006b2b8; name: FUN_ram_0006b2b8; body bytes: 138 */

void FUN_ram_0006b2b8(void)

{
  gp = 0x20004000;
  DAT_ram_200019cc = 0xff;
  DAT_ram_20001d51 = 0xff;
  DAT_ram_20001d52 = 0xff;
  DAT_ram_20001f48 = 0;
  DAT_ram_20001f14 = 1;
  DAT_ram_20001acc = 0;
  DAT_ram_20001f1c = 6;
  DAT_ram_20001f26 = &cycleh;
  DAT_ram_20001ac0 = 0;
  DAT_ram_20001f17 = 0;
  DAT_ram_20001f52 = 0xff;
  DAT_ram_20001f19 = 7;
  DAT_ram_20001f1a = 7;
  tmos_memset(&DAT_ram_20001ac4,0,6);
  return;
}

