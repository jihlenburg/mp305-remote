/* Address: ram:000037f8; name: FUN_ram_000037f8; body bytes: 24 */

bool FUN_ram_000037f8(void)

{
  bool bVar1;
  
  gp = &DAT_ram_20002000;
  bVar1 = DAT_ram_20002f7c != '\0';
  if (bVar1) {
    DAT_ram_20002f7c = '\0';
  }
  return bVar1;
}

