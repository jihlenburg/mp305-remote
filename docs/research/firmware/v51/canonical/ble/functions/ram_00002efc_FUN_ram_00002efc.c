/* Address: ram:00002efc; name: FUN_ram_00002efc; body bytes: 92 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_00002efc(int param_1)

{
  undefined4 extraout_a4;
  
  gp = &DAT_ram_20002000;
  (*_DAT_ram_00040138)(0xffff,&DAT_ram_20003434);
  (*_DAT_ram_000400ac)(&LAB_ram_00002e9e);
  (*_DAT_ram_00040130)
            (&DAT_ram_20002cbc,4,0x10,&PTR_LAB_ram_00002d8c_ram_20002cfc,extraout_a4,
             _DAT_ram_00040130);
  if (param_1 != 0) {
    DAT_ram_20002f64 = param_1;
  }
  return;
}

