/* Address: ram:00004ddc; name: FUN_ram_00004ddc; body bytes: 60 */

void FUN_ram_00004ddc(void)

{
  gp = &DAT_ram_20002000;
  FUN_ram_00002498(0x100,1);
  FUN_ram_00002498(0x200,3);
  FUN_ram_0000289e();
  FUN_ram_000028d0(3);
  FUN_ram_000028ea(1,3);
  DAT_ram_e000e100 = 0x8000000;
  return;
}

