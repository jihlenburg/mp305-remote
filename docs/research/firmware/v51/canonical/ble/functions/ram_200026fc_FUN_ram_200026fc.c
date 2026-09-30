/* Address: ram:200026fc; name: FUN_ram_200026fc; body bytes: 30 */

void FUN_ram_200026fc(void)

{
  gp = &DAT_ram_20002000;
  if ((DAT_ram_40002406 & 1) != 0) {
    DAT_ram_40002406 = 1;
    FUN_ram_00003724();
  }
  return;
}

