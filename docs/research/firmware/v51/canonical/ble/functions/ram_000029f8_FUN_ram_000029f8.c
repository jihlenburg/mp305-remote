/* Address: ram:000029f8; name: FUN_ram_000029f8; body bytes: 102 */

void FUN_ram_000029f8(void)

{
  gp = &DAT_ram_20002000;
  DAT_ram_4000800c = DAT_ram_4000800c & 0x33;
  DAT_ram_4000800d = DAT_ram_4000800d & 0x33;
  DAT_ram_40008000 = DAT_ram_40008000 & 0xd6 | 4;
  DAT_ram_4000101a = DAT_ram_4000101a & 0xff3f;
  DAT_ram_40008001 = DAT_ram_40008001 & 0x7e;
  DAT_ram_40008002 = DAT_ram_40008002 & 0xf8;
  return;
}

