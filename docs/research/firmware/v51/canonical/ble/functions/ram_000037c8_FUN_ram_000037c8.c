/* Address: ram:000037c8; name: FUN_ram_000037c8; body bytes: 24 */

bool FUN_ram_000037c8(void)

{
  bool bVar1;
  
  gp = &DAT_ram_20002000;
  bVar1 = DAT_ram_20002f7d != '\0';
  if (bVar1) {
    DAT_ram_20002f7d = '\0';
  }
  return bVar1;
}

