/* Address: ram:000037b0; name: FUN_ram_000037b0; body bytes: 24 */

bool FUN_ram_000037b0(void)

{
  bool bVar1;
  
  gp = &DAT_ram_20002000;
  bVar1 = DAT_ram_20002f7e != '\0';
  if (bVar1) {
    DAT_ram_20002f7e = '\0';
  }
  return bVar1;
}

