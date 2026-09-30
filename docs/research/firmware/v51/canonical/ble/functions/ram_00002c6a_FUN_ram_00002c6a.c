/* Address: ram:00002c6a; name: FUN_ram_00002c6a; body bytes: 114 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_00002c6a(undefined4 param_1)

{
  undefined4 extraout_a4;
  
  gp = &DAT_ram_20002000;
  (*_DAT_ram_00040138)(0xffff,&DAT_ram_20003224);
  (*_DAT_ram_00040138)(0xffff,&DAT_ram_20003014);
  (*_DAT_ram_000400ac)(&LAB_ram_00002c02);
  (*_DAT_ram_00040130)
            (&DAT_ram_20002c40,7,0x10,&PTR_LAB_ram_00002ab6_ram_20002cb0,extraout_a4,
             _DAT_ram_00040130);
  DAT_ram_20002f60 = param_1;
  return;
}

