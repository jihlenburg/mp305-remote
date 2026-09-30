/* Address: ram:0000343e; name: FUN_ram_0000343e; body bytes: 104 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_0000343e(void)

{
  gp = &DAT_ram_20002000;
  DAT_ram_4000102f = DAT_ram_4000102f & 0xfa | 2;
  DAT_ram_40001040 = 0;
  FUN_ram_00003156();
  FUN_ram_00001e18(0x7e4,1,1,0,0,0);
                    /* WARNING: Could not recover jumptable at 0x000034a4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_DAT_ram_00040074)(0);
  return;
}

