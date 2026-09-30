/* Address: ram:000037e0; name: FUN_ram_000037e0; body bytes: 24 */

bool FUN_ram_000037e0(void)

{
  bool bVar1;
  
  gp = &DAT_ram_20002000;
  bVar1 = DAT_ram_20002f80 != '\0';
  if (bVar1) {
    DAT_ram_20002f80 = '\0';
  }
  return bVar1;
}

