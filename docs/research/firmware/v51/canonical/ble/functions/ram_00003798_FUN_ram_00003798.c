/* Address: ram:00003798; name: FUN_ram_00003798; body bytes: 24 */

bool FUN_ram_00003798(void)

{
  bool bVar1;
  
  gp = &DAT_ram_20002000;
  bVar1 = DAT_ram_20002f7f != '\0';
  if (bVar1) {
    DAT_ram_20002f7f = '\0';
  }
  return bVar1;
}

