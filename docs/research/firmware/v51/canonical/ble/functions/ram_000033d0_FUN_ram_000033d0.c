/* Address: ram:000033d0; name: FUN_ram_000033d0; body bytes: 70 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_000033d0(void)

{
  gp = &DAT_ram_20002000;
  DAT_ram_20002f74 = (*_DAT_ram_00040080)(FUN_ram_0000322a);
  FUN_ram_0000343e();
  FUN_ram_0000354a();
                    /* WARNING: Could not recover jumptable at 0x00003414. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_DAT_ram_00040058)(DAT_ram_20002f74,0x2000,0x2ee00);
  return;
}

