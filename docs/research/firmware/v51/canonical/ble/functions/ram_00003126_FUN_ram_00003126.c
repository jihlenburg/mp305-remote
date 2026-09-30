/* Address: ram:00003126; name: FUN_ram_00003126; body bytes: 30 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_00003126(void)

{
  gp = &DAT_ram_20002000;
                    /* WARNING: Could not recover jumptable at 0x00003142. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_DAT_ram_00040130)(0x20002d08,0x13,0x10,0x20002e38);
  return;
}

